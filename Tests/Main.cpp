// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "SLogLib/SLogLib"
#include "SLogLib/SysUtils.h"
#include <thread>
#include <iostream>

using namespace SLogLib;

const int       NUM_THREADS  = 100;
const int       NUM_MESSAGES = 1000;

int                    threadID     = 1;
std::mutex             threadIDMutex;

std::list<std::string> loggerNames;
std::mutex             loggerNamesMutex;

void test_logging()
{
	std::lock_guard<std::mutex> _lock1(threadIDMutex);
	{
		if(threadID % 5 == 0)
		{
			std::cout << threadID << " ";

			std::lock_guard<std::mutex> _lock(loggerNamesMutex);
			std::string _loggerName = loggerNames.front();
			loggerNames.pop_front();
			removeLoggingDevice(_loggerName);
		
			std::stringstream _fileNameStream;
			_fileNameStream << "Test" << threadID << ".log";
		
			std::stringstream _loggerNameStream;
			_loggerNameStream << "FileLogger" << threadID;
		
			loggerNames.emplace_back(_loggerNameStream.str());
			addLoggingDevice(new FileLogger(_fileNameStream.str(), Open::Immediately, new InfoFormatter, _loggerNameStream.str()));
		}

		threadID++;
	}
	
	for(int i=0 ; i<NUM_MESSAGES ; ++i)
	{
		SLOGLIB_LOG_MSG_INFO("TID=" << getCurrentThreadID() << "    " << i);
	}
}

int main()
{
	//addLoggingDevice(new ConsoleLogger(new InfoFormatter));
	addLoggingDevice(new FileLogger("Test.log", Open::Immediately, new InfoFormatter, "FileLogger"));
	loggerNames.emplace_back("FileLogger");

	std::vector<std::thread> _threads;
	for(int i=0 ; i<NUM_THREADS ; ++i)
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
	
	SLOGLIB_LOG_MSG_INFO("PID=" << getCurrentProcessID());
	return 0;
}
