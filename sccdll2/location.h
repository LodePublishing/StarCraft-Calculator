#ifndef __LOCATION_H
#define __LOCATION_H

#include "main.h"

#define MAX_LOCATIONS 10
#define MAX_PLAYER 4


class SCCDLL_API MAP_LOCATION_BASIC
{
	private:
		char name[32];
		int mineralCount,mineralDistance,geysirCount;
		int distance[MAX_LOCATIONS]; //~~~

	//	int isCliff; //only reachable per dropship
	//	int canShootbetweenwhichconnection... (cliffdrop oder so...)
	public:
		int setName(const char* line);
		int setMineralCount(int num);
		int setMineralDistance(int num);
		int setGeysirCount(int num);
		int setDistance(int num,int dist);

		const char* getName();
		int getMineralCount();
		int getMineralDistance();
		int getGeysirCount();

		int getDistance(int num);
		int force[MAX_PLAYER][UNIT_TYPE_COUNT];
		MAP_LOCATION_BASIC();
};

class SCCDLL_API MAP_LOCATION
{
	private:
		int mineralCount,mineralDistance,geysirCount;
		int distance[MAX_LOCATIONS]; //~~~
	//	int isCliff; //only reachable per dropship
	//	int canShootbetweenwhichconnection... (cliffdrop oder so...)
	public:
		int setMineralCount(int num);
		int setMineralDistance(int num);
		int setGeysirCount(int num);
		int setDistance(int num,int dist);

		int availible[UNIT_TYPE_COUNT];
		int force[UNIT_TYPE_COUNT];

		int getMineralCount();
		int getMineralDistance();
		int getGeysirCount();
		int getDistance(int num);

		MAP_LOCATION();
};

#endif