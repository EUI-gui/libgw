#pragma once

#ifdef GW_STATIC
	#ifdef _WINDLL 
	#define GW_CORE_EXPORT __declspec(dllexport)
	#else 
	#define GW_CORE_EXPORT
	#endif
#else
#define GW_CORE_EXPORT __declspec(dllimport)
#endif // GW_STATIC

