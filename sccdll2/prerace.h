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
		int playerNum;
		static int run;
		int mins,gas,timer,IP;
        int mineralHarvestPerSecond[MAX_LOCATIONS][45];
        int gasHarvestPerSecond[MAX_LOCATIONS][5];
		int harvestedGas,harvestedMins;
		int supply,maxSupply;
		static MAP* pMap;
		static LAST last[MAX_LENGTH];
		static int lastcounter;
		static int lastwhat;
        int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...*/
        int length;
	public:
		const UNIT_STATISTICS* pStats;
		//Location ueberlegen...Andere Spieler interessieren eigentlich nur peripher bei Bewegungen und beim Sammeln! Also ein ganz normales Location wie bisher machen und ein location in denen Gegner/Alliierte mit drin sind
		MAP_LOCATION location[MAX_LOCATIONS];
        int Code[2][MAX_LENGTH];
		void harvestResources();
		static GA* ga;
		PLAYER* player;   //private? mmmh...
		int getPlayer();
		int loadPlayer(int num);
        int adjustMineralHarvest(int loc);
        int adjustGasHarvest(int loc);
		int setSupply(int num);
		int setMaxSupply(int num);
		int setMins(int num);
		int setGas(int num);
		int setTimer(int num);
		static int setMap(MAP* map);

			
		int getSupply();
		int getMaxSupply();
		int getMins();
		int getGas();
		int getTimer();
		static int getRun();
		PRERACE();
};

#endif // __PRERACE_H