#pragma once
#include "Command.h"
#include "Grid.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "CellLogic.h"
#include "OverlapComp.h"
#include "OverlapManager.h"
#include "PlayerDiggerLogic.h"
#include "SceneFactoryCursedArc.h"
#include "NobbinLogic.h"
namespace MiniLord
{
	class SwitchSceneCommand: public Command
	{
	public:
		SwitchSceneCommand(Scene* SceneToLoad,Scene* sceneToClose)
			:m_pSceneToLoad(SceneToLoad),m_pSceneToClose(sceneToClose)
		{
			m_sceneToCloseName = m_pSceneToClose->GetName();
			m_sceneToLoadName = m_pSceneToLoad->GetName();

			if ((!m_pSceneToLoad || !m_pSceneToClose) && (m_sceneToCloseName != "" && m_sceneToLoadName != ""))
				throw std::invalid_argument("switch scene constructor invalid args");

		};
		SwitchSceneCommand(const std::string& sceneToLoadName, const std::string& sceneToCloseName)
			:m_sceneToLoadName(sceneToLoadName),m_sceneToCloseName(sceneToCloseName)
		{
			m_pSceneToLoad = SceneManager::GetInstance().GetScene(m_sceneToLoadName);
			m_pSceneToClose = SceneManager::GetInstance().GetScene(m_sceneToCloseName);
			if (!m_pSceneToLoad || !m_pSceneToClose)
				throw std::invalid_argument("switch scene constructor invalid args");
		}


		void Execute() override
		{
			m_pSceneToClose->SetActive(false);
			m_pSceneToLoad->SetActive();
		};
	private:
		Scene* m_pSceneToLoad = nullptr;
		Scene* m_pSceneToClose = nullptr;
		std::string m_sceneToLoadName = "";
		std::string m_sceneToCloseName = "";
	};


	class LoadDiggerScene : public Command
	{
	public:
		LoadDiggerScene(int gameMode,Scene* menuToClose):m_Gamemode(gameMode),m_Menu(menuToClose){}

		void Execute() override
		{
			if(m_Menu)
				m_Menu->SetActive(false);
			SceneManager::GetInstance().AddScene(SceneFactoryCursedArc::Digger(m_Gamemode));
		}
	private:
		Scene* m_Menu=nullptr;
		int m_Gamemode = 0;

	};





	class PlaySoundEffect : public Command
	{
	public:
		PlaySoundEffect(int EffectID) :m_EffectID(EffectID) {};

		void Execute() override
		{
			ServiceLocator::GetSoundSystem().PlaySoundEffect(m_EffectID,0.5f);
		}
	private:
		int m_EffectID;
	};

	class PrintDebugMessage : public Command
	{
	public:
		PrintDebugMessage(const std::string& msg) : msg(msg) {};

		void Execute() override
		{
			std::cout << msg << std::endl;
		}
	private:
		std::string msg;
	};

	class BasicMoveCommand : public Command
	{
	public:
		BasicMoveCommand(ActorComponent* actor,glm::fvec2 directionAndSpeed) :m_ActorToMove(actor), m_DirectionAndSpeed(directionAndSpeed){};

		void Execute() override
		{
			m_ActorToMove->AddVelocity(m_DirectionAndSpeed);
		};
	private:
		ActorComponent* m_ActorToMove;
		glm::fvec2 m_DirectionAndSpeed;
	};

	class DiggerFireBullet : public Command
	{
	public:
		DiggerFireBullet(PlayerDiggerLogic* player) : m_player(player){}

		void Execute() override { m_player->FireProjectile(); };
	private:
		PlayerDiggerLogic* m_player;

	};


	class GridLockedMoveCommand : public Command
	{
	public:
		GridLockedMoveCommand(GameObject* objectToMove, const glm::fvec2& directionAndSpeed, Grid* grid, float PaddingForAxisSwitch) :
			m_pGrid(grid), m_GameObjectToMove(objectToMove), m_DirectionAndSpeed(directionAndSpeed), m_PaddingForAxesSwitch(PaddingForAxisSwitch)
		{};

		void Execute() override
		{
			auto position = m_GameObjectToMove->GetTransform().GetWorldPosition();
			auto cell = m_pGrid->GetCellAtPosition(glm::fvec2{position.x,position.y});


			if(cell != nullptr)
			{
				CellLogic* cellLogic = cell->GetComponent<CellLogic>();
				auto var = cellLogic->GetDirections();
				auto Cellpos = cell->GetTransform().GetWorldPosition();

				auto& currentTransform = m_GameObjectToMove->GetTransform();
				auto oldPos = currentTransform.GetLocalPosition();

				auto* actorComp = m_GameObjectToMove->GetComponent<ActorComponent>();
				if (actorComp == nullptr)
					std::cout << "no actor comp in ojbect to move" << std::endl;

				if (auto plLogic = m_GameObjectToMove->GetComponent<PlayerDiggerLogic>())
					plLogic->SavePlayerDirection(m_DirectionAndSpeed);

				if(auto NobbingPLayer = m_GameObjectToMove->GetComponent<NobbinLogic>())
				{
					auto dt = TimeManager::GetInstance().GetDeltaTime();
					auto futureCell = m_pGrid->GetCellAtPosition(glm::fvec2{ position.x + m_DirectionAndSpeed.x * dt,position.y *m_DirectionAndSpeed.y });
					if( auto futureLogic = futureCell->GetComponent<CellLogic>())
					{
						if (!futureLogic->IsDiggedOut())
							return;
					}
				}

				if (cellLogic->GetHorizontalLane()->IsPointOverlapping(currentTransform.GetWorldPosition()))
				{
					if ((var & Cell_Up || Cellpos.y <= oldPos.y) && m_DirectionAndSpeed.y < 0)
					{
						currentTransform.SetPosition(Cellpos.x, oldPos.y, oldPos.z); // align
						//currentTransform.Translate(0, m_DirectionAndSpeed.y * dt,0);
						glm::fvec2 dir{ 0,m_DirectionAndSpeed.y };
						actorComp->AddVelocity(dir);

					}

					if ((var & Cell_Down || Cellpos.y >= oldPos.y) && m_DirectionAndSpeed.y > 0)
					{
						currentTransform.SetPosition(Cellpos.x, oldPos.y, oldPos.z); // align
						glm::fvec2 dir{ 0,m_DirectionAndSpeed.y };
						actorComp->AddVelocity(dir);
					}
				}

				if (cellLogic->GetVerticalLane()->IsPointOverlapping(currentTransform.GetWorldPosition()))
				{
					if ((var & Cell_Right || Cellpos.x >= oldPos.x) && m_DirectionAndSpeed.x > 0)
					{
						currentTransform.SetPosition(oldPos.x, Cellpos.y, oldPos.z); // align
						//currentTransform.Translate(m_DirectionAndSpeed.x * dt, 0,0);
						glm::fvec2 dir{ m_DirectionAndSpeed.x ,0};
						actorComp->AddVelocity(dir);
					}

					if ((var & Cell_Left || Cellpos.x <= oldPos.x) && m_DirectionAndSpeed.x < 0)
					{
						currentTransform.SetPosition(oldPos.x, Cellpos.y, oldPos.z); // align
						//currentTransform.Translate(m_DirectionAndSpeed.x * dt, 0,0);
						glm::fvec2 dir{ m_DirectionAndSpeed.x ,0 };
						actorComp->AddVelocity(dir);
					}
				}
			}
			else
			{
				std::cout <<"no cell found" << std::endl;
			}

		}

	private:
		Grid* m_pGrid;
		//ActorComponent* m_pActorComp;
		GameObject* m_GameObjectToMove;
		glm::fvec2 m_DirectionAndSpeed;
		float m_PaddingForAxesSwitch;

	};

}

