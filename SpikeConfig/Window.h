#pragma once

namespace SpikeConfig
{
	class Window
	{
	public:
		Window();

		Window(unsigned int width, unsigned int height);

		const unsigned int GetClientWidth() const;
		const unsigned int GetClientHeight() const;

	private:
		unsigned int _clientWidth = 0, _clientHeight = 0;
	};
}