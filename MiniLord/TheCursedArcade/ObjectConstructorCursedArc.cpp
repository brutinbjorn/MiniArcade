#pragma once
#include "CursedArcadePCH.h"
#include "ObjectConstructorCursedArc.h"

#include "GameObject.h"
#include "Grid.h"
#include "RenderComponent.h"
#include "GemLogic.h"
#include "OverlapComp.h"
#include "BagLogic.h"

using namespace MiniLord;
//void ObjectConstructorCursedArc::GameGridDigger(std::shared_ptr<GameObject>& newObj,const std::string& currentScene, int collums,
//	int rows, const glm::fvec2& TotalGridSize)
//{
//
//	auto gridComp = new Grid(currentScene, collums, rows, TotalGridSize);
//	newObj->AddComponent(gridComp);
//
//
//
//}

void ObjectConstructorCursedArc::GameGridDigger(std::shared_ptr<GameObject>& newObj, const std::string& jsonFile)
{
	auto GridComp = new Grid(jsonFile);
	newObj->AddComponent(GridComp);
	//auto val = GridComp->CreateCellsAndLanesFromJSONFile(sizeOfCells);
	//for (int index =0; index < val.size(); index++)
	//currentScene->AddGameObject(val[index]);

}

void ObjectConstructorCursedArc::DiggerScoreComponent(std::shared_ptr<GameObject> newObj)
{
	//auto playerOneHealthBar = new LivesDisplayComp("Common/HeartSymbol.png", PlayerComp->GetLives());
	//UI->AddComponent(playerOneHealthBar);
	//PlayerComp->GetSubject().AddObserver(playerOneHealthBar);

}

void ObjectConstructorCursedArc::DiggerGem(std::shared_ptr<GameObject>& newObj)
{
	//rendering
	auto RenderSprite = new RenderComponent();
	RenderSprite->SetTexture("Digger/Gem.png");
	RenderSprite->SetSize(32,32 );
	RenderSprite->SetOffset(-16, -16);
	newObj->AddComponent(RenderSprite);

	auto overlap = new OverlapComp(SDL_Rect(-16 + 4,-16 + 4,32 - 8,32 - 8));
	newObj->AddComponent(overlap);
	//auto collision = new CollisionComponent(glm::fvec2{32,32});
	//newObj->AddComponent(collision);

	auto gemLogic = new GemLogic();
	newObj->AddComponent(gemLogic);

}

void ObjectConstructorCursedArc::DiggerGoldBag(std::shared_ptr<GameObject>& newObj,Grid* theGrid,glm::ivec2 widthDepthIndex,glm::fvec2 sizeOfCells)
{
	//rendering

	int Xsize = static_cast<int>(sizeOfCells.x);
	int Ysize = static_cast<int>(sizeOfCells.y);
	auto RenderSprite = new RenderComponent();
	RenderSprite->SetTexture("Digger/Gold_Bag.png");
	RenderSprite->SetSize(Xsize,Ysize);
	RenderSprite->SetOffset(-Xsize/2, -Ysize/2);

	newObj->AddComponent(RenderSprite);

	auto renderGold = new RenderComponent();
	renderGold->SetTexture("Digger/GoldPile.png");
	renderGold->SetSize(Xsize,Ysize);
	renderGold->SetOffset(-Xsize / 2, Ysize / 2);
	renderGold->SetVisible(false);

	auto overlap = new OverlapComp(SDL_Rect{-Xsize/2,-Ysize/2,Xsize,Ysize});
	overlap->SetIsCollider(true);
	newObj->AddComponent(overlap);

	auto bagLogic = new BagLogic(theGrid, widthDepthIndex, sizeOfCells,RenderSprite,renderGold);
	newObj->AddComponent(bagLogic);

}
