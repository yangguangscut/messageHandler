/*
 * testClient.c
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include "socketConnect.h"
#include <iostream>
#include <string>
using namespace std;
#define MAXLINE 4096
int main(int argc, char** argv) {
	int sockfd;
	struct sockaddr_in server_address;
	string data = "{\"action\":\"sendMsg\",\"id\":\"969041723\"}";

	string hostname="127.0.0.1";
	sockfd = createClientSocket((char*)hostname.c_str(), 9001);
	if (sockfd == -1) {
		cout<<"create client socket failed"<<endl;
		return 1;
	}
	int count=send(sockfd, data.c_str(), data.size(), 0);
	int returnCode=0;
	if(count<=0){
		cout<<"send() error"<<endl;
		returnCode=1;
	}
	close(sockfd);
	return returnCode;
}
