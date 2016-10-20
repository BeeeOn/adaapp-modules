/**
 * @file GenericZWaveMessageFactory.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include <map>

#include <Poco/Exception.h>

#include "Manufacturers/FibaroZWaveMessageFactory.h"
#include "ZWaveMessageFactory.h"

class GenericZWaveMessageFactory : public ZWaveMessageFactory {
public:
	ZWaveMessage *create(const uint32_t &manufacturer, const uint32_t &product) override;

	/*
	 * Register Z-Wave manufacturer to factory using manufacturer id.
	 * @param &manufacturer Unique number of manufacturer
	 * @param &factory Manufacturer object
	 */
	void registerManufacturer(const uint32_t &manufacturer, ZWaveMessageFactory *factory);

private:
	std::map<const uint32_t, ZWaveMessageFactory *> m_manufacturers;
};
