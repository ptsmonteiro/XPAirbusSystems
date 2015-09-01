
/*
SDK210Tests Example
Tests the new SDK 2.10 functions.

Version 1.0.0.1		Intitial Sandy Barbour 25/01/2012

NOTES
1.
This example will only work with the new plugin SDK 2.10 and will only run in X-Plane V10.

2.
The 2.10 plugin SDK now has 64 bit safe variables.

Unfortunately early Micrsoft Visual Studio products do not have the required header files to support this.
I know that VS6 does not and I believe that 2003 does not either.
VS2008 onwards is fine and that is what I tested this example with on windows.

So, any VS6 users will need to try and located a header that will allow the example to compile.
This is a MS problem and not an SDK problem.

I did find this header that worked.

http://www.azillionmonkeys.com/qed/pstdint.h

But we will not be supporting it or any other headers usage in this example.
*/

//---------------------------------------------------------------------------

#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#include "XPLMMenus.h"
#include "XPLMUtilities.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPLMScenery.h"
#include "XPLMPlanes.h"
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

A320 myPlane;

enum
{
/*0*/	MAIN_FLCB = 0,
/*1*/	TEMP_FLCB,
/*2*/	INFO,
/*3*/	MENU_2,
/*4*/	DRAWING
};

enum
{
/*0*/	USER_AIRCRAFT = 0,
/*1*/	AI_AIRCRAFT
};

char SDK210TestsVersionNumber[] = "v1.00";

char SDK210Tests_Buffer[256];
XPLMFlightLoopID SDK210Tests_XPLMTempFlightLoopID = NULL;
XPLMObjectRef	SDK210Tests_Windsock=NULL;
XPLMProbeRef	SDK210Tests_Windsock_Probe=NULL;

// Number of edit boxes in widget
#define SDK210TESTS_MAX_ITEMS 5

// Description text for widget edit boxes
char SDK210TestsDataDesc[SDK210TESTS_MAX_ITEMS][255] = {"Main FLCB", "Temp FLCB", "Info", "Menu 2", "Drawing"};

// Used as interlock for widget
int SDK210TestsMenuItem1;

// Used by menus
XPLMMenuID	SDK210TestsMenuId = NULL, SDK210TestsMenuId2 = NULL;
int	SDK210TestsMenuIndex1 = 0, SDK210TestsMenuIndex2 = 0, SDK210TestsMenuIndex3 = 0;
int	SDK210TestsMenuItem = 0, SDK210TestsMenuItem2 = 0;
int SDK210TestsCreateFLCB = 0;
int SDK210TestsDestroyFLCB = 0;

// Datarefs
XPLMDataRef	SDK210Tests_refx = NULL;
XPLMDataRef	SDK210Tests_refy = NULL;
XPLMDataRef	SDK210Tests_refz = NULL;
XPLMDataRef	SDK210Tests_wrl_type = NULL;

// Widgets
XPWidgetID	SDK210TestsWidget = NULL, SDK210TestsWindow = NULL;
XPWidgetID	SDK210TestsButton1 = NULL, SDK210TestsButton2 = NULL, SDK210TestsButton3 = NULL, SDK210TestsButton4 = NULL;
XPWidgetID	SDK210TestsButton5 = NULL, SDK210TestsButton6 = NULL, SDK210TestsButton7 = NULL, SDK210TestsButton8 = NULL;
XPWidgetID	SDK210TestsText[SDK210TESTS_MAX_ITEMS] = {NULL};
XPWidgetID	SDK210TestsEdit[SDK210TESTS_MAX_ITEMS] = {NULL};

// Used by the Draw Objects test
XPLMObjectRef	SDK210TestsObject=NULL;
int SDK210TestsDrawingEnabled = 0;

// Used by the FLCB test
int	SDK210TestsMainLoopCBCounter = 0;
int	SDK210TestsTempLoopCBCounter = 0;

char *pSDK210TestsAircraft[2];
char SDK210TestsAircraftPath[2][512];

//---------------------------------------------------------------------------

// Displays data in widget
float SDK210TestsMainLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon);;
float SDK210TestsTempLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon);;

// Callback for Error Tests
void	SDK210TestsErrorCB(const char * msg)
{
	XPLMDebugString("================================================================\n");
	XPLMDebugString("SDK210Tests: SDK210TestsErrorCB - error CB called: ");
	XPLMDebugString(msg);
	XPLMDebugString("\n");
	XPLMDebugString("----------------------------------------------------------------\n");
}

// Menu Prototypes
void SDK210TestsMenuHandler(void *, void *);
void SDK210TestsMenuHandler2(void *, void *);

// Widget prototypes
void CreateSDK210Tests(int x1, int y1, int w, int h);

int SDK210TestsHandler(
						XPWidgetMessage			inMessage,
						XPWidgetID				inWidget,
						intptr_t				inParam1,
						intptr_t				inParam2);

// Prototype for Draw Object tests
int	SDK210TestsDrawWindsock(
                                   XPLMDrawingPhase     inPhase,    
                                   int                  inIsBefore,    
                                   void *               inRefcon);


void SDK210TestsNativePaths(void);
void SDK210TestsAcquireAircraft(void);
void SDK210TestsLoadAircraft(int Mode);

//---------------------------------------------------------------------------

PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
	strcpy(outName, "AirbusSystems");
	strcpy(outSig, "matiasmonteiro.projects.AirbusSystems");
	strcpy(outDesc, "Airbus Systems Plugin");

	//myPlane->start();

	// Register the callback for errors
	XPLMSetErrorCallback(SDK210TestsErrorCB);

	// Datarefs to get the aicraft position
	SDK210Tests_refx = XPLMFindDataRef("sim/flightmodel/position/local_x");
	SDK210Tests_refy = XPLMFindDataRef("sim/flightmodel/position/local_y");
	SDK210Tests_refz = XPLMFindDataRef("sim/flightmodel/position/local_z");

	SDK210Tests_wrl_type = XPLMFindDataRef("sim/graphics/view/world_render_type");

	// Create the menus
	SDK210TestsMenuItem = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "SDK210Tests", NULL, 1);
	SDK210TestsMenuId = XPLMCreateMenu("SDK210Tests", XPLMFindPluginsMenu(), SDK210TestsMenuItem, SDK210TestsMenuHandler, NULL);
	SDK210TestsMenuItem2 = XPLMAppendMenuItem(SDK210TestsMenuId, "SDK210Tests", (void *)"SDK210Tests", 1);
	
	SDK210TestsMenuItem1 = 0;
	XPLMRegisterFlightLoopCallback(SDK210TestsMainLoopCB, 1.0, NULL);

	// This used for the Draw Objects tests
	XPLMRegisterDrawCallback( SDK210TestsDrawWindsock, xplm_Phase_Objects, 0, 0 );

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	// Clean up
	if(SDK210Tests_Windsock) XPLMUnloadObject(SDK210Tests_Windsock);
	if(SDK210Tests_Windsock_Probe) XPLMDestroyProbe(SDK210Tests_Windsock_Probe);
	XPLMDestroyMenu(SDK210TestsMenuId);
    XPLMUnregisterDrawCallback(SDK210TestsDrawWindsock, xplm_Phase_Objects, 0, 0);
	XPLMUnregisterFlightLoopCallback(SDK210TestsMainLoopCB, NULL);
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
	switch(inMsg) 
	{
		case XPLM_MSG_WILL_WRITE_PREFS:
			XPLMDebugString("================================================================\n");
			XPLMDebugString("SDK210Tests: XPluginReceiveMessage - Will write prefs.\n");
			XPLMDebugString("----------------------------------------------------------------\n");
			break;
		case XPLM_MSG_LIVERY_LOADED:
			XPLMDebugString("================================================================\n");
			sprintf(SDK210Tests_Buffer,"SDK210Tests: XPluginReceiveMessage - Livery loaded for plane %d.\n", inParam);
			XPLMDebugString(SDK210Tests_Buffer);
			XPLMDebugString("----------------------------------------------------------------\n");
			break;		
	}
}

//---------------------------------------------------------------------------

// Used to test the creation and destruction of a Flightloop Callback from within a Flightloop Callback.
float SDK210TestsMainLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon)
{
	SDK210TestsMainLoopCBCounter++;
	if (SDK210TestsMainLoopCBCounter>100)
		SDK210TestsMainLoopCBCounter=0;
	if (SDK210TestsMenuItem1 == 1)
	{
		sprintf(SDK210Tests_Buffer,"Main FLCB Counter = %d\n", SDK210TestsMainLoopCBCounter);
		XPSetWidgetDescriptor(SDK210TestsEdit[MAIN_FLCB], SDK210Tests_Buffer);
	}
	if (SDK210TestsCreateFLCB)
	{
		XPLMCreateFlightLoop_t	SDK210Tests_XPLMCreateFlightLoop_t_ptr = { sizeof(XPLMCreateFlightLoop_t), xplm_FlightLoop_Phase_AfterFlightModel, SDK210TestsTempLoopCB, NULL };		
		SDK210Tests_XPLMTempFlightLoopID = XPLMCreateFlightLoop(&SDK210Tests_XPLMCreateFlightLoop_t_ptr);
		SDK210TestsCreateFLCB = 0;
	}
	if (SDK210TestsDestroyFLCB)
	{
		XPLMDestroyFlightLoop(SDK210Tests_XPLMTempFlightLoopID);
		SDK210TestsDestroyFLCB = 0;
		XPSetWidgetDescriptor(SDK210TestsEdit[TEMP_FLCB], "");
	}

	return 1.0;
}

// Temporary Flightloop Callback
float SDK210TestsTempLoopCB(float elapsedMe, float elapsedSim, int counter, void * refcon)
{
	SDK210TestsTempLoopCBCounter++;
	if (SDK210TestsTempLoopCBCounter>100)
		SDK210TestsTempLoopCBCounter=0;
	if (SDK210TestsMenuItem1 == 1)
	{
		sprintf(SDK210Tests_Buffer,"Temp FLCB Counter = %d\n", SDK210TestsTempLoopCBCounter);
		XPSetWidgetDescriptor(SDK210TestsEdit[TEMP_FLCB], SDK210Tests_Buffer);
	}

	return 1.0;
}

//---------------------------------------------------------------------------

// Process Menu 1 selections
void SDK210TestsMenuHandler(void * mRef, void * iRef)
{
    // Menu selected for widget
	if (!strcmp((char *) iRef, "SDK210Tests"))
	{
		if (SDK210TestsMenuItem1 == 0)
		{
			CreateSDK210Tests(100, 550, 650, 330);
			SDK210TestsMenuItem1 = 1;
		}
	}
}						

// Process Menu 2 selections
void SDK210TestsMenuHandler2(void * mRef, void * iRef)
{
    // Menu Index 1 Selected
	if (!strcmp((char *) iRef, "1"))
	{
		if (SDK210TestsMenuItem1 == 1)
		{
			sprintf(SDK210Tests_Buffer,"Menu 2 : Item 1 : mRef = %x, iRef = %x\n", mRef, iRef);
			XPSetWidgetDescriptor(SDK210TestsEdit[MENU_2], SDK210Tests_Buffer);
		}
	}

    // Menu Index 2 Selected
	if (!strcmp((char *) iRef, "2"))
	{
		if (SDK210TestsMenuItem1 == 1)
		{
			sprintf(SDK210Tests_Buffer,"Menu 2 : Item 2 : mRef = %x, iRef = %x\n", mRef, iRef);
			XPSetWidgetDescriptor(SDK210TestsEdit[MENU_2], SDK210Tests_Buffer);
		}
	}

    // Menu Index 3 Selected
	if (!strcmp((char *) iRef, "3"))
	{
		if (SDK210TestsMenuItem1 == 1)
		{
			sprintf(SDK210Tests_Buffer,"Menu 2 : Item 3 : mRef = %x, iRef = %x\n", mRef, iRef);
			XPSetWidgetDescriptor(SDK210TestsEdit[MENU_2], SDK210Tests_Buffer);
		}
	}
}						

//---------------------------------------------------------------------------

// Creates the widget with buttons for test and edit boxes for info
void CreateSDK210Tests(int x, int y, int w, int h)
{
	int Item;

	int x2 = x + w;
	int y2 = y - h;
	char Buffer[255];
	
	sprintf(Buffer, "%s %s %s", "SDK210Tests", SDK210TestsVersionNumber, "- Sandy Barbour 2012");
	SDK210TestsWidget = XPCreateWidget(x, y, x2, y2,
					1,	// Visible
					Buffer,	// desc
					1,		// root
					NULL,	// no container
					xpWidgetClass_MainWindow);

	XPSetWidgetProperty(SDK210TestsWidget, xpProperty_MainWindowHasCloseBoxes, 1);

	SDK210TestsWindow = XPCreateWidget(x+50, y-50, x2-50, y2+50,
					1,	// Visible
					"",	// desc
					0,		// root
					SDK210TestsWidget,
					xpWidgetClass_SubWindow);

	XPSetWidgetProperty(SDK210TestsWindow, xpProperty_SubWindowType, xpSubWindowStyle_SubWindow);

	SDK210TestsButton1 = XPCreateWidget(x+60, y-60, x+180, y-82,
						1, " Create Temp FLCB", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton1, xpProperty_ButtonType, xpPushButton);

	SDK210TestsButton2 = XPCreateWidget(x+190, y-60, x+330, y-82,
						1, " Schedule Temp FLCB", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton2, xpProperty_ButtonType, xpPushButton);

	SDK210TestsButton3 = XPCreateWidget(x+340, y-60, x+470, y-82,
						1, " Destroy Temp FLCB", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton3, xpProperty_ButtonType, xpPushButton);

	SDK210TestsButton4 = XPCreateWidget(x+480, y-60, x+580, y-82,
						1, " Native Paths", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton4, xpProperty_ButtonType, xpPushButton);

	SDK210TestsButton5 = XPCreateWidget(x+60, y-90, x+180, y-112,
						1, " Append Menu Item", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton5, xpProperty_ButtonType, xpPushButton);

	SDK210TestsButton6 = XPCreateWidget(x+190, y-90, x+330, y-112,
						1, " Remove Menu Item", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton6, xpProperty_ButtonType, xpPushButton);
	
	SDK210TestsButton7 = XPCreateWidget(x+340, y-90, x+470, y-112,
						1, " Drawing Enable", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton7, xpProperty_ButtonType, xpPushButton);

	SDK210TestsButton8 = XPCreateWidget(x+480, y-90, x+580, y-112,
						1, " Drawing Disable", 0, SDK210TestsWidget,
						xpWidgetClass_Button);

	XPSetWidgetProperty(SDK210TestsButton8, xpProperty_ButtonType, xpPushButton);

	for (Item=0; Item<SDK210TESTS_MAX_ITEMS; Item++)
	{
		SDK210TestsText[Item] = XPCreateWidget(x+60, y-(120 + (Item*30)), x+160, y-(142 + (Item*30)),
							1,	// Visible
							SDK210TestsDataDesc[Item],// desc
							0,		// root
							SDK210TestsWidget,
							xpWidgetClass_Caption);

		SDK210TestsEdit[Item] = XPCreateWidget(x+170, y-(120 + (Item*30)), x+570, y-(142 + (Item*30)),
							1, "", 0, SDK210TestsWidget,
							xpWidgetClass_TextField);

		XPSetWidgetProperty(SDK210TestsEdit[Item], xpProperty_TextFieldType, xpTextEntryField);
	}

	XPAddWidgetCallback(SDK210TestsWidget, SDK210TestsHandler);
	XPSetWidgetProperty(SDK210TestsButton1, xpProperty_Enabled, 1);
	XPSetWidgetProperty(SDK210TestsButton2, xpProperty_Enabled, 0);
	XPSetWidgetProperty(SDK210TestsButton3, xpProperty_Enabled, 0);
	XPSetWidgetProperty(SDK210TestsButton5, xpProperty_Enabled, 1);
	XPSetWidgetProperty(SDK210TestsButton6, xpProperty_Enabled, 0);
	XPSetWidgetProperty(SDK210TestsButton7, xpProperty_Enabled, 1);
	XPSetWidgetProperty(SDK210TestsButton8, xpProperty_Enabled, 0);
}

//Handle the widget messages
int	SDK210TestsHandler(
						XPWidgetMessage			inMessage,
						XPWidgetID				inWidget,
						intptr_t				inParam1,
						intptr_t				inParam2)
{
	// When widget close cross is clicked we only hide the widget
	if (inMessage == xpMessage_CloseButtonPushed)
	{
		if (SDK210TestsMenuItem1 == 1)
		{
			XPDestroyWidget(SDK210TestsWidget, 1);
			SDK210TestsMenuItem1 = 0;
		}
		return 1;
	}

	// Process when a button on the widget is pressed
	if (inMessage == xpMsg_PushButtonPressed)
	{
		if (inParam1 == (intptr_t)SDK210TestsButton1)
		{
			SDK210TestsTempLoopCBCounter = 0;
			SDK210TestsCreateFLCB = 1;
			SDK210TestsDestroyFLCB = 0;
			XPSetWidgetProperty(SDK210TestsButton1, xpProperty_Enabled, 0);
			XPSetWidgetProperty(SDK210TestsButton2, xpProperty_Enabled, 1);
			XPSetWidgetProperty(SDK210TestsButton3, xpProperty_Enabled, 1);
			XPSetWidgetDescriptor(SDK210TestsEdit[INFO], "Click on [Schedule Temp FLCB]");
			return 1;
		}

		if (inParam1 == (intptr_t)SDK210TestsButton2)
		{
			XPLMScheduleFlightLoop(SDK210Tests_XPLMTempFlightLoopID, 1.0, true);
			XPSetWidgetProperty(SDK210TestsButton2, xpProperty_Enabled, 0);
			XPSetWidgetDescriptor(SDK210TestsEdit[INFO], "");
			return 1;
		}

		if (inParam1 == (intptr_t)SDK210TestsButton3)
		{
			SDK210TestsDestroyFLCB = 1;
			SDK210TestsCreateFLCB = 0;
			XPSetWidgetProperty(SDK210TestsButton3, xpProperty_Enabled, 0);
			XPSetWidgetProperty(SDK210TestsButton2, xpProperty_Enabled, 0);
			XPSetWidgetProperty(SDK210TestsButton1, xpProperty_Enabled, 1);
			XPSetWidgetDescriptor(SDK210TestsEdit[TEMP_FLCB], "");
			return 1;
		}

		if (inParam1 == (intptr_t)SDK210TestsButton4)
		{
			XPSetWidgetProperty(SDK210TestsButton4, xpProperty_Enabled, 0);
			XPLMDebugString("================================================================\n");
			XPLMDebugString("SDK210Tests: SDK210TestsHandler -  Native Paths Feature Enabled.\n");
			XPLMDebugString("----------------------------------------------------------------\n");
			XPLMEnableFeature("XPLM_USE_NATIVE_PATHS",1);
			SDK210TestsNativePaths();
			XPLMReleasePlanes();
			XPLMEnableFeature("XPLM_USE_NATIVE_PATHS",0);
			XPLMDebugString("================================================================\n");
			XPLMDebugString("SDK210Tests: SDK210TestsHandler -  Native Paths Feature Disabled.\n");
			XPLMDebugString("----------------------------------------------------------------\n");
			SDK210TestsNativePaths();
			XPLMReleasePlanes();
			XPLMDebugString("================================================================\n");
			XPSetWidgetProperty(SDK210TestsButton4, xpProperty_Enabled, 1);
			return 1;
		}
		
		if (inParam1 == (intptr_t)SDK210TestsButton5)
		{
			SDK210TestsMenuId2 = XPLMCreateMenu("Test Menu 1", SDK210TestsMenuId, SDK210TestsMenuItem2, SDK210TestsMenuHandler2, NULL);
			SDK210TestsMenuIndex1 = XPLMAppendMenuItem(SDK210TestsMenuId2, "Test Menu Item 1", (void *)"1", 1);
			SDK210TestsMenuIndex2 = XPLMAppendMenuItem(SDK210TestsMenuId2, "Test Menu Item 2", (void *)"2", 1);
			SDK210TestsMenuIndex3 = XPLMAppendMenuItem(SDK210TestsMenuId2, "Test Menu Item 3", (void *)"3", 1);
			XPSetWidgetProperty(SDK210TestsButton5, xpProperty_Enabled, 0);
			XPSetWidgetProperty(SDK210TestsButton6, xpProperty_Enabled, 1);
			return 1;
		}

		if (inParam1 == (intptr_t)SDK210TestsButton6)
		{
			XPLMRemoveMenuItem(SDK210TestsMenuId2, SDK210TestsMenuIndex3);
			XPLMRemoveMenuItem(SDK210TestsMenuId2, SDK210TestsMenuIndex2);
			XPLMRemoveMenuItem(SDK210TestsMenuId2, SDK210TestsMenuIndex1);
			XPLMDestroyMenu(SDK210TestsMenuId2);
			XPSetWidgetProperty(SDK210TestsButton5, xpProperty_Enabled, 1);
			XPSetWidgetProperty(SDK210TestsButton6, xpProperty_Enabled, 0);
			XPSetWidgetDescriptor(SDK210TestsEdit[MENU_2], "");
			return 1;
		}

		if (inParam1 == (intptr_t)SDK210TestsButton7)
		{
			SDK210TestsDrawingEnabled = 1;
			XPSetWidgetProperty(SDK210TestsButton7, xpProperty_Enabled, 0);
			XPSetWidgetProperty(SDK210TestsButton8, xpProperty_Enabled, 1);
			return 1;
		}

		if (inParam1 == (intptr_t)SDK210TestsButton8)
		{
			SDK210TestsDrawingEnabled = 0;
			XPSetWidgetDescriptor(SDK210TestsEdit[DRAWING], "");
			XPSetWidgetProperty(SDK210TestsButton7, xpProperty_Enabled, 1);
			XPSetWidgetProperty(SDK210TestsButton8, xpProperty_Enabled, 0);
			return 1;
		}
	
	}
	return 0;
}						

//---------------------------------------------------------------------------

// Function for Draw Object tests
void SDK210TestsGotWindsock(XPLMObjectRef obj, void * ref)
{
	XPLMDebugString("================================================================\n");
	XPLMDebugString("SDK210Tests: - SDK210TestsGotWindsock Callback called.\n");
	XPLMDebugString("----------------------------------------------------------------\n");
	SDK210Tests_Windsock = obj;
}

void SDK210TestsLoadWindsock(const char * fname, void * ref)
{
	XPLMDebugString("================================================================\n");
	XPLMDebugString("SDK210Tests: - SDK210TestsLoadWindsock : Before XPLMLoadObjectAsync Call.\n");
	XPLMLoadObjectAsync(fname, SDK210TestsGotWindsock, NULL);
	XPLMDebugString("SDK210Tests: - SDK210TestsLoadWindsock : After XPLMLoadObjectAsync Call.\n");
	XPLMDebugString("----------------------------------------------------------------\n");
}

int	SDK210TestsDrawWindsock(
                                   XPLMDrawingPhase     inPhase,    
                                   int                  inIsBefore,    
                                   void *               inRefcon)
{
	static bool LookedForWindsock = false;
	if (SDK210TestsDrawingEnabled)
	{
		if (SDK210Tests_Windsock == NULL && !LookedForWindsock)
		{
			XPLMLookupObjects("lib/airport/landscape/windsock.obj", 0, 0, SDK210TestsLoadWindsock, NULL);
			LookedForWindsock = true;
		}
		if (SDK210Tests_Windsock && !SDK210Tests_Windsock_Probe)
			SDK210Tests_Windsock_Probe = XPLMCreateProbe(xplm_ProbeY);
			
		if (SDK210Tests_Windsock && SDK210Tests_refx && SDK210Tests_refy && SDK210Tests_refz && SDK210Tests_Windsock_Probe)
		{
			XPLMProbeInfo_t info;
			info.structSize = sizeof(info);

			XPLMProbeResult result = XPLMProbeTerrainXYZ(
											SDK210Tests_Windsock_Probe,
											XPLMGetDataf(SDK210Tests_refx),
											XPLMGetDataf(SDK210Tests_refy),
											XPLMGetDataf(SDK210Tests_refz),
											&info);
			if(result == xplm_ProbeHitTerrain)
			{
				XPLMDrawInfo_t	DrawInfo_t = { 0 };
				DrawInfo_t.structSize = sizeof(DrawInfo_t);
				DrawInfo_t.x = info.locationX;
				DrawInfo_t.y = info.locationY;
				DrawInfo_t.z = info.locationZ;
				if(info.is_wet)DrawInfo_t.pitch += 20.0;
				if (XPLMGetDatai(SDK210Tests_wrl_type)) 
					DrawInfo_t.heading += 30.0;
				XPLMDrawObjects(SDK210Tests_Windsock, 1, &DrawInfo_t, 0, 1);
				if (SDK210TestsMenuItem1 == 1)
				{
					sprintf(SDK210Tests_Buffer,"Drawing Enabled : X = %f, Y = %f, Z = %f\n", info.locationX, info.locationY, info.locationZ);
					XPSetWidgetDescriptor(SDK210TestsEdit[DRAWING], SDK210Tests_Buffer);
				}
			}
		}
	}
	return 1;
}

//---------------------------------------------------------------------------

void SDK210TestsNativePaths(void)
{
	char PluginPath[512], Name[256], FilePath[512], Signature[256], Description[256];
	char PrefsPath[512];
	XPLMPluginID PluginID = NULL;
	char NameBuffer[4096];
	char *Indices[4096];
	int ReturnFile;
	int TotalFile;
	int	ReturnValue;
	int	Offset = 0;

	#if IBM
		#define PLUGIN_ADMIN_NAME "win.xpl"
	#elif APL
		#define PLUGIN_ADMIN_NAME "mac.xpl"
	#elif LIN
		#define PLUGIN_ADMIN_NAME "lin.xpl"
	#else
		#error Platform not defined!
	#endif

	XPLMGetSystemPath(PluginPath);
	strcat(PluginPath, "Resources");
	strcat(PluginPath, XPLMGetDirectorySeparator());
	strcat(PluginPath, "plugins");
	strcat(PluginPath, XPLMGetDirectorySeparator());
	strcat(PluginPath, "PluginAdmin");
	strcat(PluginPath, XPLMGetDirectorySeparator());
	ReturnValue = XPLMGetDirectoryContents(PluginPath, Offset, NameBuffer, sizeof(NameBuffer), Indices, sizeof(Indices) / sizeof(char *), &TotalFile, &ReturnFile);
	sprintf(SDK210Tests_Buffer,"SDK210Tests: SDK210TestsNativePaths -  XPLMGetDirectoryContents - PluginPath = %s.\n", PluginPath);
	XPLMDebugString(SDK210Tests_Buffer);
	sprintf(SDK210Tests_Buffer,"SDK210Tests: SDK210TestsNativePaths -  XPLMGetDirectoryContents - TotalFile = %d.\n", TotalFile);
	XPLMDebugString(SDK210Tests_Buffer);
	strcat(PluginPath, PLUGIN_ADMIN_NAME);
	PluginID = XPLMFindPluginByPath(PluginPath);
	XPLMGetPluginInfo(PluginID, Name, FilePath, Signature, Description);
	sprintf(SDK210Tests_Buffer,"SDK210Tests: SDK210TestsNativePaths -  XPLMGetPluginInfo - Name = %s, FilePath = %s, Signature = %s, Description = %s.\n", Name, FilePath, Signature, Description);
	XPLMDebugString(SDK210Tests_Buffer);
	XPLMGetPrefsPath(PrefsPath);
	sprintf(SDK210Tests_Buffer,"SDK210Tests: SDK210TestsNativePaths - XPLMGetPrefsPath - PrefsPath = %s.\n", PrefsPath);
	XPLMDebugString(SDK210Tests_Buffer);

	strcpy(FilePath, "Output");
	strcat(FilePath, XPLMGetDirectorySeparator());
	strcat(FilePath, "situations");
	strcat(FilePath, XPLMGetDirectorySeparator());
	strcat(FilePath, "SDK210Test.sit");
	sprintf(SDK210Tests_Buffer,"SDK210Tests: SDK210TestsNativePaths - XPLMSaveDataFile - FilePath = %s.\n", FilePath);
	XPLMDebugString(SDK210Tests_Buffer);
	XPLMSaveDataFile(xplm_DataFile_Situation, FilePath);
	///XPLMLoadDataFile(xplm_DataFile_Situation, FilePath);

	strcpy(FilePath, "Output");
	strcat(FilePath, XPLMGetDirectorySeparator());
	strcat(FilePath, "replays");
	strcat(FilePath, XPLMGetDirectorySeparator());
	strcat(FilePath, "SDK210Test.rep");
	sprintf(SDK210Tests_Buffer,"SDK210Tests: SDK210TestsNativePaths -  XPLMSaveDataFile - FilePath = %s.\n", FilePath);
	XPLMDebugString(SDK210Tests_Buffer);
	XPLMSaveDataFile(xplm_DataFile_ReplayMovie, FilePath);
	///XPLMLoadDataFile(xplm_DataFile_ReplayMovie, FilePath); 

	SDK210TestsLoadAircraft(USER_AIRCRAFT);
	SDK210TestsAcquireAircraft();
}

//---------------------------------------------------------------------------

void SDK210TestsAcquireAircraft(void)
{
	int	PlaneCount;
	int Index;
	char FileName[256], AircraftPath[256];

	XPLMCountAircraft(&PlaneCount, 0, 0);
	if (PlaneCount > 1)
	{
		for (Index = 1; Index < PlaneCount; Index++)
		{
			XPLMGetNthAircraftModel(Index, FileName, AircraftPath);   
			strcpy(SDK210TestsAircraftPath[Index-1], AircraftPath);
			pSDK210TestsAircraft[Index-1] = (char *)SDK210TestsAircraftPath[Index-1];
		}
		if (XPLMAcquirePlanes((char **)&pSDK210TestsAircraft, NULL, NULL))
		{
			XPLMDebugString("SDK210Tests: SDK210TestsAcquireAircraft - Aircraft Acquired successfully\n");
			SDK210TestsLoadAircraft(AI_AIRCRAFT);
		}
		else
		{
			XPLMDebugString("SDK210Tests: SDK210TestsAcquireAircraft - Aircraft not Acquired\n");
		}
	}
}

//---------------------------------------------------------------------------

void SDK210TestsLoadAircraft(int AircraftType)
{
	char AircraftPath[512];

	XPLMGetSystemPath(AircraftPath);
	///strcat(AircraftPath, XPLMGetDirectorySeparator());
	strcat(AircraftPath, "Aircraft");
	strcat(AircraftPath, XPLMGetDirectorySeparator());
	strcat(AircraftPath, "General Aviation");
	strcat(AircraftPath, XPLMGetDirectorySeparator());
	strcat(AircraftPath, "Cirrus TheJet");
	strcat(AircraftPath, XPLMGetDirectorySeparator());
	strcat(AircraftPath, "c4.acf");
	sprintf(SDK210Tests_Buffer,"SDK210Tests: SDK210TestsLoadAircraft -  AircraftPath = %s.\n", AircraftPath);
	XPLMDebugString(SDK210Tests_Buffer);

	if (AircraftType == USER_AIRCRAFT)
		XPLMSetUsersAircraft(AircraftPath);
	if (AircraftType == AI_AIRCRAFT)
		XPLMSetAircraftModel(1, AircraftPath);
}

//---------------------------------------------------------------------------
