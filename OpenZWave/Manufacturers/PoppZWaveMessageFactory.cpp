/**
 * @file PoppZWaveMessageFactory.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/Exception.h>

#include "Products/Popp123601ZWaveMessage.h"
#include "Manufacturers/PoppZWaveMessageFactory.h"

ZWaveMessage *PoppZWaveMessageFactory::create(const uint32_t &manufacturer,
	const uint32_t &product)
{
	switch(product) {
	case POPP_123601:
		return new Popp123601ZWaveMessage();
	default:
		throw Poco::NotFoundException("Unsupported product " + std::to_string(product));
	}
}
