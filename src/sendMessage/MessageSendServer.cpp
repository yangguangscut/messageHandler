/*
 * Message send server
 * *
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
#include "MessageSendServer.h"
#include "socketConnect.h"
#include "msgCommand.h"
#include "jsonTransfer.h"
#include "MessageDao.h"
#include "callParams.h"

using namespace std;

MessageSendServer::MessageSendServer(int port, int backlog, string sqlHost,
		int sqlPort, string dbName, string sqlUser, string sqlPwd) {
	this->port = port;
	this->backlog = backlog;
	this->serverSocket = -1;
	this->sqlHost = sqlHost;
	this->sqlPort = sqlPort;
	this->dbName = dbName;
	this->sqlUser = sqlUser;
	this->sqlPwd = sqlPwd;
}
bool MessageSendServer::init() {
	this->serverSocket = createServerSocket(this->port, backlog);
	if (serverSocket == -1) {
		return false;
	}
	cout << "[OK] message send server is initialized successfully." << endl;
	return true;
}

void MessageSendServer::start() {
	cout << "[OK] start message send server." << endl;
	if (this->serverSocket == -1) {
		cout << "[FA] failed to start receive server. Port may have been used."
				<< endl;
		return;
	}
	while (1) {
		int clientSocket = acceptClientSocket(this->serverSocket);
		if (clientSocket != -1) {
			cout << "[OK] catch a connect. now handle it." << endl;
			struct callParams * params = new callParams;
			params->clientSocket = clientSocket;
			params->sqlHost = this->sqlHost;
			params->sqlPort = this->sqlPort;
			params->dbName = this->dbName;
			params->sqlUser = this->sqlUser;
			params->sqlPwd = this->sqlPwd;
			pthread_t thread;
			if (0 != (pthread_create(&thread, NULL, doSend, params))) {
				cout << "pthread_create() error" << endl;
				break;
			}
		}
	}
}

MessageSendServer::~MessageSendServer() {
	if (this->serverSocket != -1) {
		close(this->serverSocket);
	}
	cout << "[OK] server closed!" << endl;
}

void * doSend(void * callParams) {
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
	if (cmd != "") {
		cmd_sendMsg msgcmd;
		bool success = getSendMsgCmd(cmd, msgcmd);
		if (success) {
			string result;
			bool success = messageDao.addMsg(msgcmd.fromUserId, msgcmd.toUserId,
					msgcmd.message);
			if (success) {
				result.append("{\"result\":1,\"msg\":\"Send successful!\"}");
			} else {
				result.append("{\"result\":0,\"msg\":\"Send failed!\"}");
			}
			int count = send(clientSockfd, result.c_str(), result.size(), 0);
			if (count == result.size()) {
				cout << "send success." << endl;
			}
		}
		// 目前一个连接只处理一个命令
	}
	close(clientSockfd);
	return NULL; // nothing need to be returned.
}

