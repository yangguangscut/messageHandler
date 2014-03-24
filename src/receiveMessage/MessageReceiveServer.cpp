/*
 * MessageServerThread.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include "MessageReceiveServer.h"
#include "socketConnect.h"
#include "msgCommand.h"
#include "jsonTransfer.h"
#include "MessageDao.h"
#include "callParams.h"

using namespace std;

MessageReceiveServer::MessageReceiveServer(int port, int backlog,
		string sqlHost, int sqlPort, string dbName, string sqlUser,
		string sqlPwd) {
	this->port = port;
	this->backlog = backlog;
	this->serverSocket = -1;
	this->sqlHost = sqlHost;
	this->sqlPort = sqlPort;
	this->dbName = dbName;
	this->sqlUser = sqlUser;
	this->sqlPwd = sqlPwd;
}

bool MessageReceiveServer::init() {
	this->serverSocket = createServerSocket(this->port, backlog);
	if (serverSocket == -1) {
		return false;
	}
	cout << "[OK] message receive server is initialized successfully." << endl;
	return true;
}

void MessageReceiveServer::start() {
	cout << "[OK] start message receive server, listen on port " << this->port
			<< endl;
	if(this->serverSocket==-1){
		cout<<"[FA] failed to start receive server. Port may have been used."<<endl;
		return;
	}
	while (1) {
		// 接收一个客户端连接
		int clientSocket = acceptClientSocket(this->serverSocket);
		cout << "[OK] catch a connect. now handle it." << endl;
		// 创建一个线程处理该连接
		struct callParams * params = new callParams; // 向新线程传递的参数。
		params->clientSocket = clientSocket;
		params->sqlHost = this->sqlHost;
		params->sqlPort = this->sqlPort;
		params->dbName = this->dbName;
		params->sqlUser = this->sqlUser;
		params->sqlPwd = this->sqlPwd;
		if (clientSocket != -1) {
			pthread_t thread;
			if (0 != (pthread_create(&thread, NULL, doReceive, params))) {
				cout << "pthread_create() error" << endl;
				break;
			}
		}
	}
}

MessageReceiveServer::~MessageReceiveServer() {
	if (this->serverSocket != -1) {
		close(this->serverSocket);
	}
	cout << "[OK] server closed!" << endl;
}

void * doReceive(void * callParams) {
	struct callParams * params = (struct callParams *) callParams;
	string sqlHost = params->sqlHost;
	int sqlPort = params->sqlPort;
	string dbName = params->dbName;
	string sqlUser = params->sqlUser;
	string sqlPwd = params->sqlPwd;
	int clientSockfd = params->clientSocket;
	delete params;
	MessageDao messageDao = MessageDao(sqlHost, sqlPort, dbName, sqlUser,
			sqlPwd);
	messageDao.init();
	string cmd;
	readJSON(clientSockfd, -1, cmd);
	bool success = false;
	string result;
	if (cmd != "") {
		cmd_receiveMsg msgcmd;
		bool success = getReceiveMsgCmd(cmd, msgcmd);
		if (success) {
			success = messageDao.getUnreadMsgs(msgcmd.userID, result);
		}
	}
	if (!success) {
		result.append("{\"result\":0,\"msg\":\"Receive failed!\"}");
	}
	int count = send(clientSockfd, result.c_str(), result.size(), 0);
	if (count == result.size()) {
		clog << "send success." << endl;
	}
	// 目前一个连接只处理一个命令
	close(clientSockfd);
	return NULL; // nothing need to be returned.
}

