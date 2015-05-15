
// Copyright (c) 2015 Saurabh Garg
// 
// This file is part of SLogLib; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License v2.1 as
// published by the Free Software Foundation.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Author(s): Saurabh Garg

#include "SLogLib/SLogLib"

int main()
{
	// Add these lines at the beginning of your program.
	// The devices and formatters are automatically deleted by SLogLib.
	using namespace SLogLib;
	addLoggingDevice(new ConsoleLogger(new NullFormatter));
	addLoggingDevice(new FileLogger("foo.log", new DetailedFormatter));	
	
	// The following line writes the message to both console and file.
	int a = 10;
	double b = 15.3;
	const char* c = "Success";
	SLOGLIB_LOG_MSG_INFO("a = " << a << " b = " << b);
	SLOGLIB_LOG_MSG_INFO(c);
	
	unsigned int a1 = MESSAGE_LEVEL_INFO;
	unsigned int a2 = MESSAGE_LEVEL_WARNING;
	unsigned int a3 = MESSAGE_LEVEL_ERROR;
	unsigned int a4 = MESSAGE_LEVEL_DEBUG;
	unsigned int a5 = MESSAGE_LEVEL_DETAIL;

	return 0;
}
