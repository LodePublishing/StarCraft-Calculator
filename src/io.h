#ifndef __IO_H
#define __IO_H


#include "anarace.h" 

#define HEIGHT 16 // Number of entries (build order list)
#define WIDTH 11 // witdh of the entries
#define COLOR_1 34
#define COLOR_2 36
#define COLOR_3 37

inline int UpperCase(char x) {if(x>91) return (x-32); else return(x);}
extern void setColor(unsigned char c);
extern void setAt(unsigned char cnt);

#ifdef WIN32
#include <windows.h>
extern HANDLE scr;
const unsigned char colorsWin32[7]= 
//Translate Linux ANSI Colors to SetConsoleTextAttribute Colors
{
	                FOREGROUND_RED,FOREGROUND_GREEN,FOREGROUND_RED|FOREGROUND_GREEN,FOREGROUND_BLUE,FOREGROUND_RED|FOREGROUND_BLUE,FOREGROUND_GREEN|FOREGROUND_BLUE,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN
};
extern void print(const char * x);
#define clrscr() system("cls")
#define gotoxy(x,y) {COORD pos={(x),(y)}; SetConsoleCursorPosition(scr,pos); }

#elif __linux__
#define clrscr() printf("\033[2J") // Bildschirm loeschen
#define gotoxy(x,y) printf("\033[%d;%dH",(y),(x))
#define print(x) printf((x))
#endif

#endif



class IO
{
	public:
        char tmp[255];
	int pFitnessGraphicsCounter;
        int pFitnessDifference;
        int sFitnessGraphicsCounter;
        int sFitnessDifference;
        int tFitnessGraphicsCounter;
        int tFitnessDifference;
        
        int oldsFitness;
        int oldpFitness;
	int oldtFitness;
	
        int calc;
        int tgGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT];
        struct boLog
        {
                int count;
                int order;
        } bolog[MAX_LENGTH],globalForcelog[UNIT_TYPE_COUNT];
	

	void screen(ANARACE* anaplayer);
	IO();
};
