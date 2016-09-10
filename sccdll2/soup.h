#ifndef __SOUP_H
#define __SOUP_H

#include "anarace.h"
#include "race.h"
#include "goal.h"
#include "map.h"
#include "ga.h"

class SCCDLL_API SOUP
{
	private:
		RACE* player[MAX_PROGRAMS];
		MAP* pMap;
		int run_number,goalsInitialized,playerInitialized,mapInitialized,goalCount,gaInitialized;
		GOAL_ENTRY* goal[MAX_PLAYER];
		GA* ga;
		MAP_LOCATION_BASIC location[MAX_LOCATIONS];
	public:
		int setGoal(GOAL_ENTRY* goal, int player);
		int setMap(MAP* map);
		int setParameters(GA* ga);

		//ERROR doFullCheckAndInitAllTheStuff();

		//Problem Changes on the fly <> full check
		// evtl ne 'running' oder 'changed' (in settings) Variable einfuehren, die dann bei jeder Aenderung eine volle Pruefung macht...
		// mmh

		int initSoup();

		SOUP();
		~SOUP();
		ANARACE* anaplayer[MAX_PLAYER];
		ANARACE* newGeneration(); //one generation, copies stats and results of best individual and average values of the soup in 'best'
};

#endif