#include "MouseInput.h"

#ifdef _WIN32
SpikeInput::MouseOutput SpikeInput::MouseInput::GetAbsoluteMouse(HWND hWnd)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(hWnd, &cursorPos);

	SpikeUI::Containers::Point point(cursorPos.x, cursorPos.y);

	static bool lButton;
	auto lButtonState = GetKeyState(VK_LBUTTON) < 0;
	auto lButtonDown = lButtonState ? !lButton : false;
	auto lButtonUp = lButtonState ? false : lButton;

	static bool rButton;
	auto rButtonState = GetKeyState(VK_RBUTTON) < 0;
	auto rButtonDown = rButtonState ? !rButton : false;
	auto rButtonUp = rButtonState ? false : rButton;

	lButton = lButtonState;
	rButton = rButtonState;

	return SpikeInput::MouseOutput ({ 
		SpikeUI::Containers::Point(cursorPos.x, cursorPos.y),  
		lButtonDown,
		lButtonUp,
		rButtonDown,
		rButtonUp});
}
#endif
