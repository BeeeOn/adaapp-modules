/**
 * @file DLinkZWaveMessageFactory.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/Exception.h>

#include "Manufacturers/DLinkZWaveMessageFactory.h"

ZWaveMessage *DLinkZWaveMessageFactory::create(const uint32_t &manufacturer,
	const uint32_t &product)
{
	switch (product) {
	case DLINK_DCH_Z120: {
		return new DLinkDchZ120ZWaveMessage();
	}
	default:
		throw Poco::NotFoundException("Unsupported product");
	}
}
