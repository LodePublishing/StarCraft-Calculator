#ifndef __RACE_H
#define __RACE_H

#include "main.h"

class RACE
{
public:
	int force[60];
	int ftime[60]; //when the goal is reached / when the last item is produced
	int availible[60];
	int mins,gas;
	
	//TODO: gather new data for mining and gasing
	
	unsigned short min,n;
	unsigned short peonmins,peongas, peonbuilding, length,BuildingRunning;
	short Supply,Max_Supply;
	unsigned char suc,IP;

	unsigned char ready;

	unsigned char Code[MAX_LENGTH][2];

	struct Program
	{
		int need_Supply,have_Supply,success,built,dominant,have_Minerals,have_Gas,time,mins,gas,temp;		
	} program[MAX_LENGTH];
	struct Building
	{
		unsigned short RB; // Remaining Buildtime
		unsigned short type; // Type of Building
		unsigned char on_the_run; //unit that is running towards the enemy
		unsigned char location;
		unsigned char IP;
		// Main, Front, Enemy Front, Enemy Main, Drop(?), Expansion(?)
	} building[MAX_BUILDINGS];

	unsigned char nr,ok;

	int harvested_gas,harvested_mins;
	int pFitness,sFitness,timer,gasready,minsready;

	// => zerg.h, terra.h, protoss.h
	virtual void Set_Goals() {};
	virtual void Build(unsigned char what) {};
	virtual void Calculate() {}; 
	virtual void InitRaceSpecific() {};
	virtual void readjust_goals() {};

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
