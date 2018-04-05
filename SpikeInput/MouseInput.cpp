#include "MouseInput.h"

#ifdef _WIN32
SpikeInput::MouseOutput SpikeInput::MouseInput::GetAbsoluteMouse(HWND hWnd)
{
	static MouseOutput result;

	static POINT cursorPos;
	GetCursorPos(&cursorPos);
	GetMessagePos();
	ScreenToClient(hWnd, &cursorPos);

	result.MOx = cursorPos.x;
	result.MOy = cursorPos.y;
	
	static bool lButton;
	static bool lButtonState;
	lButtonState = _MOLButtonState;
	result.MOLeftButtonDown = lButtonState ? !lButton : false;
	result.MOLeftButtonUp = lButtonState ? false : lButton;

	static bool rButton;
	static bool rButtonState;
	rButtonState = GetAsyncKeyState(VK_RBUTTON) < 0;
	result.MORightButtonDown = rButtonState ? !rButton : false;
	result.MORightButtonUp = rButtonState ? false : rButton;

	lButton = lButtonState;
	rButton = rButtonState;

	return result;
}
#endif
void SpikeInput::MouseInput::SetLButtonState(bool value)
{
	_MOLButtonState = value;
}
