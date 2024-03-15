#pragma once

#if defined(NG_PLATFORM_LINUX)
	#if defined(NG_DEBUG)
		#define NG_ENABLE_ASSERTS
		#include <signal.h>
		#define NG_DEBUGBREAK() raise(SIGTRAP)
	#else
		#define NG_DEBUGBREAK() 
	#endif

	#if defined(NG_BUILD_SHARED)
		#define NG_API __attribute__ ((visibility ("default")))
	#else
		#define NG_API
	#endif
#elif defined(NG_PLATFORM_WINDOWS)
	#if defined(NG_DEBUG)
		#define NG_ENABLE_ASSERTS
		#define NG_DEBUGBREAK() __debugbreak()
	#else
		#define NG_DEBUGBREAK() 
	#endif

	#if defined(NG_BUILD_SHARED)
		#define NG_API __declspec(dllexport)
	#else
		#define NG_API __declspec(dllimport)
	#endif
#else
	#error "Unsupported platform!"
#endif

