/**
 * @file BeeeOnMessage.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <iostream>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Logger.h>
#include <Poco/NumberParser.h>

#include "BeeeOnMessage.h"

using namespace std;
using namespace Poco::JSON;
using Poco::NumberParser;

BeeeOnMessage::BeeeOnMessage():
	logger(Poco::Logger::get("BeeeOnMessage"))
{
}

string BeeeOnMessage::modulesValuesAsString()
{
	string values = "";

	for (const auto &item : m_values)
		values += "\tmodule_id: " + to_string(item.moduleID) + ", value: "
			+ item.value + "\n";

	return values;
}

string BeeeOnMessage::toJSONString()
{
	Poco::JSON::Object jsonMsg;
	Poco::JSON::Object sensorValues;
	Poco::JSON::Object::Ptr data;
	Poco::JSON::Array ptr;

	jsonMsg.set("state", "data");
	jsonMsg.set("device_id", std::to_string(m_deviceID));
	jsonMsg.set("euid", std::to_string(m_euid));

	for (size_t i = 0; i < m_values.size(); i++) {
		data = new Poco::JSON::Object();
		data->set("module_id", to_string(m_values[i].moduleID));
		data->set("value", m_values[i].value);
		ptr.set(i, data);
		jsonMsg.set("data", ptr);
	}

	Poco::Dynamic::Var jsonVar = jsonMsg;
	return jsonVar.convert<std::string>();
}

bool BeeeOnMessage::insertFromJSONString(const std::string &msg)
{
	Object::Ptr parsedJson;

	try {
		parsedJson = parseJsonObject(msg);
		m_state = getStringValue(parsedJson, "state");

		if (m_state == "clear")
			m_euid = NumberParser::parse64(getStringValue(parsedJson, "euid"));
		else if (m_state == "set") {
			m_euid = NumberParser::parse64(getStringValue(parsedJson, "euid"));
			m_deviceID = NumberParser::parse64(getStringValue(parsedJson, "device_id"));

			Array::Ptr dataArray = parsedJson->getArray("data");

			for (size_t i = 0; i < dataArray->size(); ++i) {
				Object::Ptr item = dataArray->getObject(i);
				string value = getStringValue(item, "value");
				string moduleID = getStringValue(item, "module_id");
				m_values.push_back({(int)NumberParser::parseHex(moduleID), value});
			}
		}

		logger.debug("euid: " + to_string(m_euid) 
			+ "\ndevice: " + to_string(m_deviceID) 
			+ "\nstate: " + m_state + " valid: " + to_string(m_valid )
			+ "\n" + modulesValuesAsString(),
			__FILE__, __LINE__);

		return true;
	}
	catch (Poco::SyntaxException e) {
		logger.error("Parsing message failed: " + (string)e.what());
		logger.log(e, __FILE__, __LINE__);
		return false;
	}
	catch (Poco::InvalidAccessException e) {
		logger.error("Parsing message failed: missing an attribute");
		logger.log(e, __FILE__, __LINE__);
		return false;
	}
	catch (Poco::Exception e) {
		logger.error("Parsing message failed: "+ (string)e.what());
		logger.log(e, __FILE__, __LINE__);
		return false;
	}
}

std::string BeeeOnMessage::getStringValue(Poco::JSON::Object::Ptr jsonObject,
	const std::string &key)
{
	Poco::Dynamic::Var item;
	item = jsonObject->get(key);
	return item.convert<string>();
}

Object::Ptr BeeeOnMessage::parseJsonObject(const std::string &data)
{
	Parser jsonParser;
	jsonParser.parse(data);
	Poco::Dynamic::Var parsedJsonResult = jsonParser.result();
	return parsedJsonResult.extract<Object::Ptr>();
}
