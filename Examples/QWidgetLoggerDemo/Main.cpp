
// This file is part of SLogLib; you can redistribute it and/or
// modify it under the terms of the MIT License.
// 
// Copyright (c) 2018 Saurabh Garg
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

#include <QtCore/QtGlobal>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include "SLogLib/SLogLib"
#include "QWidgetLogger.h"
#include "SLogLib/Formatters/HtmlFormatter.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	SLogLib::HtmlFormatter* _formatter = new SLogLib::HtmlFormatter();
	//_formatter->setBottomMargin(2);

	QWidgetLogger* _logger = new QWidgetLogger(_formatter);
	_logger->show();
	
	SLogLib::addLoggingDevice(_logger);
	SLOGLIB_LOG_MSG_INFO  ("Testing 1");
	SLOGLIB_LOG_MSG_WARN  ("Testing 2");
	SLOGLIB_LOG_MSG_ERROR ("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum");
	SLOGLIB_LOG_MSG_DEBUG ("Testing 4");
	SLOGLIB_LOG_MSG_DETAIL("Testing 5");

	return a.exec();
}
