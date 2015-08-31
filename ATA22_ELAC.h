#pragma once
class ATA22_ELAC
{
public:
	ATA22_ELAC();
	~ATA22_ELAC();

	float getAileronPos();
	float getElevatorPos();

	float getRollOrder();
	float getYawRateOrder();


protected:
	ATA34_ADIRU *getADIRU();

	void getFMGC();
	void getAccelero();
	void getLGCIU();
	void getRadioAlt();

	float getSideStickX();
	float getSideStickY();
	float getPedalsPos();
};

