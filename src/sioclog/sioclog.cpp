/*
 * sioclog.cpp
 *
 *  Created on: 2018. 6. 8.
 *      Author: shinkw
 */


#include "sioclog.h"

sioc_log::sioc_log() {
	m_log_level = 4;
}

void sioc_log::Log(int level, const char *timestr, const char *logstr) {
	std::lock_guard<std::mutex> guard(m_log_mutex);

	std::cout << timestr << " ";
	if (level == DEBUG_LOG_LEVEL) {
		std::cout << "[DEBUG]   ";
	}

	if (level == INFO_LOG_LEVEL) {
		std::cout << "[INFO]    ";
	}

	if (level == WARN_LOG_LEVEL) {
		std::cout << "[WARNING] ";
	}

	if (level == ERROR_LOG_LEVEL) {
		std::cout << "[ERROR]   ";
	}

	if (level == INIT_LOG_LEVEL) {
		std::cout << "[INIT]    ";
	}

	std::string outstr = logstr;
	auto idx = outstr.find("\r\n");
	if (idx != std::string::npos) {
		outstr.replace(idx, 2, "--");
	}

	std::cout << outstr << std::endl;
}


void SetLogLevel(int level) {
	sioc_log *logmgr = sioc_log::GetInstance();
	logmgr->SetLogLevel(level);
}

void Log(int level, const char *format, ...) {
	if (format == nullptr) return;

	sioc_log *logmgr = sioc_log::GetInstance();
	if (level < logmgr->GetLogLevel()) return;

	char logstr[1024] = {0, };
	va_list ap;
	va_start(ap, format);
	vsnprintf(logstr, sizeof(logstr), format, ap);
	va_end(ap);

	using namespace std;
	using namespace std::chrono;

	system_clock::time_point now = system_clock::now();
	system_clock::duration tp = now.time_since_epoch();

	tp -= duration_cast<seconds>(tp);

	time_t tt = system_clock::to_time_t(now);
	struct tm *t = localtime(&tt);

	char timestr[1024] = {0, };
	snprintf(timestr, sizeof(timestr), "[%04u-%02u-%02u %02u:%02u:%02u.%03u]",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
			t->tm_sec, static_cast<unsigned>(tp / milliseconds(1)));

	logmgr->Log(level, timestr, logstr);
}
