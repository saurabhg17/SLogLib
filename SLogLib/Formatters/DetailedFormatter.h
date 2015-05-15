
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

#ifndef _SLOGLIB_DETAILEDFORMATTER_H_
#define _SLOGLIB_DETAILEDFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include <sstream>
#include <iomanip>

namespace SLogLib {
;

// The DetailedFormatter class formats all messages. A message is formatted as: 
// Msg Level  : 
// Time       : Year-Month-Day Hour:Minutes:Seconds:Millisecond
// Process ID : 
// Thread ID  : 
// FileName   : 
// FuncName   : 
// Line No.   : 
// CallStack  : FileName : FunctionName [Line number]
//              FileName : FunctionName [Line number]
//              .
//              .
// Message    : message line 1
//              message line 2
//              .
//              .
class DetailedFormatter : public AbstractFormatter
{
public:
	
	inline std::string FormatMessage(const Message& msg) const
	{
		size_t _size = msg.mCallStack->size();
		CallInfo _callInfo;
		_callInfo = (*msg.mCallStack)[_size-1];
		
		std::ostringstream _stream;
		_stream << "Msg Level  : " << msg.mLevel                  << std::endl;
		_stream << "Time       : " << msg.mDateTime.mYear         << "-"
			                       << msg.mDateTime.mMonth        << "-"
								   << msg.mDateTime.mDay          << " "
								   << msg.mDateTime.mHour         << ":"
								   << msg.mDateTime.mMinute       << ":"
								   << msg.mDateTime.mSecond       << ":"
								   << msg.mDateTime.mMilliseconds << std::endl;
		_stream << "Process ID : " << msg.mProcessId              << std::endl;
		_stream << "Thread ID  : " << msg.mThreadId               << std::endl;
		_stream << "FileName   : " << _callInfo.mFileName         << std::endl;
		_stream << "FuncName   : " << _callInfo.mFuncName         << std::endl;
		_stream << "Line No.   : " << _callInfo.mLineNumber       << std::endl;
		_stream << "CallStack  : ";
		
		for(size_t i=0 ; i<msg.mCallStack->size() ; ++i)
		{
			CallInfo _callInfo = (*msg.mCallStack)[i];
			
			if(i==0)
			{
				_stream << _callInfo.mFileName;
			}
			else
			{
				_stream << "             " << _callInfo.mFileName;
			}
			_stream << " : " << _callInfo.mFuncName;
			_stream << " [" << _callInfo.mLineNumber << "]" << std::endl;
		}
		
		_stream << "Message    : " << msg.mUserMessage << std::endl << std::endl;
		return _stream.str();
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_DETAILEDFORMATTER_H_