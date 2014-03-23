/*
 * mysqlConnect.h
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#ifndef MYSQLCONNECT_H_
#define MYSQLCONNECT_H_

#include <string>

MYSQL * msql_connect_db(std::string host,int port, std::string user,
		std::string password, std::string dbs);

#endif /* MYSQLCONNECT_H_ */
