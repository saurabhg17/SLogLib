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
	LoggingManager::Instance().AddDevice(device);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void removeLoggingDevice(const std::string& name)
{
	LoggingManager::Instance().RemoveDevice(name);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void removeLoggingDevice(AbstractLoggingDevice* device)
{
	LoggingManager::Instance().RemoveDevice(device);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AbstractLoggingDevice* queryLoggingDevice(const std::string& name)
{
	return LoggingManager::Instance().QueryDevice(name);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void writeMessage(const std::string& fileName,
	              const std::string& funcName,
				  unsigned int       lineNo,
				  MessageLevel       level,
				  const std::string& msg)
{
	LoggingManager::Instance().WriteMessage(fileName, funcName, lineNo, level, msg);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void disableLogging()
{
	LoggingManager::Instance().SetDisabled(true);
}
void enableLogging()
{
	LoggingManager::Instance().SetDisabled(false);
}
bool isLoggingEnabled()
{
	return LoggingManager::Instance().IsDisabled();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SLogLib.
