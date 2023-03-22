#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace MiniLord
{
	class ScoreComponent :
	    public BaseComponent
	{
	public:
		ScoreComponent(MiniLord::TextComponent* text);
		~ScoreComponent() override = default;

		void Update(const float) override;
		void Render() const override;
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

	private:
		TextComponent* nm_pTextComp;
		bool m_needsUpdate; //dirty flag.
		int m_score;
	};
}

