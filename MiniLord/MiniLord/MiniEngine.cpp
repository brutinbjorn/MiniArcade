#include "MiniLordPCH.h"
#include "MiniEngine.h"

#include "Scene.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "EngineMenu.h"
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace MiniLord;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void MiniEngine::Initialize()
{
#ifdef USE_SDL2
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1020,
		720,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	srand(0);
#endif

#ifdef USE_SDLMIXER2
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
#endif
}

void MiniEngine::Cleanup()
{
#ifdef USE_SDL2
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
#endif

}

void MiniEngine::run()
{
	Initialize();
	// tell the resource managers where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	//JsonManager::GetInstance().Init("../Data/");
	TimeManager::GetInstance().init();
	TimeManager::GetInstance().PrintTime(true);
	TimeManager::GetInstance().start();

	LoadGame();
	{
		auto& input = InputManager::GetInstance();
		auto& time = TimeManager::GetInstance();

	//	SceneManager::GetInstance().PostInitialize();
		bool doContinue = true;
		while (doContinue)
		{
			//SteamAPI_RunCallbacks();
			time.Update();
			doContinue = input.ProcessInput();
			while (time.ShouldDoFixedUpdateAndLowerLag())
			{
				float ft = time.GetMsPerUpdate();
				FixedUpdate(ft);
			}
			float dt = time.GetDeltaTime();
			Update(dt);
			LateUpdate(dt);
			Render();



			//TODO ADD this_Thread::Sleep_for(sleeptime) om aan een target FPS te geraken, anders gaat de game aan MAX_FPS draaien, en ook de CPU pushen, denk aan bordelands 2 die da probeerde.

		}
	}
	Cleanup();
}

void MiniEngine::LoadGame()
{
	auto startScene = std::shared_ptr<Scene>(new EngineMenu("StartMenu"));
	SceneManager::GetInstance().AddScene(startScene);
	startScene->Initialize();

}

void MiniEngine::FixedUpdate(const float ft)
{
	SceneManager::GetInstance().FixedUpdate(ft);
}

void MiniEngine::Update(const float dt)
{
	SceneManager::GetInstance().Update(dt);
}

void MiniEngine::LateUpdate(const float lt)
{
	SceneManager::GetInstance().LateUpdate(lt);
}

void MiniEngine::Render() const
{
	Renderer::GetInstance().Render();
}
