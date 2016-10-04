/**
 * @file OpenZWaveModule.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

class OpenZWaveModule {
public:
	OpenZWaveModule(const Poco::Util::AbstractConfiguration &config);

	void start();
	void stop();

private:
	Poco::Logger &logger;
	const Poco::Util::AbstractConfiguration &m_config;

	/*
	 * Set Options for OpenZWave from ini file
	 */
	void loadConfiguration();

	/*
	 * Load Certification path from ini files
	 */
	std::string loadCertificationPath();
};
