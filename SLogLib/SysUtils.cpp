// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SysUtils.h"
#ifdef SLOGLIB_OS_WINDOWS
	#include <Windows.h>
#elif defined(SLOGLIB_OS_LINUX) || defined(SLOGLIB_OS_OSX)
	#include <time.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <unistd.h>
#endif

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void sleep(unsigned int msec)
{
#ifdef SLOGLIB_OS_WINDOWS
	Sleep(msec);
#elif defined(SLOGLIB_OS_LINUX) || defined(SLOGLIB_OS_OSX)
	if(msec == 0)
	{
		msec = 10;
	}
	struct timespec _req = {msec/1000, (msec%1000)*1000*1000};
	while(nanosleep(&_req, &_req) == -1)
	{
		continue;
	}
#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
unsigned int getCurrentProcessID() noexcept
{
#if defined(SLOGLIB_OS_WINDOWS)
	return ::GetCurrentProcessId();
#elif defined(SLOGLIB_OS_LINUX) || defined(SLOGLIB_OS_OSX)
	return getpid();
#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
unsigned int getCurrentThreadID() noexcept
{
#if defined(SLOGLIB_OS_WINDOWS)
	return ::GetCurrentThreadId();
#elif defined(SLOGLIB_OS_LINUX) || defined(SLOGLIB_OS_OSX)
	return 0; // gettid();
#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
DateTime getLocalDateTime() noexcept
{
	DateTime _dateTime;
	#if defined(SLOGLIB_OS_WINDOWS)
		SYSTEMTIME __dateTime;
		memset(&__dateTime, 0, sizeof(SYSTEMTIME));
		GetLocalTime(&__dateTime);
		_dateTime.mYear         = __dateTime.wYear;
		_dateTime.mMonth        = __dateTime.wMonth;
		_dateTime.mDayOfWeek    = __dateTime.wDayOfWeek;
		_dateTime.mDay          = __dateTime.wDay;
		_dateTime.mHour         = __dateTime.wHour;
		_dateTime.mMinute       = __dateTime.wMinute;
		_dateTime.mSecond       = __dateTime.wSecond;
		_dateTime.mMilliseconds = __dateTime.wMilliseconds;
	#elif defined(SLOGLIB_OS_LINUX) || defined(SLOGLIB_OS_OSX)
		// Get the seconds and microseconds elapsed since Jan 1 1970 in UTC.
		struct timeval _utcTime;
		gettimeofday(&_utcTime, 0);
		
		// Convert to the local time.
		tm* _localTime = localtime(&_utcTime.tv_sec);
		_dateTime.mYear         = _localTime->tm_year+1900;
		_dateTime.mMonth        = _localTime->tm_mon+1;
		_dateTime.mDayOfWeek    = _localTime->tm_wday;
		_dateTime.mDay          = _localTime->tm_mday;
		_dateTime.mHour         = _localTime->tm_hour;
		_dateTime.mMinute       = _localTime->tm_min;
		_dateTime.mSecond       = _localTime->tm_sec;
		_dateTime.mMilliseconds = _utcTime.tv_usec/1000.0;
	#endif
	return _dateTime;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};
