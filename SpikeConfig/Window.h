#pragma once

#ifdef DLL_SPIKECONFIG
#define SPIKECONFIG_EXPORT __declspec(dllexport)
#else
#define SPIKECONFIG_EXPORT __declspec(dllimport)
#endif

namespace SpikeConfig
{
	class SPIKECONFIG_EXPORT Window
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