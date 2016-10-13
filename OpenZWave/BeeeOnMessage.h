/**
 * @file BeeeOnMessage.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include <string>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Logger.h>

#include "ZWaveMessage.h"

/*
 * Represents a message from adaap to OpenZWave daemon
 */
class BeeeOnMessage {
public:
	BeeeOnMessage();

	void setState(const std::string state)
	{
		m_state = state;
	}

	std::string getState()
	{
		return m_state;
	}

	void setValues(const std::vector<BeeeOnSensorValue> values)
	{
		m_values = values;
	}

	void getValues(std::vector<BeeeOnSensorValue> &values)
	{
		values = m_values;
	}

	void setEUID(const uint64_t euid)
	{
		m_euid = euid;
	}

	uint64_t getEUID()
	{
		return m_euid;
	}

	void setDeviceID(const int deviceID)
	{
		m_deviceID = deviceID;
	}

	int getDeviceID()
	{
		return m_deviceID;
	}

	/*
	 * Show BeeeOn data
	 */
	std::string modulesValuesAsString();

	/*
	 * Convert items of BeeeOnMessage to JSON message.
	 */
	std::string toJSONString();

	/*
	 * Parse message from adaaap to the BeeeOnMessage class.
	 * @param &msg JSON string from adaaapp
	 * @return true if
	 */
	 bool insertFromJSONString(const std::string &msg);

private:
	Poco::Logger &logger;
	std::string m_state;
	bool m_valid;
	std::vector<BeeeOnSensorValue> m_values;
	uint64_t m_euid;
	int m_deviceID;

	/*
	 * @param data JSON message from adaapp
	 * @return
	 */
	Poco::JSON::Object::Ptr parseJsonObject(const std::string &data);

	/*
	 * @param jsonObject
	 * @param &key value to be find
	 */
	std::string getStringValue(Poco::JSON::Object::Ptr jsonObject,
		const std::string &key);
};
