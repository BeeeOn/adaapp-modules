/**
 * @file PhilioPST021CZWaveMessage.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/NumberParser.h>

#include "Products/PhilioPST021CZWaveMessage.h"

#define ALARM_OPEN         8
#define ALARM_SAFETY       3
#define ALARM_IDLE         0

#define MODULE_MAGNETIC_CONTACT     0
#define MODULE_TEMPERATURE          1
#define MODULE_LUMINANCE            2
#define MODULE_BATTERY              3

using std::string;
using std::vector;

void PhilioPST021CZWaveMessage::extractValues(vector<BeeeOnSensorValue> &values,
	const vector<ZWaveSensorValue> &zwaveValues)
{
	string value;

	if (getLuminance(value, zwaveValues))
		values.push_back({MODULE_LUMINANCE, value});

	if (getTemperature(value, zwaveValues))
		values.push_back({MODULE_TEMPERATURE, value});

	if (getSensorValue(value, zwaveValues))
		values.push_back({MODULE_MAGNETIC_CONTACT, value});

	if (getBatteryLevel(value, zwaveValues))
		values.push_back({MODULE_BATTERY, value});
}
