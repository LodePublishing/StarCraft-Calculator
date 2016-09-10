#ifndef __RACE_H
#define __RACE_H

#include "main.h"
#include "settings.h"

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
};



class RACE
{
private:
	//void Build(int what);
	void CalculateFitness();
	void Harvest_Resources();
	int nr,ok,BuildingRunning,ready;
	void adjustMineralHarvest(int loc);
	void adjustGasHarvest(int loc);

	static void init(SETTINGS* set);
        static void adjustGoals(SETTINGS* set);
        static void generateBasicBuildOrder(); //pre-process goals to create a b
        static int genoToPhaenotype[UNIT_TYPE_COUNT];
        static int phaenoToGenotype[UNIT_TYPE_COUNT];
	static int maxBuildTypes;
        static int isBuildable[UNIT_TYPE_COUNT];
        static int isVariable[UNIT_TYPE_COUNT];
        static const UNIT_STATISTICS* pStats;
        static const int* basicMineralHarvestPerSecond;
        static const int* basicGasHarvestPerSecond;

        int mineralHarvestPerSecond[MAX_LOCATIONS][45];
        int gasHarvestPerSecond[MAX_LOCATIONS][5];

        static int basicBuildOrder[2][MAX_LENGTH];
        static int basicLength;
        static int initialized;
        int suc,IP;
        void harvestResources();
        int window,prev,start;
	
       
	
	
public:
	int mutationRate;
	LOCATION location[MAX_LOCATIONS]; //Location[0] == globalForce/globalAvailible!!
        GOAL goal[MAX_GOALS];
//        int goalCount;
//        int allGoal[UNIT_TYPE_COUNT]; //former goal...
//        int globalGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT];
//        void addGoal(int unit, int count, int time, int location);

	int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...)
	
	int mins,gas,timer;
	int supply,maxSupply;

	//TODO: gather new data for mining and gasing
	int length;
	
	int Code[2][MAX_LENGTH];

	struct Program
	{
		int needSupply,haveSupply,success,built,dominant,haveMinerals,haveGas,time,mins,gas,temp,location;		
	} program[MAX_LENGTH];



	Building building[MAX_BUILDINGS];


	
	int harvested_gas,harvested_mins;
	int pFitness,sFitness;


	
	void mutateGeneCode(int generateBuildOrder);
	//void Calculate(SETTINGS* settings); 
	void resetGeneCode(int generateBuildOrder);//resets either to a pre-processed buildorder or a completely random one
	void resetLocations(LOCATION* loc);
	void resetData(MISC* misc); //resets all data to standard values
	void crossOver(RACE* parent2, RACE* child1, RACE* child2);
//	void analyzeBuildOrder(); //statistics! TODO implement own statistic race 
	RACE(SETTINGS* set);
};

#endif //__RACE_H
