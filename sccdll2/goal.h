#ifndef __GOAL_H
#define __GOAL_H

#include "main.h"

class SCCDLL_API GOAL_ENTRY
{
	private:
		char name[128];
		int race;
		int raceInitialized;
	 	const UNIT_STATISTICS* pStats;

		int goalCount;
		int allGoal[UNIT_TYPE_COUNT];
		GOAL goal[MAX_GOALS];
		int isBuildable[UNIT_TYPE_COUNT];
        int isVariable[UNIT_TYPE_COUNT];
	public:
		const char* getName();
		int getRace();
		int isRaceInitialized();
		
		int setName(const char* line);
		int setRace(int num);

		int addGoal(int unit, int count, int time, int location);
	
		int adjustGoals();

		int isGoal(int unit);


		GOAL_ENTRY();
};

#endif