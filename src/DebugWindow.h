#pragma once
#include <stdio.h>
#include <string.h>
#include "XPLM/XPLMDisplay.h"
#include "XPLM/XPLMGraphics.h"

class DebugWindow
{
private:
	XPLMWindowID	gWindow = NULL;
	
	static char* formatString(const char* prefix, double value);
	static char* formatString(const char* prefix, float value);
	static char* formatString(const char* prefix, int value);
	static void appendLine(const char* message);
	
	
public:
	

	static int WindowClickCallback(
		XPLMWindowID         inWindowID,
		int                  x,
		int                  y,
		XPLMMouseStatus      inMouse,
		void *               inRefcon);

	static void WindowKeyCallback(
		XPLMWindowID         inWindowID,
		char                 inKey,
		XPLMKeyFlags         inFlags,
		char                 inVirtualKey,
		void *               inRefcon,
		int                  losingFocus);

	static void WindowRenderCallback(
		XPLMWindowID         inWindowID,
		void *               inRefcon);

	DebugWindow();
	~DebugWindow();
};