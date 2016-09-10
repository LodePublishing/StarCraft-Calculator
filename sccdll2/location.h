#ifndef __LOCATION_H
#define __LOCATION_H

#include "main.h"

#define MAX_LOCATIONS 9
#define MAX_PLAYER 2


class SCCDLL_API MAP_LOCATION
{
	private:
		char name[32];
		int mineralCount,mineralDistance,geysirCount;
	//	int isCliff; //only reachable per dropship
	//	int canShootbetweenwhichconnection... (cliffdrop oder so...)
	public:
		int setName(const char* line);
		int setMineralCount(int num);
		int setMineralDistance(int num);
		int setGeysirCount(int num);

		const char* getName();
		int getMineralCount();
		int getMineralDistance();
		int getGeysirCount();
		
		int distance[MAX_LOCATIONS]; //~~~
		int force[MAX_PLAYER][UNIT_TYPE_COUNT];
		MAP_LOCATION();
};

#endif