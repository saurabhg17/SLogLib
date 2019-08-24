
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

#ifndef _SLOGLIB_INFOFORMATTER_H_
#define _SLOGLIB_INFOFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include <sstream>
#include <iomanip>

namespace SLogLib {
;

// The InfoFormatter class formats only informational messages and ignores all other messages.
// A message is formatted as: 
// Hour:Minutes:Seconds:Millisecond    message line 1
//                                     message line 2
//                                     .
//                                     .
class InfoFormatter : public AbstractFormatter
{
public:

	explicit InfoFormatter(NewLineFlag newLineFlag = DoNotAppendNewLine)
		: AbstractFormatter(newLineFlag)
	{}


	inline std::string FormatMessage(const Message& msg) const override
	{
		if(msg.mLevel != eLevelInfo)
		{
			return "";
		}
		
		std::ostringstream _stream;
		_stream.fill('0');
		_stream.width(2);
		
		// Newlines are written as new lines without date time.
		if(msg.mUserMessage == "\n")
		{
			_stream << std::endl;
		}
		else
		{
			_stream.fill('0');
			_stream << std::setw(2) << msg.mDateTime.mHour         << ":"
					<< std::setw(2) << msg.mDateTime.mMinute       << ":"
					<< std::setw(2) << msg.mDateTime.mSecond       << ":"
					<< std::setw(3) << msg.mDateTime.mMilliseconds << "    ";
			
			size_t      _padSize = 16;
			std::string _temp    = msg.mUserMessage;
			size_t      _loc     = _temp.find("\n");
			while(_loc != std::string::npos)
			{
				_temp.insert(_loc+1, _padSize, ' ');
				_loc = _temp.find("\n", _loc + _padSize);
			}
			_stream << _temp << std::endl;
		}
		
		return _stream.str();
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_INFOFORMATTER_H_
