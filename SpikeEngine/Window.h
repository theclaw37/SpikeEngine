#pragma once

#include "Engine.h"

namespace SpikeEngine
{
	class Window
	{
	public:
		Window();

		const UINT GetClientWidth();
		const UINT GetClientHeight();

	private:
		UINT _clientWidth = 0, _clientHeight = 0;
	};
}