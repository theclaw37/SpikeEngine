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
	enum ConfigState
	{
		Initial = 1,
		Loaded = 2,
		Error = 4
	};

	class SPIKECONFIG_EXPORT Config : public SpikeUtils::Singleton<Config>
	{
		friend class SpikeUtils::Singleton<Config>;

	public:
		void Load(const std::string& path);
		
		ConfigState GetState() const;
		Window const & GetWindow() const;
		virtual ~Config() = default;
	private:
		Config();

		ConfigState CState;

		Window CWindow;
		void LoadWindow(picojson::value const & object);
	};
}