#include "SpikeConfig.h"
#include "picojson.h"

void SpikeConfig::Config::Load(const std::string & path)
{
	auto file = std::ifstream(path, std::ifstream::in);

	picojson::value root;
	picojson::parse(root, file);

	if (!root.contains("window"))
		throw SpikeConfig::Exceptions::ConfigSectionNotFoundException("window");

	LoadWindow(root.get("window"));
}

SpikeConfig::Window const & SpikeConfig::Config::GetWindow() const
{
	return window;
}

void SpikeConfig::Config::LoadWindow(picojson::value const & object)
{
	auto width = static_cast<unsigned int>(object.get("width").get<double>());
	auto height = static_cast<unsigned int>(object.get("height").get<double>());

	window = Window(width, height);
}
