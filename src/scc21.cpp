#include "settings.h"
#include "soup.h"
#include "race.h"
#include <time.h>
#include <stdlib.h>
#include "main.h"

int RACE::genoToPhaenotype[UNIT_TYPE_COUNT];
int RACE::phaenoToGenotype[UNIT_TYPE_COUNT];
int RACE::isBuildable[UNIT_TYPE_COUNT];
int RACE::isVariable[UNIT_TYPE_COUNT];
int RACE::basicBuildOrder[2][MAX_LENGTH];
int RACE::basicLength;
const UNIT_STATISTICS* RACE::pStats;
int RACE::initialized;
int RACE::maxBuildTypes;
const int* RACE::basicMineralHarvestPerSecond;
const int* RACE::basicGasHarvestPerSecond;

int main(int argc[], int argv[])
{
	srand(time(NULL));
	SETTINGS* set=new SETTINGS();
	SOUP* soup=new SOUP(set);
/*while(!soup.complete)
{
	soup.run(); //make a run and put the best one in statistics
	io.print(soup.statistics,RUN);		
}
soup.make_additional_statistics();
io.print(soup.statistics,FINAL); // file/screen
io.save(soup.statistics);*/
	delete soup;
	delete set;
	return(0);
}


