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
using namespace std;

int main(int argc,char ** argv){
	string json="{\"action\":\"sendMsg\",\"from\":\"969041723\",\"to\":\"87614453\",\"msg\":\"this is a test \"}";
	cmd_receiveMsg * cmd=getReceiveMsgCmd(json);
	cout<<cmd->userID<<endl;
}
