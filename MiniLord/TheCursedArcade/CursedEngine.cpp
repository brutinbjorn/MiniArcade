#include "CursedArcadePCH.h"
#include "CursedEngine.h"
#include "SceneFactoryCursedArc.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

void MiniLord::CursedEngine::LoadGame()
{
	auto& scenesManager = SceneManager::GetInstance();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	auto mainMenu = SceneFactoryCursedArc::GameMenu();
	scenesManager.AddScene(mainMenu);

	auto levelOne = SceneFactoryCursedArc::Digger();
	scenesManager.AddScene(levelOne);
	
}
