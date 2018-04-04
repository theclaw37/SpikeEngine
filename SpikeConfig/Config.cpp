#include <fstream>
#include "Config.h"
#include "Exceptions.h"
#include "picojson.h"

// Platform specific headers
#ifdef __linux__

#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif

SpikeConfig::Config::Config() : CState(ConfigState::Initial) {}

void SpikeConfig::Config::Load(const std::string & path)
{
	auto file = std::ifstream(path, std::ifstream::in);

	picojson::value root;
	picojson::parse(root, file);

	if (!root.contains("window"))
		throw SpikeConfig::Exceptions::ConfigSectionNotFoundException("window");

	LoadWindow(root.get("window"));

	CState = ConfigState::Loaded;
}

SpikeConfig::ConfigState SpikeConfig::Config::GetState() const
{
	return CState;
}

SpikeConfig::Window const & SpikeConfig::Config::GetWindow() const
{
	return CWindow;
}

void SpikeConfig::Config::LoadWindow(picojson::value const & object)
{
	auto width = static_cast<unsigned int>(object.get("width").get<double>());
	auto height = static_cast<unsigned int>(object.get("height").get<double>());

	CWindow = Window(width, height);
}
