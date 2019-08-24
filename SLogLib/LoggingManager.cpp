// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

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
