/**
 * @file MosquittoClient.h
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#pragma once

#include <iostream>

#include <unistd.h>

#include <Poco/Activity.h>
#include <Poco/Runnable.h>

#include <mosquittopp.h>

#include "BeeeOnMessage.h"
#include "GenericZWaveMessageFactory.h"

const std::string DATA_INTERFACE_FROM_ADAAPP = "BeeeOn/MQTTDataModule/FromAdaApp";
const std::string DATA_INTERFACE_TO_ADAAPP = "BeeeOn/MQTTDataModule/ToAdaApp";

/*
 * MQTT client for communication between adaapp and OpenZWave
 */
class MosquittoClient : public mosqpp::mosquittopp {
public:
	MosquittoClient(int keepalive = 60, int port = 1883, std::string id = "ozwave",
			std::string mainTopic = DATA_INTERFACE_FROM_ADAAPP, std::string host = "localhost");

	/*
	 * Send BeeeOnMessage to adaapp from OpenZWave
	 * @param &message message to be sent
	 */
	void sendBeeeOnMessage(BeeeOnMessage &message)
	{
		sendMessage(message.toJSONString(), DATA_INTERFACE_TO_ADAAPP);
	}

	/*
	 * Set ZWave network identifier
	 * @param homeID unique ZWave network identifier
	 */
	void setHomeID(uint32_t homeID)
	{
		m_homeID = homeID;
	}

	/*
	 * Start the activity
	 */
	void start()
	{
		m_activity.start();
	}

	/*
	 * Stop the activity
	 */
	void stop()
	{
		m_activity.stop();
	}

	/*
	 * Set ZWaveMessageFactory, which generates ZWaveMessages
	 * @param *factory Facotry which generates ZWaveMessages
	 */
	void setFactory(GenericZWaveMessageFactory *factory)
	{
		m_factory = factory;
	}

private:
	Poco::Logger& logger;
	int m_keepalive;
	int m_port;
	std::string m_id;
	std::string m_topic;
	std::string m_host;
	uint32_t m_homeID;
	Poco::Activity<MosquittoClient> m_activity;
	GenericZWaveMessageFactory *m_factory;

	/*
	 * Callback after connecting to the broker
	 * @param rc return code of the connection response
	 **/
	void on_connect(int rc) override;

	/*
	 * Callback after receive message
	 * @param message received message
	 */
	void on_message(const struct mosquitto_message *message) override;

	/*
	 * Run activity with connecting to the mqtt broker
	 */
	void runActivity();

	/*
	 * Select action from message
	 * @param &msg string message from adaaap
	 */
	void selectAction(const std::string &msg);

	/*
	 * Send data to the broker
	 * @param &message message to be sent
	 * @param &topic
	 */
	bool sendMessage(const std::string &message, const std::string &topic, int qos = 0);

	/*
	 * Send data from adaap to ZWave network - set actuator.
	 * @param &msg JSON message to be sent
	 */
	void setValue(BeeeOnMessage &message);
};
