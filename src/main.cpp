#include "main.h"

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

	// Allocate debug window
	FbwOutputWindow = new DebugWindow();

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
	XPLMUnregisterDrawCallback(AirbusSystemsDrawCB, xplm_Phase_Objects, 0, 0);
	XPLMUnregisterFlightLoopCallback(AirbusSystemsFlightLoopCB, NULL);


	// TODO: Call destructor on Debugwindows.
	// TODO: Unregister drawing callbacks
	// TODO: Delete debug Window ?


	// Clean up
	delete Aircraft;

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
	Aircraft->update(elapsedMe, elapsedSim, counter);

	return AirbusSystemsFlightLoopIntervalSeconds;
}

int	AirbusSystemsDrawCB(XPLMDrawingPhase inPhase, int inIsBefore, void * inRefcon)
{
	return 1;
}