// Platform specific headers
#ifdef __linux__

#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif

#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "SpikeConfig.h"


SpikeEngine::Game game;

#ifdef __linux__

int main(int argc, char *argv[])
{
	std::cout << "Hello from linux"
	std::getchar();
	return 0;
}

#elif _WIN32

LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
		SpikeConfig::Config::Instance().Load("config.json");
	}
	catch (SpikeConfig::Exceptions::ConfigSectionNotFoundException& csnfe)
	{
		return -1;
	}
	catch (std::exception& e)
	{
		return -1;
	}

	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"SpikeMainWindow";

	RegisterClassEx(&wc);

	RECT clientWindow = { 
		0, 
		0, 
		SpikeConfig::Config::Instance().GetWindow().GetClientWidth(), 
		SpikeConfig::Config::Instance().GetWindow().GetClientHeight()};
	AdjustWindowRect(&clientWindow, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		L"SpikeMainWindow",
		L"SpikeEngine",
		WS_OVERLAPPEDWINDOW,
		0, 0,
		clientWindow.right - clientWindow.left,
		clientWindow.bottom - clientWindow.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	
	game.LoadUI("");
	game.LoadRenderer(hWnd);

	MSG msg;
	float deltaTime = 0;
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				break;
		}

		auto deltaTimer = SpikeUtils::Timer().Start();
		game.Update(deltaTime);
		game.Frame(deltaTime);
		deltaTime = deltaTimer.Measure<SpikeUtils::Timer::Seconds>();
	}

	UnregisterClass(L"SpikeMainWindow", hInstance);
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
				PostQuitMessage(0);
		} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

#endif