/*
 * messageServer.c
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */

#include "socketConnect.h"
#include "msgCommand.h"
#include "MessageReceiveServer.h"
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<pthread.h>
#include <string>
using std::string;

const int messageServerPort = 6001;
const int backlog = 10;
#define MAXLINE 40960

int main(int argc, char ** args) {
	MessageReceiveServer server=MessageReceiveServer(9001,10);
	server.init();
	server.start();
}

