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
#include <sstream>
#include <string>
#include <vector>
#include "msgCommand.h"
#include "jsonTransfer.h"
using namespace boost::property_tree;
using namespace std;

bool getReceiveMsgCmd(string & json_str, cmd_receiveMsg & cmd) {
	stringstream ss(json_str);
	ptree pt;
	string cmd_type;
	try {
		read_json(ss, pt);
	} catch (ptree_error &e) {
		cout << "read json error, json_str: " << json_str.c_str() << endl;
		return false;
	}
	try {
		cmd_type = pt.get<string>("action");
		if ("receiveMsg" == cmd_type) {
			cmd.userID = pt.get<string>("id");
			return true;
		}
		return false;
	} catch (ptree_error & e) {
		return false;
	}
}

bool getSendMsgCmd(string & json_str, cmd_sendMsg & cmd) {
	stringstream ss(json_str);
	ptree pt;
	string cmd_type;
	try {
		read_json(ss, pt);
	} catch (ptree_error &e) {
		cout << "read json error, json_str: " << json_str.c_str() << endl;
		return false;
	}
	try {
		cmd_type = pt.get<string>("action");
		if ("sendMsg" == cmd_type) {
			cmd.fromUserId = pt.get<string>("from");
			cmd.toUserId = pt.get<string>("to");
			cmd.message = pt.get<string>("msg");
			return true;
		}
		return false;

	} catch (ptree_error & e) {
		return false;
	}
}
