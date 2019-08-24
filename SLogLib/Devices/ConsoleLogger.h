
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
