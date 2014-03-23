/*
 * MessageDao.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#include "MessageDao.h"
#include "mysqlConnect.h"
#include <string>
#include <iostream>
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
		cout << "[OK] database " << this->dbName << " inited.";
		return true;
	} else {
		return false;
	}
}

bool MessageDao::addMsg(string from, string to, string msg) {
	if (this->database == NULL) {
		cout << "database doesn't exist!" << endl;
		return false;
	}
	string query = "u" + to;
	// 1. 查看用户的表是否存在
	MYSQL_RES * tables = mysql_list_tables(this->database, query.c_str());
	bool exists=true;
	if(tables==NULL){
		exists=false;
	}
	if(exists){
		MYSQL_ROW row=mysql_fetch_row(tables);
		if(row==NULL){
			exists=false;
		}else{
			char * tablename=row[0];

		}
	}
	cout  <<"table u"<<to<<" doesn't exist!";



	query = "insert into u" + to + " (peer_id,data,time) values (" + from + ","
			+ msg + ",now())";
	int failed = mysql_query(this->database, query.c_str());
	if (failed) {
		return false;
	}

	if (this->database != NULL) {

	}
	return false;
}

MessageDao::~MessageDao() {
	// TODO Auto-generated destructor stub
}

