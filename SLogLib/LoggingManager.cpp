
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

#include "LoggingManager.h"
#include "SysUtils.h"

namespace SLogLib {
;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
LoggingManager::LoggingManager()
{
	mIsDisabled = false;
}
LoggingManager::~LoggingManager()
{
	for(AbstractLoggingDevice* _device :  mLoggingDevices)
	{
		delete _device;
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::AddDevice(AbstractLoggingDevice* device)
{
	if(!mIsDisabled && device != nullptr)
	{
		mLoggingDevices.push_back(device);
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::RemoveDevice(AbstractLoggingDevice* device)
{
	if(!mIsDisabled)
	{
		// We don't have to worry about iter becoming invalid 
		// since we exit from loop immediately after erasing.
		for(auto _iter = mLoggingDevices.begin() ; _iter!=mLoggingDevices.end() ; ++_iter)
		{
			AbstractLoggingDevice* _device = *_iter;
			if(device == _device)
			{
				mLoggingDevices.erase(_iter);
				delete _device;
				return;
			}
		}
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::RemoveDevice(const std::string& deviceName)
{
	if(!mIsDisabled)
	{
		// We don't have to worry about iterator becoming invalid 
		// since we exit from loop immediately after erasing.
		for(auto _iter = mLoggingDevices.begin() ; _iter!=mLoggingDevices.end() ; ++_iter)
		{
			AbstractLoggingDevice* _device = *_iter;
			if(deviceName == _device->Name())
			{
				mLoggingDevices.erase(_iter);
				delete _device;
				return;
			}
		}
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AbstractLoggingDevice* LoggingManager::QueryDevice(const std::string& deviceName)
{
	for(AbstractLoggingDevice* _device : mLoggingDevices)
	{
		if(deviceName == _device->Name())
		{
			return _device;
		}
	}
	return nullptr;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::PushFunction(const std::string& fileName,
	                              const std::string& funcName, 
								  unsigned int       lineNumber)
{
	if(!mIsDisabled)
	{
		mCallStack.push_back(CallInfo(fileName, funcName, lineNumber));
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::PopFunction()
{
	if(!mIsDisabled)
	{
		mCallStack.pop_back();
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::WriteMessage(const std::string& fileName, 
	                              const std::string& funcName,
								  unsigned int       lineNumber,
								  MessageLevel       level,
								  const std::string& message)
{
	if(!mIsDisabled)
	{
		// Update the call stack.
		mCallStack.push_back(CallInfo(fileName, funcName, lineNumber));
		
		// Generate the message.
		Message _message;
		_message.mUserMessage = message;
		_message.mDateTime    = SLogLib::getLocalDateTime();
		_message.mLevel       = level;
		_message.mCallStack   = &mCallStack;
		_message.mProcessId   = SLogLib::getCurrentProcessID();
		_message.mThreadId    = SLogLib::getCurrentThreadID();
		
		// Iterate over all LoggingDevices and write the message
		// to the enabled devices.
		for(AbstractLoggingDevice* _device : mLoggingDevices)
		{
			if(_device->IsEnabled())
			{
				_device->WriteMessage(_message);
			}
		}
		
		// Update the call stack.
		mCallStack.erase(--mCallStack.end());
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SLogLib.
