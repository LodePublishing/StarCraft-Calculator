#ifndef __GOAL_H
#define __GOAL_H

#include "main.h"

#define MAX_GOAL_ENTRIES 25

class SCCDLL_API GOAL_ENTRY
{
	private:
		char name[128];
		int race;
		int raceInitialized;
		int maxBuildTypes;
	 	const UNIT_STATISTICS* pStats;

		int goalCount;
		int allGoal[UNIT_TYPE_COUNT];
	public:
		int isBuildable[UNIT_TYPE_COUNT];
        int isVariable[UNIT_TYPE_COUNT];
        int phaenoToGenotype[UNIT_TYPE_COUNT];
		int genoToPhaenotype[UNIT_TYPE_COUNT];
		GOAL goal[MAX_GOALS];

		const char* getName();
		int getRace();
		int getMaxBuildTypes();
		const UNIT_STATISTICS* getpStats();
		int isRaceInitialized();
		
		int setName(const char* line);
		int setRace(int num);

		int addGoal(int unit, int count, int time, int location);
	
		int adjustGoals();

		int isGoal(int unit);


		GOAL_ENTRY();
};

#endif