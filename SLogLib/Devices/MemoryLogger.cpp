// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/Devices/MemoryLogger.h"

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
MemoryLogger::MemoryLogger(AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter)
{
}
MemoryLogger::MemoryLogger(AbstractFormatter* formatter, const std::string& name) 
	: AbstractLoggingDevice(formatter, name)
{
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void MemoryLogger::_WriteMessage(const std::string& message)
{
	std::lock_guard<std::mutex> _lock(mMessagesMutex);
	mMessages.emplace_back(message);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
std::string MemoryLogger::Messages() const
{
	std::lock_guard<std::mutex> _lock(mMessagesMutex);

	std::stringstream _stream;
	for(const std::string& _message : mMessages)
	{
		_stream << _message;
	}
	return _stream.str();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
