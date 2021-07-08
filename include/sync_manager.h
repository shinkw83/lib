/*
 * sync_manager.h
 *
 *  Created on: 2018. 5. 14.
 *      Author: shinkw
 */

#ifndef SOURCE_LIB_SYNC_MANAGER_SYNC_MANAGER_H_
#define SOURCE_LIB_SYNC_MANAGER_SYNC_MANAGER_H_

#include <pqxx/pqxx>

#include "sync_common.h"
#include "device_manager.h"
#include "device_check.h"
#include "subscriber.h"
#include "publisher.h"
#include "sioctimer.h"

typedef std::function<void(std::vector<device_sync_msg>)> deviceCallback;
typedef std::function<void()> alarmCallback;
typedef std::function<void()> mapChangeCallback;

class sync_manager : public xthread {
public:
	sync_manager();
	virtual ~sync_manager();

	bool InitSyncManager();
	bool CertifyTMS();

	void SetDeviceInfoCallbackFunc(deviceCallback func);
	void SetAlarmCallbackFunc(alarmCallback func);
	void SetMapChangeCallbackFunc(mapChangeCallback func);

	proc_info GetProcInfo() { return m_proc_info; }

	static std::string GetCurrentSystemTime();

	void SetDeviceListType(device_manager::get_list_type type) { m_get_list_type = type; }

private:
	virtual int Proc();

	void set_proc_info();
	bool init_curl();
	bool get_detail_info();
	void insert_device_id();

	void get_all_device_info();

	void sync_device_info();
	void send_device_info(std::vector<device_sync_msg> &device_sync_msg_list);

	void run_device_check(std::vector<device_info>::iterator iter);

	void send_hb_func();
	void subscribe_sync_th();

private:
	device_manager *m_devmgr = nullptr;

	pqxx::connection *m_pq_conn = nullptr;
	pqxx::work *m_pq_work = nullptr;

	bool m_use_docker = true;

	proc_info m_proc_info;

	CURL *m_curl = nullptr;
	struct curl_slist *m_headerlist = nullptr;

	std::mutex m_device_mutex;
	std::map<std::string, device_info> m_device_info;

	deviceCallback m_cb_func = nullptr;
	alarmCallback m_alarm_cb = nullptr;
	mapChangeCallback m_map_cb = nullptr;

	device_manager::get_list_type m_get_list_type = device_manager::modify;

	std::map<std::string, device_check *> m_dev_stat_check;

	std::string m_mqtt_address;
	std::string m_mqtt_user;
	std::string m_mqtt_password;
	std::string m_mqtt_pub_client_id;
	std::string m_mqtt_sub_client_id;

	std::shared_ptr<mqtt_subscriber> m_mqtt_sub;
	std::shared_ptr<mqtt_publisher> m_mqtt_pub;

	sioc_timer m_hb_timer;
	int m_hb_timer_id = 0;
	int m_hb_time = 5;

	std::thread m_sync_sub_th;
};



#endif /* SOURCE_LIB_SYNC_MANAGER_SYNC_MANAGER_H_ */
