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
		0, 0,
		clientWindow.right - clientWindow.left,
		clientWindow.bottom - clientWindow.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;

	SpikeUI::Controls::TextArea textArea_title(
		SpikeUI::Containers::Rectangle(30, 30, 230, 80),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(1.0, 1.0, 1.0));
	textArea_title.Text = "SpikeEngine";
	textArea_title.DHit = SpikeUI::UI::DrawableHit::Enable;

	SpikeUI::Controls::Button button1(
		SpikeUI::Containers::Rectangle(30, 100, 230, 150),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::TextArea button1_text(
		SpikeUI::Containers::Rectangle(30, 100, 230, 150),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button1_text.Text = "New Game";

	SpikeUI::Controls::Button button2(
		SpikeUI::Containers::Rectangle(30, 200, 230, 250),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::TextArea button2_text(
		SpikeUI::Containers::Rectangle(30, 200, 230, 250),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button2_text.Text = "Options";

	SpikeUI::Controls::Button button3(
		SpikeUI::Containers::Rectangle(30, 300, 230, 350),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::TextArea button3_text(
		SpikeUI::Containers::Rectangle(30, 300, 230, 350),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button3_text.Text = "Help";

	SpikeUI::Controls::Button button4(
		SpikeUI::Containers::Rectangle(30, 400, 230, 450),
		SpikeUI::Colour::Colour(0.5, 0.5, 0.5));
	SpikeUI::Controls::TextArea button4_text(
		SpikeUI::Containers::Rectangle(30, 400, 230, 450),
		SpikeUI::Containers::Font("Arial", 25),
		SpikeUI::Colour::Colour(0.0, 0.0, 0.0));
	button4_text.Text = "Quit";


	auto hoverIn = [](SpikeUI::Controls::TextArea& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(0.0, 0.0, 0.0);
	};
	auto hoverOut = [](SpikeUI::Controls::TextArea& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(1.0, 1.0, 1.0);
	};
	auto lClickDown = [](SpikeUI::Controls::TextArea& ref)
	{
		OutputDebugStringA((ref._SpikeEngineId() + " Down\n").c_str());
	};
	auto lClickUp = [](SpikeUI::Controls::TextArea& ref)
	{
		OutputDebugStringA((ref._SpikeEngineId() + " Up\n").c_str());
	};

	auto hoverInB = [](SpikeUI::Controls::Button& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(1.0, 1.0, 1.0);
	};
	auto hoverOutB = [](SpikeUI::Controls::Button& ref)
	{
		ref.Colour = SpikeUI::Colour::Colour(0.5, 0.5, 0.5);
	};
	auto lClickDownB = [](SpikeUI::Controls::Button& ref)
	{
		OutputDebugStringA((ref._SpikeEngineId() + " Down\n").c_str());
	};
	auto lClickUpB = [](SpikeUI::Controls::Button& ref)
	{
		OutputDebugStringA((ref._SpikeEngineId() + " Up\n").c_str());
	};

	auto lClickUpBQuit = [](SpikeUI::Controls::Button& ref)
	{
		PostQuitMessage(0);
	};

	textArea_title.receiveFocus = hoverIn;
	textArea_title.loseFocus = hoverOut;
	textArea_title.lClickDown = lClickDown;
	textArea_title.lClickUp = lClickUp;

	button1.receiveFocus = hoverInB;
	button1.loseFocus = hoverOutB;
	button1.lClickDown = lClickDownB;
	button1.lClickUp = lClickUpB;

	button2.receiveFocus = hoverInB;
	button2.loseFocus = hoverOutB;
	button2.lClickDown = lClickDownB;
	button2.lClickUp = lClickUpB;

	button3.receiveFocus = hoverInB;
	button3.loseFocus = hoverOutB;
	button3.lClickDown = lClickDownB;
	button3.lClickUp = lClickUpB;

	button4.receiveFocus = hoverInB;
	button4.loseFocus = hoverOutB;
	button4.lClickDown = lClickDownB;
	button4.lClickUp = lClickUpBQuit;

	SpikeUI::UI::UI ui(SpikeUI::Containers::Rectangle(
		0, 
		0, 
		clientWindow.right - clientWindow.left,
		clientWindow.bottom - clientWindow.top));

	ui.Insert(textArea_title, SpikeUI::UI::Front);
	ui.Insert(button1, SpikeUI::UI::Front);
	ui.Insert(button2, SpikeUI::UI::Front);
	ui.Insert(button3, SpikeUI::UI::Front);
	ui.Insert(button4, SpikeUI::UI::Front);
	ui.Insert(button1_text, button1._SpikeEngineId(), SpikeUI::UI::Front);
	ui.Insert(button2_text, button2._SpikeEngineId(), SpikeUI::UI::Front);
	ui.Insert(button3_text, button3._SpikeEngineId(), SpikeUI::UI::Front);
	ui.Insert(button4_text, button4._SpikeEngineId(), SpikeUI::UI::Front);

	auto renderer = SpikeRenderer::DirectXRenderer(hWnd);
	renderer.InitRenderer();

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
		
		float r = abs(sin(elapsed / 2000.0f));
		float g = abs(sin(elapsed / 2000.0f + 3.1416f / 4.0));
		float b = abs(sin(elapsed / 2000.0f + 3.1416f / 2.0));

		auto deltaTimer = SpikeUtils::Timer().Start();
		renderer.RenderFrame(r, g, b);
		renderer.RenderUI(ui);
		renderer.PresentToScreen();
		deltaTime = deltaTimer.Measure<SpikeUtils::Timer::Seconds>();
		auto framesPerSecond = deltaTimer.Measure<SpikeUtils::Timer::FramesPerSecond>();

		/*wchar_t buffer[25];
		swprintf(buffer, 25, L"SpikeEngine - %.*f FPS", 1, framesPerSecond);
		SetWindowText(hWnd, buffer);*/
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