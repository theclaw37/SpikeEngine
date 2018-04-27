#pragma once

//Useful macros
#define CLAMP(x, low, high) (x < low) ? low : ((x > high) ? high : x)

#include "_SpikeEngineObject.h"
#include "_SpikeEngineResource.h"
#include "SpikeEngineResourceManager.h"
#include "Singleton.h"
#include "Timer.h"