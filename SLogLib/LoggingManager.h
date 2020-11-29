// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_LOGGINGMANAGER_H_
#define _SLOGLIB_LOGGINGMANAGER_H_

#include "SLogLib/Config.h"
#include "SLogLib/DisableCopyMove.h"
#include "SLogLib/AddToCallStack.h"
#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include <list>
#include <mutex>
#include <atomic>

namespace SLogLib {
;

struct LoggingManagerPriv;

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

	S_DISABLE_COPYMOVE(LoggingManager);
	~LoggingManager();

	void EnableLogging() noexcept;
	void DisableLogging() noexcept;
	void SetDisabled(bool d) noexcept;
	bool IsDisabled() const noexcept;
	
	
public:
	
	// Return the only instance of LoggingManager.
	static LoggingManager* Instance()
	{
		static LoggingManager _singleton;
		return &_singleton;
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
					  unsigned int       lineNumber) noexcept;
	
	// Pop the topmost function from the call stack.
	void PopFunction() noexcept;
	
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
	
	LoggingManagerPriv* mPriv;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_LOGGINGMANAGER_H_
