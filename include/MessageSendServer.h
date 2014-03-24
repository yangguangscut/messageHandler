/*
 * MessageSendServer.h
 *
 *  Created on: Mar 23, 2014
 *      Author: yang
 */

#ifndef MESSAGESENDSERVER_H_
#define MESSAGESENDSERVER_H_
#include <iostream>
using std::string;
/**
 * 消息发送服务器，处理用户发送消息的请求。
 */
class MessageSendServer {
	public:
		MessageSendServer(int port, int backlog, string sqlHost, int sqlPort,
				string dbName, string sqlUser, string sqlPwd);
		/**
		 * 初始化服务器，在指定端口上监听请求。
		 */
		bool init();
		/**
		 * 启动服务器，服务器开始处理用户的请求。
		 */
		void start();
		/**
		 * 关闭数据库连接
		 */
		virtual ~MessageSendServer();
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
 * 具体处理用户发送消息请求的方法。当用户请求到来时，服务器创建新的线程处理用户的请求，将指定该方法作为新的线程的入口。
 */
void * doSend(void * argument);
#endif /* MESSAGESENDSERVER_H_ */
