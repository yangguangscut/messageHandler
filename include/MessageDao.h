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
#include <pthread.h>
using namespace std;

/**
 * 该类用来对用户的消息数据库进行管理，主要包括从数据库中获取尚未处理的消息，以及向数据库中插入一条消息。
 */
class MessageDao {
	public:
		MessageDao(string sqlHost, int sqlPort, string dbName, string sqlUser,
				string sqlPwd);
		/**
		 * 初始化数据库，打开数据库连接。
		 */
		bool init();
		/**
		 * 获取未处理的消息，并将其从数据库中删除
		 */
		bool getUnreadMsgs(string & userid, string & jsonString);
		/**
		 * 在接收方的数据库表中插入一条消息记录。
		 */
		bool addMsg(string & from, string & to, string & msg);
		/**
		 * 如果连接打开了，那么关闭数据库连接。
		 */
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
