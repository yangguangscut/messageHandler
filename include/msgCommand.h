/*
 * msgCommand.h
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#ifndef MSG_COMMAND_H_
#define MSG_COMMAND_H_
#include <string>
using std::string;

/**
 * 接收消息命令的消息格式
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
 * 发送消息命令的消息格式
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
