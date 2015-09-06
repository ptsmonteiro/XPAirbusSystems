#include "core\core.h"

MessageLogger::MessageLogger()
{
}

MessageLogger::~MessageLogger()
{
}

void MessageLogger::LogMessage(const char* msg)
{
	XPLMDebugString(msg);
}
