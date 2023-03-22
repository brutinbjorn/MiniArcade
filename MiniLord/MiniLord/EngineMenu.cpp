#include "MiniLordPCH.h"
#include "EngineMenu.h"

#include "GameObject.h"
#include "ObjectConstructor.h"
#include "RenderComponent.h"
#include "RotateGameObject.h"
#include "Renderer.h"


//windowsize
void MiniLord::EngineMenu::Initialize()
{


	auto windowSize = Renderer().GetInstance().GetWindowSize();
	auto Background = ObjectConstructor::RenderObject("Background.jpg");
	Background->GetComponent<RenderComponent>()->SetSize(windowSize.x,windowSize.y);
	AddGameObject(Background);

	auto DAELogo = ObjectConstructor::RenderObject("logo.png");
	DAELogo->GetTransform().SetPosition(static_cast<float>(windowSize.x / 2), static_cast<float>(windowSize.y / 2),0);
	AddGameObject(DAELogo);



	auto CenterRotatingObject = std::make_shared<GameObject>();
	std::cout << "Window size" << windowSize.x << ":" << windowSize.y << "/n";
	CenterRotatingObject->GetTransform().SetPosition(glm::fvec3(static_cast<float>(windowSize.x / 2), static_cast<float>(windowSize.y / 3 * 2), 0));
	AddGameObject(CenterRotatingObject);

	auto FirstPlanetRotatingObject = ObjectConstructor::RenderObject("Digger/Digger_Player_Front.jpg");
	auto Rotation1 = new RotateGameObject(-1, 30);
	FirstPlanetRotatingObject->AddComponent(Rotation1);
	FirstPlanetRotatingObject->SetParentGameObject(CenterRotatingObject.get());
	AddGameObject(FirstPlanetRotatingObject);


	auto SecondPlanetRotatingObject = ObjectConstructor::RenderObject("Digger/Digger_Skull.jpg");
	auto Rotation2 = new RotateGameObject(3, 30);
	SecondPlanetRotatingObject->AddComponent(Rotation2);
	SecondPlanetRotatingObject->SetParentGameObject(FirstPlanetRotatingObject.get());
	AddGameObject(SecondPlanetRotatingObject);


	auto FPSTimer = ObjectConstructor::FPSCounter(SDL_Color{ 250,0,0 },glm::ivec2(5,5),"lingua.otf",20);
	AddGameObject(FPSTimer);


}
