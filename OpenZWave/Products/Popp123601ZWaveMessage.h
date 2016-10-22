/**
 * @file Popp123601ZWaveMessage.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessage.h"

#define POPP_123601              0x0001
#define DEVICE_ID_POPP_123601    17

class Popp123601ZWaveMessage : public ZWaveMessage {
public:
	void extractValues(std::vector<BeeeOnSensorValue> &values,
		const std::vector<ZWaveSensorValue> &zwaveValues) override;

	void setValue(const std::vector<BeeeOnSensorValue> &beeeonValues,
		const uint8_t &nodeId) override;

	void setAfterStart() override
	{
	}

	int getDeviceID() override
	{
		return DEVICE_ID_POPP_123601;
	}
};
