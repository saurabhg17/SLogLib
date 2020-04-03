// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "AbstractLoggingDevice.h"
#include "SLogLib/SysUtils.h"
#include <mutex>
#include <atomic>
#include <cassert>
#include <iomanip>

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
struct AbstractLoggingDevicePriv
{
	AbstractLoggingDevicePriv(AbstractFormatter* formatter)
		: mFormatter(formatter), mIsEnabled(true), mIsBuffered(false), mBufferedMessagesCount(1000)
	{
		assert(mFormatter);
		mBufferedMessages.reserve(mBufferedMessagesCount);

		static std::atomic_int _deviceID = 1;
		std::ostringstream _stream;
		_stream << "LoggingDevice_" << std::setfill('0') << std::setw(3) << _deviceID++;
		mName = _stream.str();
	}

	AbstractLoggingDevicePriv(AbstractFormatter* formatter, const std::string& name)
		: mFormatter(formatter), mName(name), mIsEnabled(true), mIsBuffered(false), mBufferedMessagesCount(1000)
	{
		assert(mFormatter);
		mBufferedMessages.reserve(mBufferedMessagesCount);
	}

	AbstractLoggingDevicePriv::~AbstractLoggingDevicePriv()
	{
		delete mFormatter;
	}

	AbstractFormatter*       mFormatter;
	std::string              mName;
	bool                     mIsEnabled;             // Default: true
	bool                     mIsBuffered;            // Default: false
	size_t                   mBufferedMessagesCount; // Default: 1000
	std::vector<std::string> mBufferedMessages;
	std::recursive_mutex     mBufferedMessagesMutex;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AbstractLoggingDevice::AbstractLoggingDevice(AbstractFormatter* formatter)
{
	mPriv = new AbstractLoggingDevicePriv(formatter);
}
AbstractLoggingDevice::AbstractLoggingDevice(AbstractFormatter* formatter, const std::string& name)
{
	mPriv = new AbstractLoggingDevicePriv(formatter, name);
}
AbstractLoggingDevice::~AbstractLoggingDevice()
{
	delete mPriv;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
std::string AbstractLoggingDevice::Name() const
{
	return mPriv->mName;
}
bool AbstractLoggingDevice::IsEnabled() const
{
	return mPriv->mIsEnabled;
}
bool AbstractLoggingDevice::IsBuffered() const
{
	return mPriv->mIsBuffered;
}
size_t AbstractLoggingDevice::BufferedMessagesCount() const
{
	return mPriv->mBufferedMessagesCount;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::WriteMessage(const Message& message)
{
	if(mPriv->mIsEnabled)
	{
		std::string _formattedMessage = mPriv->mFormatter->FormatMessage(message);
		if(mPriv->mIsBuffered)
		{
			// Use a recursive lock as we need to lock again in _FlushBufferedMessages().
			std::lock_guard<std::recursive_mutex> _lock(mPriv->mBufferedMessagesMutex);

			if(mPriv->mBufferedMessages.size() < mPriv->mBufferedMessagesCount)
			{
				mPriv->mBufferedMessages.emplace_back(_formattedMessage);
			}
			if(mPriv->mBufferedMessages.size() == mPriv->mBufferedMessagesCount)
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
	mPriv->mIsEnabled = x;
	
	// If a buffered device is disabled then existing messages should be written.
	if(mPriv->mIsBuffered && !mPriv->mIsEnabled)
	{
		_FlushBufferedMessages();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::SetBuffered(bool x)
{
	mPriv->mIsBuffered = x;
	
	// If buffering is disabled then existing messages should be written.
	if(!mPriv->mIsBuffered)
	{
		_FlushBufferedMessages();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void AbstractLoggingDevice::SetBufferedMessagesCount(size_t x)
{
	std::lock_guard<std::recursive_mutex> _lock(mPriv->mBufferedMessagesMutex);
	mPriv->mBufferedMessages.reserve(x);
	mPriv->mBufferedMessagesCount = x;
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
	std::lock_guard<std::recursive_mutex> _lock(mPriv->mBufferedMessagesMutex);
	for(const std::string& _message : mPriv->mBufferedMessages)
	{
		_WriteMessage(_message);
	}
	mPriv->mBufferedMessages.clear();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
