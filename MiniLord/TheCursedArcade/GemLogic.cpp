#include "CursedArcadePCH.h"
#include "GemLogic.h"

#include "GameObject.h"
#include "PlayerDiggerLogic.h"

using namespace MiniLord;

void GemLogic::OverlapEventBegin(GameObject* otherCollider)
{
	if(auto val = otherCollider->GetComponent<PlayerDiggerLogic>() != nullptr)
	{
		int var = 25;
		m_subject.Notify(ObserverMessage::Msg_SCORE_CHANGED, &var, sizeof(int));
		GetGameObject()->SetMarkForDeletion(true);

	}

	

}
