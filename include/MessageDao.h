/*
 * MessageDao.h
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#ifndef MESSAGEDAO_H_
#define MESSAGEDAO_H_

#include <string>
#include <mysql/mysql.h>
using namespace std;

class MessageDao {
	public:
		MessageDao(string sqlHost, int sqlPort, string dbName, string sqlUser,
				string sqlPwd);
		bool init();
		void getUnreadMsgs(string userid);
		bool addMsg(string from, string to, string msg);
		virtual ~MessageDao();
	private:
		string sqlHost;
		int sqlPort;
		string dbName;
		string sqlUser;
		string sqlPwd;
		MYSQL * database;
};

#endif /* MESSAGEDAO_H_ */
