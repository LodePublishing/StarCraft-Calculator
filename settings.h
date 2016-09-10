#ifndef SETTINGS_H
#define SETTINGS_H

#include "main.h"
#include <stdio.h>
#ifdef __WIN32__
#define clrscr() system("cls")
#define setattr(a,v,b)  //missing
#define gotoxy(x,y)             //missing
#elif __linux__
#define clrscr() printf("\033[2J") // Bildschirm loeschen
#define gotoxy(x,y) printf("\033[%d;%dH",(y),(x))
#endif

class Settings
{
	public:
	//Output Switches 0/1
	unsigned short colors,Detailed_Output;
	//Map Data
	unsigned short Time_to_Enemy,Mineral_Mod,Time_to_Wallin,Scout_Time;
	unsigned short Mineral_Blocks,Vespene_Geysirs,Verbose;
	//Internal Options
	unsigned short Max_Time,Max_Generations,Mutations,Mutation_Rate;
	unsigned char InitSettings();
	unsigned char InitGoal(char I[11]);
	void AdjustMining();
};

extern Settings setup;	// definiert in settings.cpp

inline void setattr(unsigned char a,unsigned char v,unsigned char b)
{ if(setup.colors==1) printf("\033[%d;%d;%dm", (a), (v), (b)); }
 
#endif
