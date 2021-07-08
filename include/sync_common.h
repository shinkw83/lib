/*
 * sync_common.h
 *
 *  Created on: 2018. 5. 16.
 *      Author: shinkw
 */

#ifndef SOURCE_LIB_SYNC_MANAGER_SYNC_COMMON_H_
#define SOURCE_LIB_SYNC_MANAGER_SYNC_COMMON_H_

#include <thread>
#include <mutex>
#include <set>
#include <atomic>
#include <iostream>
#include <deque>
#include <vector>

#include "sioclog.h"
#include "xthread.h"

extern "C" {
#include <curl/curl.h>
}

#include "json.h"


typedef struct proc_info {
	std::string proc_name;
	std::string serial_no;
	std::string redis_key;
	std::vector<std::string> device_code;
	std::string device_id;
	std::string vendor_code;

	std::string area_id;
	std::string area_name;

	std::string tms_api_url;
	std::string dev_detail_url;
	std::string dev_reg_url;
	std::string dev_sync_req_edit_url;
	std::string dev_sync_req_find_url;
	std::string dev_status_url;

	uint log_level;
	uint status_notify_duration;
	uint ping_count;

	proc_info() {
		log_level = 2;
		status_notify_duration = 5;
		ping_count = 3;
	}
} proc_info;

typedef struct device_info {
	std::string device_id;
	std::string device_name;
	std::string device_code;
	std::string device_type_code;
	std::string serial_no;
	std::string area_id;
	std::string area_name;
	std::string vendor_code;
	std::string ip_address;
	uint port;
	std::string id;
	std::string password;
	std::string link_url;
	std::string del_yn;
	std::string mainFlag;
	std::string version;
	std::string config;
	std::string parent_device_id;

	device_info() {
		port = 0;
	}

} device_info;

enum { device_add = 1, device_modify = 2, device_delete = 3 };

typedef struct device_sync_msg {
	int type;	// add = 1, modify = 2, delete = 3
	device_info info;

	device_sync_msg() {
		type = -1;
	}

} device_sync_msg;

size_t sync_manager_write_to_string(void *contents, size_t size, size_t nmemb, std::string *s);
void ltrim(std::string &text);

#endif /* SOURCE_LIB_SYNC_MANAGER_SYNC_COMMON_H_ */
