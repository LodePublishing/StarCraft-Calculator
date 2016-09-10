#ifndef __PRERACE_H
#define __PRERACE_H

#include "baserace.h"

class SCCDLL_API PRERACE:public BASERACE
{
	private:
		int player;
		int mins,gas,timer;
        int mineralHarvestPerSecond[MAX_LOCATIONS][45];
        int gasHarvestPerSecond[MAX_LOCATIONS][5];
		int supply,maxSupply;
	public:
		int getPlayer();
		int loadPlayer(int num);
        int adjustMineralHarvest(int loc);
        int adjustGasHarvest(int loc);
		int setSupply(int num);
		int setMaxSupply(int num);
		int setMins(int num);
		int setGas(int num);
		int setTimer(int num);
		int getSupply();
		int getMaxSupply();
		int getMins();
		int getGas();
		int getTimer();


/*		static const UNIT_STATISTICS* pStats;

		
        ,timer; //starting/current mins/gas/timer
	
		GOAL goal[MAX_GOALS];
		static int goalCount;
		static int allGoal[UNIT_TYPE_COUNT]; //former goal...
		static int globalGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT]; //?
		void addGoal(int unit, int count, int time, int location);
	
		static int maxBuildTypes;
        static int genoToPhaenotype[UNIT_TYPE_COUNT];
        static int phaenoToGenotype[UNIT_TYPE_COUNT];
		static int isBuildable[UNIT_TYPE_COUNT];
        static int isVariable[UNIT_TYPE_COUNT];
		

        void adjustMineralHarvest(int loc);
        void adjustGasHarvest(int loc);
		
		
		Building building[MAX_BUILDINGS];
		static int initialized;//»»
		
		static LAST last[MAX_LENGTH];
		int lastwhat; //~~
		static int lastcounter;
		int IP;

        
        int mutationRate;
        int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...

		void harvestResources();

        /*int buildGene(int what);
        void calculateFitness(int ready);
        static void init();
        static void adjustGoals();
        static void generateBasicBuildOrder(); //pre-process goals to create a b
        void harvestResources();
        static int genoToPhaenotype[UNIT_TYPE_COUNT];*/
/*        int length;
		int harvestedGas,harvestedMins;

//Output:
	int pFitness,sFitness,tFitness;
    int Code[2][MAX_LENGTH];
	//int phaenoCode[2][MAX_LENGTH];
//Controls:
	static const DATA* pSet;
/*	void mutateGeneCode();
	void calculate(); 
	void resetGeneCode();//resets either to a pre-processed buildorder or a completely random one
	void resetData(); //resets all data to standard values
	void initLocations();
	void crossOver(RACE* parent2, RACE* child1, RACE* child2);*/
	PRERACE();
};

#endif // __PRERACE_H