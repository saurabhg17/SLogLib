// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_ABSTRACTFORMATTER_H_
#define _SLOGLIB_ABSTRACTFORMATTER_H_

#include "SLogLib/Message.h"
#include "SLogLib/Types.h"
#include <string>

namespace SLogLib {
;

///! The AbstractFormatter class is the base class of all formatters. A formatter formats a 
///! Message to a std::string. A logging device uses a formatter to format a message.
class AbstractFormatter
{
public:

	explicit AbstractFormatter(NewLineFlag newLineflag = DoNotAppendNewLine)
		: mNewLineFlag(newLineflag)
	{}
	
	virtual ~AbstractFormatter() = default;
	
	///! Format a message to std::string.
	virtual std::string FormatMessage(const Message& msg) const = 0;

	
protected:

	NewLineFlag mNewLineFlag;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_ABSTRACTFORMATTER_H_
