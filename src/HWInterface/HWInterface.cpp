/*
 * @file HWInterface.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief Hardware interface implementation
 */

#include "HWInterface.h"

HWInterface::HWInterface()
{
	leds.reset(new Leds());
}

bool HWInterface::setLeds(struct ledConfiguration ledConf)
{
	return leds->setConfiguration(ledConf);
}
