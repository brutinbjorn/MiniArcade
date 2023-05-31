#pragma once
#include "CursedArcadePCH.h"
#include "ObjectConstructorCursedArc.h"

#include "GameObject.h"
#include "Grid.h"

using namespace MiniLord;
void ObjectConstructorCursedArc::GameGridDigger(std::shared_ptr<GameObject>& newObj,const std::string& currentScene, int collums,
	int rows, const glm::fvec2& TotalGridSize)
{

	auto gridComp = new Grid(currentScene, collums, rows, TotalGridSize);
	newObj->AddComponent(gridComp);
}
