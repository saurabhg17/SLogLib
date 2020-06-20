// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_MESSAGE_H_
#define _SLOGLIB_MESSAGE_H_

#include "SLogLib/CallInfo.h"
#include "SLogLib/SysUtils.h"
#include "SLogLib/Types.h"
#include <string>

namespace SLogLib {
;

// The Message structure stores a message to be logged.
struct Message
{
	std::string  mUserMessage;
	DateTime     mDateTime;
	MessageLevel mLevel;
	CallStack*   mCallStack; // Don't delete; owned by LoggingManager.
	unsigned int mProcessId;
	unsigned int mThreadId;
	
	Message() noexcept
		: mLevel(MessageLevel::Info), mCallStack(nullptr), mProcessId(0), mThreadId(0)
	{}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_MESSAGE_H_
