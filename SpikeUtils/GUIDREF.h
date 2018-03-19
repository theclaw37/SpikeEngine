#pragma once

#include "GUID.h"

namespace SpikeUtils
{
	class __declspec(dllexport) GUIDREF
	{
	public:
		const std::string & _SpikeEngineId()
		{
			return _SpikeRef.Value();
		}
	private:
		SpikeUtils::GUID _SpikeRef = SpikeUtils::GUID::Generate();
	};
}
