/**
 * @file FibaroZWaveMessageFactory.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "Products/FibaroFGK107ZWaveMessage.h"
#include "ZWaveMessageFactory.h"

#define FIBARO_MANUFACTURER       0x010f

/*
 * It creates Fibaro product.
 */
class FibaroZWaveMessageFactory : public ZWaveMessageFactory {
public:
	ZWaveMessage *create(const uint32_t &manufacturer,
		const uint32_t &product) override;
};
