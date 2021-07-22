// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "LoggingManager.h"
#include "SysUtils.h"
#include <list>
#include <mutex>
#include <atomic>

namespace SLogLib {
;

// It is set to true after LoggingManager is destructed.
// After LoggingManager is destructed, LoggingManager::Instance() returns nullptr.
static std::atomic<bool> gLoggingManagerDestructed{ false };

// Stores call stack per thread.
// thread_local cannot be used with class members, and static thread_local class member 
// cannot use __declspec under Windows, hence call stack is declared globally.
thread_local CallStack gCallStack;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
bool LoggingManager::destructed()
{
	return gLoggingManagerDestructed;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
struct LoggingManagerPriv
{
	LoggingManagerPriv() noexcept
		: mIsDisabled(false)
	{
	}
	
	~LoggingManagerPriv()
	{
		// Destructor should be called by the main thread, just before program dies.
		std::lock_guard<std::mutex> _lock(mLoggingDevicesMutex);
		for(AbstractLoggingDevice* _device : mLoggingDevices)
		{
			delete _device;
		}
		
		gLoggingManagerDestructed = true;
	}
	
	// Stores the list of all logging devices registered with SLogLib.
	std::list<AbstractLoggingDevice*> mLoggingDevices;
	
	// For synchronized access to mLoggingDevices.
	std::mutex mLoggingDevicesMutex;
	
	// If true then disable logging.
	std::atomic_bool mIsDisabled;
};
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
LoggingManager::LoggingManager()
	: mPriv(new LoggingManagerPriv) 
{
}
LoggingManager::~LoggingManager()
{
	delete mPriv;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// mIsDisabled is atomic.
void LoggingManager::EnableLogging()
{
	mPriv->mIsDisabled = false;
}
void LoggingManager::DisableLogging()
{
	mPriv->mIsDisabled = true;
}
void LoggingManager::SetDisabled(bool d)
{
	mPriv->mIsDisabled = d;
}
bool LoggingManager::IsDisabled() const
{
	return mPriv->mIsDisabled;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::AddDevice(AbstractLoggingDevice* device)
{
	if(device == nullptr)
	{
		return;
	}
	
	if(IsDisabled())
	{
		return;
	}
	
	std::lock_guard<std::mutex> _lock(mPriv->mLoggingDevicesMutex);
	
	// Device name must be unique.
	for(const AbstractLoggingDevice* _device : mPriv->mLoggingDevices)
	{
		if(_device && !_device->Name().empty() && (device->Name() == _device->Name()))
		{
			std::stringstream _stream;
			_stream << "SLogLib: Device with name '"<< device->Name() << "' already exists.";
			throw std::runtime_error(_stream.str());
		}
	}
	
	mPriv->mLoggingDevices.push_back(device);
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
	if(mPriv->mIsDisabled)
	{
		return;
	}
	
	// Lock must be here because another thread can add 
	// a new device while we are iterating over logging devices.
	std::lock_guard<std::mutex> _lock(mPriv->mLoggingDevicesMutex);
	
	// We don't have to worry about iterator becoming invalid 
	// since we exit from loop immediately after erasing the device
	for(auto _iter = mPriv->mLoggingDevices.begin() ; _iter!=mPriv->mLoggingDevices.end() ; ++_iter)
	{
		AbstractLoggingDevice* _device = *_iter;
		if(deviceName == _device->Name())
		{
			mPriv->mLoggingDevices.erase(_iter);
			delete _device;
			return;
		}
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AbstractLoggingDevice* LoggingManager::QueryDevice(const std::string& deviceName)
{
	// Lock must be here because another thread can add/remove 
	// a new device while the for loop is running.
	std::lock_guard<std::mutex> _lock(mPriv->mLoggingDevicesMutex);
	
	for(AbstractLoggingDevice* _device : mPriv->mLoggingDevices)
	{
		if(_device && deviceName == _device->Name())
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
	if(!mPriv->mIsDisabled)
	{
		// Since call stack is per thread no synchronization is required.
		gCallStack.emplace_back(fileName, funcName, lineNumber);
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void LoggingManager::PopFunction()
{
	if(!mPriv->mIsDisabled)
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
	if(mPriv->mIsDisabled)
	{
		return;
	}
	
	
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
	std::lock_guard<std::mutex> _lock(mPriv->mLoggingDevicesMutex);
	
	// Iterate over all LoggingDevices and write the message
	// to the enabled devices.
	for(AbstractLoggingDevice* _device : mPriv->mLoggingDevices)
	{
		if(_device && _device->IsEnabled())
		{
			_device->WriteMessage(_message);
		}
	}
	
	PopFunction();
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SLogLib.
