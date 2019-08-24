// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_MEMORYLOGGER_H_
#define _SLOGLIB_MEMORYLOGGER_H_

#include "SLogLib/Config.h"
#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include <list>

namespace SLogLib {
;

// The FileLogger class writes logging messages to the memory. This is usefule when log need to be 
// available after the problem ends.
class SLOGLIB_DLL_API MemoryLogger : public AbstractLoggingDevice
{
public:
	
	MemoryLogger(AbstractFormatter* formatter);
	MemoryLogger(AbstractFormatter* formatter, const std::string& name);
	
	std::string allMessages() const;

	inline std::list<std::string> messages() const {return mMessages;}

private:
	
	void _WriteMessage(const std::string& message) override;


private:

	// There is no point buffering message for a memory logger.
	void EnableBuffering() {}
	void SetBuffered(bool) {}


public: // Disable copying.

	// Delete copy constructor and assignment operator.
	MemoryLogger(const MemoryLogger&) = delete;
    MemoryLogger & operator=(const MemoryLogger&) = delete;
	
	// Delete move constructor and assignment operator.
	MemoryLogger(const MemoryLogger&&) = delete;
    MemoryLogger & operator=(const MemoryLogger&&) = delete;

private:

	std::list<std::string> mMessages;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_MEMORYLOGGER_H_
