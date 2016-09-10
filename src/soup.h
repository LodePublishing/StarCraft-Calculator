#ifndef __SOUP_H
#define __SOUP_H

#include "settings.h"
//#include "statistics.h"
#include "race.h"
#include "anarace.h"

class SOUP
{
	private:
		RACE p[MAX_PLAYER];
		RACE* player[MAX_PLAYER];
		int run_number;
	public:
		SOUP(SETTINGS* set);
		~SOUP();
		ANARACE anaplayer;
		
		void run(); //one generation, copies stats and results of best individual and average values of the soup in 'best'
		//STATISTICS* statistics[RUNNINGS]; //list of result of all best of all runs
		const SETTINGS* settings;
};
#endif
