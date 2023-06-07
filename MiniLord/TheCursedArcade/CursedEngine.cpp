#include "CursedArcadePCH.h"
#include "CursedEngine.h"
#include "SceneFactoryCursedArc.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "ContactListener.h"

void MiniLord::CursedEngine::LoadGame()
{
	auto& scenesManager = SceneManager::GetInstance();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	//ServiceLocator::RegisterPhysics(new Box2DPhysics(glm::fvec2(0,0)));
	//auto world = ServiceLocator::GetPhysics();

	//auto myContactListener = std::make_shared<ContactListener>();
	//world.AddContactListener(myContactListener);

	auto mainMenu = SceneFactoryCursedArc::GameMenu();
	scenesManager.AddScene(mainMenu);

	auto levelOne = SceneFactoryCursedArc::Digger();
	scenesManager.AddScene(levelOne);
	
}
