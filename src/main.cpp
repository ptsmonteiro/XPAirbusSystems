
#pragma warning(disable:4477)
#pragma warning(disable:4313)

#include "XPLM\XPLMPlugin.h"
#include "XPLM\XPLMDisplay.h"
#include "XPLM\XPLMProcessing.h"
#include "XPLM\XPLMDataAccess.h"
#include "XPLM\XPLMMenus.h"
#include "XPLM\XPLMUtilities.h"
#include "Widgets\XPWidgets.h"
#include "Widgets\XPStandardWidgets.h"
#include "XPLM\XPLMScenery.h"
#include "XPLM\XPLMPlanes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "A320.h"

#if IBM
#include <windows.h>
#include <stdio.h>
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

//---------------------------------------------------------------------------

A320 *aircraft;

const float AirbusSystemsFlightLoopIntervalSeconds = 0.01;

char VersionNumber[] = "v1.00";

char Buffer[256];

//---------------------------------------------------------------------------

// Displays data in widget
float AirbusSystemsFlightLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon);;

// Callback for Error Tests
void	AirbusSystemsErrorCB(const char * msg)
{
	XPLMDebugString("================================================================\n");
	XPLMDebugString("AirbusSystemsErrorCB - error CB called: ");
	XPLMDebugString(msg);
	XPLMDebugString("\n");
	XPLMDebugString("----------------------------------------------------------------\n");
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
	strcpy(outName, "AirbusSystems");
	strcpy(outSig, "matiasmonteiro.projects.AirbusSystems");
	strcpy(outDesc, "Airbus Systems Plugin");

	// Allocate aircraft
	aircraft = new A320();

	// Register the callback for errors
	XPLMSetErrorCallback(AirbusSystemsErrorCB);

	// Main flight loop
	XPLMRegisterFlightLoopCallback(AirbusSystemsFlightLoopCB, AirbusSystemsFlightLoopIntervalSeconds, NULL);

	// This used for the Draw Objects tests
	XPLMRegisterDrawCallback( AirbusSystemsDrawCB, xplm_Phase_Objects, 0, 0 );

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	// Clean up
	delete aircraft;

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
	XPLMDebugString("================================================================\n");
	sprintf(Buffer, "AirbusSystems: XPluginReceiveMessage - Type %d.\n", inMsg);
	XPLMDebugString(Buffer);
	XPLMDebugString("----------------------------------------------------------------\n");
}

// Used to test the creation and destruction of a Flightloop Callback from within a Flightloop Callback.
float AirbusSystemsFlightLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon)
{
	aircraft->update(elapsedMe);
	return AirbusSystemsFlightLoopIntervalSeconds;
}

int	AirbusSystemsDrawCB(XPLMDrawingPhase     inPhase,    
                        int                  inIsBefore,    
                        void *               inRefcon)
{
	return 1;
}
