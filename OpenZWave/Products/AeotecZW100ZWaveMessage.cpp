/**
 * @file FibaroFGK107ZWaveMessage.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <vector>

#include <Poco/NumberParser.h>

#include "Products/AeotecZW100ZWaveMessage.h"

#define PIR_SENSOR_ACTUATOR        6
#define PIR_SENSOR_INDEX           4
#define SENSOR_PIR_INTENSITY       2
#define SENSOR_INDEX_REFRESH_TIME  111

#define SHAKE    3
#define MOTION   8
#define IDLE     0

#define MODULE_SHAKE_SENSOR            0
#define MODULE_PIR_SENSOR              1
#define MODULE_ULTRAVIOLET             2
#define MODULE_LIGHT                   3
#define MODULE_ROOM_TEMPERATURE        4
#define MODULE_ROOM_HUMIDITY           5
#define MODULE_PIR_SENSOR_SENSITIVITY  6
#define MODULE_BATTERY                 7
#define MODULE_REFRESH_TIME            8

using std::string;
using std::to_string;
using std::vector;

AeotecZW100ZWaveMessage::AeotecZW100ZWaveMessage()
{
	setMapValue();
}

void AeotecZW100ZWaveMessage::extractValues(vector<BeeeOnSensorValue> &values,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	string value;

	if (getUltraviolet(value, zwaveValues))
		values.push_back({MODULE_ULTRAVIOLET, value});

	if (getLuminance(value, zwaveValues))
		values.push_back({MODULE_LIGHT, value});

	if (getTemperature(value, zwaveValues))
		values.push_back({MODULE_ROOM_TEMPERATURE, value});

	if (getHumidity(value, zwaveValues))
		values.push_back({MODULE_ROOM_HUMIDITY, value});

	if (getPirSensitivity(value, zwaveValues))
		values.push_back({MODULE_PIR_SENSOR_SENSITIVITY, value});

	if (getBatteryLevel(value, zwaveValues))
		values.push_back({MODULE_BATTERY, value});

	if (getRefreshTime(value, zwaveValues))
		values.push_back({MODULE_REFRESH_TIME, value});

	getDetectionSensor(values, zwaveValues);
}

void AeotecZW100ZWaveMessage::setValue(const vector<BeeeOnSensorValue> &beeeonValues,
	const uint8_t &nodeId)
{
	std::string value;
	for (const BeeeOnSensorValue &item : beeeonValues) {
		if (item.moduleID == PIR_SENSOR_ACTUATOR) {
			int actuatorValue = int(Poco::NumberParser::parseFloat(item.value));
			auto search = m_pirSensor.find(to_string(actuatorValue));

			if (search == m_pirSensor.end())
				return;

			setActuator(search->second, COMMAND_CLASS_CONFIGURATION,
				PIR_SENSOR_INDEX, nodeId);
		}
		else if (item.moduleID == MODULE_REFRESH_TIME) {
			setActuator(item.value, COMMAND_CLASS_CONFIGURATION,
				SENSOR_INDEX_REFRESH_TIME, nodeId);
		}
	}
}

bool AeotecZW100ZWaveMessage::getPirSensitivity(string& value,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	if (!getSpecificValue(value, COMMAND_CLASS_CONFIGURATION,
		PIR_SENSOR_INDEX, zwaveValues))
		return false;

	for (const auto &item : m_pirSensor) {
		if (item.second == value) {
			value = item.first;
			return true;
		}
	}

	return false;
}

bool AeotecZW100ZWaveMessage::getRefreshTime(string& value,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	if (getSpecificValue(value, COMMAND_CLASS_CONFIGURATION,
		SENSOR_INDEX_REFRESH_TIME, zwaveValues))
		return true;

	return false;
}

void AeotecZW100ZWaveMessage::getDetectionSensor(vector<BeeeOnSensorValue> &values,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	int sensorState = 0;

	for (const ZWaveSensorValue &item : zwaveValues) {
		if (!isEqual(item.commandClass, COMMAND_CLASS_ALARM, item.index,
				SENSOR_INDEX_BULGAR))
			continue;

		if (!extractInt(sensorState, item))
			continue;

		if (sensorState == SHAKE) {
			values.push_back({MODULE_SHAKE_SENSOR, "1"});
		} else if (sensorState == MOTION) {
			values.push_back({MODULE_PIR_SENSOR, "1"});
		} else {
			values.push_back({MODULE_SHAKE_SENSOR, "0"});
			values.push_back({MODULE_PIR_SENSOR, "0"});
		}
	}
}

void AeotecZW100ZWaveMessage::setMapValue()
{
	m_pirSensor.insert(std::make_pair("0", "Disabled"));
	m_pirSensor.insert(std::make_pair("1", "Enabled level 1 (minimum sensitivity)"));
	m_pirSensor.insert(std::make_pair("2", "Enabled level 2"));
	m_pirSensor.insert(std::make_pair("3", "Enabled level 3"));
	m_pirSensor.insert(std::make_pair("4", "Enabled level 4"));
	m_pirSensor.insert(std::make_pair("5", "Enabled level 5 (maximum sensitivity)"));
}
