#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Observer.h"

namespace MiniLord
{
	class ScoreComponent :
		public BaseComponent, public Interface::Observer
	{
	public:
		ScoreComponent(MiniLord::TextComponent* text, const std::string& scoreText = "score: ");
		~ScoreComponent() override = default;


		void Initialize() override;
		void Update(const float) override;
		void FixedUpdate(const float) override {};
		void LateUpdate(const float) override {};
		void Render() const override {};
		void GuiRender() override {};
		
		void AddScore(int score)
		{
			
			m_score += score;
			m_needsUpdate = true;
		}
		void SetScore(int newScore)
		{
			m_score = newScore;
			m_needsUpdate = true;
		}
		int GetScore()
		{
			
			return m_score;
		}


		//bool Recieve(BaseComponent*, const std::string&) override;
		void OnNotify(ObserverMessage msg, void* argPointer, int ArgLength) override;
		void OnNotifyDestruction(ObserverMessage msg, void* argPointer, int argLength) override;

	private:
		std::string m_scoretext = "";
		bool m_AchievementTriggered = false;
		TextComponent* nm_pTextComp = nullptr;
		bool m_needsUpdate = false; //dirty flag.
		int m_score = 0;
	};
}

