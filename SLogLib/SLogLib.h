
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

#ifndef _SLOGLIB_LOGGING_H_
#define _SLOGLIB_LOGGING_H_

#include "SLogLib/Config.h"
#include "SLogLib/LoggingManager.h"
#include "SLogLib/AddToCallStack.h"
#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include <sstream>
#include <string>

#if !defined(SLOGLIB_DISABLE_LOGGING)
	// The macro to write the message to all logging devices.
	// level is the message level.
	// msg is the message to write to logging devices.
	#define SLOGLIB_LOG_MESSAGE(level, msg)         \
	{                                                    \
		unsigned int _lineNo = __LINE__;                 \
		std::ostringstream __stream__unique__;           \
		__stream__unique__ << msg;                       \
		SLogLib::writeMessage(__FILE__,                  \
                              __FUNCTION__,              \
							  _lineNo,                   \
							  traceLevel,                \
							  __stream__unique__.str()); \
	}
	
	// Convenience macros to write the message at various levels.
	#define SLOGLIB_LOG_MSG_INFO(msg)   SLOGLIB_LOG_MESSAGE(SLogLib::MESSAGE_LEVEL_INFO   , msg);
	#define SLOGLIB_LOG_MSG_WARN(msg)   SLOGLIB_LOG_MESSAGE(SLogLib::MESSAGE_LEVEL_WARNING, msg);
	#define SLOGLIB_LOG_MSG_ERROR(msg)  SLOGLIB_LOG_MESSAGE(SLogLib::MESSAGE_LEVEL_ERROR  , msg);
	#define SLOGLIB_LOG_MSG_DEBUG(msg)  SLOGLIB_LOG_MESSAGE(SLogLib::MESSAGE_LEVEL_DEBUG  , msg);
	#define SLOGLIB_LOG_MSG_DETAIL(msg) SLOGLIB_LOG_MESSAGE(SLogLib::MESSAGE_LEVEL_DEBUG  , msg);
	
	// The macro to add the current function to the call stack.
	#define SLOGLIB_ADD_TO_CALLSTACK SLogLib::AddToCallStack \
	logger_unique_var_name##__LINE__(__FILE__, __FUNCTION__, __LINE__);
#else
	#define SLOGLIB_LOG_MESSAGE(traceLevel, msg)
	#define SLOGLIB_LOG_MSG_INFO(msg)
	#define SLOGLIB_LOG_MSG_WARN(msg)
	#define SLOGLIB_LOG_MSG_ERROR(msg)
	#define SLOGLIB_LOG_MSG_DEBUG(msg)
	#define SLOGLIB_LOG_MSG_DETAIL(msg)
	#define SLOGLIB_ADD_TO_CALLSTACK
#endif

namespace SLogLib {
;

// Add a new logging device.
SLOGLIB_DLL_API void addLoggingDevice(AbstractLoggingDevice* device);

// Remove a logging device.
SLOGLIB_DLL_API void removeLoggingDevice(AbstractLoggingDevice* device);
SLOGLIB_DLL_API void removeLoggingDevice(const std::string& name);

// Get a pointer to the logging device from name.
// Returned pointer must not be deleted or changed.
SLOGLIB_DLL_API AbstractLoggingDevice* queryLoggingDevice(const std::string& name);

// Write a message to all active logging devices.
SLOGLIB_DLL_API void writeMessage(const std::string& fileName, 
	                              const std::string& funcName,
								  unsigned int       lineNo,
								  unsigned int       level,
								  const std::string& msg);

// Disable and enable logging. These functions are useful when logging has to
// be enabled or disabled at runtime.
SLOGLIB_DLL_API void disableLogging();
SLOGLIB_DLL_API void enableLogging();
SLOGLIB_DLL_API bool isLoggingEnabled();

};	// End namespace SLogLib.

#endif // _SLOGLIB_LOGGINGMANAGER_H_
