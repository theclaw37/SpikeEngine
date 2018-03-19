#include "SpikeEngine.h"
#include "Timer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

double deltaTime = 0;

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

	try
	{
		SpikeConfig::Config::Instance().Load("config.json");
	}
	catch (SpikeConfig::Exceptions::ConfigSectionNotFoundException& csnfe)
	{
		const size_t cSize = strlen(csnfe.what()) + 1;
		wchar_t* wc = new wchar_t[cSize];
		size_t outSize;
		mbstowcs_s(&outSize, wc, cSize, csnfe.what(), cSize-1);

		MessageBox(NULL,
			wc,
			L"Error",
			MB_ICONEXCLAMATION | MB_OK);

		delete wc;
	}
	catch (std::exception& e)
	{
		const size_t cSize = strlen(e.what()) + 1;
		wchar_t* wc = new wchar_t[cSize];
		size_t outSize;
		mbstowcs_s(&outSize, wc, cSize, e.what(), cSize - 1);

		MessageBox(NULL,
			wc,
			L"Error",
			MB_ICONEXCLAMATION | MB_OK);

		delete wc;
		return 0;
	}

	RECT clientWindow = { 0, 0, SpikeConfig::Config::Instance().GetWindow().GetClientWidth(), SpikeConfig::Config::Instance().GetWindow().GetClientHeight()};
	AdjustWindowRect(&clientWindow, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		L"SpikeMainWindow",
		L"SpikeEngine",
		WS_OVERLAPPEDWINDOW,
		300, 300,
		clientWindow.right - clientWindow.left,
		clientWindow.bottom - clientWindow.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	
	auto renderer = SpikeRenderer::DirectXRenderer(hWnd);
	renderer.InitRenderer();

	MSG msg;

	auto timer = SpikeUtils::Timer().Start();
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				break;
		}
		auto elapsed = timer.Measure<SpikeUtils::Timer::Milliseconds>();

		SpikeUI::Text::TextArea textArea(
			SpikeUI::Containers::Rectangle(800, 500, 100, 100),
			SpikeUI::Text::Font("Arial", 50),
			SpikeUI::Colour::Colour(1.0, 0.0, 0.0));
		textArea.Text = "This is Red text, written with the Arial font. Is it red?";

		SpikeUI::Text::TextArea textArea2(
			SpikeUI::Containers::Rectangle(1100, 600, 800, 100),
			SpikeUI::Text::Font("Times New Roman", 25),
			SpikeUI::Colour::Colour(0.0, 1.0, 0.0));
		textArea2.Text = "This text should be displayed as Green, with Times New Roman. Is it displayed correctly?";

		SpikeUI::Text::TextArea textArea3(
			SpikeUI::Containers::Rectangle(1200, 900, 400, 400),
			SpikeUI::Text::Font("Magneto", 65),
			SpikeUI::Colour::Colour(0.0, 0.0, 1.0));
		textArea3.Text = "This text is actually blue ... But is it really?";


		SpikeUI::UI::UI ui;
		ui.Insert(textArea);
		ui.Insert(textArea2);
		ui.Insert(textArea3);
		
		float r = abs(sin(elapsed / 2000.0f));
		float g = abs(sin(elapsed / 2000.0f + 3.1416f / 4.0));
		float b = abs(sin(elapsed / 2000.0f + 3.1416f / 2.0));

		auto deltaTimer = SpikeUtils::Timer().Start();
		renderer.RenderFrame(r, g, b);
		renderer.RenderUI(ui);
		renderer.PresentToScreen();
		deltaTime = deltaTimer.Measure<SpikeUtils::Timer::Seconds>();
		auto framesPerSecond = deltaTimer.Measure<SpikeUtils::Timer::FramesPerSecond>();

		wchar_t buffer[25];
		swprintf(buffer, 25, L"SpikeEngine - %.*f FPS", 1, framesPerSecond);
		SetWindowText(hWnd, buffer);
	}

	renderer.ShutdownRenderer();
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