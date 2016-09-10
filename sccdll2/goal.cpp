#include "goal.h"
#include <string.h>

const char* GOAL_ENTRY::getName()
{
	return name;
};

int GOAL_ENTRY::getRace()
{
	return race;
};

int GOAL_ENTRY::setName(const char* line)
{
	strcpy(name,line);
	return(1);
};

int GOAL_ENTRY::isRaceInitialized()
{
	if(raceInitialized==1)
		return(1);
	else return(0);
};


int GOAL_ENTRY::setRace(int num)
{
	if((num<0)||(num>=3))
		return(0);
	pStats=&(stats[race=num][0]);
	raceInitialized=1;
	return(1);
};

int GOAL_ENTRY::adjustGoals()
{
	int i,j,k;

	for(j=6;j--;) // Nuclear Warhead needs 6 steps (?) ~~~~
		for(i=UNIT_TYPE_COUNT;i--;)
			if((allGoal[i]>0)||(isBuildable[i]>0))
			{
				isBuildable[i]=1;
				for(k=0;k<3;k++)
					if((pStats[i].prerequisite[k]>0)&&(allGoal[pStats[i].prerequisite[k]]==0))
						addGoal(pStats[i].prerequisite[k],1,0,0);
				if((pStats[i].facility2>0)&&(allGoal[pStats[i].facility2]==0)&&(pStats[i].facility_type!=NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE)&&(pStats[i].facility_type!=NEEDED_UNTIL_COMPLETE_IS_LOST))
				{
					isVariable[pStats[i].facility2]=1;
					if(pStats[i].facility_type!=IS_LOST) //do not set those morph-facilities as goals...
						addGoal(pStats[i].facility2,1,0,0);
					else isBuildable[pStats[i].facility2]=1;// ... but make them buildable :)
				}
				if((pStats[i].facility[0]>0)&&(allGoal[pStats[i].facility[0]]==0)&&((pStats[i].facility[1]==0)||(allGoal[pStats[i].facility[1]]==0))&&((pStats[i].facility[2]==0)||(allGoal[pStats[i].facility[2]]==0)))
// only facility[0] is important
				{
					isVariable[pStats[i].facility[0]]=1;
					if((pStats[i].facility_type==NEEDED_ONCE)||(pStats[i].facility_type==NEEDED_UNTIL_COMPLETE)||(pStats[i].facility_type==NEEDED_ALWAYS))
						addGoal(pStats[i].facility[0],1,0,0);
					else isBuildable[pStats[i].facility[0]]=1; // ... same as above...
				}
			}
	long Need_Gas=0;
	for(i=UNIT_TYPE_COUNT;i--;)
		Need_Gas+=(allGoal[i]*pStats[i].gas);
	if(Need_Gas>0)
	{
		isBuildable[REFINERY]=1;
		if(allGoal[REFINERY]==0)
		       addGoal(REFINERY,1,0,0); //ASSIMILATOR == EXTRACTOR == REFINERY
		isBuildable[GAS_SCV]=1; //ONE_MINERAL_SCV... = ONE_MINERAL_PROBE... = ONE_MINERAL_DRONE...
		isVariable[GAS_SCV]=1;
	};
//      isBuildable[WINDOW_MOVE_ADD_3]=1;isVariable[WINDOW_MOVE_ADD_3]=1;
//      isBuildable[WINDOW_MOVE_ADD_1]=1;isVariable[WINDOW_MOVE_ADD_1]=1;
//      isBuildable[WINDOW_MOVE_SUB_1]=1;isVariable[WINDOW_MOVE_SUB_1]=1;
	isBuildable[MOVE_ONE_1_FORWARD]=1;isVariable[MOVE_ONE_1_FORWARD]=1;
	isBuildable[MOVE_ONE_3_FORWARD]=1;isVariable[MOVE_ONE_3_FORWARD]=1;
	isBuildable[MOVE_ONE_1_BACKWARD]=1;isVariable[MOVE_ONE_1_BACKWARD]=1;

	//TODO: ueberlegen ob nicht einfach Move+ und Move- reichen...
	return(1);
};


int GOAL_ENTRY::isGoal(int unit)
{
	if(allGoal[unit]>0)
		return(1);
	else return(0);
};

int GOAL_ENTRY::addGoal(int unit, int count, int time, int location)
{
	if(unit==0) 
		return(0);
	allGoal[unit]+=count;

	int i=0;
	for(i=0;i<goalCount;i++)
		if((goal[i].unit==unit)&&(goal[i].time==time)&&(goal[i].location==location))
		{
			goal[i].count+=count;
			i=goalCount+1;
		}
	if(i<goalCount+1)
	{
		goal[goalCount].unit=unit;
		goal[goalCount].time=time;
		goal[goalCount].location=location;
		goal[goalCount].count=count;
		goalCount++;
	}
	return(1);
};

GOAL_ENTRY::GOAL_ENTRY()
{
	int i;
	raceInitialized=0;
	strcpy(name,"Error!");
	goalCount=0;
	for(i=0;i<MAX_GOALS;i++)
	{
		goal[i].count=0;
		goal[i].time=0;
		goal[i].unit=0;
		goal[i].location=0;
	}
	for(i=0;i<UNIT_TYPE_COUNT;i++)
		allGoal[i]=0;
	for(i=UNIT_TYPE_COUNT;i--;)
	{
	  isVariable[i]=0;
	  isBuildable[i]=0;
	}
};
