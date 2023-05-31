#pragma once
#include "ActorComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "SquareComponent.h"
#include "TimeManager.h"


//werken basicly zoals functors.
namespace MiniLord
{
	
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class SwapSceneCommand final : public Command
	{
	public:
		SwapSceneCommand(const std::string& Scene):m_SceneName(Scene){};
	private:
		std::string m_SceneName = {};

	};

	class SwapSquareColor final : public Command
	{
	public:
		SwapSquareColor(SquareComponent* square, const SDL_Color& colorToSwapTo):
		m_pSquare(square),m_ColorOn(colorToSwapTo),m_ColorOff (square->GetColor()){};

		SwapSquareColor(SquareComponent* square, const SDL_Color& colorWhenOff,const SDL_Color& colorWhenOn):
		m_pSquare(square), m_ColorOn(colorWhenOn), m_ColorOff(colorWhenOff){};

	private:
		SquareComponent* m_pSquare = nullptr;
		SDL_Color m_ColorOn = {};
		SDL_Color m_ColorOff = {};
	};

	class MoveGameObjectCommand final : public Command
	{
	public:
		MoveGameObjectCommand(MiniLord::GameObject* objToMove, const glm::fvec2& dir) :
		m_pObjToMove(objToMove),TimeRef(TimeManager::GetInstance()),m_DirToMove(dir){};
		void Execute() override
		{
			auto time = TimeRef.GetDeltaTime();
			m_pObjToMove->GetTransform().Translate(m_DirToMove.x * time,m_DirToMove.y * time,0);
		};
	private:
		MiniLord::GameObject* m_pObjToMove = nullptr;
		glm::fvec2 m_DirToMove {};
		TimeManager& TimeRef;

	};

	class MoveActorCommand final : public Command
	{
	public:
		MoveActorCommand(ActorComponent* Actor,const glm::fvec2& m_DirectionAndSpeed)
		: m_pActor(Actor),m_Direction(m_DirectionAndSpeed) {};

		void Execute() override
		{
			m_pActor->AddVelocity(m_Direction);
		}
	private:
		
		ActorComponent* m_pActor = nullptr;
		glm::fvec2 m_Direction = {};

	};

	class ShootTest final : public Command
	{
		
	};

	class LoseLifeCommand : public Command
	{
	public:
		LoseLifeCommand(PlayerComponent* player):m_Player(player)
		{};

		void Execute() override
		{
			std::cout << "apply damage" << std::endl;
			m_Player->ApplyDamage(1);
		};
	private:
		PlayerComponent* m_Player = nullptr;
	};

	class AddPointsCommand : public Command
	{
	public:
		AddPointsCommand(PlayerComponent* player) :m_Player(player) {};

		void Execute() override
		{
			std::cout << "score schould update" << std::endl;
			m_Player->AddScore(50);
		};
	private:
		PlayerComponent* m_Player = nullptr;
	};

	class TestPrintCommand : public Command
	{
	public:
		TestPrintCommand(const std::string& text) : m_textToPrint(text) {};

		void Execute() override
		{
			std::cout << m_textToPrint << std::endl;
		};
	private:
		std::string m_textToPrint ;
	};

}