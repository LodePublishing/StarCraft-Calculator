#ifndef __HARVEST_H
#define __HARVEST_H

#include "main.h"
class SCCDLL_API HARVEST_SPEED
{
	private:
		int minerals[45];
		int gas[5];
	public:
		int getHarvestMineralSpeed(int num);
		int getHarvestGasSpeed(int num);
		int setHarvestMineralSpeed(int num,int speed);
		int setHarvestGasSpeed(int num,int speed);

		HARVEST_SPEED();
};

#endif