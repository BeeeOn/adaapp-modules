/**
 * @file GenericZWaveMessageFactory.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <string>

#include "GenericZWaveMessageFactory.h"

ZWaveMessage *GenericZWaveMessageFactory::create(const uint32_t &manufacturer, const uint32_t &product)
{
	auto search = m_manufacturers.find(manufacturer);

	if (search != m_manufacturers.end())
		return search->second->create(manufacturer, product);
	else
		throw Poco::Exception("Manufacturer " + std::to_string(manufacturer) + " is not registered");
}

void GenericZWaveMessageFactory::registerManufacturer(const uint32_t &manufacturer, ZWaveMessageFactory *factory)
{
	if (factory != NULL)
		m_manufacturers.insert(std::make_pair(manufacturer, factory));
}
