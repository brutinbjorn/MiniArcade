#include "CursedArcadePCH.h"
#include "BagState.h"

#include <random>

#include "ActorComponent.h"
#include "BagLogic.h"
#include "CellLogic.h"
#include "RenderComponent.h"
#include "TimeManager.h"
#include "OverlapComp.h"
#include "OverlapManager.h"


using namespace MiniLord;

BagState* BurriedState::Update(GameObject* obj)
{
	auto bag = obj->GetComponent<BagLogic>();
	glm::ivec2 startpos = bag->GetPositionOnGrid();
	auto cellUnder = bag->GetGrid()->GetCellFromArray(startpos.y+1,startpos.x);

	if(cellUnder)
	if(auto val = cellUnder->GetComponent<CellLogic>())
	{
		if (val->IsDiggedOut())
		{
			return new ComprimisedState(2);
		}
	};
	return nullptr;
}


void ComprimisedState::OnEnter(GameObject* obj)
{
	if(auto render = obj->GetComponent<RenderComponent>())
	{
		m_originalOffset = render->GetOffset();
	}
}

BagState* ComprimisedState::Update(GameObject* obj)
{
	auto dt = TimeManager::GetInstance().GetDeltaTime();
	m_offsetTime -= dt;
	m_timer -= dt;
	if(m_offsetTime <= 0)
	{
		m_offsetTime = m_DoRandomOffsetAt;
		if(auto render = obj->GetComponent<RenderComponent>())
		{
			auto randomposX  = std::rand() % 4 + 1;
			auto randomposy = std::rand() % 4 + 1;

			render->SetOffset(m_originalOffset.x + randomposX,
				m_originalOffset.y + randomposy);
		}
	}
	if(m_timer <= 0)
	{
		if (auto render = obj->GetComponent<RenderComponent>())
			render->SetOffset(m_originalOffset.x,m_originalOffset.y);

		return new FallingState();
	}
	return nullptr;

}


void FallingState::OnEnter(GameObject* obj)
{
	if(auto bag = obj->GetComponent<BagLogic>())
	{
		bag->SetIsFalling(true);
		bag->SetIsInmovable(true);

		if (auto currentCell = bag->GetGrid()->GetCellAtPosition(obj->GetTransform().GetWorldPosition())->GetComponent<CellLogic>())
		{
			m_lastPos = currentCell->GetWidthDepth();
			if (auto grid = bag->GetGrid())
			{
				if (auto cell = grid->GetCellAtPosition(obj->GetTransform().GetWorldPosition()))
				{
					auto getPos = cell->GetTransform().GetWorldPosition();
					obj->GetTransform().SetPosition(getPos);
				}
			}

		}
		else
		{
			std::cout << "help" << std::endl;
		}
	}
}

BagState* FallingState::Update(GameObject* obj)
{
	if(auto bag = obj->GetComponent<BagLogic>())
	{
		auto pos = obj->GetTransform().GetLocalPosition(); // Get position

		auto grid = bag->GetGrid();
		if(!grid)
			throw std::runtime_error("falling state: Grid was not found");

		auto* CellObj = grid->GetCellAtPosition({pos.x,pos.y}); // get the current cell the Bag is over.

		if(CellObj == nullptr)
		{
			return nullptr;
			//throw std::runtime_error("falling state: no cell was found");
		}
			
		// the current cell the bag is over
		if(auto cellLogic = CellObj->GetComponent<CellLogic>()) 
		{

			auto width = cellLogic->GetWidthIndex();
			auto otherY = cellLogic->GetDepthIndex();

			if(m_lastPos.x != width || otherY != m_lastPos.y)// if cell is not the same, add to count and update.
			{
				m_CellsPassed++; 
				m_lastPos = cellLogic->GetWidthDepth();
				bag->SetPositionOnGrid({ m_lastPos.y,m_lastPos.x }); //set new width/depth

				//check if what next cell is.
				if(auto nextCell= grid->GetCellFromArray(m_lastPos.y + 1, m_lastPos.x))
				{
					if(auto nextCellLogic = nextCell->GetComponent<CellLogic>())
					{
						if(m_CellsPassed  <= 1 && !nextCellLogic->IsDiggedOut())
						{
							auto cellcenter = CellObj->GetTransform().GetWorldPosition();
							obj->GetTransform().SetPosition(cellcenter);
							return new RestState();
						}
						if( m_CellsPassed >= 2 && !nextCellLogic->IsDiggedOut())
						{
							return new GoldState();
						}
					}

				}
				else
				{// no next cell found, hit the bottom?

					if (m_CellsPassed >= 2)
					{
						return new GoldState();
					}
					auto cellcenter = CellObj->GetTransform().GetWorldPosition();
					obj->GetTransform().SetPosition(cellcenter);
					return new RestState();
				}
			}
		}

		//else keep falling.
		if(auto comp =obj->GetComponent<ActorComponent>())
		{
			auto velocity = glm::fvec2{ 0,bag->GetSpeed() } ;
			comp->AddVelocity(velocity);
		}

	}
	return nullptr;

}

void RestState::OnEnter(GameObject* obj)
{
	if(auto baglogic = obj->GetComponent<BagLogic>())
	{
		baglogic->SetIsInmovable(false);
		baglogic->SetIsFalling(false);
	};
	
}

BagState* RestState::Update(GameObject* obj)
{
	auto baglogic = obj->GetComponent<BagLogic>();

	if(auto mygrid = baglogic->GetGrid())
	{
		if (auto currentCell = mygrid->GetCellAtPosition(obj->GetTransform().GetWorldPosition()))
		{
			if(auto cellLogic = currentCell->GetComponent<CellLogic>())
			{
				if (auto cellUnder = mygrid->GetCellFromArray(cellLogic->GetDepthIndex() + 1, cellLogic->GetWidthIndex()))
				{
					if (cellUnder->GetComponent<CellLogic>()->IsDiggedOut())
						return new FallingState();
				}
			}
		}

	//	mygrid->GetCellAtPosition()	
	}
	return nullptr;
}

void GoldState::OnEnter(GameObject* obj)
{
	if(auto bag = obj->GetComponent<BagLogic>())
	{
		if(auto grid = bag->GetGrid())
		{
			auto pos = obj->GetTransform().GetWorldPosition();
			auto currentCel = grid->GetCellAtPosition(pos);
			obj->GetTransform().SetPosition(currentCel->GetTransform().GetWorldPosition());
		}

		bag->SetIsFalling(false);
		bag->SetIsInmovable(true);
		bag->SwapToGoldSprite();
		obj->GetComponent<OverlapComp>()->SetIsCollider(false);
	}


}
