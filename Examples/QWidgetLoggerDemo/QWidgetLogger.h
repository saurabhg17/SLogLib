
// Copyright (c) 2015 Saurabh Garg
// 
// This file is part of SLogLib; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License v2.1 as
// published by the Free Software Foundation.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
