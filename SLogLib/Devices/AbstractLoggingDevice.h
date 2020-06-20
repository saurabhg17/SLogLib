// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_ABSTRACTLOGGINGDEVICE_H_
#define _SLOGLIB_ABSTRACTLOGGINGDEVICE_H_

#include "SLogLib/Config.h"
#include "SLogLib/Message.h"
#include "SLogLib/Formatters/AbstractFormatter.h"
#include <string>
#include <vector>

namespace SLogLib {
;

// PIMPL: Hide implementation details.
struct AbstractLoggingDevicePriv;

// The AbstractLoggingDevice class is the abstract base class of all logging devices. 
// 
// Logging device needs a formatter to format messages send to it. Formatter can be set only
// during construction and cannot be changed later. The logging device owns the specified formatter
// and deletes it automatically. This means that a unique instance of formatter must be created for 
// each device.
// 
// A logging device is identified by a name, which can be set during construction. If a name is 
// not specified than a name of the form LoggingDevice_XXX (XXX is a natural number) is 
// automatically assigned. Once a logging device is constructed its name cannot be changed.
// 
// A logging device can be enabled or disabled. A disabled device ignore all messages sent to it.
// A device is enabled by default.
// Related functions: Enable(), Disable(), IsEnabled(), and SetEnabled().
// 
// It is possible to buffer a number of messages before sending them to the device for writing. 
// A device is not buffered by default. Buffering can be enabled or disabled by 
// EnableBuffering() and DisableBuffering(). There is also a more general function SetBuffered(). 
// The number of messages buffered (default: 1000) is specified by SetBufferedMessagesCount().
// 
// Ideally, any new logging device inherited from the AbstractLoggingDevice should be thread-safe,
// however, if it is not possible to make it thread-safe then isThreadSafe() should return false.
// 
// All logging devices which support buffering should call _FlushBufferedMessages() from their 
// destructor to write any pending messages before the device is deleted.
class SLOGLIB_DLL_API AbstractLoggingDevice
{
public:
	
	explicit AbstractLoggingDevice(AbstractFormatter* formatter);
	AbstractLoggingDevice(AbstractFormatter* formatter, const std::string& name);
	virtual ~AbstractLoggingDevice();
	
	// Format the message and write it to the device.
	// For a buffered device, the message may not be immediately written to the device.
	// This function is called by the LoggingManager to write a message to the device.
	// Note that this is not a virtual function and should not be overridden by the derived classes.
	void WriteMessage(const Message& message);
	

public: // Getters and setters.
	
	std::string Name() const;
	
	inline void Enable()          {SetEnabled(true);}
	inline void Disable()         {SetEnabled(false);}
	bool IsEnabled() const noexcept;
	void SetEnabled(bool x);
	
	inline void EnableBuffering()  {SetBuffered(true);}
	inline void DisableBuffering() {SetBuffered(false);}
	bool IsBuffered() const noexcept;
	void SetBuffered(bool x);
	
	size_t BufferedMessagesCount() const noexcept;
	void SetBufferedMessagesCount(size_t x);
	
	inline virtual bool IsThreadSafe() const noexcept {return true;}


protected:
	
	// Write a single message to the logging device.
	virtual void _WriteMessage(const std::string& message) = 0;
	
	// Write an array of messages to the logging device.
	// The default implementation simply calls _WriteMessage() for each message.
	// If it is possible to write set of messages faster than calling _WriteMessage() 
	// iteratively than override this function.
	virtual void _WriteMessages(const std::vector<std::string>& messages);
	
	// Flush the currently buffered messages to the device.
	// For a buffered device, concrete class must call this in the destructor to ensure 
	// all messages are written to the device before it is deleted.
	void _FlushBufferedMessages();


public: // Disable copying and moving.

	// Delete copy constructor and assignment operator.
	AbstractLoggingDevice(const AbstractLoggingDevice&) = delete;
    AbstractLoggingDevice & operator=(const AbstractLoggingDevice&) = delete;

	// Delete move constructor and assignment operator.
	AbstractLoggingDevice(const AbstractLoggingDevice&&) = delete;
    AbstractLoggingDevice & operator=(const AbstractLoggingDevice&&) = delete;

private:
	
	AbstractLoggingDevicePriv* mPriv;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_ABSTRACTLOGGINGDEVICE_H_
