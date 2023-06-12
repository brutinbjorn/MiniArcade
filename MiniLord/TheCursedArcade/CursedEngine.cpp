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

	//int music;
	//erviceLocator::GetSoundSystem().LoadSound(music, "LevelMusic1.mp3");

	auto mainMenu = SceneFactoryCursedArc::GameMenu();
	scenesManager.AddScene(mainMenu);


	
}
