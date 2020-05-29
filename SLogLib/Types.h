// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_TYPES_H_
#define _SLOGLIB_TYPES_H_

#include "SLogLib/Config.h"
#include <string>

namespace SLogLib {
;

// Levels indicating severity of message.
enum class MessageLevel
{
	Info,
	Warn,
	Error,
	Debug,
	Detail
};

SLOGLIB_DLL_API std::string toString(const MessageLevel& messageLevel);


// Flag for inserting new line after every message.
enum class NewLine
{
	No  = 0,
	Yes = 1
};

// Flag to indicate when a file should be opened for writing.
enum class Open
{
	Immediately, FirstUse
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_TYPES_H_
