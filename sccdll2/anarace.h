#ifndef __ANARACE_H
#define __ANARACE_H

//#include "main.h"
//#include "settings.h"
#include "prerace.h"

struct SUCCESS
{
	int what; // what kind of error
	int type; // unit number
	int loc; // location
};


struct PROGRAM
{
	int needSupply;
	int haveSupply;
	int built;
	int dominant;
	int time;
	int mins;
	int gas;
	int temp;
	int location;
	int successType; //type of error
	int successUnit; //unit number
	int successLocation; //where the code took place on the map
}; 




class SCCDLL_API ANARACE: public PRERACE
{
	private:
		int buildGene(int what);
        int unchangedGenerations;
		int run;
        int generation;
        int maxpFitness;
        int maxsFitness;
		int maxtFitness;
        PROGRAM program[MAX_LENGTH];
		BUILDING building[MAX_BUILDINGS];
		static int successType; //type of error
		static int successUnit; //unit number
		static int successLocation; //where the code took place on the map
	public:
		int getProgramSuccessType(int IP);
		int getProgramSuccessUnit(int IP);
		int getProgramSuccessLocation(int IP);

		int setProgramSuccessType(int num);
		int setProgramSuccessUnit(int num);
		int setProgramSuccessLocation(int num);

		int phaenoCode[MAX_LENGTH];

		int getProgramNeedSupply(int IP);
		int getProgramHaveSupply(int IP);
		int getProgramIsBuilt(int IP);
		int getProgramTime(int IP);
		int getProgramHaveMinerals(int IP);
		int getProgramHaveGas(int IP);
		int getProgramLocation(int IP);
		int getProgramTemp(int IP);

		int getUnchangedGenerations();
		int getRun();
		int getGeneration();
		int getMaxpFitness();
		int getMaxsFitness();
		int getMaxtFitness();

		int setUnchangedGenerations(int num);
		int setRun(int num);
		int setGeneration(int num);
		int setMaxpFitness(int num);
		int setMaxsFitness(int num);
		int setMaxtFitness(int num);

		void calculate(); 
		void resetData(); //resets all data to standard values
		ANARACE();
};

#endif //__ANARACE_H
