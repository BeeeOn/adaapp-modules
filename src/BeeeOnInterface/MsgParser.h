/*
 * @file MsgParser.h
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief JSON to IOMessage transformation class
 */

#pragma once

#include <iostream>
#include <string>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>

#include "IOMessage.h"

class MsgParser {
private:
	IOMessage message;
	Poco::JSON::Object::Ptr parseJsonObject(std::string data);
	std::string getStringValue(Poco::JSON::Object::Ptr jsonObject, std::string key);
	unsigned char getCharValue(Poco::JSON::Object::Ptr jsonObject, std::string key);
	struct ledConfiguration getLedsConfiguration(Poco::JSON::Object::Ptr jsonObject, std::string key);

public:
	MsgParser();
	IOMessage parseMsg(std::string);
};
