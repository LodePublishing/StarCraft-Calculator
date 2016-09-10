#ifndef __GA_H
#define __GA_H

#include "main.h"

class SCCDLL_API GA
{
	public:
		int goalCount;
		int mapCount;
		int playerCount;
		int maxTime;
		int maxTimeOut;
		int maxLength;
		int maxRuns;
		int maxGenerations;
		int preprocessBuildOrder;
		int currentMap;
	GA();
};

#endif
