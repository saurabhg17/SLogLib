
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

#ifndef QWIDGETLOGGER_H
#define QWIDGETLOGGER_H

#include <QtCore/QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets/QWidget>
	#include <QtWidgets/QTextEdit>
#elif QT_VERSION >= 0x040000
	#include <QtGui/QWidget>
	#include <QtGui/QTextEdit>
#endif
#include "SLogLib/Devices/AbstractLoggingDevice.h"

class QWidgetLogger : public QWidget, public SLogLib::AbstractLoggingDevice
{
	Q_OBJECT
	
public:
	
	QWidgetLogger(SLogLib::AbstractFormatter* formatter);
	QWidgetLogger(SLogLib::AbstractFormatter* formatter, const std::string& name);
	QWidgetLogger(SLogLib::AbstractFormatter* formatter, const std::string& name, bool isEnabled, bool isBuffered, size_t numBufferedMessages);
	~QWidgetLogger();
	
private:
	
	// Write a single message to the logging device.
	void _WriteMessage(const std::string& message);

	void _Initialize();
	
private:
	
	QTextEdit* mTextEdit;
};

#endif // QWIDGETLOGGER_H
