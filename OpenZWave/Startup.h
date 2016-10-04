/**
 * @file Startup.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Poco/File.h>
#include <Poco/Util/ServerApplication.h>

using namespace Poco;
using namespace Poco::Util;

class Startup : public ServerApplication {
public:
	Startup()
	{
	}

protected:
	/*
	 * Load configuration for OpenZWave and Logging
	 */
	void loadAllConfiguration();

	/*
	 * Read configuration data from file
	 * @param &file configuration file
	 * @return true if the file has been loaded successfully
	 */
	bool readConfiguration(const File &file);

	/*
	 * Find and load configuration file
	 */
	void findAndLoadConfig();

	/*
	 * Find and load logging file
	 */
	void findAndLoadLogging();

	/*
	 * Initialize Application, it load configuration file and run application.
	 */
	void initialize(Application &app) override;

	/*
	 * Main method of the program
	 */
	int main(const std::vector <std::string> &args) override;
};
