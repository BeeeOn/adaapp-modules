/**
 * @file FibaroFGK107ZWaveMessage.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include <map>

#include "ZWaveMessage.h"

#define AEOTEC_ZW100              0x0064
#define DEVICE_ID_AEOTEC_ZW100    27

class AeotecZW100ZWaveMessage : public ZWaveMessage {
public:
	AeotecZW100ZWaveMessage();

	void extractValues(std::vector<BeeeOnSensorValue> &value,
		const std::vector<ZWaveSensorValue> &zwaveValues) override;

	void setValue(const std::vector<BeeeOnSensorValue> &beeeonValues,
		const uint8_t &nodeId) override;

	void setAfterStart() override
	{
	}

	int getDeviceID() override
	{
		return DEVICE_ID_AEOTEC_ZW100;
	}

private:
	std::map<std::string, std::string> m_pirSensor;

	void setMapValue();

	bool getPirSensitivity(std::string& value,
		const std::vector<ZWaveSensorValue> &zwaveValues);

	bool getRefreshTime(std::string& value,
		const std::vector<ZWaveSensorValue> &zwaveValues);

	void getDetectionSensor(std::vector<BeeeOnSensorValue> &values,
		const std::vector<ZWaveSensorValue> &zwaveValues);
};
