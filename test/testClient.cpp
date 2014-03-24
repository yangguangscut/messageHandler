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
	string json;
	string data;
	string hostname = "127.0.0.1";
	int count;
	bool success;
	// 直接接收
	cout << "receive message of 812035671:" << endl;
	data = "{\"action\":\"receiveMsg\",\"id\":\"812035671\"}";

	sockfd = createClientSocket(hostname, 9002);
	if (sockfd == -1) {
		cout << "create client socket failed" << endl;
		return 1;
	}
	count = send(sockfd, data.c_str(), data.size(), 0);
	if (count <= 0) {
		cout << "send() error" << endl;
	}
	success = readJSON(sockfd, -1, json);
	if (success) {
		cout << json << endl;
	} else {
		cout << "get message failed,user may not exists." << endl;
	}
	close(sockfd);

	// 发送一条接收一条
	cout << "send message from 969041723 to 812035671:" << endl;
	data =
			"{\"action\":\"sendMsg\",\"from\":\"969041723\",\"to\":\"812035671\",\"msg\":\"这是一个神奇的测试\"}";
	sockfd = createClientSocket(hostname, 9001);
	if (sockfd == -1) {
		cout << "create client socket failed" << endl;
		return 1;
	}
	count = send(sockfd, data.c_str(), data.size(), 0);
	if (count <= 0) {
		cout << "send() error" << endl;
	}
	success = readJSON(sockfd, -1, json);
	if (success) {
		cout << json << endl;
		json.clear();
	} else {
		cout << "send message failed,user may not exists." << endl;
	}
	close(sockfd);

	cout << "receive message of 812035671:" << endl;
	data = "{\"action\":\"receiveMsg\",\"id\":\"812035671\"}";

	sockfd = createClientSocket(hostname, 9002);
	if (sockfd == -1) {
		cout << "create client socket failed" << endl;
		return 1;
	}
	count = send(sockfd, data.c_str(), data.size(), 0);
	if (count <= 0) {
		cout << "send() error" << endl;
	}
	success = readJSON(sockfd, -1, json);
	if (success) {
		cout << json << endl;
	} else {
		cout << "get message failed,user may not exists." << endl;
	}
	close(sockfd);

	// 发送10条去接收
	for (int i = 0; i < 10; i++) {
		// 1. 发送消息
		cout << "send message from 969041723 to 812035671:" << endl;
		data =
				"{\"action\":\"sendMsg\",\"from\":\"969041723\",\"to\":\"812035671\",\"msg\":\"这是一个神奇的测试\"}";
		sockfd = createClientSocket(hostname, 9001);
		if (sockfd == -1) {
			cout << "create client socket failed" << endl;
			return 1;
		}
		count = send(sockfd, data.c_str(), data.size(), 0);
		if (count <= 0) {
			cout << "send() error" << endl;
		}
		success = readJSON(sockfd, -1, json);
		if (success) {
			cout << json << endl;
			json.clear();
		} else {
			cout << "send message failed,user may not exists." << endl;
		}
		close(sockfd);
	}

	cout << "receive message of 812035671:" << endl;
	data = "{\"action\":\"receiveMsg\",\"id\":\"812035671\"}";

	sockfd = createClientSocket(hostname, 9002);
	if (sockfd == -1) {
		cout << "create client socket failed" << endl;
		return 1;
	}
	count = send(sockfd, data.c_str(), data.size(), 0);
	if (count <= 0) {
		cout << "send() error" << endl;
	}
	success = readJSON(sockfd, -1, json);
	if (success) {
		cout << json << endl;
	} else {
		cout << "get message failed,user may not exists." << endl;
	}
	close(sockfd);

	// 不同的用户发送去接收
	for (int i = 0; i < 5; i++) {
		// 1. 发送消息
		cout << "send message from 969041723 to 812035671:" << endl;
		data =
				"{\"action\":\"sendMsg\",\"from\":\"969041723\",\"to\":\"812035671\",\"msg\":\"这是一个神奇的测试\"}";
		sockfd = createClientSocket(hostname, 9001);
		if (sockfd == -1) {
			cout << "create client socket failed" << endl;
			return 1;
		}
		count = send(sockfd, data.c_str(), data.size(), 0);
		if (count <= 0) {
			cout << "send() error" << endl;
		}
		success = readJSON(sockfd, -1, json);
		if (success) {
			cout << json << endl;
			json.clear();
		} else {
			cout << "send message failed,user may not exists." << endl;
		}
		close(sockfd);
	}
	for (int i = 0; i < 5; i++) {
		// 1. 发送消息
		cout << "send message from 747235671 to 812035671:" << endl;
		data =
				"{\"action\":\"sendMsg\",\"from\":\"747235671\",\"to\":\"812035671\",\"msg\":\"这是一个神奇的测试\"}";
		sockfd = createClientSocket(hostname, 9001);
		if (sockfd == -1) {
			cout << "create client socket failed" << endl;
			return 1;
		}
		count = send(sockfd, data.c_str(), data.size(), 0);
		if (count <= 0) {
			cout << "send() error" << endl;
		}
		success = readJSON(sockfd, -1, json);
		if (success) {
			cout << json << endl;
			json.clear();
		} else {
			cout << "send message failed,user may not exists." << endl;
		}
		close(sockfd);
	}

	cout << "receive message of 812035671:" << endl;
	data = "{\"action\":\"receiveMsg\",\"id\":\"812035671\"}";

	sockfd = createClientSocket(hostname, 9002);
	if (sockfd == -1) {
		cout << "create client socket failed" << endl;
		return 1;
	}
	count = send(sockfd, data.c_str(), data.size(), 0);
	if (count <= 0) {
		cout << "send() error" << endl;
	}
	success = readJSON(sockfd, -1, json);
	if (success) {
		cout << json << endl;
	} else {
		cout << "get message failed,user may not exists." << endl;
	}
	close(sockfd);

	return 0;
}
