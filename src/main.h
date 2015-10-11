#pragma warning(disable:4477)
#pragma warning(disable:4313)

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
#include "DebugWindow.h"


/* Globals*/

extern float AirbusSystemsFlightLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon);

/* Privates*/
const float AirbusSystemsFlightLoopIntervalSeconds = 0.1;
const char VersionNumber[] = "v1.00";
char Buffer[256];

DebugWindow* FbwOutputWindow;

