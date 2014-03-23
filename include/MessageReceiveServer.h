/*
 * MessageServerThread.h
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */

#ifndef MESSAGESERVERTHREAD_H_
#define MESSAGESERVERTHREAD_H_
#include<string>
#include<vector>
using namespace std;
class MessageReceiveServer {
	public:
		MessageReceiveServer(int port, int backlog);
		bool init();
		void start();
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

};

void * run(void * argument);
vector<string> receiveMessages(string user);

#endif /* MESSAGESERVERTHREAD_H_ */
