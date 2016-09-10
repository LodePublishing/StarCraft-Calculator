#ifndef SETTINGS_H
#define SETTINGS_H

#include "main.h"
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#define clrscr() system("cls")
extern HANDLE scr;
#define gotoxy(x,y) {COORD pos={(x),(y)}; SetConsoleCursorPosition(scr,pos); }       

extern void print(const char * x); 

#elif __linux__
#define clrscr() printf("\033[2J") // Bildschirm loeschen
#define gotoxy(x,y) printf("\033[%d;%dH",(y),(x))
#define print(x) printf((x))
#endif

class Settings
{
	public:
	Settings();
	~Settings();
	//Output Switches 0/1
	unsigned short Detailed_Output,Console24Lines,Gizmo;
	//Map Data
	unsigned short Time_to_Enemy,Mineral_Mod,Time_to_Wallin,Scout_Time;
	unsigned short Mineral_Blocks,Vespene_Geysirs,Verbose;
	//Internal Options
	unsigned short Max_Time,Max_Generations,Mutations,Mutation_Rate;
	unsigned char InitSettings();
	unsigned char InitGoal(char I[11]);
	void setColor(unsigned char c);
	void AdjustMining();
	void Fatal(char * strn);
	private:
	unsigned char colors;
};

extern Settings setup;	// definiert in settings.cpp

#endif
