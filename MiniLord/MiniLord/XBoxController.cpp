#include "MiniLordPCH.h"
#include "XBoxController.h"

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")
using namespace MiniLord;



class XBoxController::XBoxControllerImp
{
public:
	XBoxControllerImp() = default;
	~XBoxControllerImp() = default;
	void Update(int ControllerID);
	bool IsDown(ControllerButton button) const;
	bool IsUp(ControllerButton button) const;
	bool IsPressed(ControllerButton button) const;
private:
	XINPUT_STATE previeusState{};
	XINPUT_STATE CurrentState{};
};

void XBoxController::XBoxControllerImp::Update(int ControllerID)
{
	CopyMemory(&previeusState, &CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&CurrentState, sizeof(XINPUT_STATE));

	//ZeroMemory(&CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT ); // voorbeeld van het gebruik meerdere controllers
	XInputGetState(ControllerID, &CurrentState);
}

bool XBoxController::XBoxControllerImp::IsDown(ControllerButton button) const
{
	return ((CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0) &&
		((previeusState.Gamepad.wButtons & static_cast<unsigned int>(button)) == 0);
}

bool XBoxController::XBoxControllerImp::IsUp(ControllerButton button) const
{
	return ((CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) == 0) &&
		((previeusState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0);
}

bool XBoxController::XBoxControllerImp::IsPressed(ControllerButton button) const
{
	return (CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0;
}

void XBoxController::Update() const
{
	if (m_pImpl != nullptr)
		m_pImpl->Update(m_controllerIdx);
}

bool XBoxController::IsPressed(ControllerButton Button) const
{
	return m_pImpl->IsPressed(Button);
}

bool XBoxController::IsUp(ControllerButton button) const
{
	return m_pImpl->IsUp(button);
}

XBoxController::XBoxController(int controllerIndex)
	: m_controllerIdx(controllerIndex)
{
	m_pImpl = new XBoxControllerImp();
}

XBoxController::~XBoxController()
{
	delete m_pImpl;
}

bool XBoxController::IsDown(ControllerButton Button) const
{
	return m_pImpl->IsDown(Button);
}


