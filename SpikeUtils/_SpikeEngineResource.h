#pragma once

#ifdef DLL_SPIKEUTILS
#define SPIKEUTILS_EXPORT __declspec(dllexport)
#else
#define SPIKEUTILS_EXPORT __declspec(dllimport)
#endif

#include "GUID.h"
#include <unordered_map>

namespace SpikeUtils
{
	template <class ResourceType>
	class _SpikeEngineResource
	{
	public:
		_SpikeEngineResource() : _SpikeRef(SpikeUtils::GUID::Generate()) {}

		const std::string & _SpikeResourceId() const
		{
			return _SpikeRef.Value();
		}

		bool operator==(_SpikeEngineResource const &) = delete;
		virtual bool operator==(ResourceType const &) const = 0;

		virtual ~_SpikeEngineResource() = default;
	private:
		SpikeUtils::GUID _SpikeRef;
	};
}

namespace std 
{
	template <class ResourceType>
	struct hash<SpikeUtils::_SpikeEngineResource<ResourceType>>
	{
		size_t operator()(SpikeUtils::_SpikeEngineResource const & ref) const
		{
			return hash<ResourceType>()(static_cast<ResourceType const &>(ref));
		}
	};
}
