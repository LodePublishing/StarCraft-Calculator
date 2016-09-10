#ifndef SETTINGS_H
#define SETTINGS_H

#include "main.h"
#include <stdio.h>

#define DATA_SET_SIZE 16


class Settings
{
	public:
	Settings();
	~Settings();
	//Output Switches 0/1
	unsigned short Detailed_Output,Console24Lines,Gizmo,generateBuildOrder;
	//Map Data
	unsigned short Time_to_Enemy,Mineral_Mod,Time_to_Wallin,Scout_Time;
	unsigned short Mineral_Blocks,Vespene_Geysirs,Verbose;
	//Internal Options
	unsigned short Max_Time,Max_Generations,Mutations,Mutation_Rate;
	unsigned char Init();
	unsigned char InitGoal(char I[11]);
	void AdjustMining();
	void Fatal(char * strn);
};

extern Settings settings;	// definiert in settings.cpp

#endif
