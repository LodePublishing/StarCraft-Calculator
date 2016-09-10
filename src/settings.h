#ifndef SETTINGS_H
#define SETTINGS_H

#include "main.h"
#include <stdio.h>

#define DATA_SET_SIZE 8


class Settings
{
	public:
	Settings();
	~Settings();
	void toBuffer(char* buffer);
	void fromBuffer(char* buffer);
	//Output Switches 0/1
	int Detailed_Output,Console24Lines,Gizmo,generateBuildOrder;
	//Map Data
	int Mineral_Mod;
	int Verbose;
	//Internal Options
	int Max_Time,Max_Generations;
	int Init();
	void Fatal(char * strn);
	int race;
	int colors;
	int max_runs;
	MAP map[MAX_LOCATIONS];
	UNIT_STATISTICS* stats;
};

#endif
