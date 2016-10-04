/**
 * @file OpenZWaveModule.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <iostream>

#include <unistd.h>

#include <Poco/Logger.h>
#include <Poco/Util/AbstractConfiguration.h>

#include <Manager.h>
#include <Options.h>

#include "OpenZWaveModule.h"
#include "PocoLoggerAdapter.h"

using namespace std;
using namespace OpenZWave;
using namespace Poco;

#define DEFAULT_DONGLE_PATH           "/dev/ttyACM0"
#define DEFAULT_DRIVER_MAX_ATTEMPTS   5
#define DEFAULT_POLL_INTERVAL         300
#define DEFAULT_CONFIG_PATH           (string)"/etc/openzwave"
#define DEFAULT_USER_PATH             (string)"/etc/beeeon/openzwave/"
#define DEFAULT_LOGGING               true
#define DEFAULT_CONFIGURATION_FILE    true
#define DEFAULT_CETFICATION_PATH      (string)"/etc/openvpn/client.crt"

OpenZWaveModule::OpenZWaveModule(const Util::AbstractConfiguration &config):
	logger(Logger::get("OpenZWaveModule")),
	m_config(config),
	m_driver(m_config.getString("openzwave.dongle_path", DEFAULT_DONGLE_PATH))
{
}

void OpenZWaveModule::loadConfiguration()
{
	string configPath = "";
	string userPath = "";
	bool configurationFile = true;
	bool logging = true;
	int pollInterval = DEFAULT_POLL_INTERVAL;
	int driverMaxAttempts = DEFAULT_DRIVER_MAX_ATTEMPTS;

	try {
		// Path to xml config file for openzwave library
		configPath = m_config.getString("openzwave.config_path",
			DEFAULT_CONFIG_PATH);

		// Path to save user's data, store Z-Wave network config data and state
		userPath = m_config.getString("openzwave.user_path",
			DEFAULT_USER_PATH);

		// Enable or disable logging
		logging = m_config.getBool("openzwave.enable_logging",
			DEFAULT_LOGGING);

		// True if save config to file
		configurationFile = m_config.getBool("openzwave.configuration_file",
			DEFAULT_CONFIGURATION_FILE);

		// For old devicces, detect status changes
		pollInterval = m_config.getInt("openzwave.poll_interval",
			DEFAULT_POLL_INTERVAL);

		// Maximum number of retries before application shutdown, 0 - never
		driverMaxAttempts = m_config.getInt("openzwave.driver_max_attempts",
			DEFAULT_DRIVER_MAX_ATTEMPTS);
	}
	catch (Exception &ex) {
		logger.warning("use default configuration for logging");
		logger.log(ex, __FILE__, __LINE__);
	}

	Options::Create(configPath, userPath, "");
	Options::Get()->AddOptionInt("PollInterval", pollInterval);
	Options::Get()->AddOptionBool("logging", logging);
	Options::Get()->AddOptionBool("SaveConfiguration", configurationFile);
	Options::Get()->AddOptionInt("DriverMaxAttempts", driverMaxAttempts);
	Options::Get()->Lock();
}

std::string OpenZWaveModule::loadCertificationPath()
{
	string certificatePath = "";

	try {
		// Certification path to determine gateway ID for generate EUID
		certificatePath = m_config.getString("openzwave.certificate",
			DEFAULT_CETFICATION_PATH);
	}
	catch (Exception &ex) {
		logger.warning("use default configuration for certificatin path");
		logger.log(ex, __FILE__, __LINE__);
	}
	return certificatePath;
}

void OpenZWaveModule::start()
{
	// pocoLogger is deleted by OpenZWave library
	PocoLoggerAdapter *pocoLogger = new PocoLoggerAdapter();
	Log::SetLoggingClass(pocoLogger);

	loadConfiguration();
	Manager::Create();

	m_driver.registerItself();
}

void OpenZWaveModule::stop()
{
	if (!m_driver.unregisterItself())
		logger.error("The driver " + m_driver.getUSBDriverPath()
				+ "could not be found");

	Manager::Destroy();
	Options::Destroy();
}
