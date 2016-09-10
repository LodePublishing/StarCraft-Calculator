#ifndef __ANARACE_H
#define __ANARACE_H

#include "main.h"
#include "settings.h"

class ANARACE
{
private:
	int buildGene(int what);
        void calculateFitness(int ready);
        void adjustMineralHarvest(int loc);
        void adjustGasHarvest(int loc);
        static void init();
        static void adjustGoals();
        static void generateBasicBuildOrder(); //pre-process goals to create a b
        void harvestResources();
public:
//Output:

	struct Success
	{
		int what; // what kind of error
		int type; // unit number
		int loc; // location
	} success;
	
        struct Program
        {
                int needSupply,haveSupply,built,dominant,haveMinerals,haveGas,time,mins,gas,temp,location,type;
		Success success;
        } program[MAX_LENGTH];

        static int maxBuildTypes;
        static int basicLength;
        static int initialized;
        static int phaenoToGenotype[UNIT_TYPE_COUNT];
	static int genoToPhaenotype[UNIT_TYPE_COUNT];
        static int isBuildable[UNIT_TYPE_COUNT];
        static int isVariable[UNIT_TYPE_COUNT];
        static int basicBuildOrder[2][MAX_LENGTH];
        static const UNIT_STATISTICS* pStats;
        static const MAP* map;
        static const int* basicMineralHarvestPerSecond;
        static const int* basicGasHarvestPerSecond;
        int mineralHarvestPerSecond[MAX_LOCATIONS][45];
        int gasHarvestPerSecond[MAX_LOCATIONS][5];
        int window,prev,start,IP;
        int mins,gas;
        int supply,maxSupply;
        int mutationRate;
	int timer;
        int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...)
struct Building
{
        int RB; // Remaining Buildtime
        int type; // Type of Building
        int unitCount; //number of units which are moving... currently ONLY for movements...
        int IP;
        int facility; // in what facility it was produced
        int location;
        int goal; //For movement!
        // TODO: Aus Optimierungsgruenden: Eine logforce Variable die _Alle_ Einheiten mitzaehlt
} building[MAX_BUILDINGS]; //Building declaration in main.h
        LOCATION location[MAX_LOCATIONS]; //Location[0] == globalForce/globalAvailible!!
        static GOAL goal[MAX_GOALS];

	int harvested_gas,harvested_mins;
	int pFitness,sFitness,length;
        int Code[2][MAX_LENGTH];
//Controls:
	static const SETTINGS* pSet;
	void mutateGeneCode();
	void calculate(); 
	void resetGeneCode();//resets either to a pre-processed buildorder or a completely random one
	void resetData(); //resets all data to standard values
	void initLocations();
	void crossOver(ANARACE* parent2, ANARACE* child1, ANARACE* child2);
	ANARACE();
};

#endif //__ANARACE_H
