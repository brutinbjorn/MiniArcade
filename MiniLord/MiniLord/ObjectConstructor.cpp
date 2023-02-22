#include "MiniLordPCH.h"
#include "ObjectConstructor.h"
#include "GameObject.h"
//#include "BaseComponent.h"
#include "RenderComponent.h"

//std::shared_ptr<dae::GameObject> ObjectConstructor::BasicActor(const std::string& RenderFile)
//{
//	auto newActor = std::make_shared<dae::GameObject>();
//
//	auto PeterComp = new ActorComponent();
//	newActor->AddComponent(PeterComp);
//
//	auto RenderComp = new RenderComponent();
//	RenderComp->SetTexture(RenderFile);
//	newActor->AddComponent(RenderComp);
//
//	return newActor;
//}
//
//std::shared_ptr<dae::GameObject> ObjectConstructor::HealthBar(const glm::vec3& pos, const std::string& img )
//{
//	auto NewHealthBar = std::make_shared<dae::GameObject>();
//	NewHealthBar->GetTransform()->SetPosition(pos.x,pos.y,pos.z);
//	//auto RenderComp = new RenderComponent();
//
//	//auto TextComp = new dae::TextComponent("levens:", font, RenderComp);
//
//	auto LiveComp = new HealthComponent(3);
//	NewHealthBar->AddComponent(LiveComp);
//
//	auto LiveBarComp = new HealthBarComponent(LiveComp,img);
//	NewHealthBar->AddComponent(LiveBarComp);
//
//	return NewHealthBar;
//}
//
//std::shared_ptr<dae::GameObject> ObjectConstructor::ScoreBar(const std::string& FontFile,const std::string& Text,unsigned int size,const glm::fvec2& pos)
//{
//	//auto ScoreBar = std::make_shared<dae::GameObject>();
//	//auto RenderComp = new RenderComponent();
//	//auto TextComp = new dae::TextComponent("levens:", font, RenderComp);
//	//auto ScoreBarComp = new ScoreComponent(TextComp);
//	//ScoreBar->AddComponent(RenderComp);
//	//ScoreBar->AddComponent(TextComp);
//	//ScoreBar->AddComponent(ScoreBarComp);
//	//ScoreBar->GetTransform()->SetPosition(pos);
//	//return ScoreBar;
//
//	auto newObject = TextObject(FontFile,Text,size,pos);
//	auto textcomp = newObject->GetComponent<dae::TextComponent>();
//
//	ScoreComponent* newScore = new ScoreComponent(textcomp);
//	newObject->AddComponent(newScore);
//
//	return newObject;
//}
//
//std::shared_ptr<dae::GameObject> ObjectConstructor::BaseButton(const glm::vec3& pos,const SDL_Rect& relativeRect,
//	const std::shared_ptr<dae::Font>& font)
//{
//
//	auto button = std::make_shared<dae::GameObject>();
//	button->GetTransform()->Translate(pos);
//
//	auto buttonSqr = new SquareComponent();
//	button->AddComponent(buttonSqr);
//	buttonSqr->SetSquare(relativeRect);
//
//	//auto font3 = dae::ResourceManager::GetInstance().LoadFont(font, size);
//
//
//	auto TextRender = new RenderComponent();
//	button->AddComponent(TextRender);
//	auto Text = new dae::TextComponent("test",font,TextRender);
//	button->AddComponent(Text);
//
//
//	return button;
//
//}
//
//std::shared_ptr<dae::GameObject> ObjectConstructor::TextObject(const std::string& FontFile, const std::string& text, unsigned int size, glm::fvec2 pos)
//{
//	auto textObject = std::make_shared<dae::GameObject>();
//	RenderComponent* textRenderComp = new RenderComponent;
//
//	auto font3 = dae::ResourceManager::GetInstance().LoadFont(FontFile, size);
//	dae::TextComponent* textComp = new dae::TextComponent(text, font3, textRenderComp);
//	textObject->AddComponent(textRenderComp);
//	textObject->AddComponent(textComp);
//
//	textObject->SetPosition(pos.x, pos.y);
//	return textObject;
//
//
//}

std::shared_ptr<MiniLord::GameObject> MiniLord::ObjectConstructor::RenderObject(const std::string & TexturePath, float Xpos, float Ypos)
{

	auto newObject = std::make_shared<GameObject>();
	auto rendercomp = new RenderComponent;
	rendercomp->SetTexture(TexturePath);
	rendercomp->SetPosition(Xpos, Ypos);
	//rendercomp->SetSize(250, 250);
	newObject->AddComponent(rendercomp);
	return newObject;

}
