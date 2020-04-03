// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/Devices/MemoryLogger.h"

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
struct MemoryLoggerPriv
{
	std::list<std::string> mMessages;
	mutable std::mutex     mMessagesMutex;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
MemoryLogger::MemoryLogger(AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter)
{
	mPriv = new MemoryLoggerPriv;
}
MemoryLogger::MemoryLogger(AbstractFormatter* formatter, const std::string& name) 
	: AbstractLoggingDevice(formatter, name)
{
	mPriv = new MemoryLoggerPriv;
}
MemoryLogger::~MemoryLogger()
{
	delete mPriv;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
const std::list<std::string>& MemoryLogger::MessageList() const
{
	return mPriv->mMessages;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void MemoryLogger::_WriteMessage(const std::string& message)
{
	std::lock_guard<std::mutex> _lock(mPriv->mMessagesMutex);
	mPriv->mMessages.emplace_back(message);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
std::string MemoryLogger::Messages() const
{
	std::lock_guard<std::mutex> _lock(mPriv->mMessagesMutex);

	std::stringstream _stream;
	for(const std::string& _message : mPriv->mMessages)
	{
		_stream << _message;
	}
	return _stream.str();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
