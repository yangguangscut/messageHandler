/*
 * mysqlConnect.h
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#ifndef MYSQLCONNECT_H_
#define MYSQLCONNECT_H_

#include <string>
using std::string;

/**
 * 连接数据库服务器
 */
MYSQL * msql_connect_db(string host, int port, string user, string password,
		string dbs);
/**
 * 检测某个表是否存在
 */
bool tableExists(MYSQL * database, string tablename);

/**
 * 执行一条sql语句
 */
bool execQuery(MYSQL * database, string query);

#endif /* MYSQLCONNECT_H_ */
