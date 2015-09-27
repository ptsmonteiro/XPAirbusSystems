#pragma once
#include <stdio.h>
#include <string.h>
#include "XPLM\XPLMDisplay.h"
#include "XPLM\XPLMGraphics.h"

class DebugWindow
{
private:
	XPLMWindowID	gWindow = NULL;

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