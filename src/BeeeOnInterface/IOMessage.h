/*
 * @file IOMessage.h
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief IO message representation class
 */

#pragma once

#include <iostream>
#include <string>

#include <Poco/Logger.h>

#include <Leds.h>

#define MSG_ACTION "Action"
#define MSG_EVENT_NAME "EventName"
#define MSG_LEDS_CONFIGURATION "LedsConfiguration"
#define MSG_PRIORITY "Priority"
#define MSG_SENDER "Sender"

class IOMessage {
public:
	IOMessage();
	std::string eventName;
	std::string action;
	std::string senderName;
	unsigned char priority;
	struct ledConfiguration ledConf;
	bool validity;
	void debug_print();
};
