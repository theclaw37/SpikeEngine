#pragma once

#include <iostream>

namespace SpikeUtils
{
	class __declspec(dllexport) GUID final
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