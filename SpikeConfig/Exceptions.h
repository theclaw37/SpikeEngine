#pragma once

namespace SpikeConfig
{
	namespace Exceptions
	{
		struct __declspec(dllexport) ConfigSectionNotFoundException : public std::exception {
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