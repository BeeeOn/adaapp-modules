/*
 * @file HWInterface.h
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief
 */

#pragma once

#include <memory>

#include "Leds.h"

class HWInterface {
private:
	std::unique_ptr<Leds> leds;
public:
	HWInterface();
	bool setLeds(struct ledConfiguration ledConf);
};
