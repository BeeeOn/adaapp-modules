/*
 * @file Sender.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief BeeeOn message sender implementation
 */

#include <Poco/Logger.h>

#include "Sender.h"

using namespace std;

void Sender::send(IOMessage msg, int port)
{
	Poco::Logger& log = Poco::Logger::get("IODaemon");
	string message = Sender::createMsg(msg);
	Poco::Net::SocketAddress sa("localhost", port);
	Poco::Net::DatagramSocket dgs;
	dgs.connect(sa);
	log.debug("Sending message on port " + to_string(port) + ", message:" + message);
	dgs.sendBytes(message.data(), message.size());
}

string Sender::createMsg(IOMessage ioMessage)
{
	Poco::JSON::Object jsonMsg;
	Poco::JSON::Object ledConf;
	Poco::JSON::Object ledConfRed;
	Poco::JSON::Object ledConfGreen;
	Poco::JSON::Object ledConfBlue;
	jsonMsg.set(MSG_ACTION, ioMessage.action);
	jsonMsg.set(MSG_EVENT_NAME, ioMessage.eventName);
	jsonMsg.set(MSG_PRIORITY, ioMessage.priority);
	jsonMsg.set(MSG_SENDER, ioMessage.senderName);
	ledConf.set(MSG_LEDS_RED, (int)ioMessage.ledConf.red);
	ledConf.set(MSG_LEDS_GREEN, (int)ioMessage.ledConf.green);
	ledConf.set(MSG_LEDS_BLUE, ioMessage.ledConf.blue);
	jsonMsg.set(MSG_LEDS_CONFIGURATION, ledConf);
	Poco::Dynamic::Var jsonVar = jsonMsg;
	return jsonVar.convert<std::string>();
}
