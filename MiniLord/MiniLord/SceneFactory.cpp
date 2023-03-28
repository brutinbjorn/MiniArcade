#include "MiniLordPCH.h"
#include "SceneFactory.h"

#include "ActorComponent.h"
#include "CacheTest1.h"
#include "CacheTest2.h"
#include "Command.h"
#include "DemoImguiComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ObjectConstructor.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "RotateGameObject.h"

using namespace MiniLord;





std::shared_ptr<Scene> SceneFactory::DefaultDAEScene(const std::string& name)
{
	auto defaultScene = std::make_shared<Scene>(name);
	auto windowSize = Renderer().GetInstance().GetWindowSize();
	auto Background = ObjectConstructor::RenderObject("Background.jpg");
	Background->GetComponent<RenderComponent>()->SetSize(windowSize.x, windowSize.y);
	defaultScene->AddGameObject(Background);

	auto DAELogo = ObjectConstructor::RenderObject("logo.png");
	DAELogo->GetTransform().SetPosition(static_cast<float>(windowSize.x / 2), static_cast<float>(windowSize.y / 2), 0);
	defaultScene->AddGameObject(DAELogo);

	return defaultScene;
}

std::shared_ptr<Scene> SceneFactory::OrbitingGameObjects(const std::string& name)
{
	auto windowSize = Renderer().GetInstance().GetWindowSize();

	auto newScene = std::make_shared<Scene>(name);

	auto CenterRotatingObject = std::make_shared<GameObject>();
	std::cout << "Window size" << windowSize.x << ":" << windowSize.y << "/n";
	CenterRotatingObject->GetTransform().SetPosition(glm::fvec3(static_cast<float>(windowSize.x / 2), static_cast<float>(windowSize.y / 3 * 2), 0));
	newScene->AddGameObject(CenterRotatingObject);

	auto FirstPlanetRotatingObject = ObjectConstructor::RenderObject("Digger/Digger_Player_Front.jpg");
	auto Rotation1 = new RotateGameObject(-1, 30);
	FirstPlanetRotatingObject->AddComponent(Rotation1);
	FirstPlanetRotatingObject->SetParentGameObject(CenterRotatingObject.get());
	newScene->AddGameObject(FirstPlanetRotatingObject);

	auto SecondPlanetRotatingObject = ObjectConstructor::RenderObject("Digger/Digger_Skull.jpg");
	auto Rotation2 = new RotateGameObject(3, 30);
	SecondPlanetRotatingObject->AddComponent(Rotation2);
	SecondPlanetRotatingObject->SetParentGameObject(FirstPlanetRotatingObject.get());
	newScene->AddGameObject(SecondPlanetRotatingObject);

	auto FPSTimer = ObjectConstructor::FPSCounter(SDL_Color{ 250,0,0 }, glm::ivec2(5, 5), "lingua.otf", 20);
	newScene->AddGameObject(FPSTimer);

	return newScene;
}

std::shared_ptr<Scene> SceneFactory::MovingGameObjects(const std::string& name)
{

	auto& inputmang = InputManager::GetInstance();

	auto MovingScene = std::make_shared<Scene>(name);
	auto playerOne = std::make_shared<GameObject>();

	//actor
	auto actorOne = new ActorComponent();
	playerOne->AddComponent(actorOne);
	//end actor

	//Render
	auto renderCompOne = new RenderComponent();
	renderCompOne->SetTexture("Digger/Digger_Player_Front.jpg");
	playerOne->AddComponent(renderCompOne);

	//end render
	MovingScene->AddGameObject(playerOne);

	Command* moveUpCommand = new MoveActorCommand(actorOne, glm::fvec2(0.f, -50.f));
	Action moveUpAction = Action{XBoxController::ControllerButton::None,SDL_KeyCode::SDLK_w,moveUpCommand,InputType::IsPressed};
	inputmang.AddAction(moveUpAction);

	Command* moveDownCommand = new MoveActorCommand(actorOne, glm::fvec2{ 0,50.f });
	Action moveDownAction = Action{ XBoxController::ControllerButton::None,SDL_KeyCode::SDLK_s,moveDownCommand,InputType::IsPressed };
	inputmang.AddAction(moveDownAction);

	Command* moveLeftCommand = new MoveActorCommand(actorOne, glm::fvec2(-50.f, 0.f));
	Action moveLeft = Action{ XBoxController::ControllerButton::None,SDL_KeyCode::SDLK_a,moveLeftCommand,InputType::IsPressed };
	inputmang.AddAction(moveLeft);

	Command* moveRightCommand = new MoveActorCommand(actorOne, glm::fvec2{ 50.f,0 });
	Action moveRight = Action{ XBoxController::ControllerButton::None,SDL_KeyCode::SDLK_d,moveRightCommand,InputType::IsPressed };
	inputmang.AddAction(moveRight);


	//
	// player.
	//
	auto PlayerTwo = std::make_shared<GameObject>();
	auto ActorTwo = new ActorComponent();
	PlayerTwo->AddComponent(ActorTwo);

	auto renderTwo = new RenderComponent();
	renderTwo->SetTexture("Digger/Digger_Skull.jpg");
	PlayerTwo->AddComponent(renderTwo);


	MovingScene->AddGameObject(PlayerTwo);
	Command* MoveUpCommandTwo = new MoveActorCommand(ActorTwo, glm::fvec2(0,-100.f));
	Action MoveUpTwo = Action{ XBoxController::ControllerButton::DPadUp,SDLK_UNKNOWN,MoveUpCommandTwo,InputType::IsPressed };
	inputmang.AddAction(MoveUpTwo);

	Command* MoveDownCommandTwo = new MoveActorCommand(ActorTwo, glm::fvec2(0, 100.f));
	Action moveDownTwo = Action{ XBoxController::ControllerButton::DPadDown,SDLK_UNKNOWN,MoveDownCommandTwo,InputType::IsPressed };
	inputmang.AddAction(moveDownTwo);

	Command* moveLeftCommandTwo = new MoveActorCommand(ActorTwo, glm::fvec2(-100.f,0.f));
	Action moveLeftTwo = Action{ XBoxController::ControllerButton::DPadLeft,SDLK_UNKNOWN,moveLeftCommandTwo,InputType::IsPressed };
	inputmang.AddAction(moveLeftTwo);

	Command* moveRightCommandTwo = new MoveActorCommand(ActorTwo, glm::fvec2(100.f, 0));
	Action moveRightTwo = Action{ XBoxController::ControllerButton::DPadRight,SDLK_UNKNOWN,moveRightCommandTwo,InputType::IsPressed };
	inputmang.AddAction(moveRightTwo);


	//set positions;
	auto windowSize = Renderer().GetInstance().GetWindowSize();



	playerOne->GetTransform().SetPosition(static_cast<float>(windowSize.x)/3.f,static_cast<float>(windowSize.y)/2.f,0.f);
	PlayerTwo->GetTransform().SetPosition(static_cast<float>(windowSize.x)/3.f*2.f, static_cast<float>(windowSize.y)/2.f, 0.f);



	return MovingScene;

}

std::shared_ptr<Scene> SceneFactory::GuiSceneTest(const std::string& name)
{
	auto newScene = std::make_shared<Scene>(name);
	std::shared_ptr<GameObject> DemoImGui = std::make_shared<GameObject>();
	auto DemoMenu = new DemoImguiComponent();
	DemoImGui->AddComponent(DemoMenu);
	newScene->AddGameObject(DemoImGui);

	std::shared_ptr<GameObject> TrashTestOne = std::make_shared<GameObject>();
	auto cacheTestOne = new CacheTest1();
	TrashTestOne->AddComponent(cacheTestOne);
	newScene->AddGameObject(TrashTestOne);

	std::shared_ptr<GameObject> trashTestTwo = std::make_shared<GameObject>();
	auto CacheTestTwo = new CacheTest2();
	trashTestTwo->AddComponent(CacheTestTwo);
	newScene->AddGameObject(trashTestTwo);
	return newScene;


}
