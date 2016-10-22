/**
 * @file Popp123601ZWaveMessage.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <string>
#include <vector>

#include "Popp123601ZWaveMessage.h"

#define MODULE_SWITCH  0

using std::string;
using std::vector;

void Popp123601ZWaveMessage::extractValues(vector<BeeeOnSensorValue> &values,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	string data;

	if (getSwitchBinary(data, zwaveValues))
		values.push_back({0, data});
}

void Popp123601ZWaveMessage::setValue(const vector<BeeeOnSensorValue> &beeeonValues,
	const uint8_t &nodeId)
{
	for (const BeeeOnSensorValue &item : beeeonValues) {
		if (item.moduleID == 0)
			setActuator(item.value, COMMAND_CLASS_SWITCH_BINARY, 0, nodeId);
	}
}
