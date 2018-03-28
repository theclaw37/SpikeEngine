#include "Window.h"

SpikeConfig::Window::Window() : Window(320, 240)
{
}

SpikeConfig::Window::Window(unsigned int width, unsigned int height) : _clientWidth(width), _clientHeight(height) {}

const unsigned int SpikeConfig::Window::GetClientWidth() const
{
	return _clientWidth;
}

const unsigned int SpikeConfig::Window::GetClientHeight() const
{
	return _clientHeight;
}
