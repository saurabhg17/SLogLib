
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

#ifndef _SLOGLIB_LOGGINGMANAGER_H_
#define _SLOGLIB_LOGGINGMANAGER_H_

#include "SLogLib/Config.h"
#include "SLogLib/AddToCallStack.h"
#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include <list>

namespace SLogLib {
;

// The LoggingManager class the core engine. It manages various logging devices and writes messages 
// to currently enabled logging devices.
// 
// LoggingManager is a single instance class. Use Instance() static function to get its instance.
// It is possible to disable logging at runtime using DisableLoggin() or SetIsDisabled(). To
// enable logging again use EnableLogging(). The current status can be retrieved by isDisabled().
// Note that if logging is disabled then devices cannot be added or removed.
// 
// Easy to use macros and functions are provided in Logging.h and they should be used rather than 
// this class.
class SLOGLIB_DLL_API LoggingManager
{
public:

	~LoggingManager();

	// Disable copying of LoggingManager instances in the client code.
	// This makes sure there is only one instance of the logger.
	LoggingManager(const LoggingManager&) = delete;
	LoggingManager& operator=(const LoggingManager&) = delete;
	LoggingManager(const LoggingManager&&) = delete;
    LoggingManager & operator=(const LoggingManager&&) = delete;

	
public:
	
	// Return the only instance of LoggingManager.
	static LoggingManager& Instance()
	{
		static LoggingManager _singleton;
		return _singleton;
	}
	
	// Add a new logging device. The device is owned by the logging manager and is automatically 
	// deleted when LoggingManager is destructed.
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
	
public:
	
	inline void EnableLogging()     {mIsDisabled = false;}
	inline void DisableLogging()    {mIsDisabled = true;}
	inline void SetDisabled(bool d) {mIsDisabled = d;}
	inline bool IsDisabled() const  {return mIsDisabled;}


private:
	
	LoggingManager();


private:
	
	// For storing the list of logging devices.
	std::list<AbstractLoggingDevice*> mLoggingDevices;
	
	// For storing the current call stack.
	CallStack mCallStack;
	
	// If true then disable logging.
	bool mIsDisabled;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_LOGGINGMANAGER_H_
