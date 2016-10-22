/**
 * @file PhilioZWaveMessageFactory.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/Exception.h>

#include "Manufacturers/PhilioZWaveMessageFactory.h"

ZWaveMessage *PhilioZWaveMessageFactory::create(const uint32_t &manufacturer,
	const uint32_t &product)
{
	switch (product) {
	case PHILIO_PST02_1C: {
		return new PhilioPST021CZWaveMessage();
	}
	default:
		throw Poco::NotFoundException("Unsupported product");
	}
}
