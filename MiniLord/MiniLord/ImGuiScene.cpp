#include "MiniLordPCH.h"
#include "ImGuiScene.h"

#include "GameObject.h"
#include "CacheTest1.h"
#include "CacheTest2.h"
#include "DemoImguiComponent.h"

void MiniLord::ImGuiScene::Initialize()
{

	//std::shared_ptr<GameObject> DemoImGui = std::make_shared<GameObject>();
	//auto DemoMenu = new DemoImguiComponent();
	//DemoImGui->AddComponent(DemoMenu);
	//AddGameObject(DemoImGui);


	std::shared_ptr<GameObject> TrashTestOne = std::make_shared<GameObject>();
	auto cacheTestOne = new CacheTest1();
	TrashTestOne->AddComponent(cacheTestOne);
	AddGameObject(TrashTestOne);

	std::shared_ptr<GameObject> trashTestTwo = std::make_shared<GameObject>();
	auto CacheTestTwo = new CacheTest2();
	trashTestTwo->AddComponent(CacheTestTwo);
	AddGameObject(trashTestTwo);


}
