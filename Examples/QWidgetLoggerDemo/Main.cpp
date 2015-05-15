
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

#include <QtCore/QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets/QApplication>
#elif QT_VERSION >= 0x040000
	#include <QtGui/QApplication>
#endif

#include "SLogLib/SLogLib"
#include "QWidgetLogger.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QWidgetLogger* _logger = new QWidgetLogger(new SLogLib::DetailedFormatter());
	_logger->show();
	SLogLib::addLoggingDevice(_logger);
	
	SLOGLIB_LOG_MSG_INFO("Testing 1");
	SLOGLIB_LOG_MSG_INFO("Testing 2");
	SLOGLIB_LOG_MSG_INFO("Testing 3");
	
	return a.exec();
}
