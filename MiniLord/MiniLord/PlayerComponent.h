#pragma once
#include "ActorComponent.h"
#include "BaseComponent.h"
#include "Subject.h"

namespace MiniLord
{
	class PlayerComponent : public BaseComponent
	{
	public:
		PlayerComponent(ActorComponent* ActorToControl, int lives = 3):m_pActorComp(ActorToControl),m_lives(lives) {};
		~PlayerComponent()override = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		void Initialize() override;
		void FixedUpdate(const float) override {};
		void Update(const float) override {};
		void LateUpdate(const float) override {};
		void Render() const override {};
		void GuiRender() override {};

		//subject
		Subject& GetSubject() { return m_Subject; };

		//health logic
		int GetLives() const { return m_lives; };
		void SetLives(int newLives)
		{
			m_lives = newLives;
			m_Subject.Notify(ObserverMessage::Msg_PLAYER_LIFE_CHANGED,&m_lives,sizeof(m_lives));
		};
		//or heal by applying negative damage;
		void ApplyDamage(int damage)
		{
			m_lives -= damage;
			m_Subject.Notify(ObserverMessage::Msg_PLAYER_LIFE_CHANGED,&m_lives,sizeof(m_lives)); 
		};
		void SetScore(int newScore)
		{
			m_Score = newScore;
			m_Subject.Notify(ObserverMessage::Msg_SCORE_CHANGED, &m_Score, sizeof(m_Score));

		}
		int GetScore() const { return m_Score; };

		void AddScore(int toAdd)
		{
			m_Score += toAdd;
			m_Subject.Notify(ObserverMessage::Msg_SCORE_CHANGED, &m_Score, sizeof(m_Score));
		}

	private:
		ActorComponent* m_pActorComp = nullptr;
		Subject m_Subject;
		int m_lives;
		int m_Score;


	};
}

