#include "MiniLordPCH.h"
#include "ObjectConstructor.h"
#include "GameObject.h"
//#include "BaseComponent.h"
#include "ButtonComponent.h"
#include "Command.h"
#include "Font.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "SquareComponent.h"
#include "FPSRenderComponent.h"
#include "Command.h"

using namespace MiniLord;
std::shared_ptr<GameObject> MiniLord::ObjectConstructor::RenderObject(const std::string & TexturePath, float Xpos, float Ypos)
{
	auto newObject = std::make_shared<GameObject>();
	auto rendercomp = new RenderComponent;
	rendercomp->SetTexture(TexturePath);
	newObject->AddComponent(rendercomp);


	newObject->GetTransform().SetPosition(Xpos, Ypos, 0);
	return newObject;

}

std::shared_ptr<GameObject> ObjectConstructor::Text(const std::string& text,
	const std::string& fontLocation, const int size, const SDL_Color& color)
{
	auto TextObject = std::make_shared<GameObject>();
	auto RenderComp = new RenderComponent;

	TextObject->AddComponent(RenderComp);
	auto font = ResourceManager::GetInstance().LoadFont(fontLocation, size);
	auto TextComp = new TextComponent(text,font,RenderComp);
	TextComp->SetColor(color);
	TextObject->AddComponent(TextComp);

	return TextObject;
}


//TODO Finish button.
std::shared_ptr<GameObject> ObjectConstructor::Button(const SDL_Rect & rect, std::unique_ptr<Command> command, const std::string& fontLocation ,const std::string& textOnButton, SDL_Color textColor )
{

	auto button = std::make_shared<GameObject>();//= Text(textOnButton, fontLocation, 20, textColor);

	auto SquareComp = new SquareComponent(rect);
	button->AddComponent(SquareComp);

	auto ButtonComp = new ButtonComponent(SquareComp,std::move(command));
	button->AddComponent(ButtonComp);


	//return button;

	//auto TextObject = std::make_shared<GameObject>();
	auto RenderComp = new RenderComponent;

	button->AddComponent(RenderComp);
	auto font = ResourceManager::GetInstance().LoadFont(fontLocation, 20);
	auto TextComp = new TextComponent(textOnButton, font, RenderComp);
	TextComp->SetColor(textColor);
	button->AddComponent(TextComp);

	return button;



}

std::shared_ptr<GameObject> ObjectConstructor::FPSCounter(const SDL_Color& color, const glm::ivec2 position, const std::string& FontLocation, const int size)
{
	auto newFPSCounter = std::make_shared<GameObject>();
	auto RenderComp = new RenderComponent;
	newFPSCounter->AddComponent(RenderComp);

	auto  font = ResourceManager::GetInstance().LoadFont(FontLocation, static_cast<int>(size));
	auto TextComp = new TextComponent("FPS:", font, RenderComp);
	TextComp->SetColor(color);

	newFPSCounter->AddComponent(TextComp);
	newFPSCounter->GetTransform().SetPosition(static_cast<float>(position.x), static_cast<float>(position.y),0);
	auto FPSLogic = new FPSRenderComponent(TextComp);
	newFPSCounter->AddComponent(FPSLogic);
	return newFPSCounter;

}

