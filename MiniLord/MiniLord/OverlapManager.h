#pragma once
#include "Singleton.h"


namespace MiniLord
{
	class OverlapComp;

	class OverlapManager : public Singleton<OverlapManager>
	{
	public:
		void RegisterOverlapComp(OverlapComp*);
		void RemoveOverlapComp(OverlapComp* toRemove);

		void CheckForOverlaps();

	private:
		friend class Singleton<OverlapManager>;
		OverlapManager() = default;
		bool CheckOverlapSquares(SDL_Rect left, SDL_Rect right);


		std::vector<OverlapComp*> m_overlapComponents;
	};
	
}

