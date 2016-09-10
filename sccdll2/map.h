#ifndef __MAP_H
#define __MAP_H

#include "player.h"
#include "location.h"

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

		MAP_LOCATION location[MAX_LOCATIONS];
		PLAYER player[MAX_PLAYER];
		MAP();
		~MAP();
};

#endif