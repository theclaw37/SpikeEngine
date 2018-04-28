#pragma once

#include <memory>

namespace SpikeUtils
{
	class SpikeResourceManager
	{
	public:
		template <typename ResourceType>
		static std::shared_ptr<ResourceType> RegisterResource(ResourceType & resource)
		{
			auto pointer = std::make_shared<ResourceType>(resource);
			if (pointer)
			{
				auto result = _SpikeEngineResource<ResourceType>::_SEResources.insert(pointer);
				if (result.second)
				{
					_SpikeEngineResource<ResourceType>::_SEResourcesById.insert({
						pointer->_SpikeResourceId(),
						pointer
						});
				}
				if (!result.second)
				{
					pointer = *(result.first);
				}
			}

			return pointer;
		}

		template <typename ResourceType>
		static std::shared_ptr<ResourceType> RetrieveResource(SpikeUtils::GUID const & guid)
		{
			auto search = _SpikeEngineResource<ResourceType>::_SEResourcesById.find(guid);
			if (search != _SpikeEngineResource<ResourceType>::_SEResourcesById.end())
				return search->second;

			return nullptr;
		}
	};
}