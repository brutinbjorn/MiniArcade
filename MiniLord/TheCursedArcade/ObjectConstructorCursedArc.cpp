#pragma once
#include "CursedArcadePCH.h"
#include "ObjectConstructorCursedArc.h"

#include "ActorComponent.h"
#include "GameObject.h"
#include "Grid.h"
#include "RenderComponent.h"
#include "GemLogic.h"
#include "OverlapComp.h"
#include "BagLogic.h"
#include "CursedCommands.h"
#include "InputManager.h"
#include "NobbinLogic.h"
#include "PlayerDiggerLogic.h"
#include "BulletLogic.h"

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

void ObjectConstructorCursedArc::GameGridDigger(std::shared_ptr<GameObject> newObj, const std::string& jsonFile)
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

void ObjectConstructorCursedArc::DiggerGem(std::shared_ptr<GameObject> newObj, Interface::Observer* obs)
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
	gemLogic->AddToObserver(obs);
	newObj->AddComponent(gemLogic);

	
}

void ObjectConstructorCursedArc::DiggerGoldBag(std::shared_ptr<GameObject> newObj,Grid* theGrid,glm::ivec2 widthDepthIndex,glm::fvec2 sizeOfCells, Interface::Observer* obs)
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
	renderGold->SetOffset(-Xsize / 2, -Ysize / 2);
	renderGold->SetVisible(false);
	newObj->AddComponent(renderGold);

	auto overlap = new OverlapComp(SDL_Rect{-Xsize/2,-Ysize/2,Xsize,Ysize});
	overlap->SetIsCollider(true);
	newObj->AddComponent(overlap);

	auto actorcomp = new ActorComponent();
	actorcomp->SetOverlapComponent(overlap);
	newObj->AddComponent(actorcomp);


	auto bagLogic = new BagLogic(theGrid, widthDepthIndex, sizeOfCells,RenderSprite,renderGold);
	bagLogic->GetSubject().AddObserver(obs);
	newObj->AddComponent(bagLogic);

}

void ObjectConstructorCursedArc::DiggerNobbin(std::shared_ptr<GameObject> newobj, Grid* grid, glm::fvec2 sizeOfObject, Interface::Observer* obs)
{

	//actor 
	auto actorlog = new ActorComponent();
	newobj->AddComponent(actorlog);

	//overlap
	int Xsize = static_cast<int>(sizeOfObject.x);
	int Ysize = static_cast<int>(sizeOfObject.y);
	auto Overlap = new OverlapComp(SDL_Rect{ -Xsize / 2,-Ysize / 2,Xsize,Ysize });
	newobj->AddComponent(Overlap);
	Overlap->SetIsOverlapper(true);
	Overlap->SetIsCollider(true);

	auto render = new RenderComponent();
	render->SetTexture("Digger/Nobbin_Left.png");
	render->SetSize(Xsize, Ysize);
	render->SetOffset(-Xsize / 2, -Ysize / 2);
	newobj->AddComponent(render);

	auto renderAlt = new RenderComponent();
	renderAlt->SetTexture("Digger/Hobbin_Left.png");
	renderAlt->SetSize(Xsize, Ysize);
	renderAlt->SetOffset(-Xsize / 2, -Ysize / 2);
	renderAlt->SetVisible(false);
	newobj->AddComponent(renderAlt);


	//startPosition.
	auto enemyStartPos = grid->GetEnemySpawnPosition();
	newobj->GetTransform().SetPosition(enemyStartPos.x, enemyStartPos.y, 0);

	auto nobbinBrain = new NobbinLogic(grid, render, renderAlt, actorlog);;
	nobbinBrain->Getsubject().AddObserver(obs);
	newobj->AddComponent(nobbinBrain);


}

void ObjectConstructorCursedArc::PlayerTwo(std::shared_ptr<GameObject> newObj,Scene* currentScene, Grid* grid, Interface::Observer* obs, glm::ivec2 objSize, bool usesController)
{
	auto actorComp = new ActorComponent();
	newObj->AddComponent(actorComp);


	//playerRenderer
	auto Render = new RenderComponent();
	Render->SetTexture("Digger/Digger_Player2_moving_left.png");
	Render->SetSize(objSize.x, objSize.y);
	Render->SetOffset(-objSize.x / 2, -objSize.y / 2);
	newObj->AddComponent(Render);

	//position
	auto startPos = grid->GetPlayerStartPosition();
	newObj->GetTransform().SetPosition(startPos.x, startPos.y, 0);

	//overlap event
	auto overlapComp = new OverlapComp(SDL_Rect(-14, -14, 28, 28));
	overlapComp->SetIsCollider(true);
	newObj->AddComponent(overlapComp);

	//PlayerComponent
	auto PlayerLogic = new PlayerDiggerLogic(grid,currentScene);
	newObj->AddComponent(PlayerLogic);
	PlayerLogic->GetSubject().AddObserver(obs);

	//Commands;
	auto MoveUpOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(0.f, -100.f), grid, 10);
	auto MoveDownOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(0.f, 100.f), grid, 10);
	auto MoveLeftOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(-100.f, 0.f), grid, 10);
	auto MoveRightOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(100.f, 0.f), grid, 10);
	auto FireBullet = new DiggerFireBullet(PlayerLogic);



	if(usesController)
	{
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveUpOnGrid, SDLK_UP, XBoxController::ControllerButton::DPadUp);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveDownOnGrid, SDLK_DOWN, XBoxController::ControllerButton::DPadDown);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveLeftOnGrid, SDLK_LEFT, XBoxController::ControllerButton::DPadLeft);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveRightOnGrid, SDLK_RIGHT, XBoxController::ControllerButton::DPadRight);
		InputManager::GetInstance().AddOnKeyDownEvent(FireBullet, SDLK_0, XBoxController::ControllerButton::ButtonA);
	}
	else
	{
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveUpOnGrid, SDLK_UP, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveDownOnGrid, SDLK_DOWN, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveLeftOnGrid, SDLK_LEFT, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveRightOnGrid, SDLK_RIGHT, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyDownEvent(FireBullet, SDLK_0, XBoxController::ControllerButton::None);
	}

}

void ObjectConstructorCursedArc::PlayerNobbin(std::shared_ptr<GameObject> newObj, Grid* grid, glm::fvec2 sizeOfObject,
	Interface::Observer* obs, bool usesController)
{

	//actor 
	auto actorlog = new ActorComponent();
	newObj->AddComponent(actorlog);

	//overlap
	int Xsize = static_cast<int>(sizeOfObject.x);
	int Ysize = static_cast<int>(sizeOfObject.y);
	auto Overlap = new OverlapComp(SDL_Rect{ -Xsize / 2,-Ysize / 2,Xsize,Ysize });
	newObj->AddComponent(Overlap);
	Overlap->SetIsOverlapper(true);
	Overlap->SetIsCollider(true);

	auto render = new RenderComponent();
	render->SetTexture("Digger/Nobbin_Left.png");
	render->SetSize(Xsize, Ysize);
	render->SetOffset(-Xsize / 2, -Ysize / 2);
	newObj->AddComponent(render);

	auto renderAlt = new RenderComponent();
	renderAlt->SetTexture("Digger/Hobbin_Left.png");
	renderAlt->SetSize(Xsize, Ysize);
	renderAlt->SetOffset(-Xsize / 2, -Ysize / 2);
	renderAlt->SetVisible(false);
	newObj->AddComponent(renderAlt);


	//startPosition.
	auto enemyStartPos = grid->GetEnemySpawnPosition();
	newObj->GetTransform().SetPosition(enemyStartPos.x, enemyStartPos.y, 0);

	auto nobbinBrain = new NobbinLogic(grid, render, renderAlt, actorlog);;
	nobbinBrain->Getsubject().AddObserver(obs);
	newObj->AddComponent(nobbinBrain);


	//Commands;
	auto MoveUpOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(0.f, -100.f), grid, 10);
	auto MoveDownOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(0.f, 100.f), grid, 10);
	auto MoveLeftOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(-100.f, 0.f), grid, 10);
	auto MoveRightOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(100.f, 0.f), grid, 10);


	if (usesController)
	{
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveUpOnGrid, SDLK_UP, XBoxController::ControllerButton::DPadUp);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveDownOnGrid, SDLK_DOWN, XBoxController::ControllerButton::DPadDown);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveLeftOnGrid, SDLK_LEFT, XBoxController::ControllerButton::DPadLeft);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveRightOnGrid, SDLK_RIGHT, XBoxController::ControllerButton::DPadRight);
	}
	else
	{
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveUpOnGrid, SDLK_UP, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveDownOnGrid, SDLK_DOWN, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveLeftOnGrid, SDLK_LEFT, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveRightOnGrid, SDLK_RIGHT, XBoxController::ControllerButton::None);
	}
}

void ObjectConstructorCursedArc::PlayerBullet(std::shared_ptr<GameObject> newObj, Grid* grid,glm::fvec2 dirAndSpeed,glm::ivec2 objSize)
{

	SDL_Rect collision{ -objSize.x / 2,-objSize.y / 2,objSize.x,objSize.y };
	auto hitbox = new OverlapComp(collision);
	newObj->AddComponent(hitbox);

	auto sprite = new RenderComponent();
	sprite->SetTexture("Digger/Digger_Bullet.png");
	sprite->SetSize(objSize.x, objSize.y);
	sprite->SetOffset(-objSize.x / 2, -objSize.y / 2);
	newObj->AddComponent(sprite);

	auto accel = new ActorComponent();
	newObj->AddComponent(accel);

	auto normal = glm::normalize(dirAndSpeed);

	normal *= 300.f;
	auto bullet = new BulletLogic(normal,grid);
	newObj->AddComponent(bullet);


}


void ObjectConstructorCursedArc::PlayerOne(std::shared_ptr<GameObject> newObj, Scene* currentScene, Grid* grid, Interface::Observer* obs, glm::ivec2 objSize, bool usesController)
{
	auto actorComp = new ActorComponent();

	newObj->AddComponent(actorComp);
	//playerRenderer
	auto Render = new RenderComponent();
	Render->SetTexture("Digger/Digger_Player1_moving_left.png");
	Render->SetSize(objSize.x, objSize.y);
	Render->SetOffset(-objSize.x / 2, -objSize.y / 2);
	newObj->AddComponent(Render);

	//position
	auto startPos = grid->GetPlayerStartPosition();
	newObj->GetTransform().SetPosition(startPos.x, startPos.y, 0);

	//overlap event
	auto overlapComp = new OverlapComp(SDL_Rect(-14, -14, 28, 28));
	overlapComp->SetIsCollider(true);
	newObj->AddComponent(overlapComp);

	//PlayerComponent
	auto PlayerLogic = new PlayerDiggerLogic(grid,currentScene);
	newObj->AddComponent(PlayerLogic);
	PlayerLogic->GetSubject().AddObserver(obs);

	//Commands;
	auto MoveUpOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(0.f, -100.f), grid, 10);
	auto MoveDownOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(0.f, 100.f), grid, 10);
	auto MoveLeftOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(-100.f, 0.f), grid, 10);
	auto MoveRightOnGrid = new GridLockedMoveCommand(newObj.get(), glm::fvec2(100.f, 0.f), grid, 10);

	auto FireBullet = new DiggerFireBullet(PlayerLogic);


	
	if(usesController)
	{
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveUpOnGrid, SDLK_w, XBoxController::ControllerButton::DPadUp);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveDownOnGrid, SDLK_s, XBoxController::ControllerButton::DPadDown);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveLeftOnGrid, SDLK_a, XBoxController::ControllerButton::DPadLeft);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveRightOnGrid, SDLK_d, XBoxController::ControllerButton::DPadRight);
		InputManager::GetInstance().AddOnKeyDownEvent(FireBullet, SDLK_q, XBoxController::ControllerButton::ButtonA);
	}
	else
	{
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveUpOnGrid, SDLK_w, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveDownOnGrid, SDLK_s, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveLeftOnGrid, SDLK_a, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveRightOnGrid, SDLK_d, XBoxController::ControllerButton::None);
		InputManager::GetInstance().AddOnKeyDownEvent(FireBullet, SDLK_q, XBoxController::ControllerButton::None);
	}

}
