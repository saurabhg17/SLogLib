
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

#ifndef _SLOGLIB_MESSAGE_H_
#define _SLOGLIB_MESSAGE_H_

#include "SLogLib/CallInfo.h"
#include "SLogLib/SysUtils.h"
#include <string>

namespace SLogLib {
;

// Levels indicating severity of message.
const int MESSAGE_LEVEL_INFO    = 1;  // For logging general information.
const int MESSAGE_LEVEL_WARNING = 2;  // For logging warnings.
const int MESSAGE_LEVEL_ERROR   = 4;  // For logging error messages.
const int MESSAGE_LEVEL_DEBUG   = 8;  // For logging debugging information.
const int MESSAGE_LEVEL_DETAIL  = 16; // For logging detailed debugging information.

// The Message structure stores a message to be logged.
struct Message
{
	std::string  mUserMessage;
	DateTime     mDateTime;
	unsigned int mLevel;
	CallStack*   mCallStack; // Don't delete; owned by LoggingManager.
	unsigned int mProcessId;
	unsigned int mThreadId;
	
	Message()
		: mLevel(MESSAGE_LEVEL_INFO), mCallStack(0), mProcessId(0), mThreadId(0)
	{}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_MESSAGE_H_
