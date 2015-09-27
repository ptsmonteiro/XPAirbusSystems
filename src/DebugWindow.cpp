#include <sstream>
#include "DebugWindow.h"
#include "A320.h"

DebugWindow::DebugWindow()
{
	gWindow = XPLMCreateWindow(
		50, 600, 600, 340,
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
	if (Aircraft->updateCounter < 10) {
		return;
	}

	AdiruData adiruData;

	if (Aircraft->adiru1->currentHealth == Healthy) {
		adiruData = Aircraft->adiru1->getCurrentAdiruData();
		XPLMDrawString(color, left + 5, top - 20, formatString("ADIRU1.STAT_PRESSURE.HG		= ", adiruData.airData.staticPressureHg), NULL, xplmFont_Basic);
		XPLMDrawString(color, left + 5, top - 30, formatString("ADIRU1.HEIGHT.FT			= ", adiruData.airData.baroHeightFeet), NULL, xplmFont_Basic);
	}
	else {
		XPLMDrawString(color, left + 5, top - 20, "ADIRU1.STAT_PRESSURE.HG		= INOP", NULL, xplmFont_Basic);
		XPLMDrawString(color, left + 5, top - 30, "ADIRU1.HEIGHT.FT			= INOP", NULL, xplmFont_Basic);
	}

	if (Aircraft->adiru2->currentHealth == Healthy) {
		adiruData = Aircraft->adiru2->getCurrentAdiruData();
		XPLMDrawString(color, left + 5, top - 40, formatString("ADIRU2.STAT_PRESSURE.HG		= ", adiruData.airData.staticPressureHg), NULL, xplmFont_Basic);
		XPLMDrawString(color, left + 5, top - 50, formatString("ADIRU2.HEIGHT.FT			= ", adiruData.airData.baroHeightFeet), NULL, xplmFont_Basic);
	}
	else {
		XPLMDrawString(color, left + 5, top - 20, "ADIRU2.STAT_PRESSURE.HG		= INOP", NULL, xplmFont_Basic);
		XPLMDrawString(color, left + 5, top - 30, "ADIRU2.HEIGHT.FT			= INOP", NULL, xplmFont_Basic);
	}

	if (Aircraft->adiru3->currentHealth == Healthy) {
		adiruData = Aircraft->adiru3->getCurrentAdiruData();
		XPLMDrawString(color, left + 5, top - 60, formatString("ADIRU3.STAT_PRESSURE.HG		= ", adiruData.airData.staticPressureHg), NULL, xplmFont_Basic);
		XPLMDrawString(color, left + 5, top - 70, formatString("ADIRU3.HEIGHT.FT			= ", adiruData.airData.baroHeightFeet), NULL, xplmFont_Basic);
	}
	else {
		XPLMDrawString(color, left + 5, top - 20, "ADIRU3.STAT_PRESSURE.HG		= INOP", NULL, xplmFont_Basic);
		XPLMDrawString(color, left + 5, top - 30, "ADIRU3.HEIGHT.FT			= INOP", NULL, xplmFont_Basic);
	}
}

char* DebugWindow::formatString(const char* prefix, float value)
{
	std::stringstream sstm;
	sstm << prefix << value;

	return strdup(sstm.str().c_str());
}


char* DebugWindow::formatString(const char* prefix, int value)
{
	std::stringstream sstm;
	sstm << prefix << value;

	return strdup(sstm.str().c_str());
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
