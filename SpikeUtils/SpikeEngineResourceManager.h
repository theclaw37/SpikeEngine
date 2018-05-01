#pragma once

#include <memory>

namespace SpikeUtils
{
	class ResourceManager
	{
	public:
		template <typename ResourceType, typename ... ResourceArgs>
		static std::shared_ptr<ResourceType> RegisterResource(ResourceArgs ... args)
		{
			auto pointer = std::make_shared<ResourceType>(ResourceType(args...));
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
	};
}