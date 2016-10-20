/**
 * @file FibaroFGK107ZWaveMessage.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessage.h"

#define FIBARO_FGK_107              0x1000
#define DEVICE_ID_FIBARO_FGK_107    25

class FibaroFGK107ZWaveMessage : public ZWaveMessage {
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
		return DEVICE_ID_FIBARO_FGK_107;
	}
};
