#pragma once

#include <exception>

#ifdef DLL_SPIKECONFIG
#define SPIKECONFIG_EXPORT __declspec(dllexport)
#else
#define SPIKECONFIG_EXPORT __declspec(dllimport)
#endif

namespace SpikeConfig
{
	namespace Exceptions
	{
		struct SPIKECONFIG_EXPORT ConfigSectionNotFoundException : public std::exception {
		private:
			std::string message;
		public:
			explicit ConfigSectionNotFoundException(const std::string& message) : message("Could not load config section " + message)
			{}

			virtual const char* what() const throw() {
				return message.c_str();
			}
		};
	}
}