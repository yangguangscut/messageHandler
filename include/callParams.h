/*
 * callParams.h
 *
 *  Created on: Mar 23, 2014
 *      Author: yang
 */

#ifndef CALLPARAMS_H_
#define CALLPARAMS_H_
#include	<string>
using std::string;
/**
 * 创建新的线程时用来传递参数的结构体
 */
//struct callParams {
//		int * clientSocket; //用来读取和发送数据的客户端套接字
//		string * sqlHost; 	// 数据库的IP
//		int * sqlPort; 		// 数据库的端口
//		string * dbName; 	// 数据库的名字
//		string * sqlUser; 	// 数据库的用户
//		string * sqlPwd; 	// 数据库用户的密码
//};
struct callParams {
		int clientSocket; //用来读取和发送数据的客户端套接字
		string sqlHost; 	// 数据库的IP
		int sqlPort; 		// 数据库的端口
		string dbName; 	// 数据库的名字
		string sqlUser; 	// 数据库的用户
		string sqlPwd; 	// 数据库用户的密码
};

#endif /* CALLPARAMS_H_ */
