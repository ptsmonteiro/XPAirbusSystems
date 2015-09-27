#include "DebugWindow.h"
#include "A320.h"

DebugWindow::DebugWindow()
{
	gWindow = XPLMCreateWindow(
		50, 600, 300, 200,	
		1,					
		DebugWindow::WindowRenderCallback,	
		DebugWindow::WindowKeyCallback,
		DebugWindow::WindowClickCallback,
		NULL);	
}

void DebugWindow::WindowRenderCallback(
	XPLMWindowID         inWindowID,
	void *               inRefcon)
{
	int		left, top, right, bottom;
	float	color[] = { 1.0, 1.0, 1.0 }; 	/* RGB White */

											/* First we get the location of the window passed in to us. */
	XPLMGetWindowGeometry(inWindowID, &left, &top, &right, &bottom);

	/* We now use an XPLMGraphics routine to draw a translucent dark
	* rectangle that is our window's shape. */
	XPLMDrawTranslucentDarkBox(left, top, right, bottom);

	// This prevents access to aircraft data before any updates.
	if (Aircraft->updateCounter < 0) {
		return;
	}

	// Adiru Debug
	AdiruData adiruData = Aircraft->adiru1->getCurrentAdiruData();
	XPLMDrawString(color, left + 5, top - 20, (char*) ("ADIRU1.HEIGHT.FT = " + adiruData.airData.baroHeightFeet), NULL, xplmFont_Basic);

	adiruData = Aircraft->adiru2->getCurrentAdiruData();
	XPLMDrawString(color, left + 5, top - 20, (char*) ("ADIRU2.HEIGHT.FT = " + adiruData.airData.baroHeightFeet), NULL, xplmFont_Basic);

	adiruData = Aircraft->adiru3->getCurrentAdiruData();
	XPLMDrawString(color, left + 5, top - 20, (char*) ("ADIRU3.HEIGHT.FT = " + adiruData.airData.baroHeightFeet), NULL, xplmFont_Basic);

}

int DebugWindow::WindowClickCallback(
	XPLMWindowID         inWindowID,
	int                  x,
	int                  y,
	XPLMMouseStatus      inMouse,
	void *               inRefcon)
{
	return 1;
}

void DebugWindow::WindowKeyCallback(
	XPLMWindowID         inWindowID,
	char                 inKey,
	XPLMKeyFlags         inFlags,
	char                 inVirtualKey,
	void *               inRefcon,
	int                  losingFocus)
{
}

DebugWindow::~DebugWindow()
{
}
