#pragma once
#include "Scene.h"
namespace SceneFactoryCursedArc
{
	std::shared_ptr<MiniLord::Scene> GameMenu();

	std::shared_ptr<MiniLord::Scene> Digger(int gameMode = 0);


}
