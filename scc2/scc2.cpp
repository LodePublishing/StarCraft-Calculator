#include "C:\sc\sccdll2\settings.h"
#include "C:\sc\sccdll2\soup.h"
#include "io.h"
#include <stdio.h>

int main(int argc[], int argv[])
{
	SETTINGS settings;
	printf("%i\n",settings.loadSettingsFile("settings.txt"));
	printf("%i\n",settings.loadMapFile("map.txt"));
	printf("%i\n",settings.setCurrentMap(0));
	printf("%i\n",settings.loadGoalFile("goal.txt"));
	printf("%i\n",settings.loadHarvestFile("mining.txt"));
	printf("%i\n",settings.setGoal(0,0));
	printf("%i\n",settings.setGoal(0,1));
//player 1 goal wird nicht initialisiert!
	printf("%i\n",settings.initSoup());
	printf("%i\n",settings.newGeneration());

	return(0);
}
//Ueberlegen Map etc. offen zu legen... mmmh... oder halt wirklich alle Funktionen uebernehmen...
//ma guggn

