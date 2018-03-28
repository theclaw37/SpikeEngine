#pragma once

#include "Window.h"
#include "SpikeUtils.h"

#ifdef DLL_SPIKECONFIG
#define SPIKECONFIG_EXPORT __declspec(dllexport)
#else
#define SPIKECONFIG_EXPORT __declspec(dllimport)
#endif

namespace picojson {
	class value;
}

namespace SpikeConfig
{
	class SPIKECONFIG_EXPORT Config : public SpikeUtils::Singleton<Config>
	{
		friend class SpikeUtils::Singleton<Config>;

	public:
		void Load(const std::string& path);

		Window const & GetWindow() const;
	private:
		Config() = default;

		Window window;
		void LoadWindow(picojson::value const & object);
	};
}