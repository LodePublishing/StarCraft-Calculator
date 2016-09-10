#include "baserace.h"

BASERACE::BASERACE()
{
	maxTime=0;
	maxTimeOut=0;
	maxLength=0;
	maxRuns=0;
	maxGenerations=0;
	preprocessBuildOrder=0;
	currentMap=0;
	mapCount=0;
	pMap=0;
}

int BASERACE::maxTime;
int BASERACE::maxTimeOut;
int BASERACE::maxLength;
int BASERACE::maxRuns;
int BASERACE::maxGenerations;
int BASERACE::preprocessBuildOrder;
int BASERACE::currentMap;
int BASERACE::mapCount;
MAP* BASERACE::pMap;
