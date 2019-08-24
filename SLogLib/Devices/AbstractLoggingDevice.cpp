
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
