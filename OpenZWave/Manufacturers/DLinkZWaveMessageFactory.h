/**
 * @file DLinkZWaveMessageFactory.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include "ZWaveMessageFactory.h"
#include "Products/DLinkDchZ120ZWaveMessage.h"

#define DLINK_MANUFACTURER      0x0108

/*
 * It creates D-Link product.
 */
class DLinkZWaveMessageFactory : public ZWaveMessageFactory {
public:
	ZWaveMessage *create(const uint32_t &manufacturer, const uint32_t &product) override;
};
