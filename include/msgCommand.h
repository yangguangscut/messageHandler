/*
 * command.h
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#ifndef MSG_COMMAND_H_
#define MSG_COMMAND_H_
#include <string>
using std::string;

/**
 * receive message:
 * {
 * 		"action":"receiveMsg",
 * 		"id":"<QQ ID>"
 * }
 */
struct cmd_receiveMsg {
		string userID;
};

/**
 * send message:
 * {
 * 		"action":"sendMsg",
 * 		"from":"<QQ ID>",
 * 		"to"":<QQ ID>",
 * 		"msg":"message"
 * }
 */
struct cmd_sendMsg {
		string fromUserId;
		string toUserId;
		string message;

};

#endif /* COMMAND_H_ */
