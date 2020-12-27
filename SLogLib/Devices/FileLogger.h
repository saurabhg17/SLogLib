// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_FILELOGGER_H_
#define _SLOGLIB_FILELOGGER_H_

#include "SLogLib/Config.h"
#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include "SLogLib/DisableCopyMove.h"
#include "SLogLib/Types.h"
#include <fstream>
#include <mutex>

namespace SLogLib {
;

struct FileLoggerPriv;

// The FileLogger class writes logging messages to a file.
// 
// The FileLogger writes to a file whose name must be specified while construction and it cannot
// be changed later. For other parameters used for construction refer to AbstractLoggingDevice 
// documentation.
// 
// std::ofstream uses its own buffers and sometimes string written to it takes time to update. If 
// there is a need to see the messaged immediately after writing to the file (for debugging) it is 
// possible to automatically flush the device after every message. By default auto flush is disabled.
// Related functions: EnableAutoFlush(), DisableAutoFlush(), IsAutoFlushEnabled().
class SLOGLIB_DLL_API FileLogger : public AbstractLoggingDevice
{
public:
	
	FileLogger(const std::string& fileName, Open flag, AbstractFormatter* formatter);
	FileLogger(const std::string& fileName, Open flag, AbstractFormatter* formatter, const std::string& name);
	~FileLogger();
	
	// std::ofstream itself is a buffered device and string sent to it are not immediately written
	// to the file. Calling FlushDevice() forces std::ofstream to write its buffer to the file.
	void FlushDevice();
	
	
public:
	
	std::string FileName() const noexcept;
	void EnableAutoFlush() noexcept;
	void DisableAutoFlush() noexcept;
	void SetAutoFlush(bool b) noexcept;
	bool IsAutoFlushEnabled() const noexcept;
	
	
private:
	
	void _WriteMessage(const std::string& message) override;
	void _WriteMessages(const std::vector<std::string>& messages) override;
	
	
public: // Disable copying.
	
	S_DISABLE_COPYMOVE(FileLogger)
	
	
private:
	
	FileLoggerPriv* mPriv;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_FILELOGGER_H_
