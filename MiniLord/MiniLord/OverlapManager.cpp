#include "MiniLordPCH.h"
#include "OverlapManager.h"

#include "OverlapComp.h"


void MiniLord::OverlapManager::RegisterOverlapComp(OverlapComp* addComp)
{
	m_overlapComponents.push_back(addComp);
}

void MiniLord::OverlapManager::RemoveOverlapComp(OverlapComp* toRemove)
{
	m_overlapComponents.erase(std::remove(m_overlapComponents.begin(), m_overlapComponents.end(), toRemove), m_overlapComponents.end());
}

void MiniLord::OverlapManager::CheckForOverlaps()
{
	for (auto overlap : m_overlapComponents)
		overlap->SetOverlapState(false);

	for(auto currentOverlapTocheck: m_overlapComponents)
	{
		if(!currentOverlapTocheck->GetOverlapState() && currentOverlapTocheck->GetIsOverlapper())
			for (int i = 0; i < m_overlapComponents.size(); ++i)
			{

				auto otherOverLap = m_overlapComponents[i];
				if(otherOverLap != currentOverlapTocheck && otherOverLap->GetIsOverlapper())// not the same one
				{
					SDL_Rect currentRect = currentOverlapTocheck->GetOverlapSquareInWorld();
					SDL_Rect otherRect = m_overlapComponents[i]->GetOverlapSquareInWorld();

					//if(currentOverlapTocheck.g)

					if(CheckOverlapSquares(currentRect,otherRect))
					{
						currentOverlapTocheck->SetOverlapState(true);
						currentOverlapTocheck->OnOverlapEvent(m_overlapComponents[i]);
						m_overlapComponents[i]->SetOverlapState(true);
						m_overlapComponents[i]->OnOverlapEvent(currentOverlapTocheck);

						
						std::cout << "overlap between cube 1 at: " << currentRect.x << ":" << currentRect.y << "size of: " << currentRect.w <<":" << currentRect.h << std::endl;
						std::cout << "overlap between cube 2 at: " << otherRect.x << ":" << otherRect.y << "size of: " << otherRect.w << ":" << otherRect.h << std::endl;
					}
				}
			}
	}

}

bool MiniLord::OverlapManager::CheckIfOverLapIsGonneHappen(OverlapComp* collider, glm::fvec2 directionAndSpeed)
{
	if (!collider->GetIsCollider())
		return false;

	for (int i = 0; i < m_overlapComponents.size(); ++i)
	{
		auto other = m_overlapComponents[i];
		if(other->GetIsCollider() && other != collider)
		{
			auto movingSqr = collider->GetOverlapSquareInWorld();
			movingSqr.x += static_cast<int>(directionAndSpeed.x);
			movingSqr.y += static_cast<int>(directionAndSpeed.y);

			if (CheckOverlapSquares(movingSqr, other->GetOverlapSquareInWorld()))
			{

				return true;

			}
		}
	}
	return false;
}

bool MiniLord::OverlapManager::CheckOverlapSquares(SDL_Rect left, SDL_Rect right)
{
	if((left.x >= right.x && left.x <= right.x + right.w) // check the left side
		|| (left.x + left.w >= right.x && left.x + left.w <= right.x + right.w)) // check the right side
	{
		if((left.y >= right.y && left.y <= right.y + right.h)|| //check the top side
			(left.y + left.h >= right.y && left.y + left.w <= right.y + right.h)) // check the bottom side
		{
			return true;
		}
	}
	return false;
}

