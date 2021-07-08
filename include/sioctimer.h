#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "sioclog.h"

#define MAX_TIMER_COUNT		100

typedef std::function<void()> expire_func;
typedef std::shared_ptr<boost::asio::steady_timer> timer_pointer;

class sioc_timer {
public:
	sioc_timer();
	~sioc_timer();

	void set_timer(int id, int seconds);
	void clear_timer(int id);

	int get_timer(expire_func func, bool repeat_expire);

private:
	void start_io();
	void expire(const boost::system::error_code &e, const int &id, const int &seconds);

private:
	boost::asio::io_context io_;
	boost::asio::io_context::work work_;
	boost::asio::io_context::strand strand_;

	std::atomic<int> id_;
	std::map<int, timer_pointer> timer_map_;
	std::map<int, expire_func> func_map_;
	std::map<int, bool> repeat_map_;

	std::thread io_thread_;
};