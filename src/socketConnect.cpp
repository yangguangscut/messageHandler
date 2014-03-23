#include "socketConnect.h"
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include <iostream>
using namespace std;

int createClientSocket(char * ip, int port) {
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		return -1;
	}
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	int success = inet_pton(AF_INET, ip, &serverAddress.sin_addr);
	if (!success) {
		return -1;
	}
	serverAddress.sin_port = htons(port);
	serverAddress.sin_family = AF_INET;

	success = connect(clientSocket, (struct sockaddr*) &serverAddress,
			sizeof(serverAddress));
	if (success == -1) {
		return -1;
	}
	return clientSocket;
}

// 创建一个服务器套接字
int createServerSocket(int port, int backlog) {
	// 创建socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		return -1;
	}
	// 为socket指定地址
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	int success = bind(serverSocket, (struct sockaddr *) &serverAddress,
			sizeof(serverAddress));
	if (success == -1) {
		return -1;
	}
	// 让socket开始接收信息
	success = listen(serverSocket, backlog);
	if (success == -1) {
		return -1;
	}
	return serverSocket;
}

// 接收一个客户端套接字
int acceptClientSocket(int serverSocket) {
	int clientSocket = accept(serverSocket, NULL, NULL);
	return clientSocket;
}

string readJSON(int socketfd, int bufferSize) {
	if (bufferSize <= 0) {
		bufferSize = 4096;
	}
	int readCount;
	string cmd;
	char buff[bufferSize];
	memset(buff, '\0', bufferSize);
	int leftBrace = 0;
	int rightBrace = 0;
	bool find = false;
	bool escaped = false;
	while (1) {
		readCount = recv(socketfd, buff, bufferSize, 0);
		if (readCount <= 0) {
			cout << "read failed" << endl;
			break;
		} else {
			int i = 0;
			for (; i < readCount; i++) {
				if (buff[i] == '\\') {
					escaped = !escaped;
				} else if ((buff[i] == '{') && (!escaped)) {
					leftBrace++;
				} else if ((buff[i] == '}') && (!escaped)) {
					rightBrace++;
				}else{
					escaped=false;
				}
				if ((leftBrace == rightBrace) && (leftBrace > 0)) {
					find = true;
					break;
				}
			}
			if (find) {
				cmd.append(buff, i + 1);
				break;
				// only handle the first command.
			} else {
				cmd.append(buff, readCount);
			}
		}
	}
	if (find) {
		return cmd;
	} else {
		return "";
	}
}

