#pragma once

namespace SpikeUtils
{
	template<typename T>
	class __declspec(dllexport) Singleton
	{
	public:
		static T & Instance()
		{
			static T instance;
			return instance;
		}

		Singleton(Singleton const&) = delete;
		void operator=(Singleton const&) = delete;
	protected:
		Singleton() = default;
	};
}