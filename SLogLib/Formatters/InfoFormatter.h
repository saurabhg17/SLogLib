// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

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

	explicit InfoFormatter(NewLine newLine = NewLine::No)
		: AbstractFormatter(newLine)
	{}


	inline std::string formatMessage(const Message& msg) const override
	{
		if(msg.mLevel != MessageLevel::Info)
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
			_stream << std::setw(4) << msg.mDateTime.mYear         << "."
			        << std::setw(2) << msg.mDateTime.mMonth        << "."
			        << std::setw(2) << msg.mDateTime.mDay          << "-"
			        << std::setw(2) << msg.mDateTime.mHour         << ":"
					<< std::setw(2) << msg.mDateTime.mMinute       << ":"
					<< std::setw(2) << msg.mDateTime.mSecond       << ":"
					<< std::setw(3) << msg.mDateTime.mMilliseconds << ": ";
			
			size_t      _padSize = 25;
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
