/**
 * @file PocoLoggerAdapter.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include "PocoLoggerAdapter.h"

#define USB_DONGLE_NODE_ID    0

using namespace OpenZWave;
using namespace std;

PocoLoggerAdapter::PocoLoggerAdapter():
	logger(Poco::Logger::get("PocoLoggerAdapter"))
{
}

PocoLoggerAdapter::~PocoLoggerAdapter()
{
}

string PocoLoggerAdapter::getNodeIdString(uint8 const nodeId)
{
	if (nodeId == USB_DONGLE_NODE_ID)
		return "";

	return "NodeId: " + to_string(nodeId) + " ";
}

void PocoLoggerAdapter::Write(LogLevel logLevel, uint8 const nodeId,
	char const* format, va_list args)
{
	std::string logMessage;
	char lineBuf[1024] = {0};

	if (format != NULL && format[0] != '\0')
		vsnprintf(lineBuf, sizeof(lineBuf), format, args);

	logMessage.append(getNodeIdString(nodeId));
	logMessage.append(lineBuf);

	if (logMessage.length() > 0)
		writeLogImpl(logLevel, logMessage);
}

void PocoLoggerAdapter::writeLogImpl(LogLevel level, string logMessage)
{
	switch(level) {
	case LogLevel_Fatal:
		logger.fatal(logMessage);
		break;
	case LogLevel_Error:
		logger.error(logMessage);
		break;
	case LogLevel_Warning:
		logger.warning(logMessage);
		break;
	case LogLevel_Alert:
		logger.notice(logMessage);
		break;
	case LogLevel_Always:
	case LogLevel_Info:
		logger.information(logMessage);
		break;
	case LogLevel_Detail:
	case LogLevel_Debug:
		logger.debug(logMessage);
		break;
	case LogLevel_StreamDetail:
	case LogLevel_Internal:
		logger.trace(logMessage);
	default:
		break;
	}
}
