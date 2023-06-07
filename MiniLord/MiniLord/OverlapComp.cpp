#include "MiniLordPCH.h"
#include "OverlapComp.h"

#include "GameObject.h"
#include "OverlapManager.h"
#include "OverLapEvent.h"

MiniLord::OverlapComp::OverlapComp(SDL_Rect sizeOfBox):m_Overlap(sizeOfBox)
{
	OverlapManager::GetInstance().RegisterOverlapComp(this);
}

MiniLord::OverlapComp::~OverlapComp()
{
	OverlapManager::GetInstance().RemoveOverlapComp(this);
}

void MiniLord::OverlapComp::OnOverlapEvent(OverlapComp* other)
{
	m_IsOverLapping = true;
	other->m_IsOverLapping = true;

	for(auto comp : other->GetGameObject()->GetComponents())
	{
		if(auto event = dynamic_cast<Interface::OverlapEvent*>(comp))
		{
			event->OverlapEventBegin(GetGameObject());
		}
	}
}

SDL_Rect MiniLord::OverlapComp::GetOverlapSquareInWorld() const
{

	auto worldpos =GetGameObject()->GetTransform().GetWorldPosition();
	SDL_Rect worldSquare = m_Overlap;
	worldSquare.x += static_cast<int>(worldpos.x);
	worldSquare.y += static_cast<int>(worldpos.y);
	return worldSquare;


}


