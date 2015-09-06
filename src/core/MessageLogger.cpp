#include "core\core.h"

MessageLogger::MessageLogger()
{
}

MessageLogger::~MessageLogger()
{
}

void MessageLogger::LogMessage(char* msg)
{
	XPLMDebugString(msg);
}
