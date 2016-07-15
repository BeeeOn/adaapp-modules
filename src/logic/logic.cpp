/*
 * @file logic.cpp
 * @Author BeeeOn team - Richard Wolfert (wolfert.richard@gmail.com)
 * @date July 2016
 * @brief IO logic implementation
 */

#include "logic.h"

void Logic::addLedConfiguration(struct ledConfiguration ledConf, int priority)
{
	for (std::vector<std::pair<int, struct ledConfiguration>>::iterator it = ledConfigs.begin(); it != ledConfigs.end();) {
		if ((*it).first == priority) {
			it = ledConfigs.erase(it);
		}
		else {
			it++;
		}
	}
	ledConfigs.push_back(std::pair<int, struct ledConfiguration>(priority, ledConf));
}

void Logic::removeLedConfiguration(int priority)
{
	for (std::vector<std::pair<int, struct ledConfiguration>>::iterator it = ledConfigs.begin(); it != ledConfigs.end();) {
		if ((*it).first == priority) {
			it = ledConfigs.erase(it);
		}
		else {
			it++;
		}
	}
	
}

struct ledConfiguration Logic::getHighestLedConf()
{
	int highestPriority = 0;
	struct ledConfiguration ledConf;
	for (std::vector<std::pair<int, struct ledConfiguration>>::iterator it = ledConfigs.begin(); it != ledConfigs.end();) {
		if ((*it).first >= highestPriority) {
			ledConf = (*it).second;
			highestPriority = (*it).first;
		}
		it++;
	}
	return ledConf;
}
