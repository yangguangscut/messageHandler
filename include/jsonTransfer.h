/*
 * jsonTransfer.h
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#ifndef JSONTRANSFER_H_
#define JSONTRANSFER_H_

#include <string>
#include "msgCommand.h"
using std::string;

/**
 * 从json字符串中获取“接收消息”命令，获取成功返回true
 */
bool getReceiveMsgCmd(string & json_str, cmd_receiveMsg & cmd);

/**
 * 从json字符串中获取”发送消息“命令，获取成功返回true
 */
bool getSendMsgCmd(string & json_str, cmd_sendMsg & cmd);
#endif /* JSONTRANSFER_H_ */
