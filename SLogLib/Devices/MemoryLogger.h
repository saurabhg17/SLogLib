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
#include <mutex>

namespace SLogLib {
;

struct MemoryLoggerPriv;

// The MemoryLogger class writes logging messages to a memory buffer. This is useful when log 
// need to be stored in custom location such as database or user-defined file format at the end.
class SLOGLIB_DLL_API MemoryLogger : public AbstractLoggingDevice
{
public:
	
	explicit MemoryLogger(AbstractFormatter* formatter);
	MemoryLogger(AbstractFormatter* formatter, const std::string& name);
	~MemoryLogger();
	
	// Return all messages logged so far concatenated into a string.
	std::string Messages() const;

	// Return the list of all messages logged so far.
	const std::list<std::string>& MessageList() const;


private:
	
	void _WriteMessage(const std::string& message) override;


private:

	// Buffering message for a memory logger is not meaningful so 
	// disable all buffering functions from the parent class.
	void   EnableBuffering() = delete;
	void   DisableBuffering() = delete;
	bool   IsBuffered() const = delete;
	void   SetBuffered(bool x) = delete;
	size_t BufferedMessagesCount() = delete;
	void   SetBufferedMessagesCount(size_t x) = delete;


public: // Disable copying.

	// Delete copy constructor and assignment operator.
	MemoryLogger(const MemoryLogger&) = delete;
    MemoryLogger & operator=(const MemoryLogger&) = delete;
	
	// Delete move constructor and assignment operator.
	MemoryLogger(const MemoryLogger&&) = delete;
    MemoryLogger & operator=(const MemoryLogger&&) = delete;


private:

	MemoryLoggerPriv* mPriv;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_MEMORYLOGGER_H_
