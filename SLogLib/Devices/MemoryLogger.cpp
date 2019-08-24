// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/Devices/MemoryLogger.h"
#include "SLogLib/SysUtils.h"

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
MemoryLogger::MemoryLogger(AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter)
{
	DisableBuffering();
}
MemoryLogger::MemoryLogger(AbstractFormatter* formatter, const std::string& name) 
	: AbstractLoggingDevice(formatter, name)
{
	DisableBuffering();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void MemoryLogger::_WriteMessage(const std::string& message)
{
	mMessages.emplace_back(message);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
std::string MemoryLogger::allMessages() const
{
	std::stringstream _stream;
	for(const std::string& _message : mMessages)
	{
		_stream << _message;
	}
	return _stream.str();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
