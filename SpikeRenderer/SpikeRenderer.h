#pragma once

// Platform specific headers
#ifdef __linux__

#ifdef SPIKE_DIRECTX
#error "DirectX not supported on Linux"
#elif SPIKE_OPENGL
	// OpenGL headers etc. go here
#endif

#elif _WIN32

#ifdef SPIKE_DIRECTX
#include "DirectXRenderer.h"
#elif SPIKE_OPENGL
	// OpenGL headers etc. go here
#endif

#endif