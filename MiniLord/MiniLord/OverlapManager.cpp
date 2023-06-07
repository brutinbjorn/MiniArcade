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
		overlap->SetOverlap(false);

	for(auto currentOverlapTocheck: m_overlapComponents)
	{
		if(!currentOverlapTocheck->IsOverlapping())
			for (int i = 0; i < m_overlapComponents.size(); ++i)
			{
				if(m_overlapComponents[i] != currentOverlapTocheck)// not the same one
				{
					SDL_Rect currentRect = currentOverlapTocheck->GetOverlapSquareInWorld();
					SDL_Rect otherRect = m_overlapComponents[i]->GetOverlapSquareInWorld();

					//if(currentOverlapTocheck.g)

					if(CheckOverlapSquares(currentRect,otherRect))
					{
						currentOverlapTocheck->SetOverlap(true);
						currentOverlapTocheck->OnOverlapEvent(m_overlapComponents[i]);
						m_overlapComponents[i]->SetOverlap(true);
						m_overlapComponents[i]->OnOverlapEvent(currentOverlapTocheck);

						
						std::cout << "overlap between cube 1 at: " << currentRect.x << ":" << currentRect.y << "size of: " << currentRect.w <<":" << currentRect.h << std::endl;
						std::cout << "overlap between cube 2 at: " << otherRect.x << ":" << otherRect.y << "size of: " << otherRect.w << ":" << otherRect.h << std::endl;
					}

					
				}
			}
	}

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

