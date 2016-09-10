#ifndef __ANARACE_H
#define __ANARACE_H

#include "main.h"
#include "settings.h"
#include "prerace.h"

class SCCDLL_API ANARACE: public PRERACE
{
private:
//		int buildGene(int what);
//      static void init();
//      static void adjustGoals();
//        void harvestResources();
public:
//Output:

/*		struct Success
		{
			int what; // what kind of error
			int type; // unit number
			int loc; // location
		} success;
	
        struct Program
        {
                int needSupply,haveSupply,built,dominant,haveMinerals,haveGas,time,mins,gas,temp,location,type;
				Success success[2];
        } program[MAX_LENGTH];

	int maxBuildTypes;
//        static int initialized;
	int phaenoToGenotype[UNIT_TYPE_COUNT];
	int genoToPhaenotype[UNIT_TYPE_COUNT];
	int isBuildable[UNIT_TYPE_COUNT];
//        static const UNIT_STATISTICS* pStats;
//        static const MAP_LOCATION* pMap;
//        static const int* basicMineralHarvestPerSecond;
//        static const int* basicGasHarvestPerSecond;
//		static int lastcounter;
		static LAST last[MAX_LENGTH];
//        int mineralHarvestPerSecond[MAX_LOCATIONS][45];
//      int gasHarvestPerSecond[MAX_LOCATIONS][5];
//      int IP;
//        int mins,gas;
//        int supply,maxSupply;
//        int mutationRate;
	int timer;
//      int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...)
/*struct Building
{
        int RB; // Remaining Buildtime
        int type; // Type of Building
        int unitCount; //number of units which are moving... currently ONLY for movements...
        int IP;
        int facility; // in what facility it was produced
        int location;
        int goal; //For movement!
	int onTheRun;
        // TODO: Aus Optimierungsgruenden: Eine logforce Variable die _Alle_ Einheiten mitzaehlt
} building[MAX_BUILDINGS]; //Building declaration in main.h*/
//        LOCATION location[MAX_LOCATIONS]; //Location[0] == globalForce/globalAvailible!!
//        static GOAL goal[MAX_GOALS];

	//int harvestedGas,harvestedMins;
	//int length;
/*        int Code[2][MAX_LENGTH];

        int run;
        int generation;
        int maxpFitness;
        int maxsFitness;
	int maxtFitness;
        int unchangedGenerations;
	
//Controls:
//	static const DATA* pSet;
	void calculate(); 
	void resetData(); //resets all data to standard values
	void initLocations();*/
	ANARACE();
};

#endif //__ANARACE_H
