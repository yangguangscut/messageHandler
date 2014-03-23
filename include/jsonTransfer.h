/*
 * jsonTransfer.h
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 */

#ifndef JSONTRANSFER_H_
#define JSONTRANSFER_H_

#include "msgCommand.h"
#include <string>

cmd_receiveMsg * getReceiveMsgCmd(string json_str);
cmd_sendMsg * getSendMsgCmd(string json_str);


#endif /* JSONTRANSFER_H_ */
