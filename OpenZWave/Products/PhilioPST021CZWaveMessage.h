/**
 * @file PhilioPST021CZWaveMessage.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessage.h"

#define PHILIO_PST02_1C             0x000e
#define DEVICE_ID_PHILIO_PST02_1C   16

class PhilioPST021CZWaveMessage : public ZWaveMessage {
public:
	void extractValues(std::vector<BeeeOnSensorValue> &values,
		const std::vector<ZWaveSensorValue> &zwaveValues) override;

	void setValue(const std::vector<BeeeOnSensorValue> &beeeonValues,
		const uint8_t &nodeId) override
	{
	}

	void setAfterStart() override
	{
	}

	int getDeviceID() override
	{
		return DEVICE_ID_PHILIO_PST02_1C;
	}
};
