
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

#ifndef _SLOGLIB_ABSTRACTLOGGINGDEVICE_H_
#define _SLOGLIB_ABSTRACTLOGGINGDEVICE_H_

#include "SLogLib/Config.h"
#include "SLogLib/Message.h"
#include "SLogLib/Formatters/AbstractFormatter.h"
#include <string>
#include <list>
#include <vector>

namespace SLogLib {
;

// The AbstractLoggingDevice class is the abstract base class of all logging devices. 
// 
// Logging device needs a formatter to format messages send to it. Formatter can be set only
// during construction and cannot be changed later. The logging device owns the specified formatter
// and deletes it automatically. This means, a unique instance of formatter must be created for 
// each device.
// 
// A logging device is identified by a name, which can be set during construction. If a name is 
// not specified than a name of the form LoggingDeviceX (X is a natural number) is automatically 
// assigned. Once a logging device is constructed its name cannot be changed.
// 
// A logging device can be enabled or disabled. A disabled device ignore all messages sent to it.
// A device is enabled by default.
// Related functions: Enable(), Disable(), IsEnabled(), and SetIsEnabled().
// 
// It is possible to buffer a number of messages before sending them to the device for writing. 
// A device is not buffered by default. Buffering can be enabled or disabled by 
// EnableBuffering() and DisableBuffering(). There is also a more general function SetIsBuffered(). 
// The number of messages buffered (default: 1000) is specified by SetNumBufferedMessages().
class SLOGLIB_DLL_API AbstractLoggingDevice
{
public:
	
	AbstractLoggingDevice(AbstractFormatter* formatter);
	AbstractLoggingDevice(AbstractFormatter* formatter, const std::string& name);
	AbstractLoggingDevice(AbstractFormatter* formatter, const std::string& name, bool isEnabled, bool isBuffered, size_t numBufferedMessages);
	virtual ~AbstractLoggingDevice();
	
	// Format the message and write it to the device.
	// For a buffered device, the message may not be immediately written to the device.
	// This function is called by the LoggingManager to write a message to the device.
	void WriteMessage(const Message& message);
	
public: // Getters and setters.
	
	inline std::string Name() const {return mName;}
	
	inline void Enable()  {SetIsEnabled(true);}
	inline void Disable() {SetIsEnabled(false);}
	inline bool IsEnabled() const {return mIsEnabled;}
	void SetIsEnabled(bool x);
	
	inline void EnableBuffering()  {SetIsBuffered(true);}
	inline void DisableBuffering() {SetIsBuffered(false);}
	inline bool IsBuffered() const {return mIsBuffered;}
	void SetIsBuffered(bool x);
	
	inline size_t numBufferedMessages() const {return mNumBufferedMessages;}
	void SetNumBufferedMessages(size_t x);
	
protected:
	
	// Write a single message to the logging device.
	virtual void _WriteMessage(const std::string& message) = 0;
	
	// Write an array of messages to the logging device.
	// The default implementation simply calls _WriteMessage() for each message.
	// If it is possible to write set of messages faster than using _WriteMessage() iteratively
	// than override this function.
	virtual void _WriteMessages(const std::vector<std::string>& messages);
	
	// Flush the currently buffered messages to the device.
	// For a buffered device, concrete class must call this in the destructor to ensure 
	// all messages are written to the device.
	void _FlushBufferedMessages();
	
private:
	
	AbstractFormatter*       mFormatter;
	std::string              mName;
	bool                     mIsEnabled; // Default: true
	bool                     mIsBuffered; // Default: false
	size_t                   mNumBufferedMessages; // Default: 1000
	std::vector<std::string> mBufferedMessages;
};

// Define a type for storing logging devices.
typedef std::list<AbstractLoggingDevice*> LoggingDeviceList;

};	// End namespace SLogLib.

#endif // _SLOGLIB_ABSTRACTLOGGINGDEVICE_H_
