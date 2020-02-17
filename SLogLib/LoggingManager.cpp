// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "LoggingManager.h"
#include "SysUtils.h"

namespace SLogLib {
;

// Stores call stack per thread.
// thread_local cannot be used with class members, and static thread_local class member 
// cannot use __declspec under Windows, hence call stack is declared globally.
thread_local CallStack gCallStack;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
LoggingManager::LoggingManager() 
	: mIsDisabled(false)
{}
LoggingManager::~LoggingManager()
{
	// Destructor will be called by the main thread, just before program dies.
	std::lock_guard<std::mutex> _lock(mLoggingDevicesMutex);
	for(AbstractLoggingDevice* _device :  mLoggingDevices)
	{
		delete _device;
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// mIsDisabled is atomic.
void LoggingManager::EnableLogging()
{
	mIsDisabled = false;
}
void LoggingManager::DisableLogging()
{
	mIsDisabled = true;
}
void LoggingManager::SetDisabled(bool d)
{
	mIsDisabled = d;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::AddDevice(AbstractLoggingDevice* device)
{
	if(!mIsDisabled && device != nullptr)
	{
		std::lock_guard<std::mutex> _lock(mLoggingDevicesMutex);
		
		// Device name must be unique.
		for(AbstractLoggingDevice* _device : mLoggingDevices)
		{
			if(device->Name() == _device->Name())
			{
				std::stringstream _stream;
				_stream << "SLogLib: Device with name '"<< device->Name() << "' already exists.";
				throw std::runtime_error(_stream.str());
			}
		}
		
		mLoggingDevices.push_back(device);
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::RemoveDevice(AbstractLoggingDevice* device)
{
	if(device != nullptr)
	{
		RemoveDevice(device->Name());
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::RemoveDevice(const std::string& deviceName)
{
	if(!mIsDisabled)
	{
		// Lock must be here because another thread can add 
		// a new device while we are iterating over logging devices.
		std::lock_guard<std::mutex> _lock(mLoggingDevicesMutex);

		// We don't have to worry about iterator becoming invalid 
		// since we exit from loop immediately after erasing the device
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
	// Lock must be here because another thread can add 
	// a new device while the for loop is running.
	std::lock_guard<std::mutex> _lock(mLoggingDevicesMutex);

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
		// Since call stack is per thread no synchronization is required.
		gCallStack.emplace_back(fileName, funcName, lineNumber);
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::PopFunction()
{
	if(!mIsDisabled)
	{
		// Since call stack is per thread no synchronization is required.
		gCallStack.pop_back();
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
		PushFunction(fileName, funcName, lineNumber);
		
		// Generate the message.
		Message _message;
		_message.mUserMessage = message;
		_message.mDateTime    = SLogLib::getLocalDateTime();
		_message.mLevel       = level;
		_message.mCallStack   = &gCallStack;
		_message.mProcessId   = SLogLib::getCurrentProcessID();
		_message.mThreadId    = SLogLib::getCurrentThreadID();
		
		// Lock must be here because another thread can add or 
		// remove a device while the for loop is running.
		std::lock_guard<std::mutex> _lock(mLoggingDevicesMutex);

		// Iterate over all LoggingDevices and write the message
		// to the enabled devices.
		for(AbstractLoggingDevice* _device : mLoggingDevices)
		{
			if(_device->IsEnabled())
			{
				_device->WriteMessage(_message);
			}
		}
		
		PopFunction();
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SLogLib.
