 // TheCursedArcade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CursedArcadePCH.h"

#include "CursedEngine.h"

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

//using the same namespace as the engine to prevent headaches.
//namespace MiniLord
	int main(int, char* [])
	{
		MiniLord::CursedEngine engine{};
		engine.run();
		//engine.Cleanup();


		return 0;
	}
//}
