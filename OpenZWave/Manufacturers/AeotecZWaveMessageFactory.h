/**
 * @file AeotecZWaveMessageFactory.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessageFactory.h"
#include "Products/AeotecZW100ZWaveMessage.h"

#define AEOTEC_MANUFACTURER     0x0086

/*
 * It creates Aeotec products.
 */
class AeotecZWaveMessageFactory : public ZWaveMessageFactory {
public:
	ZWaveMessage *create(const uint32_t &manufacturer, const uint32_t &product) override;
};
