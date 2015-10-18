#include "main.h"

// Callback for Error Tests
void AirbusSystemsErrorCB(const char * msg)
{
	Logger->LogMessage((char*)msg);
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

	CurrentPluginID = XPLMGetMyID();
	
	sprintf(Buffer, "XPAS :: XPluginStart ID=%d.\n", CurrentPluginID);
	XPLMDebugString(Buffer);


	// Allocate debug window
	FbwOutputWindow = new DebugWindow();

	// Register the callback for errors
	XPLMSetErrorCallback(AirbusSystemsErrorCB);

	// This used for the Draw Objects tests
	XPLMRegisterDrawCallback(AirbusSystemsDrawCB, xplm_Phase_Objects, 0, 0);

	LoadAircraft();

	return 1;
}

void LoadAircraft() {
	Aircraft = new A320();
	Aircraft->init();

	// Main flight loop
	XPLMRegisterFlightLoopCallback(AirbusSystemsFlightLoopCB, AirbusSystemsFlightLoopIntervalSeconds, NULL);
}

void UnloadAircraft() {
	XPLMUnregisterFlightLoopCallback(AirbusSystemsFlightLoopCB, NULL);

	// Clean up
	delete Aircraft;
}

PLUGIN_API void	XPluginStop(void)
{
	XPLMUnregisterDrawCallback(AirbusSystemsDrawCB, xplm_Phase_Objects, 0, 0);
	UnloadAircraft();
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
	sprintf(Buffer, "AirbusSystems: XPluginReceiveMessage - Type:%d From:%d\n", inMsg, inFrom);
	XPLMDebugString(Buffer);

	/* Messages defined in XPLMPlugin.h */
	switch (inMsg) {
		case XPLM_MSG_PLANE_UNLOADED:
			UnloadAircraft();
			break;

		case XPLM_MSG_PLANE_LOADED:
			LoadAircraft();

			break;
	}
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