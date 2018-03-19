#pragma once

// Universal headers go here
#include <iostream>
#include <fstream>



// Platform specific headers
#ifdef __linux__

#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif

// Custom headers go here
#include "SpikeConfig.h"
#include "SpikeRenderer.h"
#include "SpikeUI.h"
