// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include <QtCore/QtGlobal>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include "SLogLib/SLogLib"
#include "QWidgetLogger.h"
#include "SLogLib/Formatters/HtmlFormatter.h"

const int NUM_THREADS  = 10;
const int NUM_MESSAGES = 100;

void test_logging()
{
	int tid = SLogLib::getCurrentThreadID();
	for(int i = 0 ; i < NUM_MESSAGES ; ++i)
	{
		SLOGLIB_LOG_MSG_INFO("TID=" << tid << "    " << i);
	}

	SLOGLIB_LOG_MSG_ERROR("TID=" << tid << "  Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum");
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidgetLogger* _logger = new QWidgetLogger(new SLogLib::HtmlFormatter());
	_logger->widget()->show();
	SLogLib::addLoggingDevice(_logger);
	
	std::vector<std::thread> _threads;
	for(int i = 0 ; i < NUM_THREADS ; ++i)
	{
		_threads.emplace_back(std::thread(test_logging));
	}

	for(std::thread& _thread : _threads)
	{
		if(_thread.joinable())
		{
			_thread.join();
		}
	}

	SLOGLIB_LOG_MSG_INFO("PID=" << SLogLib::getCurrentProcessID());

	return a.exec();
}
