#include <math.h>
#include "core\core.h"

//TODO: Move constants to proper file.

float Calculator::pressureAltitudeFt(float pressureInHg, float qnhInHg) {
	// http://williams.best.vwh.net/avform.htm#Altimetry
	// alt_set in inches, heights in feet => P_alt_corr = 145442.2*(1 - (alt_set / 29.92126) ^ 0.190261)
	
	return 145442.2*(1 - pow((pressureInHg / qnhInHg), 0.190261));
}