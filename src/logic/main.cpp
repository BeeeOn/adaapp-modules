/*
 * @file main.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief IO Daemon entry level function
 */

#include <csignal>
#include <iostream>
#include <unistd.h>

#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/File.h>
#include <Poco/FileChannel.h>
#include <Poco/Formatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>
#include <Poco/NumberFormatter.h>
#include <Poco/NumberParser.h>
#include <Poco/PatternFormatter.h>
#include <Poco/SplitterChannel.h>
#include <Poco/Util/IniFileConfiguration.h>
#include <Poco/Util/LoggingConfigurator.h>

#include <Sender.h>
#include <logic.h>

#define CONFIG_FILE "/etc/beeeon/iodaemon.ini"

void exitHandler(int signum);
void run();

using namespace std;
using Poco::AutoPtr;
using Poco::Logger;
using Poco::Runnable;
using Poco::Util::IniFileConfiguration;

volatile bool exitFlag;
void run();
void exitHandler(int);

int main()
{
	exitFlag = false;
	signal(SIGINT, exitHandler);
	signal(SIGTERM, exitHandler);

	run();

	return 0;
}

void run()
{
	int receivePort, timeout, adaappPort;
	HWInterface hw;
	Logic logic;
	Sender sender;
	Logger& log = Poco::Logger::get("IODaemon");

	AutoPtr<IniFileConfiguration> cfg;
	try {
		cfg = new IniFileConfiguration(CONFIG_FILE);
		receivePort = cfg->getInt("IODaemon.receivePort",-1);
		timeout = cfg->getInt("IODaemon.timeout", 5);
		adaappPort = cfg->getInt("adaapp.port", -1);
	}
	catch (Poco::Exception& e) {
		cerr << "Error: Problem with config file." << endl;
		return;
	}

	Poco::Util::LoggingConfigurator configurator;
	configurator.configure(cfg);
	log.information("BeeeOn IODaemon initialized, receivePort = " + to_string(receivePort) + ", timeout=" + to_string(timeout));

	Receiver recv(receivePort, timeout);

	while(!exitFlag){
		IOMessage msg;
		msg = recv.receive();
		if (msg.validity == true) {
			IOMessage response;
			response.eventName = "updateLeds";
			response.action = "";
			response.senderName = "ioDaemon";
			response.priority = msg.priority;
			response.validity = true;
			response.ledConf = msg.ledConf;
			msg.debug_print();
			if (msg.action == "setLeds") {
				logic.addLedConfiguration(msg.ledConf, msg.priority);
				hw.setLeds(logic.getHighestLedConf());
				sender.send(response, adaappPort); // TODO port to sender of original message
			}
			else if (msg.action == "unsetLeds") {
				logic.removeLedConfiguration(msg.priority);
				hw.setLeds(logic.getHighestLedConf());
				sender.send(response, adaappPort); // TODO port to sender of original message
			}
		}
	}
	
}

void exitHandler(int)
{
	Logger& log = Poco::Logger::get("IODaemon");
	log.information("IODaemon terminating...");
	exitFlag = true;
}
