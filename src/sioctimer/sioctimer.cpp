#include "sioctimer.h"

sioc_timer::sioc_timer() : io_(), work_(io_), strand_(io_) {
	io_thread_ = std::thread(&sioc_timer::start_io, this);

	id_ = 0;

	for (int i = 0; i < MAX_TIMER_COUNT; i++) {
		timer_map_[i] = nullptr;
		func_map_[i] = nullptr;
		repeat_map_[i] = false;
	}
}

sioc_timer::~sioc_timer() {
	io_.stop();

	if (io_thread_.joinable()) {
		io_thread_.join();
	}
}

void sioc_timer::start_io() {
	io_.run();
}

int sioc_timer::get_timer(expire_func func, bool repeat_expire) {
	if (id_ >= MAX_TIMER_COUNT) {
		Log(ERROR_LOG_LEVEL, "[sioc_timer] Timer is full.");
		return -1;
	}

	int id = id_++;
	timer_map_[id] = std::make_shared<boost::asio::steady_timer>(io_);
	func_map_[id] = std::move(func);
	repeat_map_[id] = repeat_expire;

	return id;
}

void sioc_timer::set_timer(int id, int seconds) {
	auto timer = timer_map_.find(id);
	if (timer == timer_map_.end()) {
		Log(ERROR_LOG_LEVEL, "[sioc_timer] Set timer failed. Unknown id[%d]", id);
		return;
	}

	timer->second->expires_from_now(boost::asio::chrono::seconds(seconds));
	timer->second->async_wait(bind_executor(strand_, boost::bind(&sioc_timer::expire, this, boost::asio::placeholders::error, id, seconds)));
}

void sioc_timer::clear_timer(int id) {
	auto timer = timer_map_.find(id);
	if (timer == timer_map_.end()) {
		Log(ERROR_LOG_LEVEL, "[sioc_timer] Clear timer failed. Unknown id[%d]", id);
		return;
	}

	timer->second->cancel();
}

void sioc_timer::expire(const boost::system::error_code &e, const int &id, const int &seconds) {
	if (e != boost::asio::error::operation_aborted) {
		Log(INFO_LOG_LEVEL, "[sioc_timer] Expire timer id[%d]", id);
		auto timer = timer_map_.find(id);
		auto func = func_map_.find(id);
		auto repeat = repeat_map_.find(id);

		if (timer == timer_map_.end() or func == func_map_.end() or repeat == repeat_map_.end()) {
			Log(ERROR_LOG_LEVEL, "[sioc_timer] Critical error. Memory crash.");
			return;
		}

		func->second();

		if (repeat->second) {
			timer->second->expires_from_now(boost::asio::chrono::seconds(seconds));
			timer->second->async_wait(boost::asio::bind_executor(strand_, boost::bind(&sioc_timer::expire, this, boost::asio::placeholders::error, id, seconds)));
		}
	}
}