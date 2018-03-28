#pragma once

// Platform specific headers
#ifdef __linux__

#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif

#include "SpikeUI.h"
#include "SpikeRenderer.h"


namespace SpikeEngine
{
	enum GameState
	{
		Initial = 1,
		Loading = 2,
		Loaded = 4,
		Playing = 8,
		Paused = 16,
		Unloading = 32,
		Destroyed = 64
	};

	class Game
	{
		GameState GameState;
		SpikeUI::UI::UI GameUI;
#ifdef _WIN32
		SpikeRenderer::DirectXRenderer GameRenderer;
#endif

		void SetErrorState();

	public:
		Game();

		void LoadUI(std::string const &);
#ifdef _WIN32
		void LoadRenderer(HWND);
#endif
		void Frame(float);
		void Update(float);

		SpikeEngine::GameState GetState();

		~Game();
	};
}