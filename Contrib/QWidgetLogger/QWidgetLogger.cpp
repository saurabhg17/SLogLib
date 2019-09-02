// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include <QtCore/QThread>
#include <QtWidgets/QScrollBar>
#include "SLogLib/SLogLib.h"
#include "QWidgetLogger.h"

using namespace SLogLib;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
QWidgetLogger::QWidgetLogger(SLogLib::AbstractFormatter* formatter)
	: AbstractLoggingDevice(formatter)
{
	mLogTextEdit = new SLogTextEdit();
}
QWidgetLogger::QWidgetLogger(SLogLib::AbstractFormatter* formatter, const std::string& name)
	: AbstractLoggingDevice(formatter, name), mLogTextEdit(nullptr)
{
	mLogTextEdit = new SLogTextEdit();
}
QWidgetLogger::~QWidgetLogger()
{
	//mLogTextEdit is automatically deleted by Qt.
	AbstractLoggingDevice::_FlushBufferedMessages();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void QWidgetLogger::_WriteMessage(const std::string& message)
{
	mLogTextEdit->_WriteMessage(message);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
SLogTextEdit::SLogTextEdit(QWidget* parent) : QTextEdit(parent)
{
	setReadOnly(true);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setAcceptRichText(false);
	setContextMenuPolicy(Qt::NoContextMenu);
	setUndoRedoEnabled(false);

	QFont font("Monospace");
	font.setStyleHint(QFont::TypeWriter);
	font.setPointSize(12);
	setFont(font);

	connect(this, SIGNAL(WriteMessageInMainThread(const QString&)), this, SLOT(WriteMessage(const QString&)));
}
void SLogTextEdit::_WriteMessage(const std::string& message)
{
	QString _message = message.c_str();
	
	// In Qt, any UI element such as QTextEdit can only be updated from the 
	// main thread i.e the thread in which QEventLoop is running. Here we check,
	// if the current thread is the thread which created this QTextEdit. If it is not,
	// then emit a signal which is connected to the WriteMessage(const QString&) slot.
	// Since, slots are always received in the main thread, message can be logged successfully.
	if(QThread::currentThread() != thread())
	{
		emit WriteMessageInMainThread(_message);
	}
	else
	{
		WriteMessage(_message);
	}
}
void SLogTextEdit::WriteMessage(const QString& message)
{
	Q_ASSERT(QThread::currentThread() == thread());

	append(message);

	QScrollBar* _scrollBar = verticalScrollBar();
	if(_scrollBar)
	{
		_scrollBar->setValue(_scrollBar->maximum());
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
