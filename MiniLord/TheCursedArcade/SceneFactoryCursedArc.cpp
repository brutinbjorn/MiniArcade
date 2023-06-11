#include "CursedArcadePCH.h"
#include "SceneFactoryCursedArc.h"

#include "ObjectConstructor.h"
#include "CursedCommands.h"
#include "DiggerManager.h"
#include "GemLogic.h"
#include "Grid.h"
#include "InputManager.h"
#include "LivesDisplayComp.h"
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
	
	std::shared_ptr<Scene> menuScene = std::make_shared<Scene>("MainMenu");

	auto HeadText = ObjectConstructor::Text("The Cursed Arcade", "lingua.otf");

	HeadText->GetTransform().SetPosition(static_cast<float>(windowsize.x / 2), 40, 0);
	menuScene->AddGameObject(HeadText);


	//SDL_Rect commonButtonSize = {-50,-20,100,40};
	//SwitchSceneCommand* SwapToSinglePlayerGame = new SwitchSceneCommand(nullptr,MenuScene.get());
	//auto GoToSinglePlayer = ObjectConstructor::Button(commonButtonSize,SwapToSinglePlayerGame);
	//MenuScene->AddGameObject(GoToSinglePlayer);


	auto buttonsize = SDL_Rect{ -100,-50,200,100 };
	auto singleplayerbutton = ObjectConstructor::Button(buttonsize, std::make_unique<LoadDiggerScene>(0, menuScene.get()), "Lingua.otf","SinglePlayer",SDL_Color{255,255,0,255});
	singleplayerbutton->GetTransform().SetPosition(static_cast<float>(windowsize.x / 2),static_cast<float>(windowsize.y / 2 - 150), 0);
	menuScene->AddGameObject(singleplayerbutton);
	
	//auto buttonsize = SDL_Rect{ -50,-100,100,200 };
	auto coopButton = ObjectConstructor::Button(buttonsize, std::make_unique<LoadDiggerScene>(1, menuScene.get()), "Lingua.otf", "Co-Op", SDL_Color{ 255,255,0,255 });
	coopButton->GetTransform().SetPosition(static_cast<float>(windowsize.x / 2), static_cast<float>(windowsize.y / 2), 0);
	menuScene->AddGameObject(coopButton);

	//auto buttonsize = SDL_Rect{ -50,-100,100,200 };
	auto VSButton =ObjectConstructor::Button(buttonsize, std::make_unique<LoadDiggerScene>(2, menuScene.get()), "Lingua.otf", "VS mode", SDL_Color{ 255,255,0,255 });
	VSButton->GetTransform().SetPosition(static_cast<float>(windowsize.x / 2), static_cast<float>(windowsize.y / 2 + 150), 0);
	menuScene->AddGameObject(VSButton);

	return menuScene;


}

std::shared_ptr<Scene> SceneFactoryCursedArc::Digger( int gameMode)
{
	//int bgSoundID;
	//ServiceLocator::GetSoundSystem().LoadSound(bgSoundID,"LevelMusic1.mp3");
	//ServiceLocator::GetSoundSystem().PlaySound(bgSoundID, 0.2f);

	//globals.
	glm::fvec2 windowsize = Renderer::GetInstance().GetWindowSize();
	auto sizeOffObjects = glm::ivec2{ 46,46 };
	auto MainGame = std::make_shared<Scene>("DiggerMainGame");

	//Grid
	auto GameField = std::make_shared<GameObject>();
	GameField->GetTransform().SetPosition((windowsize.x/2) ,(windowsize.y / 2),0);
	ObjectConstructorCursedArc::GameGridDigger(GameField, "Digger/Digger_Level01.json");
	MainGame->AddGameObject(GameField);

	auto gridManager = GameField->GetComponent<Grid>();
	//end Grid

	//EventManager
	auto DiggerEventManager = std::make_shared<GameObject>();
	MainGame->AddGameObject(DiggerEventManager);

	// scoreboard
	auto scoreObject = ObjectConstructor::Text("score:", "Lingua.otf");
	MainGame->AddGameObject(scoreObject);
	scoreObject->SetParentGameObject(DiggerEventManager.get(), true);

	// Lives
	auto LivesObject = std::make_shared<GameObject>();
	auto lives = new LivesDisplayComp("Digger/Digger_Player_Front.png", 3);
	LivesObject->AddComponent(lives);
	MainGame->AddGameObject(LivesObject);

	auto diggerManager = new DiggerManager(scoreObject.get(),LivesObject.get(),MainGame.get(),gridManager, sizeOffObjects,gameMode);
	DiggerEventManager->AddComponent(diggerManager);
	//End EventManager



	//player
	auto Player = std::make_shared<GameObject>();
	bool usesController = gameMode == 0;

	ObjectConstructorCursedArc::PlayerOne(Player, MainGame.get(),gridManager, diggerManager, sizeOffObjects,usesController);
	MainGame->AddGameObject(Player);

	diggerManager->SetPlayer(Player.get());
	diggerManager->SetPlayerRespawn(gridManager->GetPlayerStartPosition());
	//end player


	if(gameMode == 1)
	{
		auto playerTwo = std::make_shared<GameObject>();
		ObjectConstructorCursedArc::PlayerTwo(playerTwo, MainGame.get(),gridManager, diggerManager, sizeOffObjects,!usesController);
		diggerManager->SetPlayerTwo(playerTwo.get());
		diggerManager->SetPlayerTwoRespawn(gridManager->GetPlayerTwoStartPosition());
		MainGame->AddGameObject(playerTwo);
	}

	if(gameMode == 2)
	{
		auto playerEnemy = std::make_shared<GameObject>();
		ObjectConstructorCursedArc::PlayerNobbin(playerEnemy, gridManager, sizeOffObjects, diggerManager, true);
		diggerManager->SetPlayerTwo(playerEnemy.get());
		diggerManager->SetPlayerTwoRespawn(gridManager->GetEnemySpawnPosition());
		MainGame->AddGameObject(playerEnemy);
	}


	//test Enemy
	//auto enemy = std::make_shared<GameObject>();
	//{
	//	ObjectConstructorCursedArc::DiggerNobbin(enemy,gridManager,sizeOffObjects,diggerManager);
	//}
	//MainGame->AddGameObject(enemy);
	//end test Enemy

	diggerManager->LoadNextLevel();

	return MainGame;
}

