#include "CursedArcadePCH.h"
#include "SceneFactoryCursedArc.h"
#include "ObjectConstructor.h"
#include "CursedCommands.h"
#include "Grid.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ObjectConstructorCursedArc.h"
#include "ServiceLocator.h"

using namespace MiniLord;


std::shared_ptr<Scene> SceneFactoryCursedArc::GameMenu()
{
	glm::ivec2 windowsize = Renderer::GetInstance().GetWindowSize();
	
	std::shared_ptr<Scene> MenuScene = std::make_shared<Scene>("MainMenu");


	auto HeadText = ObjectConstructor::Text("The Cursed Arcade", "lingua.otf");
	HeadText->GetTransform().SetPosition(static_cast<float>(windowsize.x / 2), 40, 0);
	MenuScene->AddGameObject(HeadText);


//	SDL_Rect commonButtonSize = {-50,-20,100,40};

//	SwitchSceneCommand* SwapToSinglePlayerGame = new SwitchSceneCommand(nullptr,MenuScene.get());
//	auto GoToSinglePlayer = ObjectConstructor::Button(commonButtonSize,SwapToSinglePlayerGame);
//	MenuScene->AddGameObject(GoToSinglePlayer);
	return MenuScene;


}

std::shared_ptr<MiniLord::Scene> SceneFactoryCursedArc::Digger()
{
	//int bgSoundID;
	//ServiceLocator::GetSoundSystem().LoadSound(bgSoundID,"LevelMusic1.mp3");
	//ServiceLocator::GetSoundSystem().PlaySound(bgSoundID, 0.2f);

	glm::fvec2 windowsize = Renderer::GetInstance().GetWindowSize();

	auto MainGame = std::make_shared<Scene>("DiggerMainGame");
	auto GameField = ObjectConstructor::RenderObject("DirtBackground.png");

	//Grid
	auto bgRender = GameField->GetComponent<RenderComponent>();
	GameField->GetComponent<BaseComponent>();
	auto size = bgRender->GetTextureSize();
	MainGame->AddGameObject(GameField);
	GameField->GetTransform().SetPosition(
		(windowsize.x/2) - (size.x/2),
		(windowsize.y / 2) - (size.y/2),0);

	ObjectConstructorCursedArc::GameGridDigger(
		GameField,"DiggerMainGame", 15, 9, size);

	auto currentGird = GameField->GetComponent<Grid>();
	auto cells = currentGird->CreateAndGetCells();

	for (int i = 0; i < cells.size(); ++i)
	{
		MainGame->AddGameObject(cells[i]);
	}
	//end Grid.

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

	//int loseLifeID;
	//ServiceLocator::GetSoundSystem().LoadSoundEffect(loseLifeID,"Piano2.wav");
	//auto soundeffect = new PlaySoundEffect(loseLifeID);
	//InputManager::GetInstance().AddOnKeyDownEvent(soundeffect,SDLK_z,XBoxController::ControllerButton::None);

	//player
	SDL_Rect testSize{ 0,0,32,32 };
	auto Player = std::make_shared<GameObject>();
	{
		auto actorComp = new ActorComponent();
		Player->AddComponent(actorComp);

		auto MoveUp = new BasicMoveCommand(actorComp, glm::fvec2(0, -10.f));
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveUp, SDLK_w, XBoxController::ControllerButton::DPadUp);
		auto MoveDown = new BasicMoveCommand(actorComp, glm::fvec2(0, 10.f));
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveDown, SDLK_s, XBoxController::ControllerButton::DPadDown);
		auto MoveLeft = new BasicMoveCommand(actorComp, glm::fvec2(-10.f,0.f));
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveLeft, SDLK_a, XBoxController::ControllerButton::DPadLeft);
		auto MoveRight = new BasicMoveCommand(actorComp,glm::fvec2(10,0));
		InputManager::GetInstance().AddOnKeyHeldEvent(MoveRight, SDLK_d, XBoxController::ControllerButton::DPadRight);

		//auto box = new SquareComponent(testSize);

		auto Render = new RenderComponent();
		Render->SetTexture("Digger/Digger_Player_Front.jpg");
		Render->SetSize(32, 32);
		Player->GetTransform().SetPosition(windowsize.x/2,windowsize.y/2,0);

		//Player->AddComponent(box);
		Player->AddComponent(Render);
	}
	MainGame->AddGameObject(Player);
	//end player

	//test Enemy
	auto enemy = std::make_shared<GameObject>();
	{
		enemy->AddComponent(new ActorComponent());
		auto Render = new RenderComponent();
		Render->SetTexture("Digger/Digger_Skull.jpg");
		Render->SetSize(64, 64);
		enemy->GetTransform().SetPosition((windowsize.x / 2) + 100, windowsize.y / 2, 0);
		//auto box = new SquareComponent(testSize);
		//Player->AddComponent(box);
		enemy->AddComponent(Render);

	}
	MainGame->AddGameObject(enemy);
	//end test Enemy

	//Control info
	std::string controlMessage = "controls:\nZ to play sound.\nP to print controls.";
	auto Controls = new PrintDebugMessage(controlMessage);
	InputManager::GetInstance().AddOnKeyDownEvent(Controls, SDLK_p, XBoxController::ControllerButton::None);
	Controls->Execute();

	return MainGame;
}
