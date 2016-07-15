/*
 * @file Receiver.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief BeeeOn message receiver implementation using datagram sockets.
 */

#include "Receiver.h"

using namespace std;

Receiver::Receiver(unsigned int port, unsigned int timeout)
{
	Poco::Net::SocketAddress socketAddress(Poco::Net::IPAddress("127.0.0.1"), port);
	socket = Poco::Net::DatagramSocket(socketAddress);
	socket.setReceiveTimeout(Poco::Timespan(timeout, 0));
}

IOMessage Receiver::receive()
{
	Poco::Logger& log = Poco::Logger::get("IODaemon");
	char buffer[BUFF_SIZE];
	int charsRead;
	MsgParser parser;
	Poco::Net::SocketAddress sender;
	try {
		charsRead = socket.receiveFrom(buffer, BUFF_SIZE-1, sender);
	}
	catch (Poco::TimeoutException e) {
		return IOMessage();
	}

	buffer[charsRead] = '\0';
	log.debug("Received message: " + string(buffer));
	
	return parser.parseMsg(string(buffer));
}
