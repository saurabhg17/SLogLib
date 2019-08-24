// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/Devices/FileLogger.h"
#include "SLogLib/SysUtils.h"

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
FileLogger::FileLogger(const std::string& fileName, OpenFlag flag, AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter), mFileName(fileName), mHasAutoFlush(false), mHasDelay(false), mDelayAmount(10), mFileOpenFlag(flag)
{
	if(mFileOpenFlag == Immediately)
	{
		mFileHandle.open(fileName.c_str());
	}
}
FileLogger::FileLogger(const std::string& fileName, OpenFlag flag, AbstractFormatter* formatter, const std::string& name) 
	: AbstractLoggingDevice(formatter, name), mFileName(fileName), mHasAutoFlush(false), mHasDelay(false), mDelayAmount(10), mFileOpenFlag(flag)
{
	if(mFileOpenFlag == Immediately)
	{
		mFileHandle.open(fileName.c_str());
	}
}
FileLogger::~FileLogger()
{
	if(mFileHandle)
	{
		_FlushBufferedMessages();
		mFileHandle.close();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FileLogger::FlushDevice()
{
	mFileHandle.flush();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FileLogger::_WriteMessage(const std::string& message)
{
	if(!mFileHandle)
	{
		mFileHandle.open(mFileName.c_str());
	}

	if(mHasDelay)
	{
		SLogLib::sleep(mDelayAmount);
	}

	mFileHandle << message;
	
	if(mHasAutoFlush)
	{
		FlushDevice();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FileLogger::_WriteMessages(const std::vector<std::string>& messages)
{
	if(!mFileHandle)
	{
		mFileHandle.open(mFileName.c_str());
	}

	if(mHasDelay)
	{
		SLogLib::sleep(mDelayAmount);
	}
	
	for(const std::string& _message : messages)
	{
		mFileHandle << _message;
	}
	
	if(mHasAutoFlush)
	{
		FlushDevice();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
