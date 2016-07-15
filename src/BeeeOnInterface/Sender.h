/*
 * @file Sender.h
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief BeeeOn message sender
 */

#pragma once

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>

#include <iostream>
#include <string>

#include "IOMessage.h"

#define MSG_LEDS_RED "Red"
#define MSG_LEDS_GREEN "Green"
#define MSG_LEDS_BLUE "Blue"

class Sender {
private:
	static std::string createMsg(IOMessage ioMesage);
public:
	static void send(IOMessage msg, int port);
};
