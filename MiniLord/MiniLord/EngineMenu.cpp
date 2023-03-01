#include "MiniLordPCH.h"
#include "EngineMenu.h"

#include "GameObject.h"
#include "ObjectConstructor.h"
#include "RenderComponent.h"
#include "Renderer.h"


//windowsize
void MiniLord::EngineMenu::Initialize()
{


	auto windowSize = Renderer().GetInstance().GetWindowSize();
	auto Background = ObjectConstructor::RenderObject("Background.jpg");
	Background->GetComponent<RenderComponent>()->SetSize(windowSize.x,windowSize.y);
	AddGameObject(Background);

	auto DAELogo = ObjectConstructor::RenderObject("logo.png");
	DAELogo->SetPosition(static_cast<float>(windowSize.x/2), static_cast<float>(windowSize.y/2));
	AddGameObject(DAELogo);

	auto FPSTimer = ObjectConstructor::FPSCounter(SDL_Color{ 250,0,0 },glm::ivec2(5,5),"lingua.otf",20);
	AddGameObject(FPSTimer);

}
