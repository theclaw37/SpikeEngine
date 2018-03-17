#pragma once

#include "Singleton.h"

namespace picojson {
	class value;
}

namespace SpikeConfig
{
	class __declspec(dllexport) Config : public SpikeUtils::Singleton<Config>
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