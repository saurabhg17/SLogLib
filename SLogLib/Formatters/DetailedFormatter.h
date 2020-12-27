// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_DETAILEDFORMATTER_H_
#define _SLOGLIB_DETAILEDFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include "SLogLib/SysUtils.h"
#include <sstream>
#include <iomanip>

namespace SLogLib {
;

// The DetailedFormatter class formats messages at all levels. A message is formatted as: 
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
	
	explicit DetailedFormatter(NewLine newLine = NewLine::No) noexcept
		: AbstractFormatter(newLine)
	{}
	
	
	inline std::string formatMessage(const Message& msg) const override
	{
		size_t         _size     = msg.mCallStack->size();
		const CallInfo _callInfo = (*msg.mCallStack)[_size-1];
		
		std::ostringstream _stream;
		_stream << "Msg Level  : " << toInteger(msg.mLevel)       << std::endl;
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
			const CallInfo _callInfo1 = (*msg.mCallStack)[i];
			
			if(i==0)
			{
				_stream << _callInfo1.mFileName;
			}
			else
			{
				_stream << "             " << _callInfo1.mFileName;
			}
			_stream << " : " << _callInfo1.mFuncName;
			_stream << " [" << _callInfo1.mLineNumber << "]" << std::endl;
		}
		
		_stream << "Message    : " << msg.mUserMessage << std::endl << std::endl;
		return _stream.str();
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_DETAILEDFORMATTER_H_
