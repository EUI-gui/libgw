#pragma once

#ifdef GW_STATIC
	#ifdef _WINDLL 
		#define GW_CORE_EXPORT __declspec(dllexport)
	#else 
		#define GW_CORE_EXPORT
	#endif
#else
	#ifdef _WINDLL 
		#define GW_CORE_EXPORT __declspec(dllimport)
	#else
		#define GW_CORE_EXPORT 
	#endif // _WINDLL 

#endif // GW_STATIC

