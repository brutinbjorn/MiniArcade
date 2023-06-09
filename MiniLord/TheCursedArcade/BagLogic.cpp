#include "CursedArcadePCH.h"
#include "BagLogic.h"
#include "BagState.h"
#include "PlayerDiggerLogic.h"

using namespace MiniLord;

BagLogic::BagLogic(Grid* grid, glm::ivec2 gridPos, glm::fvec2 sizeOfCell, RenderComponent* bag, RenderComponent* gold,
	float fallSpeed): m_pGrid(grid), m_sizeOfObjects(sizeOfCell), m_positionOnGrid(gridPos),
	m_BagSprite(bag), m_GoldSprite(gold), m_speed(fallSpeed)
{
}

BagLogic::~BagLogic()
{
	delete m_state;
}


void BagLogic::Initialize()
{
	m_state = new BurriedState();
	m_state->OnEnter(GetGameObject());
}

void BagLogic::Update(const float)
{
	auto nextState = m_state->Update(GetGameObject());
	if(nextState != nullptr)
	{
		delete m_state;
		m_state = nextState;
		m_state->OnEnter(GetGameObject());
	}

}

void BagLogic::SwapToGoldSprite(bool useGoldSprite)
{
	m_BagSprite->SetVisible(!useGoldSprite);
	m_BagSprite->SetVisible(useGoldSprite);
}

void BagLogic::OverlapEventBegin(GameObject* other)
{
	if(m_IsFalling && !m_isGoldNow)
	{
		if(auto isPlayer = other->GetComponent<PlayerDiggerLogic>())
		{
			isPlayer->GotHit();
		}
	}

	if(m_isGoldNow)
	{
		GetGameObject()->SetMarkForDeletion();
	}
}

bool BagLogic::ColliderEventBegin(GameObject* otherObject, glm::fvec2 otherMovement)
{
	if(m_IsInmovable)
		return m_IsInmovable;

	if( otherObject->GetComponent<PlayerDiggerLogic>())
			GetGameObject()->GetTransform().Translate(otherMovement.x, otherMovement.y, 0);
	
	return false;
}
