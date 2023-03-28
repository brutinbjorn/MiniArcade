#include "MiniLordPCH.h"
#include "XBoxController.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib,"xinput.lib")
#include <Xinput.h>

using namespace MiniLord;

#pragma region XBOX PIMPL
class XBoxController::XBoxControllerImp
{
public:
	XBoxControllerImp();
	~XBoxControllerImp() = default;
	void Update(int ControllerID);
	bool IsDown(ControllerButton button) const;
	bool IsUp(ControllerButton button) const;
	bool IsPressed(ControllerButton button) const;
private:
	XINPUT_STATE previeusState{};
	XINPUT_STATE CurrentState{};

	//From the Example;
	WORD ButtonsPrevieusState{};
	WORD ButtonsCurrentState{};
};

XBoxController::XBoxControllerImp::XBoxControllerImp()
{
	ZeroMemory(&previeusState, sizeof(XINPUT_STATE));
	ZeroMemory(&CurrentState, sizeof(XINPUT_STATE));
}

void XBoxController::XBoxControllerImp::Update(int ControllerID)
{
	CopyMemory(&previeusState, &CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(ControllerID, &CurrentState);
	//ZeroMemory(&CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT ); // voorbeeld van het gebruik meerdere controllers

	// ^ == binary XOR;
	auto buttonChanges = CurrentState.Gamepad.wButtons ^ previeusState.Gamepad.wButtons;
	ButtonsCurrentState = buttonChanges & CurrentState.Gamepad.wButtons;
	ButtonsPrevieusState = buttonChanges & (~previeusState.Gamepad.wButtons);
}

bool XBoxController::XBoxControllerImp::IsDown(ControllerButton button) const
{
	return ButtonsCurrentState & static_cast<int>(button);
	//((CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0) &&
		//((previeusState.Gamepad.wButtons & static_cast<unsigned int>(button)) == 0);
}

bool XBoxController::XBoxControllerImp::IsUp(ControllerButton button) const
{
	return ButtonsPrevieusState & static_cast<int>(button);
	//return ((CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) == 0) &&
		//((previeusState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0);
}

bool XBoxController::XBoxControllerImp::IsPressed(ControllerButton button) const
{
	return CurrentState.Gamepad.wButtons & static_cast<int>(button);
	//return (CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0;
}
#pragma endregion XBOX PIMPL

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


