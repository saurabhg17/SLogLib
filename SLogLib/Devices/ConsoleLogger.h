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

// The ConsoleLogger class writes the logging messages to a console (STDOUT).
class ConsoleLogger : public AbstractLoggingDevice
{
public:
	
	explicit ConsoleLogger(AbstractFormatter* formatter) 
		: AbstractLoggingDevice(formatter) {}
	explicit ConsoleLogger(AbstractFormatter* formatter, const std::string& name) 
		: AbstractLoggingDevice(formatter, name) {}


protected:
	
	inline void _WriteMessage(const std::string& message) override
	{
		std::cout << message;
	}
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_CONSOLELOGGER_H_
