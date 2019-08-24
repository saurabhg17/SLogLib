// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_NULLFORMATTER_H_
#define _SLOGLIB_NULLFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include <sstream>

namespace SLogLib {
;

// The NullFormatter class simply returns the user message and ignores all other fields in the 
// message.
// By default NullFormatter doest insert new line after the message. To insert new lines after
// each message pass true to the constructor.
class NullFormatter : public AbstractFormatter
{
public:
	
	explicit NullFormatter(NewLineFlag newLineFlag = DoNotAppendNewLine)
		: AbstractFormatter(newLineFlag)
	{}

	inline std::string FormatMessage(const Message& msg) const override
	{
		if(mNewLineFlag == AppendNewLine)
		{
			std::ostringstream _stream;
			_stream << msg.mUserMessage << std::endl;
			return _stream.str();
		}
		else
		{
			return msg.mUserMessage;
		}
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_NULLFORMATTER_H_
