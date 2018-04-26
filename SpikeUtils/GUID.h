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
		bool operator==(GUID const& other) const;
		operator std::string() const;

		static GUID Generate();
		static GUID Parse(std::string const &);
		std::string const & Value() const;
	private:
		GUID(std::string const & value) : value(value) {}
		std::string value;
	};
}

namespace std 
{
	template <>
	struct hash<SpikeUtils::GUID>
	{
		size_t operator()(SpikeUtils::GUID const & ref) const
		{
			return hash<std::string>()(ref.Value());
		}
	};
}