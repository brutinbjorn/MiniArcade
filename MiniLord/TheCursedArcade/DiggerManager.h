#pragma once
#include <BaseComponent.h>
#include <Observer.h>

#include "Grid.h"
#include "Scene.h"

namespace MiniLord
{
	class DiggerManager : public BaseComponent, public Interface::Observer
	{
	public:
		DiggerManager(GameObject* ScoreObject,GameObject* livesObj,Scene* sceneToControl,Grid* gridToControl,const glm::fvec2& sizeOfObject, int gameMode);
		~DiggerManager() override = default;
		DiggerManager(const DiggerManager& other) = delete;
		DiggerManager(DiggerManager&& other) noexcept = delete;
		DiggerManager& operator=(const DiggerManager& other) = delete;
		DiggerManager& operator=(DiggerManager&& other) noexcept = delete;

		void OnNotify(ObserverMessage msg, void* argPointer, int ArgLength) override;
		void OnNotifyDestruction(ObserverMessage msg, void* argPointer, int argLength) override;
		
		void SetPlayerRespawn(glm::fvec2 Startpos) { m_playerRespawnSpot = Startpos; };
		void SetPlayer(GameObject* player) { m_Player = player; };
		void SetPlayerTwo(GameObject* playerTwo) { m_playerTwo = playerTwo; }
		void SetPlayerTwoRespawn(glm::fvec2 startpos) { m_playerTwoRespawnSpot = startpos; }

		void LoadNextLevel();
		
	private:


		void Initialize() override{};
		void FixedUpdate(const float) override{};
		void Update(const float) override ;
		void LateUpdate(const float) override{};
		void Render() const override{};
		void ResetLevel();
		void RespawnEnemyPlayer();

		int m_currentGameMode = 0;

		int m_Currentscore = 0;
		int m_lives = 3;
		int m_GemsInARow = 0;

		int m_BagsInScene = 0;
		int m_GemsInScene = 0;

		//nobbins
		int m_maxNobbins = 4;
		int m_nobbinsSpawned = 0;
		int m_nobbinsMIA = 0;

		float m_SpawnTime = 8.f;
		float m_SpawnTimeDelta = m_SpawnTime;
		glm::fvec2 m_EnemySpawnSpot = {};
		std::vector<GameObject*> m_spawnedNobbins;


		bool m_ShouldLoadNextLevel = false;

		Scene* m_currentScene = nullptr;
		Grid* m_grid = nullptr;



		int m_currentLevel = -1; 
		const std::vector<std::string> m_levelnames = { "Level01","Level02", "Level03" };

		glm::fvec2 m_playerRespawnSpot {};
		GameObject* m_Player = nullptr;
		glm::fvec2 m_playerTwoRespawnSpot{};
		GameObject* m_playerTwo = nullptr;

		glm::fvec2 m_sizeOfObject{};

		GameObject* m_ScoreObject = nullptr;
		GameObject* m_LivesObject = nullptr;
	};


}


