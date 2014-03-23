/*
 * MessageServerThread.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */

#include "MessageReceiveServer.h"
#include "socketConnect.h"
#include "stdlib.h"
#include "msgCommand.h"
#include "jsonTransfer.h"
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string>
#include <iostream>
using namespace std;

MessageReceiveServer::MessageReceiveServer(int port, int backlog) {
	this->port = port;
	this->backlog = backlog;
	this->serverSocket = -1;
}
bool MessageReceiveServer::init() {
	int serverSocket = createServerSocket(this->port, backlog);
	if (serverSocket == -1) {
		return false;
	}
	this->serverSocket = serverSocket;
	cout<<"[OK] message receive server is initialized successfully."<<endl;
	return true;
}

void MessageReceiveServer::start() {
	cout<<"[OK] start message receive server."<<endl;
	while (1) {
		int * clientSocket = (int *)malloc(sizeof(int));
		*clientSocket = acceptClientSocket(this->serverSocket);
		cout<<"[OK] catch a connect. now handle it."<<endl;
		if (*clientSocket != -1) {
			pthread_t thread;
			if (0 != (pthread_create(&thread, NULL, run, clientSocket))) {
				cout<<"pthread_create() error"<<endl;
				break;
			}
		}
	}
}

MessageReceiveServer::~MessageReceiveServer(){
	close(this->serverSocket);
	cout<<"[OK] server closed!"<<endl;
}

vector<string> receiveMessages(string user) {
	cout << "receiveMessages from user: " << user << endl;
	vector<string> result;
	return result;
}

void * run(void * clientSocket) {
	int clientSockfd = *((int *) clientSocket);
	string cmd = readJSON(clientSockfd, -1);
	if (cmd != "") {
		cmd_receiveMsg * msgcmd = getReceiveMsgCmd(cmd);
		if (msgcmd != NULL) {
			receiveMessages(msgcmd->userID);
			free(msgcmd);
		}
		// 目前一个连接只处理一个命令
	}
	free (clientSocket);
	close(clientSockfd);
	return NULL; // nothing need to be returned.
}


