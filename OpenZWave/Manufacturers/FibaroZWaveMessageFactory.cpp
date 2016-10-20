/**
 * @file FibaroZWaveMessageFactory.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/Exception.h>

#include "Manufacturers/FibaroZWaveMessageFactory.h"

ZWaveMessage *FibaroZWaveMessageFactory::create(const uint32_t &manufacturer,
	const uint32_t &product)
{
	switch(product) {
	case FIBARO_FGK_107:
		return new FibaroFGK107ZWaveMessage();
	default:
		throw Poco::NotFoundException("Unsupported product " + std::to_string(product));
	}
}
