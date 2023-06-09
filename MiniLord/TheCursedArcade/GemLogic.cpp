#include "CursedArcadePCH.h"
#include "GemLogic.h"

#include "GameObject.h"
#include "PlayerDiggerLogic.h"

using namespace MiniLord;

void GemLogic::OverlapEventBegin(GameObject* otherCollider)
{

	//if the other is the player
	if(auto val = otherCollider->GetComponent<PlayerDiggerLogic>() != nullptr)
	{
		//add score
		int var = 25;
		m_subject.Notify(ObserverMessage::Msg_SCORE_CHANGED, &var, sizeof(int));
		GetGameObject()->SetMarkForDeletion(true);
	}

}

bool GemLogic::ColliderEventBegin(GameObject*, glm::fvec2 )
{
	return false;
}
