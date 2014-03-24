/*
 * testMessageDao.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: yang
 */

#include "MessageDao.h"
#include <string>
#include <iostream>
using namespace std;
int main() {
	string sqlHost = "125.216.243.181";
	int sqlPort = 3306;
	string dbName = "msg";
	string sqlUser = "root";
	string sqlPwd = "123456";
	MessageDao * messageDao = new MessageDao(sqlHost, sqlPort, dbName, sqlUser,
			sqlPwd);
	bool success = messageDao->init();
	if (success) {
		cout << "[OK] init database " << dbName << endl;
		string from = "969041723";
		string to = "812035671";
		string msg = "this is a test!";
		success = messageDao->addMsg(&from, &to, &msg);
		if (success) {
			cout << "[OK] add message." << endl;
		} else {
			cout << "[FA] add message." << endl;
		}
		string json;
		messageDao->getUnreadMsgs(&to, &json);
		if (success) {
			cout << "[OK] get message." << json << endl;
		} else {
			cout << "[FA] get message." << json << endl;
		}
	} else {
		cout << "[FA] init database " << dbName << endl;
	}
	delete messageDao;
	return 0;
}
