/**
 * @file FibaroFGK107ZWaveMessage.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <string>
#include <vector>

#include "FibaroFGK107ZWaveMessage.h"

#define MODULE_MAGNETIC_DOOR_CONTACT  0
#define MODULE_BATTERY                1

using std::string;
using std::vector;

void FibaroFGK107ZWaveMessage::extractValues(vector<BeeeOnSensorValue> &values,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	string data;

	if (getSensorValue(data, zwaveValues))
		values.push_back({MODULE_MAGNETIC_DOOR_CONTACT, data});

	if (getBatteryLevel(data, zwaveValues))
		values.push_back({MODULE_BATTERY, data});
}
