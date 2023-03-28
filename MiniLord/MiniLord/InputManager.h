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

		bool isPressed = false;
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
		const glm::fvec2& GetMousePosition() const { return m_MousePosition; };

	private:
		InputManager();

		glm::fvec2 m_MousePosition {};
		//friend class Singleton;
		XBoxController* m_pXboxController;
		std::list<Action> m_Actions;
		friend class Singleton;


	};
}

