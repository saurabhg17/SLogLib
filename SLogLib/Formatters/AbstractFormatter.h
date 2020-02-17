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

// The AbstractFormatter class is the base class of all formatters. Formatter is used by a 
// logging device to format a Message to std::string.
class AbstractFormatter
{
public:

	explicit AbstractFormatter(NewLine newLine = NewLine::No)
		: mNewLine(newLine)
	{}
	
	virtual ~AbstractFormatter() = default;
	
	// Format a message to std::string.
	virtual std::string FormatMessage(const Message& msg) const = 0;

	
protected:

	NewLine mNewLine;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_ABSTRACTFORMATTER_H_
