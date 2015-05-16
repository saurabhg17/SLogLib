
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
