#pragma once

#if defined(NG_PLATFORM_LINUX)
	#if defined(NG_BUILD_SHARED)
		#define NG_API __attribute__ ((visibility ("default")))
	#else
		#define NG_API
	#endif
#elif defined(NG_PLATFORM_WINDOWS)
	#if defined(NG_BUILD_SHARED)
		#define NG_API __declspec(dllexport)
	#else
		#define NG_API __declspec(dllimport)
	#endif
#else
	#error "Unsupported platform!"
#endif

