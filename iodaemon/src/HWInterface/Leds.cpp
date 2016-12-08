/*
 * @file Leds.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief
 */

#include "Leds.h"

using namespace std;

Leds::Leds()
{
	setConfiguration(defaultLeds);
}

bool Leds::setConfiguration(struct ledConfiguration conf)
{
	ofstream red,green,blue;
	red.open(RED_BRIGHTNESS);
	green.open(GREEN_BRIGHTNESS);
	blue.open(BLUE_BRIGHTNESS);

	if (conf.red)
		red << "0";
	else
		red << "1";

	if (conf.green)
		green << "1";
	else
		green << "0";

	unsigned char blueIntensity = 100-conf.blue;
	if (conf.blue == 100)
		blue << "1";
	else if (conf.blue == 0)
		blue << "255";
	else
		blue << to_string((int)(blueIntensity*2.55));

	red.close();
	blue.close();
	green.close();

	return true;
}
