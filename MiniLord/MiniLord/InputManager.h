#pragma once
#include <list>

#include "Command.h"
#include "Singleton.h"
#include "XBoxController.h"


#include "SDL.h"



namespace MiniLord
{
	enum class InputType
	{
		wentDown, wentUp, IsPressed
	};

	struct Action
	{
		XBoxController::ControllerButton XButton;
		SDL_Scancode key = SDL_SCANCODE_UNKNOWN;
		Command* pCommand = nullptr;
		InputType type = InputType::wentDown;
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		~InputManager() override;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) noexcept = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) noexcept = delete;


		void CheckForController();
		void AddAction(const Action& ac);
		bool ProcessInput();

	private:
		InputManager();
		friend class Singleton;
		SDL_Event m_OldEvent;
		XBoxController* m_pXboxController;
		std::list<Action> m_Actions;

	};
}

