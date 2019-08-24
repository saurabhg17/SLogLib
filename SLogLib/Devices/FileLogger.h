// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_FILELOGGER_H_
#define _SLOGLIB_FILELOGGER_H_

#include "SLogLib/Config.h"
#include "SLogLib/Devices/AbstractLoggingDevice.h"
#include <fstream>

namespace SLogLib {
;

// The FileLogger class writes logging messages to a file.
// 
// The FileLogger writes to a file whose name must be specified while construction and it cannot
// be changed later. For other parameters used for construction refer to AbstractLoggingDevice 
// documentation.
// 
// ofstream uses its own buffers and sometimes string written to it takes time to update. If there
// is a need to see the messaged immediately after writing to the file (for debugging) it is 
// possible to automatically flush the device after every message. By default auto flush is disabled.
// Related functions: EnableAutoFlush(), DisableAutoFlush(), IsAutoFlushEnabled().
// 
// If messages come in too fast then sometimes std::ofstream writes messages in an arbitrary order.
// I have found  that inserting a small delay after writing message fixes this problem. If you have 
// this problem then enable the delay. By default there is no delay in writing messages. The amount
// of delay in milliseconds (default: 10ms) can be specified by SetDelayAmount().
// Related functions: EnableDelay(), DisableDelay(), and HasDelay().
class SLOGLIB_DLL_API FileLogger : public AbstractLoggingDevice
{
public:
	
	enum OpenFlag
	{
		Immediately, FirstUse
	};

	FileLogger(const std::string& fileName, OpenFlag flag, AbstractFormatter* formatter);
	FileLogger(const std::string& fileName, OpenFlag flag, AbstractFormatter* formatter, const std::string& name);
	~FileLogger();
	
	// std::ofstream itself is a buffered device and string send to it are not immediately written
	// to the file. Calling FlushDevice() forces std::ofstream to write its buffer to the file.
	void FlushDevice();
	

public:
	
	inline std::string FileName() const {return mFileName;}
	
	inline void EnableAutoFlush()          {mHasAutoFlush = true;}
	inline void DisableAutoFlush()         {mHasAutoFlush = false;}
	inline void SetAutoFlush(bool b)       {mHasAutoFlush = b;}
	inline bool IsAutoFlushEnabled() const {return mHasAutoFlush;}
	
	inline void EnableDelay()    {mHasDelay     = true;}
	inline void DisableDelay()   {mHasDelay     = false;}
	inline void SetDelay(bool b) {mHasAutoFlush = b;}
	inline bool HasDelay() const {return mHasDelay;}	
	
	inline void SetDelayAmount(unsigned int d) {mDelayAmount = d;}
	inline unsigned int DelayAmount() const    {return mDelayAmount;}
	

private:
	
	void _WriteMessage(const std::string& message) override;
	void _WriteMessages(const std::vector<std::string>& messages) override;
	
	
public: // Disable copying.

	// Delete copy constructor and assignment operator.
	FileLogger(const FileLogger&) = delete;
    FileLogger & operator=(const FileLogger&) = delete;
	
	// Delete move constructor and assignment operator.
	FileLogger(const FileLogger&&) = delete;
    FileLogger & operator=(const FileLogger&&) = delete;


private:
	
	std::ofstream mFileHandle;
	std::string   mFileName;
	bool          mHasAutoFlush;  // Default: false
	bool          mHasDelay;      // Default: false
	unsigned int  mDelayAmount;   // Default: 10 ms
	OpenFlag      mFileOpenFlag;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_FILELOGGER_H_
