#include "CursedArcadePCH.h"
#include "PlayerDiggerLogic.h"

#include "CellLogic.h"
#include "GameObject.h"


using namespace MiniLord;

PlayerDiggerLogic::PlayerDiggerLogic(Grid* grideToInfluence):m_pGrid(grideToInfluence)
{


}

void PlayerDiggerLogic::Update(const float)
{
	//auto pos = m_pGrid.
	auto cellImOn = m_pGrid->GetCellAtPosition(GetGameObject()->GetTransform().GetWorldPosition());

	if(auto val = cellImOn->GetComponent<CellLogic>())
	{
		val->SetDiggedOut(true);
	}


}

void PlayerDiggerLogic::GotHit()
{
	int i = -1;
	m_subject.Notify(ObserverMessage::Msg_PLAYER_LIFE_CHANGED, &i, sizeof(int));
}

void PlayerDiggerLogic::OnCollisionEnter(CollisionComponent* )
{


}
