#ifndef __ANARACE_H
#define __ANARACE_H

#include "prerace.h"

struct PROGRAM
{
	int needSupply;		// supply that is used up by all units
	int haveSupply;		// total supply of supply buildings (overlord, supply depot, command center, ...)
	int built;			// was this order successfully built?
	int dominant;		// which one of the two 'Code' entries is dominant?
	int time;			// at which time this order was started
	int mins;			// minerals at that time
	int gas;			// gas at that time
	int temp;			// unused
	int location;		// at which location was this unit built
	int successType;	// type of error
	int successUnit;	// unit number
	int isGoal;			// is this unit part of the goal list? DOES NOT WORK YET :)
}; 

class SCCDLL_API ANARACE: public PRERACE
{
	private:
		int buildGene(int unit);
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
	public:
// external data output
		int phaenoCode[MAX_LENGTH];		// the final build order: an array of unit numbers (as defined in main.h)

		int getProgramSuccessType(int IP);	// determines the type of the last error before the item was built at that IP
		int getProgramSuccessUnit(int IP);	// what unit was missing? (connected to successtype)
		int getProgramNeedSupply(int IP);	// supply that is used up by all units
		int getProgramHaveSupply(int IP);	// total supply of supply buildings (overlord, supply depot, command center, ...)
		int getProgramIsBuilt(int IP);		// was this order successfully built?
		int getProgramTime(int IP);			// at which time this order was started
		int getProgramHaveMinerals(int IP); // minerals at that time
		int getProgramHaveGas(int IP);		// gas at that time
		int getProgramLocation(int IP);		// at which location was this unit built
		int getProgramTemp(int IP);			// unused
		int getProgramIsGoal(int IP);		// is this unit part of the goal list? NOT YET WORKING!

		int getUnchangedGenerations();	// gets number of generations where no change in fitness took place
		int getRun();					// gets number of runs (one run is complete when no <unchangedGenerations> > <maxGenerations>)
		int getGeneration();			// gets number of total generations of this run
		int getMaxpFitness();			// gets primary fitness (goal and time)
		int getMaxsFitness();			// gets secondary fitness (ressources)
		int getMaxtFitness();			// gets tertiary fitness (build order appearance, some heuristics)

// internal control structures, do not touch ;-)
		int setUnchangedGenerations(int num); 
		int setRun(int num);
		int setGeneration(int num);
		int setMaxpFitness(int num);
		int setMaxsFitness(int num);
		int setMaxtFitness(int num);
		int setProgramSuccessType(int num);
		int setProgramSuccessUnit(int num);
		int calculateStep();			// calculates another time step of current generation
		void resetData();				// resets all data to standard values
		void analyzeBuildOrder();		// sets the isGoal of program

// Constructor
		ANARACE();
};

#endif //__ANARACE_H
