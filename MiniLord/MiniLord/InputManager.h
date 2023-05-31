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
		XBoxController::ControllerButton XButton = XBoxController::ControllerButton::None;
		SDL_KeyCode key = SDLK_UNKNOWN;
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

		//old way...
		void AddAction(const Action& ac);


		void AddOnKeyDownEvent(Command* command, SDL_KeyCode key,XBoxController::ControllerButton xboxbutton);
		void AddOnkeyUpEvent(Command* command, SDL_KeyCode key, XBoxController::ControllerButton xboxbutton);
		void AddOnKeyHeldEvent(Command* command, SDL_KeyCode key, XBoxController::ControllerButton xboxbutton);


		bool ProcessInput();
		const glm::fvec2& GetMousePosition() const { return m_MousePosition; };
		bool MouseWentDown() const { return m_MouseWentDown; }
	private:
		InputManager();

		glm::fvec2 m_MousePosition {};
		bool m_MouseWentDown = false;


		//friend class Singleton;
		XBoxController* m_pXboxController;
		std::list<Action> m_Actions;
		friend class Singleton;


	};
}

