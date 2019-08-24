// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "AbstractLoggingDevice.h"
#include "SLogLib/SysUtils.h"
#include <cassert>

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AbstractLoggingDevice::AbstractLoggingDevice(AbstractFormatter* formatter)
	: mFormatter(formatter), mIsEnabled(true), mIsBuffered(false), mBufferedMessagesCount(1000)
{
	assert(mFormatter);
	static int _deviceID = 1;
	mName = "LoggingDevice" + SLogLib::toString(_deviceID++);
	mBufferedMessages.reserve(mBufferedMessagesCount);
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
	if(x > mBufferedMessagesCount)
	{
		mBufferedMessages.reserve(x);
	}
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
	_WriteMessages(mBufferedMessages);
	mBufferedMessages.clear();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
