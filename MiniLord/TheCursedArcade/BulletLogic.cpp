#include "CursedArcadePCH.h"
#include "BulletLogic.h"

#include "NobbinLogic.h"
#include "GameObject.h"
#include "Grid.h"

MiniLord::BulletLogic::BulletLogic(glm::fvec2 dir, Grid* grid):
m_pActor(nullptr),m_directionAndSpeed(dir),m_pGrid(grid)
{
}

void MiniLord::BulletLogic::OverlapEventBegin(GameObject* OtherObject)
{
	if(auto nobbin = OtherObject->GetComponent<NobbinLogic>())
	{
		nobbin->GotHit();
		GetGameObject()->SetMarkForDeletion();
	}
}

void MiniLord::BulletLogic::Initialize()
{
	m_pActor = GetGameObject()->GetComponent<ActorComponent>();
	if (m_pActor == nullptr)
		std::cout << "bullet: no actor found" << std::endl;
}

void MiniLord::BulletLogic::Update(const float)
{
	m_pActor->OverWriteVelocity(m_directionAndSpeed);

	auto pos = GetGameObject()->GetTransform().GetWorldPosition();
	if (auto cell = m_pGrid->GetCellAtPosition(glm::fvec2{ pos.x,pos.y }))
	{
		if(!cell->GetComponent<CellLogic>()->IsDiggedOut())
		{
			GetGameObject()->SetMarkForDeletion();
		}
	}else
	{
		GetGameObject()->SetMarkForDeletion();
	}
	
}
