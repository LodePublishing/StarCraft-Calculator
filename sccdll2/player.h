#ifndef __PLAYER_H
#define __PLAYER_H

#include "main.h"
#include "goal.h"

class SCCDLL_API PLAYER
{
	private:
		int mins;
		int gas;
		int timer;
		int position;
		int race;
		int supply;
		int maxSupply;
        const int* basicMineralHarvestPerSecond;
        const int* basicGasHarvestPerSecond;
	public:
		GOAL_ENTRY* goal;
		int getMins();
		int getGas();
		int getTimer();
		int getPosition();
		int getRace();
		int getSupply();
		int getMaxSupply();
		int getBasicMineralHarvestPerSecond(int num);
		int getBasicGasHarvestPerSecond(int num);

		int setMins(int num);
		int setGas(int num);
		int setTimer(int num);
		int setPosition(int num);
		int setRace(int num);
		int setSupply(int num);
		int setMaxSupply(int num);
		int setBasicHarvestPerSecond(int* mining, int* gasing);
		int setGoal(GOAL_ENTRY* goal);
};


#endif