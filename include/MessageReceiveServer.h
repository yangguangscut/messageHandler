/*
 *MessageReceiveServer.h
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */

#ifndef MESSAGERECEIVESERVER_H_
#define MESSAGERECEIVESERVER_H_
#include<string>
using std::string;

/**
 * 消息接收服务器，用来处理用户的消息拉取请求。
 */
class MessageReceiveServer {
	public:
		MessageReceiveServer(int port, int backlog, string sqlHost, int sqlPort,
				string dbName, string sqlUser, string sqlPwd);
		/**
		 * 初始化服务器，开始监听套接字接口。
		 */
		bool init();
		/**
		 * 启动服务，对接收到的请求进行处理
		 */
		void start();
		/**
		 * 关闭数据库连接
		 */
		virtual ~MessageReceiveServer();
	private:
		/**
		 * Listen port.
		 */
		int port;
		/**
		 * the max number of the accept waiting list.
		 */
		int backlog;
		/**
		 * the server socket used to listen request.
		 */
		int serverSocket;

		string sqlHost;
		int sqlPort;
		string dbName;
		string sqlUser;
		string sqlPwd;

};

/**
 * 处理具体的接收消息操作，接收到用户请求后，创建新的线程，将指定该函数作为新的线程的入口。
 */
void * doReceive(void * argument);

#endif /* MESSAGESERVERTHREAD_H_ */
