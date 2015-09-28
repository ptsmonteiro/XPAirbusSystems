#include <sstream>
#include "DebugWindow.h"
#include "A320.h"

static int left, top, right, bottom;
static float TEXT_COLOR[3] = { 1.0, 1.0, 1.0 };
static int currentLineOffset;

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
	
	

	/* First we get the location of the window passed in to us. */
	XPLMGetWindowGeometry(inWindowID, &left, &top, &right, &bottom);

	/* We now use an XPLMGraphics routine to draw a translucent dark
	* rectangle that is our window's shape. */
	XPLMDrawTranslucentDarkBox(left, top, right, bottom);

	// This prevents access to aircraft data before any updates.
	if (Aircraft->updateCounter < 10) {
		return;
	}

	currentLineOffset = top;

	AdiruData adiruData;

	if (Aircraft->adiru1->currentHealth == Healthy) {
		adiruData = Aircraft->adiru1->getCurrentAdiruData();
		appendLine(formatString("ADIRU1.STAT_PRESSURE.HG		= ", adiruData.airData.staticPressureHg));
		appendLine(formatString("ADIRU1.HEIGHT.FT			= ",	 adiruData.airData.baroHeightFeet));
		appendLine(formatString("ADIRU1.IAS.KN				= ", adiruData.airData.indicatedAirspeedKn));
	}
	else {
		appendLine("ADIRU1.STAT_PRESSURE.HG		= INOP");
		appendLine("ADIRU1.HEIGHT.FT			= INOP");
	}

	if (Aircraft->adiru2->currentHealth == Healthy) {
		adiruData = Aircraft->adiru2->getCurrentAdiruData();
		appendLine(formatString("ADIRU2.STAT_PRESSURE.HG		= ", adiruData.airData.staticPressureHg));
		appendLine(formatString("ADIRU2.HEIGHT.FT			= ", adiruData.airData.baroHeightFeet));
		appendLine(formatString("ADIRU2.IAS.KN				= ", adiruData.airData.indicatedAirspeedKn));
	}
	else {
		appendLine("ADIRU2.STAT_PRESSURE.HG		= INOP");
		appendLine("ADIRU2.HEIGHT.FT			= INOP");
	}

	if (Aircraft->adiru3->currentHealth == Healthy) {
		adiruData = Aircraft->adiru3->getCurrentAdiruData();
		appendLine(formatString("ADIRU3.STAT_PRESSURE.HG		= ", adiruData.airData.staticPressureHg));
		appendLine(formatString("ADIRU3.HEIGHT.FT			= ", adiruData.airData.baroHeightFeet));
		appendLine(formatString("ADIRU3.IAS.KN				= ", adiruData.airData.indicatedAirspeedKn));
	}
	else {
		appendLine("ADIRU3.STAT_PRESSURE.HG		= INOP");
		appendLine("ADIRU3.HEIGHT.FT			= INOP");
	}
}

void DebugWindow::appendLine(char* message)
{
	XPLMDrawString(TEXT_COLOR, left + 5, currentLineOffset, message, NULL, xplmFont_Basic);
	
	currentLineOffset += 10;
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
