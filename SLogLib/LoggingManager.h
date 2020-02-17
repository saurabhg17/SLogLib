// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_LOGGINGMANAGER_H_
#define _SLOGLIB_LOGGINGMANAGER_H_

#include "SLogLib/Config.h"
#include "SLogLib/AddToCallStack.h"
#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include <list>
#include <mutex>
#include <atomic>

namespace SLogLib {
;

// The LoggingManager class is the core engine of the SLogLib. It manages various logging devices 
// and writes messages to currently enabled logging devices.
// 
// LoggingManager is a single instance class. Use Instance() static function to get its instance.
// It is possible to disable logging at runtime using DisableLogging() or SetDisabled(). To
// enable logging again use EnableLogging(). The current status can be retrieved by IsDisabled().
// Note that if logging is disabled then devices cannot be added or removed.
// 
// Easy to use macros and functions are provided in Logging.h and they should be used rather than 
// this class.
class SLOGLIB_DLL_API LoggingManager
{
public:

	// Disable copying of LoggingManager instances in the client code.
	// This makes sure there is only one instance of the logger.
	LoggingManager(const LoggingManager&) = delete;
	LoggingManager& operator=(const LoggingManager&) = delete;
	LoggingManager(const LoggingManager&&) = delete;
	LoggingManager& operator=(const LoggingManager&&) = delete;

	~LoggingManager();

	void EnableLogging();
	void DisableLogging();
	void SetDisabled(bool d);
	inline bool IsDisabled() const { return mIsDisabled; }
	
	
public:
	
	// Return the only instance of LoggingManager.
	static LoggingManager& Instance()
	{
		static LoggingManager _singleton;
		return _singleton;
	}
	
	// Add a new logging device. The device is owned by the logging manager 
	// and is automatically deleted when LoggingManager is destructed.
	void AddDevice(AbstractLoggingDevice* device);
	
	// Remove an existing logging device.
	void RemoveDevice(AbstractLoggingDevice* device);
	void RemoveDevice(const std::string& deviceName);
	
	// Get a pointer to the logging device from name.
	AbstractLoggingDevice* QueryDevice(const std::string& deviceName);

	// Push a function to the current call stack.
	void PushFunction(const std::string& fileName, 
		              const std::string& funcName,  
					  unsigned int       lineNumber);
	
	// Pop the topmost function from the call stack.
	void PopFunction();
	
	// Write the message to all enabled logging devices.
	void WriteMessage(const std::string& fileName, 
		              const std::string& funcName, 
					  unsigned int       lineNumber,
					  MessageLevel       level,
					  const std::string& message);
	

private:
	
	// Private to make the class single instance.
	LoggingManager();


private:
	
	// Stores the list of all logging devices registered with SLogLib.
	std::list<AbstractLoggingDevice*> mLoggingDevices;
	
	// For synchronized access to mLoggingDevices.
	std::mutex mLoggingDevicesMutex;

	// If true then disable logging.
	std::atomic_bool mIsDisabled;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_LOGGINGMANAGER_H_
