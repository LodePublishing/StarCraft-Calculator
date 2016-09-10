#ifndef __MAP_H
#define __MAP_H

#include "player.h"
#include "location.h"

#define MAX_MAPS 25

class SCCDLL_API MAP
{
	private:
		char* name;
		int maxLocations;//¬¬
		int maxPlayer;
	public:
		const char* getName();
		int getMaxLocations();
		int getMaxPlayer();

		int setName(const char* line);
		int setMaxLocations(int num);
		int setMaxPlayer(int num);

		int adjustDistanceList();
		int adjustSupply(); //evtl fuer jeden player einzeln :-o

		int locationList[MAX_LOCATIONS][MAX_LOCATIONS];			
		MAP_LOCATION_BASIC location[MAX_LOCATIONS];
		PLAYER player[MAX_PLAYER];
		MAP();
		~MAP();
};

#endif