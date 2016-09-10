#ifndef __PRERACE_H
#define __PRERACE_H

#include "main.h"
#include "map.h"
#include "player.h"
#include "ga.h"
#include "location.h"

class SCCDLL_API PRERACE
{
	protected:
		static MAP* pMap;
		static LAST last[MAX_LENGTH];
		static int lastcounter;
		static int lastwhat;
		static int mapInitialized;
		void harvestResources();
		const UNIT_STATISTICS* pStats;
	private:
		PLAYER* player;
		int playerNum;
		int mins,gas,timer,IP;
        int mineralHarvestPerSecond[MAX_LOCATIONS][45];
        int gasHarvestPerSecond[MAX_LOCATIONS][5];
		int harvestedGas,harvestedMins;
		int supply;		// free supply
		int maxSupply; // total supply
        int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...*/
        int length;
	public:
        int Code[2][MAX_LENGTH];
		int setpStats(const UNIT_STATISTICS* pStats);
		//Location ueberlegen...Andere Spieler interessieren eigentlich nur peripher bei Bewegungen und beim Sammeln! Also ein ganz normales Location wie bisher machen und ein location in denen Gegner/Alliierte mit drin sind
		MAP_LOCATION location[MAX_LOCATIONS];

		static MAP* getMap();
		
		static GA* ga;
		int getPlayerNum();
		int setPlayerNum(int num);

		int setPlayer(PLAYER* player);
		PLAYER* getPlayer();

		int loadPlayer(int num);
        int adjustMineralHarvest(int loc);
        int adjustGasHarvest(int loc);
		int setSupply(int num);
		int setMaxSupply(int num);
		int setMins(int num);
		int setGas(int num);
		int setTimer(int num);
		int resetLocations();
		static int setMap(MAP* map);
		static void resetMapInitialized();

		int getIP();
		int setIP(int num);

		int setMineralHarvestPerSecond(int loc,int worker,int num);
		int getMineralHarvestPerSecond(int loc,int worker);

		int setGasHarvestPerSecond(int loc,int worker,int num);
		int getGasHarvestPerSecond(int loc,int worker);

		int getHarvestedMins();
		int getHarvestedGas();

		int setHarvestedMins(int num);
		int setHarvestedGas(int num);

		int setFinalTime(int goal, int num);
		int getFinalTime(int goal);

		int getLength();
		int setLength(int num);
		
		int getSupply();
		int getMaxSupply();
		int getMins();
		int getGas();
		int getTimer();
		PRERACE();
};

#endif // __PRERACE_H