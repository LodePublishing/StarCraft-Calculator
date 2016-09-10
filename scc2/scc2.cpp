#include "C:\sc\sccdll2\settings.h"
#include "C:\sc\sccdll2\soup.h"
#include "io.h"
#include <stdio.h>
#include <time.h>

int main()
{
	SETTINGS settings;
	ANARACE* anarace;
	srand(time(NULL));
	printf("%i\n",settings.loadHarvestFile("mining.txt")); //mining als erstes immer!
	printf("%i\n",settings.loadSettingsFile("settings.txt"));
	printf("%i\n",settings.loadMapFile("map.txt"));
	printf("%i\n",settings.setCurrentMap(0));
	printf("%i\n",settings.loadGoalFile("goal.txt"));
	printf("%i\n",settings.setGoal(0,1));
	printf("%i\n",settings.setGoal(0,2));
	printf("%i\n",settings.initSoup()); //202
	IO io(settings.getGa());
	while(anarace=settings.newGeneration())
		io.screen(anarace);
	return(0);
}
//Ueberlegen Map etc. offen zu legen... mmmh... oder halt wirklich alle Funktionen uebernehmen...
//ma guggn