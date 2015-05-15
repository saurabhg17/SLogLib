
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

#ifndef _SLOGLIB_ERRORFORMATTER_H_
#define _SLOGLIB_ERRORFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include <sstream>
#include <iomanip>

namespace SLogLib {
;

// The ErrorFormatter class formats only error messages and ignores all other messages.
// A message is formatted as: 
// Time       : Year-Month-Day Hour:Minutes:Seconds:Millisecond
// FileName   : 
// FuncName   : 
// Line No.   : 
// Message    : message line 1
//              message line 2
//              .
//              .
class ErrorFormatter : public AbstractFormatter
{
public:
	
	inline std::string FormatMessage(const Message& msg) const
	{
		if(msg.mLevel != MESSAGE_LEVEL_ERROR)
		{
			return "";
		}
		
		std::ostringstream _stream;
		_stream.fill('0');
		_stream.width(2);
		
		if(msg.mUserMessage == "\n")
		{
			_stream << std::endl;
		}
		else
		{
			_stream << "Time       : " << msg.mDateTime.mYear         << "-"
				                       << msg.mDateTime.mMonth        << "-"
									   << msg.mDateTime.mDay          << " "
									   << msg.mDateTime.mHour         << ":"
									   << msg.mDateTime.mMinute       << ":"
									   << msg.mDateTime.mSecond       << ":"
									   << msg.mDateTime.mMilliseconds << std::endl;
			
			CallInfo _callInfo = (*msg.mCallStack)[msg.mCallStack->size()-1];
			_stream << "FileName   : " << _callInfo.mFileName   << std::endl;
			_stream << "FuncName   : " << _callInfo.mFuncName   << std::endl;
			_stream << "Line No.   : " << _callInfo.mLineNumber << std::endl;
			
			std::string _temp = msg.mUserMessage;
			size_t      _loc   = _temp.find("\n");
			while(_loc != std::string::npos)
			{
				_temp.insert(_loc+1, "          ");
				_loc = _temp.find("\n", _loc + 10);
			}
			
			_stream << "Message    : " << _temp << std::endl << std::endl;
		}
		
		return _stream.str();
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_ERRORFORMATTER_H_