/**
 * @file ZWaveMessageFactory.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessage.h"

/*
 * For each supported device create a report.
 */
class ZWaveMessageFactory {
public:
	/*
	 * It creates ZWaveMessage representing specific message implementation.
	 * @param &manufacturer Unique number of manufacturer
	 * @param &product Unique number of product
	 * @return ZWaveMessage represent specific product from Z-Wave network
	 */
	virtual ZWaveMessage *create(const uint32_t &manufacturer, const uint32_t &product) = 0;
};
