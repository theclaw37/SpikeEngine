#pragma once

#ifdef DLL_SPIKEUTILS
#define SPIKEUTILS_EXPORT __declspec(dllexport)
#else
#define SPIKEUTILS_EXPORT __declspec(dllimport)
#endif

#include "GUID.h"
#include "SpikeEngineResourceManager.h"
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace SpikeUtils
{
	template <typename ResourceType>
	class _SpikeEngineResource
	{
		friend class ResourceManager;

	public:
		_SpikeEngineResource() : _SpikeRef(SpikeUtils::GUID::Generate()) {}

		const SpikeUtils::GUID & _SpikeResourceId() const
		{
			return _SpikeRef;
		}

		bool operator==(_SpikeEngineResource const &) = delete;
		virtual bool operator==(ResourceType const &) const = 0;

		virtual ~_SpikeEngineResource() = default;
	private:
		static std::unordered_set<std::shared_ptr<ResourceType>> _SEResources;
		static std::unordered_map<SpikeUtils::GUID, std::shared_ptr<ResourceType>> _SEResourcesById;
		SpikeUtils::GUID _SpikeRef;
	};

	template <typename ResourceType>
	std::unordered_set<std::shared_ptr<ResourceType>> _SpikeEngineResource<ResourceType>::_SEResources;

	template <typename ResourceType>
	std::unordered_map<SpikeUtils::GUID, std::shared_ptr<ResourceType>> _SpikeEngineResource<ResourceType>::_SEResourcesById;
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
