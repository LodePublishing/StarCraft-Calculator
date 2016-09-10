#ifndef __SETTINGS_H
#define __SETTINGS_H

#include "soup.h"
#include "main.h"
#include "goal.h"	
#include "harvest.h"
#include "map.h"
#include "ga.h"
//Vorgehen:
// - Lade Settings, Maps, Goals aus Files
// - User waehlt Map und Goal je Spieler

class SCCDLL_API SETTINGS
{
	private:
		GOAL_ENTRY goalEntry[MAX_GOAL_ENTRIES];
		MAP map[MAX_MAPS];
		HARVEST_SPEED harvestSpeed[3];
		GA ga;
		SOUP soup;
		int setMapCount(int num);
		int setGoalCount(int num);
	public:
		int setMaxTime(int num); //sets max Time in minutes
		int setMaxTimeOut(int num);
		int setMaxLength(int num);
		int setMaxRuns(int num);
		int setMaxGenerations(int num);
		int setPlayerCount(int num);
		int setPreprocessBuildOrder(int num);
		int setCurrentMap(int num);

		int setGoal(int goal, int player);


//		int setHarvestSpeed(); //~~ maybe allow multiple harvest speeds later on

		int getMaxTime();
		int getMaxTimeOut();
		int getMaxLength();
		int getMaxRuns();
		int getMaxGenerations();
		int getPreprocessBuildOrder();
		int getCurrentMap();

		int getHarvestMineralsSpeed(int r,int n);
		int getHarvestGasSpeed(int r,int n);
		int getDistance(int l1,int l2);

		int getGoalCount();
		int getPlayerCount();
		int getMapCount();
		int getGoal(GOAL_ENTRY &goal,int num);

		int loadGoalFile(const char* goalFile);
		int loadSettingsFile(const char* settingsFile);
		int loadMapFile(const char* mapFile);
		int loadHarvestFile(const char* harvestFile);

		int newGeneration();

		int initSoup();

		void toLog(const char* msg, ...);
		SETTINGS();
};
#endif
