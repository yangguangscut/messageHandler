/*
 * testJSON.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: yang
 */
#include "jsonTransfer.h"
#include "msgCommand.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char ** argv) {
//	string json =
//			"{\"action\":\"sendMsg\",\"from\":\"969041723\",\"to\":\"87614453\",\"msg\":\"this is a test \"}";
//
	string json = "{\"id\":\"969041723\"}";
	cmd_receiveMsg cmd;
	getReceiveMsgCmd(json, &cmd);
	cout << cmd.userID << endl;

	vector<messageInfo> messages = vector<messageInfo>();
	messageInfo messageInfo1, messageInfo2, messageInfo3;

	string data = "this. is a good test";
	string peer = "969041723";
	string time = "2014-03-22";

	messageInfo1.data = data;
	messageInfo1.peer_id = peer;
	messageInfo1.time = time;

	messageInfo2.data = data;
	messageInfo2.peer_id = peer;
	messageInfo2.time = time;

	messageInfo3.data = data;
	messageInfo3.peer_id = peer;
	messageInfo3.time = time;

	messages.push_back(messageInfo1);
	messages.push_back(messageInfo2);
	messages.push_back(messageInfo3);

	string result;
	toJSON(&messages, &result);
	cout << result;
}
