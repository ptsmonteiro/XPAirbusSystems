#pragma warning(disable:4477)
#pragma warning(disable:4313)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "XPLM\XPLMPlugin.h"
#include "XPLM\XPLMDisplay.h"
#include "XPLM\XPLMGraphics.h"
#include "XPLM\XPLMProcessing.h"
#include "XPLM\XPLMDataAccess.h"
#include "XPLM\XPLMMenus.h"
#include "XPLM\XPLMUtilities.h"
#include "Widgets\XPWidgets.h"
#include "Widgets\XPStandardWidgets.h"
#include "XPLM\XPLMScenery.h"
#include "XPLM\XPLMPlanes.h"
#include "A320.h"

#if IBM
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#else
#if __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#endif

const float AirbusSystemsFlightLoopIntervalSeconds = 0.1;
const char VersionNumber[] = "v1.00";
char Buffer[256];

extern float AirbusSystemsFlightLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon);

// Callback for Error Tests
void AirbusSystemsErrorCB(const char * msg)
{
	Logger->LogMessage((char*) msg);
}


// Prototype for Draw Object tests
int	AirbusSystemsDrawCB(
	XPLMDrawingPhase     inPhase,
	int                  inIsBefore,
	void *               inRefcon);


//---------------------------------------------------------------------------

PLUGIN_API int XPluginStart(
	char *		outName,
	char *		outSig,
	char *		outDesc)
{
	strcpy(outName, "XPAS-A320");
	strcpy(outSig, "matiasmonteiro.projects.AirbusSystems");
	strcpy(outDesc, "Airbus Systems Plugin - A320");

	// Allocate aircraft
	Aircraft = new A320();
	Aircraft->init();

	// Register the callback for errors
	XPLMSetErrorCallback(AirbusSystemsErrorCB);

	// Main flight loop
	XPLMRegisterFlightLoopCallback(AirbusSystemsFlightLoopCB, AirbusSystemsFlightLoopIntervalSeconds, NULL);

	// This used for the Draw Objects tests
	XPLMRegisterDrawCallback(AirbusSystemsDrawCB, xplm_Phase_Objects, 0, 0);

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	// Clean up
	delete Aircraft;

	XPLMUnregisterDrawCallback(AirbusSystemsDrawCB, xplm_Phase_Objects, 0, 0);
	XPLMUnregisterFlightLoopCallback(AirbusSystemsFlightLoopCB, NULL);
}

PLUGIN_API int XPluginEnable(void)
{
	return 1;
}

PLUGIN_API void XPluginDisable(void)
{
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam)
{
	sprintf(Buffer, "AirbusSystems: XPluginReceiveMessage - Type %d.\n", inMsg);
	XPLMDebugString(Buffer);
}

float AirbusSystemsFlightLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon)
{
	Aircraft->update(elapsedMe);

	return AirbusSystemsFlightLoopIntervalSeconds;
}

int	AirbusSystemsDrawCB(XPLMDrawingPhase inPhase, int inIsBefore, void * inRefcon)
{
	return 1;
}