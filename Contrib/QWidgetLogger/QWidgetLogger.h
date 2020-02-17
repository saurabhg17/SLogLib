// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_QWIDGETLOGGER_H_
#define _SLOGLIB_QWIDGETLOGGER_H_

#include <string>
#include <QtWidgets/QTextEdit>
#include "SLogLib/Devices/AbstractLoggingDevice.h"

// Forward declaration.
class QWidgetLogger;

// The SLogTextEdit class derives from QTextEdit to provide a widget for displaying 
// logging messages to the user. A good place to use this widget is in a QDockWiget.
// As SLogTextEdit derives from QTextEdit, any property from QWidget can be changed
// easily.
// 
// This class is thread-safe and message can to written to it from any thread and not 
// just the main-thread (i.e. the thread running QEventLoop).
class SLogTextEdit : public QTextEdit
{
	Q_OBJECT
	friend class QWidgetLogger;

	
public:
	
	explicit SLogTextEdit(QWidget* parent=nullptr);
	

private:
	
	void _WriteMessage(const std::string& message);


private slots:
	
	void WriteMessage(const QString& message);


signals:
	
	void WriteMessageInMainThread(const QString& message);

};

// The QWidgetLogger class is a logging device which writes messages to a SLogTextEdit.
// The widget() returns the widget to be added to UI to show log messages.
class QWidgetLogger : public SLogLib::AbstractLoggingDevice
{
	Q_DISABLE_COPY(QWidgetLogger)
	
public:

	explicit QWidgetLogger(SLogLib::AbstractFormatter* formatter);
	QWidgetLogger(SLogLib::AbstractFormatter* formatter, const std::string& name);
	~QWidgetLogger();

	SLogTextEdit* widget() const {return mLogTextEdit;}


private:

	void _WriteMessage(const std::string& message) override;
	

private:

	SLogTextEdit* mLogTextEdit;
};

#endif // _SLOGLIB_QWIDGETLOGGER_H_
