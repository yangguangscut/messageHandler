/*
 * mysqlConnect.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
using namespace std;

MYSQL * msql_connect_db(string host, int port, string user, string password,
		string dbs) {
	MYSQL * con = mysql_init(NULL);
	MYSQL * con_res;
	con_res = mysql_real_connect(con, host.c_str(), user.c_str(),
			password.c_str(), dbs.c_str(), port, NULL, 0);
	if (con_res == NULL) {
		return NULL;
	} else {
		return con;
	}
}

bool tableExists(MYSQL * database, string tablename) {
	MYSQL_RES * tables = mysql_list_tables(database, tablename.c_str());
	bool exists = true;
	if (tables == NULL) {
		exists = false;
	}
	if (exists) {
		MYSQL_ROW row = mysql_fetch_row(tables);
		if (row == NULL) {
			exists = false;
		} else {
			char * name = row[0];
			if (tablename != name) {
				exists = false;
			}
		}
	}
	return exists;
}

bool execQuery(MYSQL * database, std::string query) {
	int failed = mysql_query(database, query.c_str());
	if (failed) {
		return false;
	}
	return true;
}



