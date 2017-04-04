/**
 * @file PoppZWaveMessageFactory.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "Products/Popp123601ZWaveMessage.h"
#include "ZWaveMessageFactory.h"

#define POPP_MANUFACTURER       0x0154

/*
 * It creates Popp product.
 */
class PoppZWaveMessageFactory : public ZWaveMessageFactory {
public:
	ZWaveMessage *create(const uint32_t &manufacturer,
		const uint32_t &product) override;
};
