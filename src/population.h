#ifndef __POPULATION__H__
#define __POPULATION__H__
#include "genetic.h"
#include "race.h"
#include "main.h"

class POPULATION
{
	public:
		void sortAndSelect();
		RACE * player[MAX_PLAYER];
		POPULATION();
		~POPULATION();
};
#endif
