#include "CursedArcadePCH.h"
#include "NobbinLogic.h"

#include "BagLogic.h"
#include "GameObject.h"
#include "PlayerDiggerLogic.h"
#include <TimeManager.h>

MiniLord::NobbinLogic::NobbinLogic(Grid* theGameGrid, RenderComponent* mainbodsprite, RenderComponent* HobbinSprite,ActorComponent* actor,float speed,bool isPlayerControlled):
m_grid(theGameGrid),m_pNobbinsprite(mainbodsprite),m_pHobbinSprite(HobbinSprite),m_speed(speed),m_pActor(actor),m_isPlayerControlled(isPlayerControlled)
{


}

bool MiniLord::NobbinLogic::ColliderEventBegin(GameObject* otherObject, glm::fvec2)
{
	if(auto wasbag = otherObject->GetComponent<BagLogic>())
	{

		if(wasbag->GetIsFalling())
		{
			std::cout << "Nobbing got hit by bag" << std::endl;
			int val = 250;
			m_subject.Notify(ObserverMessage::Msg_SCORE_CHANGED, &val, sizeof(int));

			GetGameObject()->SetMarkForDeletion();
		}
	}
	return false;

}

void MiniLord::NobbinLogic::OverlapEventBegin(GameObject* OtherObject)
{
	if(auto isbag = OtherObject->GetComponent<BagLogic>())
	{
		if(isbag && isbag->GetIsGold())
		{
			OtherObject->SetMarkForDeletion(true);
			m_AteGold = true;
		}
	}

	if(auto IsPlayer = OtherObject->GetComponent<PlayerDiggerLogic>())
	{
		IsPlayer->GotHit();
	}

}

void MiniLord::NobbinLogic::Update(const float)
{

	//auto dt = TimeManager::GetInstance().GetDeltaTime();

	if(!m_isPlayerControlled)
	{
		glm::fvec2 currentpos;
		currentpos.x = GetGameObject()->GetTransform().GetWorldPosition().x;
		currentpos.y = GetGameObject()->GetTransform().GetWorldPosition().y;

		glm::fvec2 targetpos;
		if (m_TargetCellToReach)
		{
			targetpos.x = m_TargetCellToReach->GetTransform().GetWorldPosition().x;
			targetpos.y = m_TargetCellToReach->GetTransform().GetWorldPosition().y;

			auto dir = glm::normalize(targetpos - currentpos);
			dir = dir * m_speed;
			m_pActor->AddVelocity(dir);
		
		}

		if (!m_TargetCellToReach || m_MinDistanceToTarget > glm::distance(targetpos,currentpos)) // if you dont have a target, or close enough to your current;
		{
			m_formerCell = m_currentCell;

			GameObject* currentCell =  m_grid->GetCellAtPosition(currentpos);
			if (currentCell == nullptr)
			{
				std::cout << "nobbin: out of bounds";
				return;
			}

			auto currentcelllogic = currentCell->GetComponent<CellLogic>();
			if (currentcelllogic ==nullptr){std::cout << "nobbin: found cell but no logic"; return;}
			m_currentCell = currentcelllogic;

			auto neighbours = m_grid->GetNeighboursOfCell(currentcelllogic);
			if (neighbours.size() <= 0){std::cout << "nobbin: no open cells found" << std::endl;return;}


			//check if at least one naighbour is dug out.set defualt go to.
			bool hasPossibleTarget = false;
			int amountofTargets = 0;
			GameObject* target = nullptr;
			for (auto possibleTarget : neighbours)
				if (possibleTarget->GetComponent<CellLogic>()->IsDiggedOut())
				{
					target = possibleTarget;
					hasPossibleTarget = true;
					amountofTargets++;
				}

			if (!hasPossibleTarget){std::cout << "nobbin: no cell around is dig out" << std::endl;return;}

			//m_formerCell = currentcelllogic;
			if (amountofTargets == 1)
			{
				std::cout << "nobbin: only one target" << std::endl;
				m_TargetCellToReach = target;
			}
			else
			{
				CellLogic* targetcell = nullptr;
				do
				{
					//pick a random direction to go
					int pick = static_cast<int>(std::rand() % neighbours.size());

					auto possibleTarget = neighbours[pick];
					targetcell = possibleTarget->GetComponent<CellLogic>();
					if (targetcell->IsDiggedOut() && targetcell != m_formerCell)
						target = possibleTarget;


				}
				while (target==nullptr);


				m_TargetCellToReach = target;

		}

		//if(m_TargetCellToReach)
		//{
		//	
		//	m_lastdirectionGone.x = m_TargetCellToReach->GetComponent<CellLogic>()->GetWidthDepth().x;
		//	m_lastdirectionGone.y = m_TargetCellToReach->GetComponent<CellLogic>()->GetWidthDepth().y;
		//}
	}
	}
	
}

void MiniLord::NobbinLogic::GotHit()
{

	m_subject.Notify(ObserverMessage::Msg_Nobbin_Hit);
	if(m_isPlayerControlled == false)
		GetGameObject()->SetMarkForDeletion();
}
