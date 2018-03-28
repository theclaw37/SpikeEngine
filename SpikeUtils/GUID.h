#pragma once

#include <iostream>

#ifdef DLL_SPIKEUTILS
#define SPIKEUTILS_EXPORT __declspec(dllexport)
#else
#define SPIKEUTILS_EXPORT __declspec(dllimport)
#endif

namespace SpikeUtils
{
	class SPIKEUTILS_EXPORT GUID final
	{
	public:
		GUID(GUID const & other) = default;
		GUID& operator=(GUID& other) = default;

		static GUID Generate();
		std::string const & Value();
	private:
		GUID(std::string const & value) : value(value)
		{}
		std::string value;
	};
}