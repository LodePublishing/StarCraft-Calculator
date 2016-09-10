#ifndef __BASERACE_H
#define __BASERACE_H

#include "map.h"

class SCCDLL_API BASERACE
{
	public:
		static int maxTime;
		static int maxTimeOut;
		static int maxLength;
		static int maxRuns;
		static int maxGenerations;
		static int preprocessBuildOrder;
		static int currentMap;
		static int mapCount;
		static MAP* pMap;
		BASERACE();
};

#endif