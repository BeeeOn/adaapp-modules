/**
 * @file DLinkDchZ120ZWaveMessage.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/NumberParser.h>

#include "Products/DLinkDchZ120ZWaveMessage.h"

#define PIR_SENSOR_SENSITIVITY_MODULE  3
#define PIR_SENSOR_SENSITIVITY_INDEX   3

#define ALARM_MOTION       8
#define ALARM_SAFETY       3
#define ALARM_IDLE         0

#define MODULE_PIR              0
#define MODULE_LUMINANCE        1
#define MODULE_TEMPERATURE      2
#define MODULE_SENSOR_ALARM     3
#define MODULE_PIR_SENSITIVITY  4
#define MODULE_BATTERY          5

using std::string;
using std::vector;

void DLinkDchZ120ZWaveMessage::extractValues(vector<BeeeOnSensorValue> &values,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	string value;

	if (getLuminance(value, zwaveValues))
		values.push_back({MODULE_LUMINANCE, value});

	if (getTemperature(value, zwaveValues))
		values.push_back({MODULE_TEMPERATURE, value});

	if (getPirSensitivity(value, zwaveValues))
		values.push_back({MODULE_PIR_SENSITIVITY, value});

	if (getBatteryLevel(value, zwaveValues))
		values.push_back({MODULE_BATTERY, value});

	getDetectionSensor(values, zwaveValues);
}

void DLinkDchZ120ZWaveMessage::setValue(const vector<BeeeOnSensorValue> &beeeonValues,
	const uint8_t &nodeId)
{
	string value;

	for (const BeeeOnSensorValue &item : beeeonValues) {
		if (item.moduleID == MODULE_PIR_SENSITIVITY)
			setActuator(item.value, COMMAND_CLASS_CONFIGURATION,
				PIR_SENSOR_SENSITIVITY_INDEX, nodeId);
	}
}

bool DLinkDchZ120ZWaveMessage::getPirSensitivity(std::string &value,
	const std::vector<ZWaveSensorValue> &zwaveValues)
{
	if (getSpecificValue(value, COMMAND_CLASS_CONFIGURATION,
		PIR_SENSOR_SENSITIVITY_INDEX, zwaveValues))
		return true;

	return false;
}

void DLinkDchZ120ZWaveMessage::getDetectionSensor(vector<BeeeOnSensorValue> &values,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	int sensorState = 0;

	for (const ZWaveSensorValue &item : zwaveValues) {
		if (!isEqual(item.commandClass, COMMAND_CLASS_ALARM, item.index,
				SENSOR_INDEX_BULGAR))
			continue;

		if (!extractInt(sensorState, item))
			continue;

		if (sensorState == ALARM_SAFETY) {
			values.push_back({MODULE_SENSOR_ALARM, "1"});
		} else if (sensorState == ALARM_MOTION) {
			values.push_back({MODULE_PIR, "1"});
		} else {
			values.push_back({MODULE_PIR, "0"});
			values.push_back({MODULE_SENSOR_ALARM, "0"});
		}
	}
}
