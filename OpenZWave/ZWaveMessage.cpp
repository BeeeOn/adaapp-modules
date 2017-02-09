/**
 * @file ZWaveMessage.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <fstream>
#include <iostream>
#include <list>

#include <Poco/AutoPtr.h>
#include <Poco/Crypto/X509Certificate.h>
#include <Poco/Exception.h>
#include <Poco/NumberParser.h>
#include <Poco/RegularExpression.h>
#include <Poco/Util/IniFileConfiguration.h>

#include <Manager.h>

#include "ZWaveMessage.h"
#include "NotificationProcessor.h"

using namespace std;
using Poco::Util::IniFileConfiguration;

#define SENSOR_INDEX_BATTERY             0
#define SENSOR_INDEX_HUMINIDITY          5
#define SENSOR_INDEX_LUMINISTANCE        3
#define SENSOR_INDEX_SENSOR              0
#define SENSOR_INDEX_TEMPERATURE         1
#define SENSOR_INDEX_ULTRAVIOLET         27

#define GATEWAY_ID_BITE_SIZE             16
#define GATEWAY_MAX_NUMBER_ID            65535
#define ZWAVE_PREFIX                     0xa8
#define DEFAULT_GATEWAY_ID               0

ZWaveMessage::ZWaveMessage():
	logger(Poco::Logger::get("ZWaveMessage"))
{                               
}

uint16_t ZWaveMessage::loadGatewayIDFromConfigFile()
{
	uint16_t gatewayID = 0;

	try {
		Poco::AutoPtr<IniFileConfiguration> config;

		config = new IniFileConfiguration(m_configFileName);
		string gatewayIDFromFile = config->getString("adapter.id",
			DEFAULT_GATEWAY_ID);

		gatewayID = Poco::NumberParser::parseUnsigned64(gatewayIDFromFile);
	}
	catch (Poco::Exception &ex) {
		logger.warning("use default configuration for gateway ID");
		logger.log(ex, __FILE__, __LINE__);
	}

	return gatewayID;
}

uint16_t ZWaveMessage::extractGatewayID()
{
	filebuf fileBuffer;
	uint16_t gatewayID = 0;
	string gatewayIDstring = "";

	if (fileBuffer.open(m_certificatePath, std::ios::in)) {
		istream is(&fileBuffer);

		Poco::Crypto::X509Certificate certificate(is);
		string gatewayAID = certificate.commonName();

		if (gatewayAID == "adapter") {
			gatewayID = loadGatewayIDFromConfigFile();
		}
		else {
			Poco::RegularExpression re("[0-9]+");
			if (re.extract(gatewayAID, gatewayIDstring) != 1)
				gatewayID = loadGatewayIDFromConfigFile();
			else
				gatewayID = Poco::NumberParser::parseUnsigned64(gatewayIDstring)
								& GATEWAY_MAX_NUMBER_ID;
		}
	}
	else {
		gatewayID = loadGatewayIDFromConfigFile();
	}

	return gatewayID;
}

uint64_t ZWaveMessage::generateEUID(const uint32_t &homeId,
	const uint8_t &nodeId)
{
	uint64_t euid = 0;
	uint64_t homeId64 = homeId;
	uint64_t gatewayId64 = extractGatewayID();

	// | 8b | 16b | 32b | 8b |
	// prefix, gatewayID, homeId, nodeId
	euid = uint64_t(ZWAVE_PREFIX) << 56;
	euid |= gatewayId64 << 40;
	euid |= homeId64 << 8;
	euid |= nodeId;

	return euid;
}

bool ZWaveMessage::asBool(const string &value)
{
	return int(Poco::NumberParser::parseFloat(value));
}

bool ZWaveMessage::extractFloat(float &value, const ZWaveSensorValue &item)
{
	try {
		value = Poco::NumberParser::parseFloat(item.value);;
		return true;
	}
	catch (Poco::Exception& ex) {
		logger.error("Failed to parse value " + item.value + "as a float");
		logger.log(ex, __FILE__, __LINE__);
		return false;
	}
}

bool ZWaveMessage::extractInt(int &value, const ZWaveSensorValue &item)
{
	try {
		value = Poco::NumberParser::parse(item.value);;
		return true;
	}
	catch (Poco::Exception& ex) {
		logger.error("Failed to parse value " + item.value + "as a int");
		logger.log(ex, __FILE__, __LINE__);
		return false;
	}
}

bool ZWaveMessage::extractBool(bool &value, const ZWaveSensorValue &item)
{
	if (item.value == "True") {
		value = true;
		return true;
	} else if (item.value == "False") {
		value = false;
		return true;
	}
	else {
		return false;
	}
}

bool ZWaveMessage::extractString(string &value, const ZWaveSensorValue &item)
{
	value = item.value;
	return true;
}

bool ZWaveMessage::getSpecificValue(string &value, const int &commandClass,
	const int &index, const vector<ZWaveSensorValue> &zwaveValues)
{
	for (const ZWaveSensorValue &item : zwaveValues) {
		if (!isEqual(item.commandClass, commandClass, item.index, index))
			continue;

		value = item.value;
		return true;
	}

	return false;
}

bool ZWaveMessage::getTemperature(string &value, const vector<ZWaveSensorValue> &zwaveValues)
{
	float temperature;

	for (const ZWaveSensorValue &item : zwaveValues) {
		if (!isEqual(item.commandClass, COMMAND_CLASS_SENSOR_MULTILEVEL,
				item.index, SENSOR_INDEX_TEMPERATURE))
			continue;

		if (!extractFloat(temperature, item))
			continue;

		if (item.unit == "F")
			temperature = (temperature - 32)/1.8;

		value = to_string(temperature);
		return true;
	}

	return false;
}

bool ZWaveMessage::getSwitchBinary(string &value, const vector<ZWaveSensorValue> &zwaveValues)
{
	bool switchValue;

	for (const ZWaveSensorValue &item : zwaveValues) {
		if (!isEqual(item.commandClass, COMMAND_CLASS_SWITCH_BINARY,
				item.index, SENSOR_INDEX_SENSOR))
			continue;

		if (!extractBool(switchValue, item))
			continue;

		value = to_string(switchValue);
		return true;
	}

	return false;
}

bool ZWaveMessage::getBatteryLevel(string &value, const vector<ZWaveSensorValue> &zwaveValues)
{
	return getSpecificValue(value, COMMAND_CLASS_BATTERY, SENSOR_INDEX_BATTERY,
			zwaveValues);
}

bool ZWaveMessage::getSensorValue(string &value, const vector<ZWaveSensorValue> &zwaveValues)
{
	bool sensorValue;

	for (const ZWaveSensorValue &item : zwaveValues) {
		if (!isEqual(item.commandClass, COMMAND_CLASS_SENSOR_BINARY,
				item.index, SENSOR_INDEX_SENSOR))
			continue;

		if (!extractBool(sensorValue, item))
			continue;

		value = to_string(sensorValue);
		return true;
	}

	return false;
}

bool ZWaveMessage::getLuminance(string &value, const vector<ZWaveSensorValue> &zwaveValues)
{
	return getSpecificValue(value, COMMAND_CLASS_SENSOR_MULTILEVEL,
			SENSOR_INDEX_LUMINISTANCE, zwaveValues);
}

bool ZWaveMessage::getHumidity(string &value, const vector<ZWaveSensorValue> &zwaveValues)
{
	return getSpecificValue(value, COMMAND_CLASS_SENSOR_MULTILEVEL,
			SENSOR_INDEX_HUMINIDITY, zwaveValues);
}

bool ZWaveMessage::getUltraviolet(string &value, const vector<ZWaveSensorValue> &zwaveValues)
{
	return getSpecificValue(value, COMMAND_CLASS_SENSOR_MULTILEVEL,
			SENSOR_INDEX_ULTRAVIOLET, zwaveValues);
}

void ZWaveMessage::sendActuatorValue(const OpenZWave::ValueID &valueId, const string &value)
{
	float data;
	int valueType = valueId.GetType();

	try {
		switch(valueType) {
		case OpenZWave::ValueID::ValueType_Bool:
			OpenZWave::Manager::Get()->SetValue(valueId, asBool(value));
			break;
		case OpenZWave::ValueID::ValueType_Byte:
			data = Poco::NumberParser::parseFloat(value);
			OpenZWave::Manager::Get()->SetValue(valueId, uint8_t(data));
			break;
		case OpenZWave::ValueID::ValueType_Short:
			data = Poco::NumberParser::parseFloat(value);
			OpenZWave::Manager::Get()->SetValue(valueId, int16_t(data));
			break;
		case OpenZWave::ValueID::ValueType_Int:
			data = Poco::NumberParser::parseFloat(value);
			OpenZWave::Manager::Get()->SetValue(valueId, int(data));
			break;
		case OpenZWave::ValueID::ValueType_List:
			OpenZWave::Manager::Get()->SetValueListSelection(valueId, value);
			break;
		default:
			logger.error("Unsupported ValueID " + to_string(valueType),
					__FILE__, __LINE__);
			break;
		}
	} catch (Poco::Exception &ex) {
		logger.error("Failed to parse value " + to_string(data) + " as a float");
		logger.log(ex, __FILE__, __LINE__);
	}
}

bool ZWaveMessage::setActuator(const std::string &value, const int &commandClass,
	const int &index, const uint8_t &nodeId)
{
	NotificationProcessor::findNodeInfo(nodeId);
	Poco::Nullable<NodeInfo> nodeInfo = NotificationProcessor::findNodeInfo(nodeId);

	if (nodeInfo.isNull())
		return false;

	for (const OpenZWave::ValueID &item : nodeInfo.value().m_values) {
		if (item.GetCommandClassId() == commandClass && item.GetIndex() == index) {
			logger.debug("Set actuator, commandClass " + to_string(commandClass)
					+ " index " + to_string(index));
			sendActuatorValue(item, value);
			return true;
		}
	}

	return false;
}
