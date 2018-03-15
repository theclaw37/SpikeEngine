#include "Engine.h"

#ifdef __linux__

int main(int argc, char *argv[])
{
	std::cout << "Hello from linux"
	std::getchar();
	return 0;
}

#elif _WIN32

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	MessageBox(NULL,
		L"Hello from Win32",
		L"SpikeEngine",
		MB_ICONEXCLAMATION | MB_OK);

	return 0;
}

#endif