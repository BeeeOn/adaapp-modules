/**
 * @file PhilioZWaveMessageFactory.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessageFactory.h"
#include "Products/PhilioPST021CZWaveMessage.h"

#define PHILIO_MANUFACTURER      0x013c

/*
 * It creates Philio product.
 */
class PhilioZWaveMessageFactory : public ZWaveMessageFactory {
public:
	ZWaveMessage *create(const uint32_t &manufacturer, const uint32_t &product) override;
};
