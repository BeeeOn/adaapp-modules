/*
 * @file IOMessage.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief IO message representation class
 */

#include "IOMessage.h"

using namespace std;

IOMessage::IOMessage()
{
	eventName = "";
	senderName = "";
	action = "";
	priority = 0;
	validity = false;
}

void IOMessage::debug_print()
{
	string message = "";
	Poco::Logger& log = Poco::Logger::get("IODaemon");
	message = "Debug print of IOMessage: \n";
	message = message + "Event name: " + eventName + "\n";
	message = message + "Action: " + action + "\n";
	message = message + "Sender name: " + senderName + "\n";
	message = message + "Priority: " + to_string(priority) + "\n";

	if (validity == true)
		message = message + "Validity: true" + "\n";
	else
		message = message + "Validity: false" + "\n";

	if (action == "setLeds") {
		message = message + "ledConfiguration: " + "\n";
		message = message + "Red: " + to_string(ledConf.red) + "\n";
		message = message + "Green: " + to_string(ledConf.green) + "\n";
		message = message + "Blue: " + to_string(ledConf.blue) + "\n";
	}

	log.debug(message);
}
