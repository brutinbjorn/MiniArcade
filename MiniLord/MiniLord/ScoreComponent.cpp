#include "MiniLordPCH.h"
#include "ScoreComponent.h"




MiniLord::ScoreComponent::ScoreComponent(MiniLord::TextComponent* text, const std::string& scoreText)
	:m_scoretext(scoreText)
	,nm_pTextComp(text)
	,m_needsUpdate(true)
	
{
}

void MiniLord::ScoreComponent::Initialize()
{

}

void MiniLord::ScoreComponent::Update(const float)
{
	if (m_needsUpdate && nm_pTextComp)
	{
		nm_pTextComp->SetText(m_scoretext + std::to_string(m_score));
		m_needsUpdate = false;

#ifdef STEAMWORKS
		//TODO DIT IS SLECHT, TRIGGERED MEERDERE KEREN EN ZEND PINGS NAAR STEAM.
		if(m_score <= 500)
		{
			if (g_SteamAchievements)
				g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
		}
#endif
	}
	  
}

void MiniLord::ScoreComponent::OnNotify(ObserverMessage msg, void* argPointer, int ArgLength)
{
	if(msg == ObserverMessage::Msg_SCORE_CHANGED && ArgLength == sizeof(int) && argPointer != nullptr)
	{
		m_score = *static_cast<int*>(argPointer);
		m_needsUpdate = true;
	}
}

void MiniLord::ScoreComponent::OnNotifyDestruction(ObserverMessage , void* , int )
{

}
