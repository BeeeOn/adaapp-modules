/**
 * @file DLinkDchZ120ZWaveMessage.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessage.h"

#define DLINK_DCH_Z120             0x000d
#define DEVICE_ID_DLINK_DCH_Z120   26

class DLinkDchZ120ZWaveMessage : public ZWaveMessage {
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
		return DEVICE_ID_DLINK_DCH_Z120;
	}

private:
	bool getPirSensitivity(std::string &value,
		const std::vector<ZWaveSensorValue> &zwaveValues);

	void getDetectionSensor(std::vector<BeeeOnSensorValue> &values,
		const std::vector<ZWaveSensorValue> &zwaveValues);
};
