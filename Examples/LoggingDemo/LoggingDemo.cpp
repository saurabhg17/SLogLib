// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/SLogLib"
#include "SLogLib/LoggingManager.h"

int main()
{
	// Add these lines at the beginning of your program.
	// The devices and formatters are automatically deleted by SLogLib.
	using namespace SLogLib;
	addLoggingDevice(new ConsoleLogger(new NullFormatter));
	addLoggingDevice(new FileLogger("foo.log", Open::Immediately, new DetailedFormatter));
	
	// The following line writes the message to both console and file.
	int a = 10;
	double b = 15.3;
	const char* c = "Success";
	SLOGLIB_LOG_MSG_INFO("a = " << a << " b = " << b);
	SLOGLIB_LOG_MSG_INFO(c);
	
	return 0;
}
