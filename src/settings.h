#ifndef __SETTINGS_H
#define __SETTINGS_H

#include "main.h"
	
#define DATA_SET_SIZE 8
#define SETTINGSFILE "settings.txt"
#define GOALFILE "goal.txt"

struct MAP
{
	int mineralCount,geysirCount;
//	int isCliff; //only reachable per dropship
//	int canShootbetweenwhichconnection... (cliffdrop oder so...)
	int distance[MAX_LOCATIONS]; //~~~
	char name[64];
};
//Je nach Map verteilen...  Mit Dire Straits mal anfangen...

struct MISC
{
	int mins,gas,timer;
	int supply,maxSupply;
	const int* pGasHarvestPerSecond;
	const int* pMineralHarvestPerSecond;
};

struct GA
{
	int maxTime,maxTimeOut,maxLength,maxRuns;
	int generateBuildOrder;
	int maxGenerations;
};

class GOALLIST
{
	public:
	GOAL goal[MAX_GOALS];
        int maxBuildTypes;
        int goalCount;
	int allGoal[UNIT_TYPE_COUNT]; //former goal...
        int globalGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT]; //?
	int isBuildable[UNIT_TYPE_COUNT];
	int isVariable[UNIT_TYPE_COUNT];
	void addGoal(int unit, int count, int time, int location);
	GOALLIST();

//	void reset();
};

class SETTINGS
{
	public:
//minerals, vespene geysirs and distances to other locations
		MAP map[MAX_LOCATIONS];
//start situation of the game (in most cases just a main builsing and 4 workers)
		LOCATION location[MAX_LOCATIONS];
// generateBasicBuildorder, MaxTime, MaxGenerations, maxRuns, 
		GA ga;
// basic non?preprocessed goals from user/elsewhere
		GOALLIST goalList;
// miscellaneous data
		MISC misc;
// gegen comp testen, mit anderen bos vergleichen, bo-datenbank 

	int init();
	void initLocations();
	int race;//~~

	void initMap(); 
	const UNIT_STATISTICS* pStats;
	SETTINGS();
	~SETTINGS();
	void initHarvest();
	void setRace(int race);
	void toBuffer(char* buffer);
	void fromBuffer(char* buffer);
	int loadGoals();
};
#endif
