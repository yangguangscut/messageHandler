/*
 * message send Server
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */

#include "socketConnect.h"
#include "msgCommand.h"
#include "MessageSendServer.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <stdlib.h>
using std::string;
using std::cout;
using std::endl;

void printUsage(char * name) {
	cout << "usage:" << endl;
	cout << name
			<< " <port> <sqlHost> <sqlPort> <dbName> <sqlUser> <sqlPassword>"
			<< endl;
}

int main(int argc, char ** args) {
	if (argc < 7) {
		printUsage(args[0]);
	}
	int port = atoi(args[1]);
	int backlog = 10;
	string sqlHost = args[2];
	int sqlPort = atoi(args[3]);
	string dbName = args[4];
	string sqlUser = args[5];
	string sqlPwd = args[6];

	MessageSendServer server = MessageSendServer(port, backlog, sqlHost,
			sqlPort, dbName, sqlUser, sqlPwd);
	bool success=server.init();
	if(success){
		server.start();
	}
}

