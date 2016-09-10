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
// 	Main[Minerals], Front, Enemy Front, Enemy Main, Cliff (Drop), Expansion[Minerals], Second Expansion[Minerals]
	// Aus Optimierungsgruenden: Eine logforce Variable die _Alle_ Einheiten mitzaehlt
};


struct Location
{
        int force[UNIT_TYPE_COUNT];
        int availible[UNIT_TYPE_COUNT];
};

struct GOAL
{
        int unit;
        int time;
        int count;
        int location;
};

class RACE
{
private:
	void Build(int what);
	void CalculateFitness();
	void Harvest_Resources();
	int nr,ok,BuildingRunning,ready;
public:
	int mutationRate;
	Location location[MAX_LOCATIONS]; //Location[0] == globalForce/globalAvailible!!
	static int isBuildable[UNIT_TYPE_COUNT];
	static int isVariable[UNIT_TYPE_COUNT];
	static int genoToPhaenotype[UNIT_TYPE_COUNT];
	static int phaenoToGenotype[UNIT_TYPE_COUNT];
	static int maxBuildTypes;
	static int goalCount;
	static int allGoal[UNIT_TYPE_COUNT]; //former goal...
	static int globalGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT];
	static GOAL goal[MAX_GOALS];
	
	int mineralHarvestPerSecond[MAX_LOCATIONS][45];
	int gasHarvestPerSecond[MAX_LOCATIONS][5];
	
	static int basicBuildOrder[2][MAX_LENGTH];
	static int basicLength;
	
	int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced (ALL locations...)
	
	int mins,gas;

	int window,prev,start; 

	//TODO: gather new data for mining and gasing
	int length;
	int Supply,Max_Supply;
	int suc,IP;

	int Code[2][MAX_LENGTH];

	struct Program
	{
		int need_Supply,have_Supply,success,built,dominant,have_Minerals,have_Gas,time,mins,gas,temp,location;		
	} program[MAX_LENGTH];

	Building building[MAX_BUILDINGS];

	int harvested_gas,harvested_mins;
	int pFitness,sFitness,timer;
	
	static void AddGoal(int unit, int count, int time, int location);
	void AdjustMining();
	
	void Mutate();
	void Calculate(); 
	void Set_Goals(char I[11]);
	void Restart();
	void generateBasicBuildorder();
	void Init();
	void crossOver(RACE* parent2, RACE* child1, RACE* child2);

	void analyzeBuildOrder(); //statistics! TODO implement own statistic race 
	
	RACE();
};

#endif //__RACE_H
