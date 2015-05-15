
// This file is part of SLogLib; you can redistribute it and/or
// modify it under the terms of the MIT License.
// 
// Copyright (c) 2015 Saurabh Garg
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
// Author(s): Saurabh Garg

#include "SLogLib/Devices/FileLogger.h"
#include "SLogLib/SysUtils.h"

namespace SLogLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
FileLogger::FileLogger(const std::string& fileName, AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter)
{
	_Initialize(fileName);
}
FileLogger::FileLogger(const std::string& fileName, AbstractFormatter* formatter, const std::string& name) 
		: AbstractLoggingDevice(formatter, name)
{
	_Initialize(fileName);
}
FileLogger::FileLogger(const std::string& fileName, AbstractFormatter* formatter, const std::string& name, bool isEnabled, bool isBuffered, size_t numBufferedMessages)
	: AbstractLoggingDevice(formatter, name, isEnabled, isBuffered, numBufferedMessages)
{
	_Initialize(fileName);
}
void FileLogger::_Initialize(const std::string& fileName)
{
	mFileHandle.open(fileName.c_str());
	mHasAutoFlush = false;
	mHasDelay     = false;
	mDelayAmount  = 10; // ms.
}
FileLogger::~FileLogger()
{
	_FlushBufferedMessages();
	mFileHandle.close();
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
	if(mHasDelay)
	{
		SLogLib::sleep(mDelayAmount);
	}
	
	for(size_t i=0 ; i<messages.size() ; ++i)
	{
		mFileHandle << messages[i];
	}
	
	if(mHasAutoFlush)
	{
		FlushDevice();
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SLogLib.