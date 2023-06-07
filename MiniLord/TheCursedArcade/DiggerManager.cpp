#include "CursedArcadePCH.h"
#include "DiggerManager.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "LivesDisplayComp.h"

//MiniLord::DiggerManager::DiggerManager(GameObject* ScoreObject,GameObject* LiveBar)
//	:m_ScoreObject(ScoreObject),m_LivesObject(LiveBar)
//{
//}

MiniLord::DiggerManager::DiggerManager(GameObject* ScoreObject) :m_ScoreObject(ScoreObject)
{
}

void MiniLord::DiggerManager::OnNotify(ObserverMessage msg, void* argPointer, int ArgLength)
{
	int val;
	switch (msg)
	{
	case ObserverMessage::Msg_SCORE_CHANGED: 
		m_Currentscore += *static_cast<int*>(argPointer);;
		val = *static_cast<int*>(argPointer);
		if (val == 25)
		{
			m_GemsInARow++;
			if (m_GemsInARow >= 6){
				m_GemsInARow = 0;
				m_Currentscore += 250;
			}
		}
		if(m_ScoreObject)
		{
			auto scoreComp = m_ScoreObject->GetComponent<TextComponent>();
			if (scoreComp)
				scoreComp->SetText("Score: " + m_Currentscore);
			else
				std::cout << "No score comp found by manager" << std::endl;
		}
		else
		{
			std::cout << "No score Object" << std::endl;
		}
		break;

	case ObserverMessage::Msg_PLAYER_LIFE_CHANGED:
		val = *static_cast<int*>(argPointer);
		if(m_LivesObject)
		{
			m_lives += val;
			auto LivesDisplay = m_LivesObject->GetComponent<LivesDisplayComp>();
			if(LivesDisplay)
			{
				LivesDisplay->OnNotify(msg, argPointer, ArgLength);
			}
			else
			{
				std::cout << "no lives component found" << std::endl;
			}
		}
		else
			break;
		
	}



}

void MiniLord::DiggerManager::OnNotifyDestruction(ObserverMessage , void* , int )
{
}

