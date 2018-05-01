#pragma once

#include <memory>
#include <unordered_map>

namespace SpikeUtils
{
	template <typename TFrom, typename TTo>
	class ResourceMapping
	{
	public:
		static std::shared_ptr<TTo> RegisterResource(
			std::shared_ptr<TFrom> from,
			std::shared_ptr<TTo> to)
		{
			_RTRMap[from] = to;
			return _RTRMap[from];
		}

		static std::shared_ptr<TTo> const RetrieveResource(
			std::shared_ptr<TFrom> from)
		{
			return _RTRMap[from];
		}
	private:
		static std::unordered_map<std::shared_ptr<TFrom>, std::shared_ptr<TTo>> _RTRMap;
	};

	template <typename TFrom, typename TTo>
	std::unordered_map<std::shared_ptr<TFrom>, std::shared_ptr<TTo>> ResourceMapping<TFrom, TTo>::_RTRMap;
}