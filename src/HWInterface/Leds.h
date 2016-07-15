/*
 * @file Leds.h
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief
 */

#pragma once

#include <iostream>
#include <fstream>

struct ledConfiguration {
	bool red;
	bool green;
	unsigned char blue;
};

// Note: in current version of gateway firmware, green led control is swaped
// with red led control
#define BLUE_BRIGHTNESS "/sys/class/leds/pancoord:blue:usr/brightness"
#define GREEN_BRIGHTNESS "/sys/class/leds/pancoord:red:usr/brightness"
#define RED_BRIGHTNESS "/sys/class/leds/pancoord:green:usr/brightness"

class Leds {
private:
	const struct ledConfiguration defaultLeds = {false, false, 90};
public:
	Leds();
	bool setConfiguration(struct ledConfiguration);
};
