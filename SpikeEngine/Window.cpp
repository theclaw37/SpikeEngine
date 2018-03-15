#include "Engine.h"

SpikeEngine::Window::Window() : _clientWidth(800), _clientHeight(600) {}

const UINT SpikeEngine::Window::GetClientWidth()
{
	return _clientWidth;
}

const UINT SpikeEngine::Window::GetClientHeight()
{
	return _clientHeight;
}
