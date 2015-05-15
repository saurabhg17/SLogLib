
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

#include "QWidgetLogger.h"
#if QT_VERSION >= 0x050000
	#include <QtWidgets/QHBoxLayout>
#elif QT_VERSION >= 0x040000
	#include <QtGui/QHBoxLayout>
#endif

using namespace SLogLib;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
QWidgetLogger::QWidgetLogger(AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter)
{
	_Initialize();
}
QWidgetLogger::QWidgetLogger(AbstractFormatter* formatter, const std::string& name)
	: AbstractLoggingDevice(formatter, name)
{
	_Initialize();
}
QWidgetLogger::QWidgetLogger(AbstractFormatter* formatter, const std::string& name, bool isEnabled, bool isBuffered, size_t numBufferedMessages)
	: AbstractLoggingDevice(formatter, name, isEnabled, isBuffered, numBufferedMessages)
{
	_Initialize();
}
QWidgetLogger::~QWidgetLogger()
{
	AbstractLoggingDevice::_FlushBufferedMessages();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void QWidgetLogger::_Initialize()
{
	mTextEdit = new QTextEdit;
	mTextEdit->setReadOnly(true);
	
	QFont font("Monospace");
	font.setStyleHint(QFont::TypeWriter);
	mTextEdit->setFont(font);
	
	QHBoxLayout* _layout = new QHBoxLayout();
	_layout->setContentsMargins(0, 0, 0, 0);
	_layout->addWidget(mTextEdit);
	this->setLayout(_layout);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void QWidgetLogger::_WriteMessage(const std::string& message)
{
	//mTextEdit->append(message.c_str());
	QString _currentText = mTextEdit->toPlainText();
	mTextEdit->setPlainText(QString("%1%2").arg(_currentText, message.c_str()));
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
