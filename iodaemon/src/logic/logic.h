/*
 * @file logic.h
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief
 */
#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "HWInterface.h"
#include "Receiver.h"

class Logic
{
private:
	std::vector<std::pair<int,struct ledConfiguration>> ledConfigs;
public:
	void addLedConfiguration(struct ledConfiguration ledConf, int priority);
	void removeLedConfiguration(int priority);
	struct ledConfiguration getHighestLedConf();
};
