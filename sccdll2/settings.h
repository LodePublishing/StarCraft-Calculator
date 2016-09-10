#ifndef __SETTINGS_H
#define __SETTINGS_H

#include "main.h"
#include "baserace.h"
#include "goal.h"	
#include "harvest.h"

//Vorgehen:
// - Lade Settings, Maps, Goals aus Files
// - User waehlt Map und Goal je Spieler

class SCCDLL_API SETTINGS
{
	private:
		BASERACE base; //ok
		GOAL_ENTRY goalEntry[25];
		MAP map[25];
		HARVEST_SPEED harvestSpeed[3];

		int goalCount;
		int mapCount;
		int playerCount;
	public:
		int setMaxTime(int num); //sets max Time in minutes
		int setMaxTimeOut(int num);
		int setMaxLength(int num);
		int setMaxRuns(int num);
		int setMaxGenerations(int num);
		int setPlayerCount(int num);
		int setPreprocessBuildOrder(int num);
		int setCurrentMap(int num);


		int getMaxTime();
		int getMaxTimeOut();
		int getMaxLength();
		int getMaxRuns();
		int getMaxGenerations();
		int getPreprocessBuildOrder();
		int getCurrentMap();
		int getHarvestMineralsSpeed(int r,int n);
		int getHarvestGasSpeed(int r,int n);

		int getCurrentGoal();
		int getGoalCount();
		int getPlayerCount();
		GOAL_ENTRY getGoal(int num);

		int loadGoalFile(const char* goalFile);
		int loadSettingsFile(const char* settingsFile);
		int loadMapFile(const char* mapFile);
		int loadHarvestFile(const char* harvestFile);

		void toLog(const char* msg, ...);
		SETTINGS();
};
#endif
