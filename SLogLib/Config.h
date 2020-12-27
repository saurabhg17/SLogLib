// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_CONFIG_H_
#define _SLOGLIB_CONFIG_H_

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Find the operation system.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define SLOGLIB_OS_WIN32
#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
	#define SLOGLIB_OS_WIN64
#elif defined(__linux__) || defined(__linux)
	#define SLOGLIB_OS_LINUX
#elif defined(__APPLE__)
	#define SLOGLIB_OS_OSX
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Define a common flag for 32 and 64 bit windows.
#if defined(SLOGLIB_OS_WIN32) || defined(SLOGLIB_OS_WIN64)
	#define SLOGLIB_OS_WINDOWS
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
#if defined(SLOGLIB_OS_WINDOWS)
	#if defined(SLOGLIB_BUILD_DLL)
		#if defined(SLOGLIB_EXPORTS)
			#define SLOGLIB_DLL_API __declspec(dllexport)
		#else
			#define SLOGLIB_DLL_API __declspec(dllimport)
		#endif
	#else
		#define SLOGLIB_DLL_API
	#endif
#else
	#define SLOGLIB_DLL_API
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

#endif // _SLOGLIB_CONFIG_H_
