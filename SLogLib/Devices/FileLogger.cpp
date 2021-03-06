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
	FileLoggerPriv(const std::string& fileName, std::ios_base::openmode mode, FileOpenFlag flag)
		: mFileName(fileName), mHasAutoFlush(false), mMode(mode), mFileOpenFlag(flag)
	{
		if(mFileOpenFlag == FileOpenFlag::Immediately)
		{
			mFileHandle.open(mFileName.c_str(), mMode);
			if(!mFileHandle.is_open())
			{
				std::stringstream _stream;
				_stream << "SLogLib: Unable to open " << mFileName << " for writing.";
				throw std::runtime_error(_stream.str());
			}
		}
	}
	
	std::ofstream           mFileHandle;
	std::string             mFileName;
	bool                    mHasAutoFlush;  // Default: false
	std::ios_base::openmode mMode;
	FileOpenFlag            mFileOpenFlag;  // Default: FirstUse.
	std::recursive_mutex    mFileWriteMutex;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
FileLogger::FileLogger(const std::string& fileName, std::ios_base::openmode mode, FileOpenFlag flag, AbstractFormatter* formatter)
	: FileLogger(fileName, mode, flag, formatter, "")
{
}
FileLogger::FileLogger(const std::string& fileName, std::ios_base::openmode mode, FileOpenFlag flag, AbstractFormatter* formatter, const std::string& name) 
  : AbstractLoggingDevice(formatter, name), mPriv(new FileLoggerPriv(fileName, mode, flag))
{
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
std::string FileLogger::FileName() const noexcept
{
	return mPriv->mFileName;
}
void FileLogger::EnableAutoFlush() noexcept
{
	mPriv->mHasAutoFlush = true;
}
void FileLogger::DisableAutoFlush() noexcept
{
	mPriv->mHasAutoFlush = false;
}
void FileLogger::SetAutoFlush(bool b) noexcept
{
	mPriv->mHasAutoFlush = b;
}
bool FileLogger::IsAutoFlushEnabled() const noexcept
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
			_stream << "SLogLib: Unable to open " << mPriv->mFileName << " for writing.";
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
			_stream << "SLogLib: Unable to open " << mPriv->mFileName << " for writing.";
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
