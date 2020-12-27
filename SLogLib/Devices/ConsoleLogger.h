// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_CONSOLELOGGER_H_
#define _SLOGLIB_CONSOLELOGGER_H_

#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include <iostream>

namespace SLogLib {
;

// The ConsoleLogger class writes the logging messages to a console (stdout).
class ConsoleLogger : public AbstractLoggingDevice
{
public:
	
	explicit ConsoleLogger(AbstractFormatter* formatter) 
		: ConsoleLogger(formatter, "")
	{}
	ConsoleLogger(AbstractFormatter* formatter, const std::string& name) 
		: AbstractLoggingDevice(formatter, name)
	{}
	
	~ConsoleLogger()
	{
		_FlushBufferedMessages();
	}
	
	
protected:
	
	inline void _WriteMessage(const std::string& message) override
	{
		// std::cout is thread-safe in the sense that its internal buffers are not
		// corrupted when called from multiple threads. However, the order in which
		// messages are printed is indeterminate.
		std::cout << message;
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_CONSOLELOGGER_H_
