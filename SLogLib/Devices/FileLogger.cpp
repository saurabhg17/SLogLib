// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/Devices/FileLogger.h"
#include "SLogLib/SysUtils.h"
#include <exception>

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
FileLogger::FileLogger(const std::string& fileName, Open flag, AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter), mFileName(fileName), mHasAutoFlush(false), mFileOpenFlag(flag)
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
FileLogger::FileLogger(const std::string& fileName, Open flag, AbstractFormatter* formatter, const std::string& name) 
	: AbstractLoggingDevice(formatter, name), mFileName(fileName), mHasAutoFlush(false), mFileOpenFlag(flag)
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
	std::lock_guard<std::mutex> _lock(mFileWriteMutex);
	mFileHandle.flush();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void FileLogger::_WriteMessage(const std::string& message)
{
	std::lock_guard<std::mutex> _lock(mFileWriteMutex);

	if(!mFileHandle)
	{
		mFileHandle.open(mFileName.c_str());
		if(!mFileHandle.is_open())
		{
			std::stringstream _stream;
			_stream << "SlogLib: Unable to open " << mFileName << " for writing.";
			throw std::runtime_error(_stream.str());
		}
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
	std::lock_guard<std::mutex> _lock(mFileWriteMutex);

	if(!mFileHandle)
	{
		mFileHandle.open(mFileName.c_str());
		if(!mFileHandle.is_open())
		{
			std::stringstream _stream;
			_stream << "SlogLib: Unable to open " << mFileName << " for writing.";
			throw std::runtime_error(_stream.str());
		}
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
