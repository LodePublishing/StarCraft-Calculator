#include "e:\scc\sccdll2\settings.h"
#include "e:\scc\sccdll2\soup.h"
#include "io.h"
#include <stdio.h>

int main(int argc[], int argv[])
{
	SETTINGS settings;
	settings.loadSettingsFile("settings.txt");
	settings.loadMapFile("map.txt");
//	settings.loadGoalFile("goal.txt");
	settings.loadHarvestFile("mining.txt");
	printf("%i\n",settings.getMaxGenerations());
//	printf("%i\n",settings.getHarvestMineralsSpeed(0,15));
	return(0);
}