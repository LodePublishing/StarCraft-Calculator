#include "settings.h"
#include "soup.h"
#include "race.h"
#include <time.h>
#include <stdlib.h>
#include "main.h"
#include "anarace.h"

int RACE::genoToPhaenotype[UNIT_TYPE_COUNT];
int RACE::phaenoToGenotype[UNIT_TYPE_COUNT];
int RACE::isBuildable[UNIT_TYPE_COUNT];
int RACE::isVariable[UNIT_TYPE_COUNT];
int RACE::basicBuildOrder[2][MAX_LENGTH];
int RACE::basicLength;
const UNIT_STATISTICS* RACE::pStats;
const SETTINGS* RACE::pSet;
int RACE::initialized;
int RACE::maxBuildTypes;
const int* RACE::basicMineralHarvestPerSecond;
const int* RACE::basicGasHarvestPerSecond;
const MAP* RACE::map;
GOAL RACE::goal[MAX_GOALS];

int ANARACE::genoToPhaenotype[UNIT_TYPE_COUNT];
int ANARACE::phaenoToGenotype[UNIT_TYPE_COUNT];
int ANARACE::isBuildable[UNIT_TYPE_COUNT];
int ANARACE::isVariable[UNIT_TYPE_COUNT];
int ANARACE::basicBuildOrder[2][MAX_LENGTH];
int ANARACE::basicLength;
const UNIT_STATISTICS* ANARACE::pStats;
const SETTINGS* ANARACE::pSet;
int ANARACE::initialized;
int ANARACE::maxBuildTypes;
const int* ANARACE::basicMineralHarvestPerSecond;
const int* ANARACE::basicGasHarvestPerSecond;
const MAP* ANARACE::map;
GOAL ANARACE::goal[MAX_GOALS];


int main(int argc[], int argv[])
{
	srand(time(NULL));
	SETTINGS* set=new SETTINGS();
	RACE::pSet=set;
	ANARACE::pSet=set;
	SOUP* soup=new SOUP(set);
	soup->run();
/*while(!soup->complete)
{
	soup->run(); //make a run and put the best one in statistics
	io.print(soup->statistics,RUN);		
}
soup.make_additional_statistics();
io.print(soup.statistics,FINAL); // file/screen
io.save(soup.statistics);*/
	delete soup;
	delete set;
	return(0);
}


