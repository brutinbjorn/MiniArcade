#include "CursedArcadePCH.h"
#include "SceneFactoryCursedArc.h"

#include "CollisionComponent.h"
#include "ObjectConstructor.h"
#include "CursedCommands.h"
#include "DiggerManager.h"
#include "GemLogic.h"
#include "Grid.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ObjectConstructorCursedArc.h"
#include "OverlapComp.h"
#include "PlayerDiggerLogic.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

using namespace MiniLord;


std::shared_ptr<Scene> SceneFactoryCursedArc::GameMenu()
{
	glm::ivec2 windowsize = Renderer::GetInstance().GetWindowSize();
	
	std::shared_ptr<Scene> MenuScene = std::make_shared<Scene>("MainMenu");

	//auto HeadText = ObjectConstructor::Text("The Cursed Arcade", "lingua.otf");
	//HeadText->GetTransform().SetPosition(static_cast<float>(windowsize.x / 2), 40, 0);
	//MenuScene->AddGameObject(HeadText);


	//SDL_Rect commonButtonSize = {-50,-20,100,40};
	//SwitchSceneCommand* SwapToSinglePlayerGame = new SwitchSceneCommand(nullptr,MenuScene.get());
	//auto GoToSinglePlayer = ObjectConstructor::Button(commonButtonSize,SwapToSinglePlayerGame);
	//MenuScene->AddGameObject(GoToSinglePlayer);
	return MenuScene;


}

std::shared_ptr<MiniLord::Scene> SceneFactoryCursedArc:: Digger()
{
	//int bgSoundID;
	//ServiceLocator::GetSoundSystem().LoadSound(bgSoundID,"LevelMusic1.mp3");
	//ServiceLocator::GetSoundSystem().PlaySound(bgSoundID, 0.2f);

	glm::fvec2 windowsize = Renderer::GetInstance().GetWindowSize();

	auto MainGame = std::make_shared<Scene>("DiggerMainGame");


	//EventManager
	auto DiggerEventManager = std::make_shared<GameObject>();
	auto scoreObject = ObjectConstructor::Text("score:", "Lingua.otf");
	scoreObject->SetParentGameObject(DiggerEventManager.get(), true);

	auto diggerManager = new DiggerManager(scoreObject.get());
	DiggerEventManager->AddComponent(diggerManager);
	MainGame->AddGameObject(DiggerEventManager);
	//End EventManager
	


	//Grid
	auto GameField = std::make_shared<GameObject>();
	//auto GameField = ObjectConstructor::RenderObject("DirtBackground.png");
	//auto bgRender = GameField->GetComponent<RenderComponent>();
	//auto size = bgRender->GetTextureSize();

	GameField->GetTransform().SetPosition((windowsize.x/2) ,(windowsize.y / 2),0);


	auto SizeOffObjects = glm::ivec2{ 32,32 };
	ObjectConstructorCursedArc::GameGridDigger(GameField, "Digger/Digger_Level01.json");
	MainGame->AddGameObject(GameField);
	auto gridManager = GameField->GetComponent<Grid>();
	auto ObjectsToAdd = gridManager->CreateCellsAndLanesFromJSONFile(SizeOffObjects);
	for (int i = 0; i < ObjectsToAdd.size(); ++i)
	{
		MainGame->AddGameObject(ObjectsToAdd[i]);
		if (auto gem = ObjectsToAdd[i]->GetComponent<GemLogic>())
			gem->AddToObserver(diggerManager);
	}
	//end Grid


	//scoreComponent
	auto scoretext = ObjectConstructor::Text("Score:", "Lingua.otf");
	scoretext->GetTransform().SetPosition(0, 0, 0);
	MainGame->AddGameObject(scoretext);

	auto scorelogic = new ScoreComponent(scoretext->GetComponent<TextComponent>());
	scoretext->AddComponent(scorelogic);
	//End ScorObject


	//measurements
	auto testCubeSide = std::make_shared<GameObject>();
	{
		auto testomp  = new SquareComponent(SDL_Rect{ 0,0,100,100 }, SDL_Color{ 0,255,0 });
		testCubeSide->AddComponent(testomp);
		testCubeSide->GetTransform().SetPosition(0, windowsize.y / 2, 0);
	}
	MainGame->AddGameObject(testCubeSide);

	auto testCubeTop = std::make_shared<GameObject>();
	{
		auto testComp2 = new SquareComponent( SDL_Rect{0,0,100,100},SDL_Color{0,255,0} );
		testCubeTop->AddComponent(testComp2);
		testCubeTop->GetTransform().SetPosition(windowsize.x/2, 0, 0);
	}
	MainGame->AddGameObject(testCubeTop);
	// end measurements


	//player
	auto Player = std::make_shared<GameObject>();
	{
		auto actorComp = new ActorComponent();
		Player->AddComponent(actorComp);

		//Commands;
		auto MoveUpOnGrid = new GridLockedMoveCommand(Player.get(), glm::fvec2(0.f,-200.f), GameField->GetComponent<Grid>(),10);
		InputManager::GetInstance().AddOnKeyDownEvent(MoveUpOnGrid,SDLK_w, XBoxController::ControllerButton::DPadUp);
		auto MoveDownOnGrid = new GridLockedMoveCommand(Player.get(), glm::fvec2(0.f, 200.f), GameField->GetComponent<Grid>(),10);
		InputManager::GetInstance().AddOnKeyDownEvent(MoveDownOnGrid, SDLK_s, XBoxController::ControllerButton::DPadDown);
		auto MoveLeftOnGrid = new GridLockedMoveCommand(Player.get(), glm::fvec2(-200.f, 0.f), GameField->GetComponent<Grid>(),10);
		InputManager::GetInstance().AddOnKeyDownEvent(MoveLeftOnGrid, SDLK_a, XBoxController::ControllerButton::DPadLeft);
		auto MoveRightOnGrid = new GridLockedMoveCommand(Player.get(), glm::fvec2(200.f, 0.f), GameField->GetComponent<Grid>(),10);
		InputManager::GetInstance().AddOnKeyDownEvent(MoveRightOnGrid, SDLK_d,XBoxController::ControllerButton::DPadRight);

		//playerRenderer
		auto Render = new RenderComponent();
		Render->SetTexture("Digger/Digger_Player_Front.png");
		Render->SetSize(SizeOffObjects.x,SizeOffObjects.y);
		Render->SetOffset(-SizeOffObjects.x / 2, -SizeOffObjects.y / 2);
		Player->AddComponent(Render);

		//position
		auto startPos = gridManager->GetPlayerStartPosition();
		Player->GetTransform().SetPosition(startPos.x,startPos.y,0);

		//overlap event
		auto overlapComp = new OverlapComp(SDL_Rect(-14, -14, 28, 28));
		overlapComp->SetIsCollider(true);
		Player->AddComponent(overlapComp);

		//PlayerComponent
		auto PlayerLogic = new PlayerDiggerLogic(gridManager);
		Player->AddComponent(PlayerLogic);
	}

	MainGame->AddGameObject(Player);
	//end player

	//test Enemy
	auto enemy = std::make_shared<GameObject>();
	{
		//
		enemy->AddComponent(new ActorComponent());

		auto Render = new RenderComponent();
		Render->SetTexture("Digger/Digger_Skull.jpg");
		Render->SetSize(SizeOffObjects.x,SizeOffObjects.y);

		enemy->AddComponent(Render);

		//startPosition.
		auto enemyStartPos = gridManager->GetEnemySpawnPosition();
		enemy->GetTransform().SetPosition(enemyStartPos.x,enemyStartPos.y,0);
	}
	MainGame->AddGameObject(enemy);
	//end test Enemy

	return MainGame;
}

