/**
 * @file AeotecZWaveMessageFactory.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/Exception.h>

#include "Manufacturers/AeotecZWaveMessageFactory.h"

ZWaveMessage *AeotecZWaveMessageFactory::create(const uint32_t &manufacturer,
	const uint32_t &product)
{
	switch (product) {
	case AEOTEC_ZW100:
		return new AeotecZW100ZWaveMessage();
	default:
		throw Poco::NotFoundException("Unsupported product " + std::to_string(product));
	}
}
