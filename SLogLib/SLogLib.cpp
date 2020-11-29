// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib.h"

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void addLoggingDevice(AbstractLoggingDevice* device)
{
	if(LoggingManager::Instance())
	{
		LoggingManager::Instance()->AddDevice(device);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void removeLoggingDevice(const std::string& name)
{
	if(LoggingManager::Instance())
	{
		LoggingManager::Instance()->RemoveDevice(name);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void removeLoggingDevice(AbstractLoggingDevice* device)
{
	if(LoggingManager::Instance())
	{
		LoggingManager::Instance()->RemoveDevice(device);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AbstractLoggingDevice* queryLoggingDevice(const std::string& name)
{
	if(LoggingManager::Instance())
	{
		return LoggingManager::Instance()->QueryDevice(name);
	}
	return nullptr;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void writeMessage(const std::string& fileName,
	              const std::string& funcName,
				  unsigned int       lineNo,
				  MessageLevel       level,
				  const std::string& msg)
{
	if(LoggingManager::Instance())
	{
		LoggingManager::Instance()->WriteMessage(fileName, funcName, lineNo, level, msg);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void disableLogging()
{
	if(LoggingManager::Instance())
	{
		LoggingManager::Instance()->SetDisabled(true);
	}
}
void enableLogging()
{
	if(LoggingManager::Instance())
	{
		LoggingManager::Instance()->SetDisabled(false);
	}
	
}
bool isLoggingEnabled()
{
	if(LoggingManager::Instance())
	{
		return LoggingManager::Instance()->IsDisabled();
	}
	return false;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SLogLib.
