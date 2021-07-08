/*
 * sioclog.h
 *
 *  Created on: 2018. 6. 8.
 *      Author: shinkw
 */

#ifndef SOURCE_LIB_SIOCLOG_SIOCLOG_H_
#define SOURCE_LIB_SIOCLOG_SIOCLOG_H_


#include <chrono>
#include <string>
#include <cstdarg>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <atomic>
#include <mutex>

#include "singleton.h"


#define DEBUG_LOG_LEVEL	1
#define INFO_LOG_LEVEL	2
#define WARN_LOG_LEVEL	3
#define ERROR_LOG_LEVEL	4
#define INIT_LOG_LEVEL	5


void Log(int level, const char *format, ...);
void SetLogLevel(int level);


class sioc_log : public singleton_T<sioc_log> {
public:
	sioc_log();
	virtual ~sioc_log() {}

	void SetLogLevel(int level) { m_log_level = level; }
	int GetLogLevel() { return m_log_level; }
	void Log(int level, const char *timestr, const char *logstr);

private:
	std::atomic<int> m_log_level;
	std::mutex m_log_mutex;
};



#endif /* SOURCE_LIB_SIOCLOG_SIOCLOG_H_ */
