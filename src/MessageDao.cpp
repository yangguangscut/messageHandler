/*
 * MessageDao.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#include <string>
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <mysql/mysql.h>
#include "MessageDao.h"
#include "mysqlConnect.h"
#include "jsonTransfer.h"
using namespace std;
/**
 * This class is responsible for handle message database.
 */
MessageDao::MessageDao(string sqlHost, int sqlPort, string dbName,
		string sqlUser, string sqlPwd) {

	this->sqlHost = sqlHost;
	this->sqlPort = sqlPort;
	this->dbName = dbName;
	this->sqlUser = sqlUser;
	this->sqlPwd = sqlPwd;
	this->database = NULL;
}

bool MessageDao::init() {
	MYSQL * database = msql_connect_db(this->sqlHost, this->sqlPort,
			this->sqlUser, this->sqlPwd, this->dbName);
	if (database != NULL) {
		this->database = database;
		clog << "[OK] database " << this->dbName << " inited." << endl;
		return true;
	} else {
		return false;
	}
}

bool MessageDao::addMsg(string & from, string & to, string & msg) {
	if (this->database == NULL) {
		clog << "database doesn't exist!" << endl;
		return false;
	}
	string tableName = "u" + to;
	// 1. 查看用户的表是否存在
	bool exists = tableExists(this->database, tableName);
	if (!exists) {
		clog << "table " << tableName << " doesn't exist!" << endl;
		return false;
	}
	// 2. 向用户表中插入数据

	string query = "insert into " + tableName
			+ " (peer_id,data,time,is_handled) values ('" + from + "','" + msg
			+ "',now(),0)";
	bool success = execQuery(this->database, query);
	return success;

}

/**
 * 查看自己邮箱中未读的信息，将消息标志为已经处理的，然后删除该消息。
 */
bool MessageDao::getUnreadMsgs(string & userid, string & jsonString) {
	if (this->database == NULL) {
		clog << "database doesn't exist!" << endl;
		return false;
	}
	string tableName = "msg_" + userid;
	// 1. 查看用户的表是否存在
	bool exists = tableExists(this->database, tableName);
	if (!exists) {
		clog << "table " << tableName << " doesn't exist!" << endl;
		return false;
	}

	// 2. 查询用户的未处理消息
	string query = "select msg_id,peer_id,data,time from " + tableName
			+ " where is_handled=0 order by peer_id";
	bool success = execQuery(this->database, query);
	if (success) {
		MYSQL_RES * resultSet = mysql_store_result(this->database);
		MYSQL_ROW row = NULL;
		stringstream ss;
		ss << "{\"result\":1,";
		int totalMsg = resultSet->row_count;
		ss << "\"msg\":{\"totalmsg\":" << totalMsg << ",\"msgs\":[";
		string currentUser = "";
		int currentUserMsg = 0;
		int peerNum = 0;
		while ((row = mysql_fetch_row(resultSet)) != NULL) {
			// 根据查到的消息组装成json语句
			if (currentUser != row[1]) { //开始了一个新的用户
				if (peerNum != 0) { // 如果当前用户不是第一个用户
					// 将上一个用户的消息装好
					ss << "],\"msgnum\":" << currentUserMsg << "},";
				}
				peerNum++;
				currentUser = row[1];
				currentUserMsg = 0;
				ss << "{\"peer\":\"" << currentUser << "\",";
				ss << "\"data\":[";
			}
			if (currentUserMsg != 0) {
				ss << ",";
			}
			currentUserMsg++;
			ss << "{\"msg\":\"" << row[2] << "\",";
			ss << "\"time\":\"" << row[3] << "\"}";

			// 更新消息
			query = "update " + tableName + " set is_handled=1 where msg_id="
					+ row[0];
			success = execQuery(this->database, query);
			if (success) {
				clog << "update message successful at" << row[0] << endl;
			} else {
				cerr << "update message failed at " << row[0] << endl;
			}
		}
		if(totalMsg>0){
			ss << "],\"msgnum\":" << currentUserMsg << "}"; //关闭最后一个用户
		}
		ss << "]" << ",\"peernum\":" << peerNum << "}}";				// 关闭整条消息
		jsonString.append(ss.str());
		mysql_free_result(resultSet);
		return true;
	}
	return false;
}

MessageDao::~MessageDao() {
	if (this->database != NULL) {
		mysql_close(this->database);
		cout << "database " << this->dbName << " closed." << endl;
	}

}

