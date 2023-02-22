#include "MiniLordPCH.h"
#include "EngineMenu.h"

#include "GameObject.h"
#include "ObjectConstructor.h"
#include "RenderComponent.h"

void MiniLord::EngineMenu::Initialize()
{
	auto Background = ObjectConstructor::RenderObject("Background.jpg");
	Background->GetComponent<RenderComponent>()->SetSize(0,0);

	auto DAELogo = ObjectConstructor::RenderObject("logo.png");
	DAELogo->SetPosition(0, 0);

	AddGameObject(Background);
}
