
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

#ifndef SLOGLIB_SYSUTILS_H_
#define SLOGLIB_SYSUTILS_H_

#include "SLogLib/Config.h"
#include <string>
#include <sstream>

namespace SLogLib {
;

// The DateTime structure stores date and time.
struct DateTime
{
	unsigned short mYear;
	unsigned short mMonth;
	unsigned short mDayOfWeek;
	unsigned short mDay;
	unsigned short mHour;
	unsigned short mMinute;
	unsigned short mSecond;
	unsigned short mMilliseconds;
	
	DateTime() 
		: mYear(0), mMonth(0), mDayOfWeek(0), mDay(0), mHour(0), mMinute(0), 
		  mSecond(0), mMilliseconds(0)
	{}
};

// Sleep the current thread for specified milliseconds.
SLOGLIB_DLL_API void sleep(unsigned int msec);

// Get the ID of the current process.
SLOGLIB_DLL_API unsigned int getCurrentProcessID();

// Get the ID of the current thread.
SLOGLIB_DLL_API unsigned int getCurrentThreadID();

// Get the current local date and time.
SLOGLIB_DLL_API DateTime getLocalDateTime();


// Convert a type to string; the type must support std::ostringstream operator.
template<class T>
inline std::string toString(const T& x)
{
	std::ostringstream _stream;
	_stream << x;
	return _stream.str();
}

};	// End namespace SLogLib.

#endif // SLOGLIB_SYSUTILS_H_
