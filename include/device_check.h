/*
 * device_check.h
 *
 *  Created on: 2019. 7. 18.
 *      Author: shinkw83
 */

#ifndef SOURCE_LIB_SYNC_MANAGER_DEVICE_CHECK_H_
#define SOURCE_LIB_SYNC_MANAGER_DEVICE_CHECK_H_


#include "sync_common.h"


class device_check : public xthread {
public:
	device_check(std::string device_id, std::string device_host, std::string status_url);
	virtual ~device_check();

private:
	virtual int Proc();

	void SendDeviceStatus(std::string data);

private:
	std::string m_device_id;
	std::string m_device_host;

	std::string m_status_url;

	CURL *m_status_curl = nullptr;
	struct curl_slist *m_status_headerlist = nullptr;
};


#endif /* SOURCE_LIB_SYNC_MANAGER_DEVICE_CHECK_H_ */
