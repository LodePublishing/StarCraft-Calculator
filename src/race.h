#ifndef __RACE_H
#define __RACE_H

#include "main.h"
#include "settings.h"

class RACE
{
private:
        static int maxBuildTypes;
        static int basicLength;
	static int initialized;
        static int phaenoToGenotype[UNIT_TYPE_COUNT];
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
        int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...)
struct Building
{
        int RB; // Remaining Buildtime
        int type; // Type of Building
        int unitCount; //number of units which are moving... currently ONLY for movements...
        int facility; // in what facility it was produced
        int location;
        int goal; //For movement!
        // TODO: Aus Optimierungsgruenden: Eine logforce Variable die _Alle_ Einheiten mitzaehlt
} building[MAX_BUILDINGS]; //building declaration in main.h
        LOCATION location[MAX_LOCATIONS]; //Location[0] == globalForce/globalAvailible!!
        static GOAL goal[MAX_GOALS];

        int buildGene(int what);
        void calculateFitness(int ready);
        void adjustMineralHarvest(int loc);
        void adjustGasHarvest(int loc);
        static void init();
        static void adjustGoals();
        static void generateBasicBuildOrder(); //pre-process goals to create a b
        void harvestResources();
        static int genoToPhaenotype[UNIT_TYPE_COUNT];
        int harvested_gas,harvested_mins,length;
public:
//Output:
	int pFitness,sFitness;
        int Code[2][MAX_LENGTH];
//Controls:
	static const SETTINGS* pSet;
	void mutateGeneCode();
	void calculate(); 
	void resetGeneCode();//resets either to a pre-processed buildorder or a completely random one
	void resetData(); //resets all data to standard values
	void initLocations();
	void crossOver(RACE* parent2, RACE* child1, RACE* child2);
	RACE();
};

#endif //__RACE_H
