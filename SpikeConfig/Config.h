#pragma once

namespace picojson {
	class value;
}

namespace SpikeConfig
{
	class Config
	{
	public:
		Config() = default;
		void Load(const std::string& path);

		Window const & GetWindow() const;
	private:
		Window window;

		void LoadWindow(picojson::value const & object);
	};
}