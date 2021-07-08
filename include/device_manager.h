/*
 * device_manager.h
 *
 *  Created on: 2018. 5. 14.
 *      Author: shinkw
 */

#ifndef SOURCE_LIB_SYNC_MANAGER_DEVICE_MANAGER_H_
#define SOURCE_LIB_SYNC_MANAGER_DEVICE_MANAGER_H_

#include "sync_common.h"

class device_manager : public xthread {
public:
	enum get_list_type { all, modify };
public:
	device_manager(proc_info &info);
	virtual ~device_manager();

	std::vector<device_info> GetDeviceList(get_list_type type);
	void SendDeviceStatus(string data);

private:
	virtual int Proc();

	void parsing_device_list(Json::Value &data_list, std::vector<device_info> &dev_list);
	void split_sync_req_id(std::string &sync_req_id, std::vector<std::string> *req_id_list);

	void push_sync_req_id(std::vector<std::string> *data);

private:
	proc_info m_proc_info;

	CURL *m_curl = nullptr;
	struct curl_slist *m_headerlist = nullptr;

	CURL *m_status_curl = nullptr;
	struct curl_slist *m_status_headerlist = nullptr;

	std::deque<std::vector<std::string> *> m_sync_req_queue;
	std::mutex m_sync_req_mutex;
};


#endif /* SOURCE_LIB_SYNC_MANAGER_DEVICE_MANAGER_H_ */
