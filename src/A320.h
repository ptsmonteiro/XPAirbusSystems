#pragma once

#include "ATA22_ELAC.h"
#include "ATA31_DMC.h"
#include "ATA31_DU.h"
#include "ATA31_EWD.h"
#include "ATA31_FWC.h"
#include "ATA31_ND.h"
#include "ATA31_PFD.h"
#include "ATA31_SD.h"
#include "ATA31_SDAC.h"
#include "ATA32_LGCIU.h"
#include "ATA34_ADIRU.h"
#include "ATA34_RadioAlt.h"

class A320
{
public:
	A320();
	~A320();

	void update();

protected:
	ATA22_ELAC * elac1;
	ATA22_ELAC * elac2;

	ATA32_LGCIU * lgciu1;
	ATA32_LGCIU * lgciu2;

	ATA31_DU * du1;
	ATA31_DU * du2;
	ATA31_DU * du3;
	ATA31_DU * du4;
	ATA31_DU * du5;
	ATA31_DU * du6;

	ATA34_RadioAlt * ra1;
	ATA34_RadioAlt * ra2;

	ATA31_FWC * fwc1;
	ATA31_FWC * fwc2;

};
