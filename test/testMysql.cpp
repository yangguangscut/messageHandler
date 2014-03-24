/*
 * testMysql.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: yang
 */

#include <mysql/mysql.h>
#include "mysqlConnect.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
	// 测试连接
	MYSQL * database = msql_connect_db("125.216.243.181", 3306, "root",
			"123456", "msg");
	if (database == NULL) {
		cout << "[OK] open database failed" << endl;
	} else {
		cout << "[FA] open database success." << endl;
	}
	// 测试表的查找
	bool exists = tableExists(database, "u1");
	if (exists) {
		cout << "[OK] test u1 table exists." << endl;
	} else {
		cout << "[FA] test u1 table exists." << endl;
	}
	exists = tableExists(database, "notexist");
	if (exists) {
		cout << "[FA] test notexist table should not exists." << endl;
	} else {
		cout << "[OK] test notexist table should not exists." << endl;
	}
	// 测试语句的执行
	string tableName = "test_msg";
	string from = "969041723";
	string to = "812035671";
	string msg = "this is a test";
	string query = "insert into " + tableName + " (peer_id,data,time,is_handled) values ('"
			+ from + "','" + msg + "',0,now())";
	cout<<query<<endl;
	bool success = execQuery(database, query);
	if(success){
		cout <<"[OK] insert data into "+tableName<<endl;
	}else{
		cout <<"[FA] insert data into "+tableName<<endl;
	}
	mysql_close(database);
}

