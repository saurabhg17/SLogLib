// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

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
