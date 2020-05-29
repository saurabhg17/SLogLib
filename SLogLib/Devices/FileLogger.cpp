// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/Devices/FileLogger.h"
#include "SLogLib/SysUtils.h"
#include <exception>
#include <mutex>

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
struct FileLoggerPriv
{
	FileLoggerPriv(const std::string& fileName, Open flag)
		: mFileName(fileName), mHasAutoFlush(false), mFileOpenFlag(flag)
	{
		if(mFileOpenFlag == Open::Immediately)
		{
			mFileHandle.open(mFileName.c_str());
			if(!mFileHandle.is_open())
			{
				std::stringstream _stream;
				_stream << "SlogLib: Unable to open " << mFileName << " for writing.";
				throw std::runtime_error(_stream.str());
			}
		}
	}
	
	std::ofstream        mFileHandle;
	std::string          mFileName;
	bool                 mHasAutoFlush;  // Default: false
	Open                 mFileOpenFlag;  // Default: FirstUse.
	std::recursive_mutex mFileWriteMutex;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
FileLogger::FileLogger(const std::string& fileName, Open flag, AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter)
{
	mPriv = new FileLoggerPriv(fileName, flag);
}
FileLogger::FileLogger(const std::string& fileName, Open flag, AbstractFormatter* formatter, const std::string& name) 
	: AbstractLoggingDevice(formatter, name)
{
	mPriv = new FileLoggerPriv(fileName, flag);
}
FileLogger::~FileLogger()
{
	if(mPriv->mFileHandle)
	{
		_FlushBufferedMessages();
		mPriv->mFileHandle.close();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
std::string FileLogger::FileName() const
{
	return mPriv->mFileName;
}
void FileLogger::EnableAutoFlush()
{
	mPriv->mHasAutoFlush = true;
}
void FileLogger::DisableAutoFlush()
{
	mPriv->mHasAutoFlush = false;
}
void FileLogger::SetAutoFlush(bool b)
{
	mPriv->mHasAutoFlush = b;
}
bool FileLogger::IsAutoFlushEnabled() const
{
	return mPriv->mHasAutoFlush;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FileLogger::FlushDevice()
{
	std::lock_guard<std::recursive_mutex> _lock(mPriv->mFileWriteMutex);
	mPriv->mFileHandle.flush();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FileLogger::_WriteMessage(const std::string& message)
{
	std::lock_guard<std::recursive_mutex> _lock(mPriv->mFileWriteMutex);

	if(!mPriv->mFileHandle)
	{
		mPriv->mFileHandle.open(mPriv->mFileName.c_str());
		if(!mPriv->mFileHandle.is_open())
		{
			std::stringstream _stream;
			_stream << "SlogLib: Unable to open " << mPriv->mFileName << " for writing.";
			throw std::runtime_error(_stream.str());
		}
	}

	mPriv->mFileHandle << message;
	
	if(mPriv->mHasAutoFlush)
	{
		FlushDevice();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FileLogger::_WriteMessages(const std::vector<std::string>& messages)
{
	std::lock_guard<std::recursive_mutex> _lock(mPriv->mFileWriteMutex);

	if(!mPriv->mFileHandle)
	{
		mPriv->mFileHandle.open(mPriv->mFileName.c_str());
		if(!mPriv->mFileHandle.is_open())
		{
			std::stringstream _stream;
			_stream << "SlogLib: Unable to open " << mPriv->mFileName << " for writing.";
			throw std::runtime_error(_stream.str());
		}
	}

	for(const std::string& _message : messages)
	{
		mPriv->mFileHandle << _message;
	}
	
	if(mPriv->mHasAutoFlush)
	{
		FlushDevice();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}	// End namespace SLogLib.
