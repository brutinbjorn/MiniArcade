#include "CursedArcadePCH.h"
#include "BagLogic.h"
#include "BagState.h"
#include "CellLogic.h"
#include "NobbinLogic.h"
#include "OverlapComp.h"
#include "PlayerDiggerLogic.h"

namespace MiniLord
{
	class OverlapComp;
}

using namespace MiniLord;

BagLogic::BagLogic(Grid* grid, glm::ivec2 gridPos, glm::fvec2 sizeOfCell, RenderComponent* bag, RenderComponent* gold,
	float fallSpeed): m_pGrid(grid), m_sizeOfObjects(sizeOfCell), m_positionOnGrid(gridPos),
	m_BagSprite(bag), m_GoldSprite(gold), m_speed(fallSpeed)
{
}

BagLogic::~BagLogic()
{
	delete m_state;
	//m_subject.Notify(ObserverMessage::Msg_bag_Destroyed);
}


void BagLogic::Initialize()
{
	m_state = new BurriedState();
	m_state->OnEnter(GetGameObject());
	m_subject.Notify(ObserverMessage::Msg_Bag_Added, nullptr, 0);
}

void BagLogic::Update(const float)
{

	if(m_state)
	{
		auto nextState = m_state->Update(GetGameObject());
		if(nextState != nullptr)
		{
			delete m_state;
			m_state = nextState;
			m_state->OnEnter(GetGameObject());
		}

		
	}
}

void BagLogic::SwapToGoldSprite(bool useGoldSprite)
{
	m_BagSprite->SetVisible(!useGoldSprite);
	m_GoldSprite->SetVisible(useGoldSprite);
	m_isGoldNow = useGoldSprite;
}

void BagLogic::OverlapEventBegin(GameObject* other)
{
	if(m_IsFalling && !m_isGoldNow)
	{
		if(auto isPlayer = other->GetComponent<PlayerDiggerLogic>())
		{
			isPlayer->GotHit();
		}

		if(auto enemy = other->GetComponent<NobbinLogic>())
		{
			enemy->GotHit();
		}
	}

	if(m_isGoldNow)
	{
		if (auto isPlayer = other->GetComponent<PlayerDiggerLogic>())
		{
			int score = 500;
			m_subject.Notify(ObserverMessage::Msg_Bag_Collected, &score, sizeof(int));
		}

		if (auto enemy = other->GetComponent<NobbinLogic>())
		{
			m_subject.Notify(ObserverMessage::Msg_bag_Destroyed);
		}

		auto comp = GetGameObject()->GetComponent<OverlapComp>();
		comp->SetIsOverlapper(false);
		comp->SetIsCollider(false);

		GetGameObject()->SetMarkForDeletion();
	}
}

bool BagLogic::ColliderEventBegin(GameObject* otherObject, glm::fvec2 otherMovement)
{
	if(m_IsInmovable)
		return m_IsInmovable;

	
	if(otherObject->GetComponent<PlayerDiggerLogic>())
	{
		auto pos = GetGameObject()->GetTransform().GetWorldPosition();

		if(auto cell = m_pGrid->GetCellAtPosition({ pos.x + otherMovement.x, pos.y + otherMovement.y }))
		{
			if(auto cellLog = cell->GetComponent<CellLogic>())
				if(cellLog->IsDiggedOut())
					GetGameObject()->GetTransform().Translate(otherMovement.x, otherMovement.y, 0);
				else return true;
			
		}
		

	}
	
	return false;
}
