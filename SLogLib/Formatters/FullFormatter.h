// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_FULLFORMATTER_H_
#define _SLOGLIB_FULLFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include <sstream>
#include <iomanip>

namespace SLogLib {
;

// The FullFormatter class formats only all messages.
// A message is formatted as: 
// Time	ThreadID	Message
// Entries are tab separated.
// Time is formatted as: Year-Month-Day Hour:Minutes:Seconds:Millisecond
class FullFormatter : public AbstractFormatter
{
public:

	explicit FullFormatter() : AbstractFormatter(NewLine::No)
	{}
	
	
	inline std::string FormatMessage(const Message& msg) const override
	{
		std::ostringstream _stream;
		_stream.fill('0');
		_stream.width(2);
		
		if(msg.mUserMessage == "\n")
		{
			_stream << std::endl;
		}
		else
		{
			_stream << msg.mDateTime.mYear         << "-"
			        << msg.mDateTime.mMonth        << "-"
					<< msg.mDateTime.mDay          << "T"
					<< msg.mDateTime.mHour         << ":"
					<< msg.mDateTime.mMinute       << ":"
					<< msg.mDateTime.mSecond       << ":"
					<< msg.mDateTime.mMilliseconds << "\t"
					<< msg.mThreadId               << "\t"
					<< msg.mUserMessage            << std::endl;
		}
		
		return _stream.str();
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_FULLFORMATTER_H_
