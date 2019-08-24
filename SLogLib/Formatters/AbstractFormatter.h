
// This file is part of SLogLib; you can redistribute it and/or
// modify it under the terms of the MIT License.
// 
// Copyright (c) 2018 Saurabh Garg
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
