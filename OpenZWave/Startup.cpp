/**
 * @file Startup.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#define SYSTEM_CONFIG_FILE   (std::string)"/etc/beeeon/openzwave/openzwave.ini"
#define SYSTEM_LOGGING_FILE  (std::string)"/etc/beeeon/openzwave/logging.ini"

#include <time.h>

#include "GenericZWaveMessageFactory.h"
#include "Startup.h"
#include "OpenZWaveModule.h"

#include "Manufacturers/AeotecZWaveMessageFactory.h"
#include "Manufacturers/DLinkZWaveMessageFactory.h"
#include "Manufacturers/FibaroZWaveMessageFactory.h"

void Startup::loadAllConfiguration()
{
	findAndLoadConfig();
	findAndLoadLogging();
}

bool Startup::readConfiguration(const File &file)
{
	if (!file.exists()) {
		logger().debug("configuration file " + file.path() + " not found");
		return false;
	}

	loadConfiguration(file.path());
	logger().notice("configuration file " + file.path() + " loaded");

	return true;
}

void Startup::findAndLoadConfig()
{
	File system(SYSTEM_CONFIG_FILE);

	if (!readConfiguration(system.path()))
		logger().warning("Config file " + SYSTEM_CONFIG_FILE + " not found");
}

void Startup::findAndLoadLogging()
{
	File system(SYSTEM_LOGGING_FILE);

	if (!readConfiguration(system.path()))
		logger().warning("Logging file " + SYSTEM_LOGGING_FILE + "not found");
}

void Startup::initialize(Application &app)
{
	loadAllConfiguration();
	Application::initialize(app);
}

int Startup::main(const std::vector <std::string> &args)
{
	srand(time(NULL));

	OpenZWaveModule module(config());

	GenericZWaveMessageFactory factory;
	module.setFactory(&factory);

	AeotecZWaveMessageFactory aeotecFactory;
	factory.registerManufacturer(AEOTEC_MANUFACTURER, &aeotecFactory);

	DLinkZWaveMessageFactory dlinkFactory;
	factory.registerManufacturer(DLINK_MANUFACTURER, &dlinkFactory);

	FibaroZWaveMessageFactory fibaroFactory;
	factory.registerManufacturer(FIBARO_MANUFACTURER, &fibaroFactory);

	module.start();

	waitForTerminationRequest();
	module.stop();

	return EXIT_OK;
}
