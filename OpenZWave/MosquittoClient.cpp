/**
 * @file MosquittoClient.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include <Manager.h>

#include <Poco/Runnable.h>
#include <Poco/NumberParser.h>

#include "MosquittoClient.h"

#define SLEEP_BETWEEN_RECONNECT     1
#define NODE_ID_MASK                0xff

using namespace OpenZWave;
using namespace std;
using Poco::NumberParser;

MosquittoClient::MosquittoClient(int keepalive, int port, std::string id,
		std::string mainTopic, std::string host):
	mosquittopp(id.c_str()),
	logger(Poco::Logger::get("MosquittoClient")),
	m_keepalive(keepalive),
	m_port(port),
	m_id(id),
	m_topic(mainTopic),
	m_host(host),
	m_activity(this, &MosquittoClient::runActivity)
{
	mosqpp::lib_init();
}

bool MosquittoClient::sendMessage(const std::string &message, const std::string &topic,
	int qos)
{
	logger.information("Send message: " + message);

	return publish(NULL, DATA_INTERFACE_TO_ADAAPP.c_str(), message.length(),
		message.c_str(), qos, false) == MOSQ_ERR_SUCCESS;
}

void MosquittoClient::on_message(const struct mosquitto_message *message)
{
	std::string msgTopic(message->topic);
	std::string msgText((const char *) message->payload);

	if (msgTopic == DATA_INTERFACE_FROM_ADAAPP) {
		logger.information("Message received on " + msgTopic
				+ "\nMessage: " + msgText);

		selectAction(msgText);
	}
}

void MosquittoClient::on_connect(int rc)
{
	logger.debug("Mosquito connecting with code: " + to_string(rc));

	if (rc == 0)
		subscribe(NULL, m_topic.c_str());
}

void MosquittoClient::runActivity()
{
	connect_async(m_host.c_str(), m_port, m_keepalive);

	while (!m_activity.isStopped()) {
		if (loop() != MOSQ_ERR_SUCCESS) {
			reconnect();
			sleep(SLEEP_BETWEEN_RECONNECT);
		}
	}
}

void MosquittoClient::setValue(BeeeOnMessage &beeeOnMessage)
{
	uint32_t manufacturer;
	uint32_t product;
	long long euid = beeeOnMessage.getEUID();
	vector<BeeeOnSensorValue> beeeOnSensorValue;

	uint8_t nodeId = euid & NODE_ID_MASK;

	try {
		manufacturer = NumberParser::parseHex(
			OpenZWave::Manager::Get()->GetNodeManufacturerId(m_homeID, nodeId));
		product = NumberParser::parseHex(
			OpenZWave::Manager::Get()->GetNodeProductId(m_homeID, nodeId));
	}
	catch (Poco::Exception &ex) {
		logger.error("parsed failed");
		logger.log(ex, __FILE__, __LINE__);
	}

	ZWaveMessage *message = m_factory->create(manufacturer, product);

	beeeOnMessage.getValues(beeeOnSensorValue);
	message->setValue(beeeOnSensorValue, nodeId);
	delete message;
}

void MosquittoClient::selectAction(const std::string &msg)
{
	BeeeOnMessage message;
	message.insertFromJSONString(msg);

	if (message.getState() == "listen")
		OpenZWave::Manager::Get()->AddNode(m_homeID, false);
	else if (message.getState() == "clean")
		OpenZWave::Manager::Get()->RemoveNode(m_homeID);
	else if (message.getState() == "remove")
		OpenZWave::Manager::Get()->RemoveFailedNode(m_homeID, message.getEUID());
	else if (message.getState() == "hardreset")
		OpenZWave::Manager::Get()->ResetController(m_homeID);
	else if (message.getState() == "set")
		setValue(message);
	else
		logger.error("Unknown command from MQTT", __FILE__, __LINE__);
}
