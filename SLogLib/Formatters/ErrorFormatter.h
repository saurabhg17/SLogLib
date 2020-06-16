// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

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

	explicit ErrorFormatter(NewLine newLine = NewLine::No)
		: AbstractFormatter(newLine)
	{}


	inline std::string formatMessage(const Message& msg) const override
	{
		if(msg.mLevel != MessageLevel::Error)
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
			
			const CallInfo _callInfo = (*msg.mCallStack)[msg.mCallStack->size()-1];
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
