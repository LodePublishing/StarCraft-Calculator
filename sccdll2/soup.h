#ifndef __SOUP_H
#define __SOUP_H

#include "settings.h"
//#include "statistics.h"
#include "race.h"
#include "anarace.h"

class SCCDLL_API SOUP
{
	private:
		RACE* player[MAX_PROGRAMS];
		int run_number;
	public:
		SOUP::SOUP(MAP* map,GOAL_ENTRY* goal, ...);
		~SOUP();
		ANARACE* anaplayer;
		
//		ANARACE* newGeneration(); //one generation, copies stats and results of best individual and average values of the soup in 'best'
		//STATISTICS* statistics[RUNNINGS]; //list of result of all best of all runs
};

#endif