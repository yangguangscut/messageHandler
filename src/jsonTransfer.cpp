/*
 * jsonTransfer.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: yang
 *
 * get commands about send and receive message from a json string
 *
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <stdio.h>
#include <iostream>
#include "msgCommand.h"
using namespace boost::property_tree;
using namespace std;

cmd_receiveMsg * getReceiveMsgCmd(string json_str) {
	stringstream ss(json_str);
	ptree pt;
	string cmd_type;
	try {
		read_json(ss, pt);
	} catch (ptree_error &e) {
		cout << "read json error, json_str: " << json_str.c_str() << endl;
		return NULL;
	}
	try {
		cmd_receiveMsg * cmd = new cmd_receiveMsg;
		cmd->userID = pt.get<string>("id");
		return cmd;
	} catch (ptree_error & e) {
		return NULL;
	}
}

cmd_sendMsg * getSendMsgCmd(string json_str) {
	stringstream ss(json_str);
	ptree pt;
	string cmd_type;
	try {
		read_json(ss, pt);
	} catch (ptree_error &e) {
		cout << "read json error, json_str: " << json_str.c_str() << endl;
		return NULL;
	}
	try {

		cmd_sendMsg * cmd = new cmd_sendMsg;
		cmd->fromUserId = pt.get<string>("from");
		cmd->toUserId = pt.get<string>("to");
		cmd->message = pt.get<string>("msg");
		return cmd;
	} catch (ptree_error & e) {
		return NULL;
	}

}
