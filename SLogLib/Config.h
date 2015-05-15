
// This file is part of SLogLib; you can redistribute it and/or
// modify it under the terms of the MIT License.
// 
// Copyright (c) 2015 Saurabh Garg
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
// Author(s): Saurabh Garg

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
	#if defined(SLOGLIB_EXPORTS)
		#define SLOGLIB_DLL_API __declspec(dllexport)
	#else
		#define SLOGLIB_DLL_API __declspec(dllimport)
	#endif
#else
	#define SLOGLIB_DLL_API
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

#endif // _SLOGLIB_CONFIG_H_
