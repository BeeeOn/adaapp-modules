/*
 * @file Receiver.h
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief BeeeOn message receiver
 */

#pragma once

#include <iostream>
#include <string>

#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Timespan.h>

#include "IOMessage.h"
#include "MsgParser.h"

#define BUFF_SIZE 2048

class Receiver {
private:
	Poco::Net::DatagramSocket socket;
	Poco::Net::SocketAddress socketAddress;
public:
	bool openSocket();
	Receiver(unsigned int port, unsigned int timeout);
	IOMessage receive();
};
