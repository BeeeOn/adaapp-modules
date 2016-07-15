/*
 * @file MsgParser.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief Parsing JSON to IOMessage implementation
 */

#include "MsgParser.h"

using namespace std;
using namespace Poco::JSON;

MsgParser::MsgParser() {}

IOMessage MsgParser::parseMsg(string data)
{
	message = IOMessage();
	Object::Ptr parsedJson;
	try{
		parsedJson = parseJsonObject(data);
		message.eventName = getStringValue(parsedJson, MSG_EVENT_NAME);
		message.action = getStringValue(parsedJson, MSG_ACTION);
		message.senderName = getStringValue(parsedJson, MSG_SENDER);
		message.priority = getCharValue(parsedJson, MSG_PRIORITY);
		
		if (message.action == "setLeds") {
			message.ledConf = getLedsConfiguration(parsedJson, MSG_LEDS_CONFIGURATION);
		}
	}
	catch (Poco::SyntaxException e) {
		cout << "Parsing message failed: " << e.what() << endl;
		message.validity = false;
		return message;
	}
	catch (Poco::InvalidAccessException e) {
		cout << "Parsing message failed: " << "Message has invalid attributes" <<  endl;
		message.validity = false;
		return message;
	}
	catch (Poco::Exception e) {
		cout << "Parsing message failed: " << e.what() << endl;
		message.validity = false;
		return message;
	}

	message.validity = true;
	return message;
}


Object::Ptr MsgParser::parseJsonObject(std::string data)
{
	Parser jsonParser;
	jsonParser.parse(data);
	Poco::Dynamic::Var parsedJsonResult = jsonParser.result();
	return parsedJsonResult.extract<Object::Ptr>();
}

std::string MsgParser::getStringValue(Poco::JSON::Object::Ptr jsonObject, std::string key)
{
	Poco::Dynamic::Var item;
	item = jsonObject->get(key);
	return item.convert<string>();
}

unsigned char MsgParser::getCharValue(Poco::JSON::Object::Ptr jsonObject, std::string key)
{
	Poco::Dynamic::Var item;
	item = jsonObject->get(key);
	return item.convert<unsigned char>();
}

struct ledConfiguration MsgParser::getLedsConfiguration(Poco::JSON::Object::Ptr jsonObject, std::string key)
{
	struct ledConfiguration ledConf;
	Object::Ptr jsonLedsConf;
	unsigned char result;

	jsonLedsConf = jsonObject->getObject(key);

	result = jsonLedsConf->get("Red").convert<unsigned char>();
	if (result == 0)
		ledConf.red = false;
	else
		ledConf.red = true;

	result = jsonLedsConf->get("Green").convert<unsigned char>();
	if (result == 0)
		ledConf.green = false;
	else
		ledConf.green = true;

	ledConf.blue = jsonLedsConf->get("Blue").convert<unsigned char>();

	return ledConf;
}
