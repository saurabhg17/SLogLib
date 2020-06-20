// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "AddToCallStack.h"
#include "LoggingManager.h"

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AddToCallStack::AddToCallStack(const std::string& fileName, 
							   const std::string& funcName, 
							   unsigned int       lineNumber) noexcept
{
	LoggingManager::Instance().PushFunction(fileName, funcName, lineNumber);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
AddToCallStack::~AddToCallStack() noexcept
{
	LoggingManager::Instance().PopFunction();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SLogLib.
