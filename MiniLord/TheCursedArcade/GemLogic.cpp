#include "CursedArcadePCH.h"
#include "GemLogic.h"

#include "GameObject.h"
#include "PlayerDiggerLogic.h"

using namespace MiniLord;

void GemLogic::Initialize()
{
	m_subject.Notify(ObserverMessage::Msg_Gem_Added, nullptr, 0);
}

void GemLogic::OverlapEventBegin(GameObject* otherCollider)
{

	//if the other is the player
	if(auto val = otherCollider->GetComponent<PlayerDiggerLogic>() != nullptr)
	{
		//add score
		int var = 25;
		m_subject.Notify(ObserverMessage::Msg_Gem_Collected, &var, sizeof(int));
		GetGameObject()->SetMarkForDeletion(true);
	}

}

bool GemLogic::ColliderEventBegin(GameObject*, glm::fvec2 )
{
	return false;
}
