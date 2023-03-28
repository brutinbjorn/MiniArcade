#include "MiniLordPCH.h"
#include "InputManager.h"

#pragma once
#include <list>
#include <map>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")

#pragma warning(push)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#include "backends/imgui_impl_sdl.h"
#include "SDL.h"
#pragma warning(pop)

using namespace MiniLord;

using ControllerCommandMap = std::map<XBoxController::ControllerButton, Command*>;
using KeyBoardCommandMap = std::map<XBoxController::KeyBoardButton, Command*>;

InputManager::InputManager()
{

}


InputManager::~InputManager()
{
	delete m_pXboxController;
	//for (size_t i = 0; i < m_pXboxController.size(); i++)
	//	delete m_pXboxController[i];

	for (std::list<Action>::iterator iter = m_Actions.begin(); iter != m_Actions.end(); ++iter)
	{
		if (iter->pCommand)
		{
			delete iter->pCommand;
			iter->pCommand = nullptr;
		}
	}
}


void InputManager::CheckForController()
{
	int controllerId = -1;


	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;

	}
	if (controllerId != -1)
	{
		if (m_pXboxController)
			delete m_pXboxController;

		m_pXboxController = new XBoxController(controllerId);
		//	std::cout << "controller found: " << controllerId << std::endl;
	}
	else
	{
		m_pXboxController = nullptr;
		//	std::cout << "no controller found" << std::endl;
	}
}

void InputManager::AddAction(const Action& ac)
{
	m_Actions.push_back(ac);
}

bool InputManager::ProcessInput()
{
	//const Uint8* keyState = SDL_GetKeyboardState(NULL);
	SDL_Event e{};
	//KEYBOARD LOOP
	//TODO might want to use a map with th keycode as key, and the action as var
	while (SDL_PollEvent(&e)) {

		//e.type == 

		if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			auto xpos = e.button.x;
			auto ypos = e.button.y;
			std::cout << "mouse position: " << xpos << ":" << ypos << std::endl;

		}
		if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			return false;
		}
		for (auto iter = m_Actions.begin(); iter != m_Actions.end(); iter++)
		{
			if (e.key.keysym.sym == iter->key)
			{
				if (e.type == SDL_KEYDOWN)
				{

					if (iter->type == InputType::wentDown)
						iter->pCommand->Execute();
					else if (iter->type == InputType::IsPressed)
						iter->isPressed = true;
				}

				if (e.type == SDL_KEYUP )
				{
					if (iter->type == InputType::wentUp)
						iter->pCommand->Execute();
					else if (iter->type == InputType::IsPressed)
						iter->isPressed = false;
				} 
			}
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for (auto actionIterator = m_Actions.begin(); actionIterator!= m_Actions.end(); actionIterator++)
	{
		if (actionIterator->isPressed && actionIterator->type == InputType::IsPressed)
			actionIterator->pCommand->Execute();
	}




	if (!m_pXboxController || !m_pXboxController->IsValid())
	{
		CheckForController();
	}

	if (m_pXboxController)
	{
		m_pXboxController->Update();

		for (std::list<Action>::iterator iter = m_Actions.begin(); iter != m_Actions.end(); ++iter)
		{

			if (m_pXboxController->IsDown(iter->XButton) && iter->type == InputType::wentDown)
			{
				iter->pCommand->Execute();
			}
			if (m_pXboxController->IsPressed(iter->XButton) && iter->type == InputType::IsPressed)
			{
				iter->pCommand->Execute();
			}
			if (m_pXboxController->IsUp(iter->XButton) && iter->type == InputType::wentUp)
			{
				iter->pCommand->Execute();
			}
		}

		if (m_pXboxController->IsDown(XBoxController::ControllerButton::Back))
			return false;
	}

	return true;
}


