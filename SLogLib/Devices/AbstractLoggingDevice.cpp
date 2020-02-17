// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "AbstractLoggingDevice.h"
#include "SLogLib/SysUtils.h"
#include <atomic>
#include <cassert>
#include <iomanip>

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AbstractLoggingDevice::AbstractLoggingDevice(AbstractFormatter* formatter)
	: mFormatter(formatter), mIsEnabled(true), mIsBuffered(false), mBufferedMessagesCount(1000)
{
	assert(mFormatter);
	mBufferedMessages.reserve(mBufferedMessagesCount);

	static std::atomic_int _deviceID = 1;
	std::ostringstream _stream;
	_stream << "LoggingDevice_" << std::setfill('0') << std::setw(3) << _deviceID++;
	mName = _stream.str();
}
AbstractLoggingDevice::AbstractLoggingDevice(AbstractFormatter* formatter, const std::string& name)
	: mFormatter(formatter), mName(name), mIsEnabled(true), mIsBuffered(false), mBufferedMessagesCount(1000)
{
	assert(mFormatter);
	mBufferedMessages.reserve(mBufferedMessagesCount);
}
AbstractLoggingDevice::~AbstractLoggingDevice()
{
	delete mFormatter;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::WriteMessage(const Message& message)
{
	if(mIsEnabled)
	{
		std::string _formattedMessage = mFormatter->FormatMessage(message);
		if(mIsBuffered)
		{
			// Use a recursive lock as we need to lock again in _FlushBufferedMessages().
			std::lock_guard<std::recursive_mutex> _lock(mBufferedMessagesMutex);

			if(mBufferedMessages.size() < mBufferedMessagesCount)
			{
				mBufferedMessages.emplace_back(_formattedMessage);
			}
			if(mBufferedMessages.size() == mBufferedMessagesCount)
			{
				_FlushBufferedMessages();
			}
		}
		else
		{
			// Calls overridden _WriteMessage() in the child class.
			_WriteMessage(_formattedMessage);
		}
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::SetEnabled(bool x)
{
	mIsEnabled = x;
	
	// If a buffered device is disabled then existing messages should be written.
	if(mIsBuffered && !mIsEnabled)
	{
		_FlushBufferedMessages();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::SetBuffered(bool x)
{
	mIsBuffered = x;
	
	// If buffering is disabled then existing messages should be written.
	if(!mIsBuffered)
	{
		_FlushBufferedMessages();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::SetBufferedMessagesCount(size_t x)
{
	std::lock_guard<std::recursive_mutex> _lock(mBufferedMessagesMutex);
	mBufferedMessages.reserve(x);
	mBufferedMessagesCount = x;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::_WriteMessages(const std::vector<std::string>& messages)
{
	for(const std::string& _message : messages)
	{
		_WriteMessage(_message);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::_FlushBufferedMessages()
{
	std::lock_guard<std::recursive_mutex> _lock(mBufferedMessagesMutex);
	for(const std::string& _message : mBufferedMessages)
	{
		_WriteMessage(_message);
	}
	mBufferedMessages.clear();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
