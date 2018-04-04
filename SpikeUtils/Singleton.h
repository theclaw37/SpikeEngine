#pragma once

#ifdef DLL_SPIKEUTILS
#define SPIKEUTILS_EXPORT __declspec(dllexport)
#else
#define SPIKEUTILS_EXPORT __declspec(dllexport)
#endif

namespace SpikeUtils
{
	template<typename T>
	class SPIKEUTILS_EXPORT Singleton
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
		virtual ~Singleton() = default;
	};
}