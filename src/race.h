#ifndef __RACE_H
#define __RACE_H

#include "main.h"

class RACE
{
public:
	int force[MAX_GOALS];
	int ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced
	int availible[MAX_GOALS];
	int mins,gas;
	
	//TODO: gather new data for mining and gasing
	
	int min,n;
	int peonmins,peongas, peonbuilding, length,BuildingRunning;
	int Supply,Max_Supply;
	int suc,IP;

	int ready;

	int Code[MAX_LENGTH][2];

	struct Program
	{
		int need_Supply,have_Supply,success,built,dominant,have_Minerals,have_Gas,time,mins,gas,temp;		
	} program[MAX_LENGTH];
	struct Building
	{
	 	int RB; // Remaining Buildtime
		int type; // Type of Building
		int on_the_run; //unit that is running towards the enemy
//		int location;
		int IP;
		int facility; // in what facility it was produced
		// Main, Front, Enemy Front, Enemy Main, Drop(?), Expansion(?)
	} building[MAX_BUILDINGS];

	int nr,ok;

	int harvested_gas,harvested_mins;
	int pFitness,sFitness,timer,gasready,minsready;

	// => zerg.h, terra.h, protoss.h
	virtual void Set_Goals() {};
	virtual void Calculate() {}; 
	virtual void InitRaceSpecific() {};
	virtual void readjust_goals() {};

	void Build(int what);
	//void Build_stats(unsigned char what);
	void CheckReady(unsigned char j);
	void CalculateFitness();
	void Mutate();
	void Restart();
	void Produce(unsigned char who);
	void generateBasicBuildorder();
	
	void Harvest_Resources();
	void Init();
	RACE();

};

#endif //__RACE_H
