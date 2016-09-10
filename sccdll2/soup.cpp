#include "soup.h"
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <windows.h>
#include "race.h"
#include "anarace.h"

bool APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

int SOUP::setMap(MAP* map)
{
	if(!map)
		return(0);
	mapInitialized=1;
	pMap=map;
	return(1);
};


int SOUP::setGoal(GOAL_ENTRY* goal, int player)
{
	if((!mapInitialized)||(player<0)||(player>=pMap->getMaxPlayer()))
		return(0);
//	if(!this->goal[player]) ~~~~~~~~
//	{
		goalCount++;
		if(goalCount==pMap->getMaxPlayer())
			goalsInitialized=1;
//	}
	this->goal[player]=goal;
	return(pMap->player[player].setGoal(goal));
};

int SOUP::setParameters(GA* ga)
{
	if(!ga)
		return(0);
	gaInitialized=1;
	this->ga=ga;
	PRERACE::ga=ga;
	return(1);
};

int SOUP::initSoup()
{
	int i;
	if(!mapInitialized)
		return(-1);
	if(!goalsInitialized)
		return(-2);
	if(!gaInitialized)
		return(-3);
	if(!PRERACE::setMap(pMap))
		return(-4);

	for(i=MAX_PROGRAMS;i--;)
	{
		player[i]=new RACE();
		if(i>MAX_PROGRAMS/2)
		{
			if(!player[i]->loadPlayer(1)) //~~
			{
				for(int j=i;j>=0;j--)
					delete player[j];
				return(-5);
			}
		}
		else
		{
			if(!player[i]->loadPlayer(0)) //~~
			{
				for(int j=i;j>=0;j--)
					delete player[j];
				return(-5);
			}
		}
	};

	for(i=2;i--;) //~~ getmaxplayer oder so
	{
		anaplayer[i]=new ANARACE();
		if(!(anaplayer[i]->loadPlayer(i))) 
		{
			for(int j=i;j>=0;j--)
				delete player[j];
			return(-6);
		};
	};
	for(i=0;i<MAX_PROGRAMS;i++)
		player[i]->resetGeneCode();

	playerInitialized=1;
	return(1);
};


SOUP::SOUP()
{
	run_number=0;
	playerInitialized=0;
	mapInitialized=0;
	goalCount=0;
	gaInitialized=0;
	goalsInitialized=0;

/*	RACE::setMap(this->map);
    RACE::sepSet=settings;
	RACE::pMap=data->pMap;
    ANARACE::pSet=settings;
	ANARACE::pMap=data->pMap;*/
//	anaplayer=new ANARACE();

//TODO!!! static pSet hier initialisieren! race und anarace noch nicht initialisieren sondern ueber new hier aufrufen!
//	for(i=RUNNINGS;i--;) statistics[i]=new STATISTICS;
};

SOUP::~SOUP()
{
	int i;
	if(playerInitialized)
		for(i=0;i<MAX_PLAYER;i++)
			delete player[i];
//	delete settings;
//	delete [] statistics;
};

int compare(const void* a,const void* b)
{
	if(( (*(RACE*)a).pFitness<(*(RACE*)b).pFitness)||(((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness<(*(RACE*)b).sFitness)) || ( ((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness==(*(RACE*)b).sFitness)&& ((*(RACE*)a).tFitness>=(*(RACE*)b).tFitness)) )
		return (1);
	else if(( (*(RACE*)a).pFitness>(*(RACE*)b).pFitness)|| ((*(RACE*)a).sFitness>(*(RACE*)b).sFitness))
		return (-1);
	else return(0);
};

//TODO: Ueber Optionen einstellen, welche Fitness ueberhaupt bzw. wie stark gewertet wird (oder ob z.B. die Fitnesswerte zusammengeschmissen werden sollen etc.)

void SOUP::resetLocations()
{

	//kommen ja immer 4, 2 oder 1 in ein paaring...
/*	int i,j;

	for(i=0;i<MAX_LOCATIONS;i++)
	{
		location[i].force=pMap->location[i].force;
		location[i].availible=
	}*/
};

ANARACE* SOUP::newGeneration()
{
	int i;
	if((!mapInitialized)||(!goalsInitialized)||(!gaInitialized)||(ANARACE::getRun()>=ga->maxRuns)) 
		return(0);

	for(i=MAX_PLAYER;i--;)
	{
		player[i]->resetData();
		if(i>0) player[i]->mutateGeneCode();
	}
	
	for(i=MAX_PLAYER;i--;)
	{
		resetLocations();
		player[i]->calculate();
	}
	/*for(i=7;i--;)
		qsort(player[i*16],MAX_PLAYER/16,sizeof(RACE),compare);
	for(i=7;i--;)
	{
		int p1=rand()%(MAX_PLAYER/16);
		int p2=rand()%(MAX_PLAYER/16);
		int c1=rand()%(MAX_PLAYER/16);
		int c2=c1;
		while(c1==c2)
			c2=rand()%(MAX_PLAYER/16);
		player[p1*16]->crossOver(player[p2*16],player[c1*16+7],player[c2*16+7]);
	}*/
/*	
int j;		
		for(i=0;i<MAX_PLAYER;i++)
			for(j=0;j<i;j++)
				if((player[j]->pFitness>player[i]->pFitness)||
				  ((player[j]->pFitness==player[i]->pFitness)&&(player[j]->sFitness>player[i]->sFitness))||
				  ((player[j]->pFitness==player[i]->pFitness)&&(player[j]->sFitness==player[i]->sFitness)&&(player[j]->tFitness>player[i]->tFitness)) )
				{
					RACE* temp;
					temp=player[i];
					player[i]=player[j];
					player[j]=temp;
				}
		//qsort(player,MAX_PLAYER,sizeof(RACE),compare);
		  for(i=20;i--;)
		{
			int t=rand()%(MAX_PLAYER/2)+MAX_PLAYER/2;
			memcpy(player[t]->Code[0],player[0]->Code[0],MAX_LENGTH*4); 
			memcpy(player[t]->Code[1],player[0]->Code[1],MAX_LENGTH*4);
		}  

		if((player[0]->pFitness>anaplayer->maxpFitness)||((player[0]->pFitness>=anaplayer->maxpFitness)&&(player[0]->sFitness>anaplayer->maxsFitness))|| ((player[0]->pFitness>=anaplayer->maxpFitness)&&(player[0]->sFitness>=anaplayer->maxsFitness)&&(player[0]->tFitness>anaplayer->maxtFitness)))
		{
			if(player[0]->tFitness>anaplayer->maxtFitness)
				anaplayer->maxtFitness=player[0]->tFitness;
			if(player[0]->sFitness>anaplayer->maxsFitness)
			{
				anaplayer->maxsFitness=player[0]->sFitness;
				anaplayer->maxtFitness=player[0]->tFitness;
			}
			if(player[0]->pFitness>anaplayer->maxpFitness)
			{
				anaplayer->maxpFitness=player[0]->pFitness;
				anaplayer->maxsFitness=player[0]->sFitness;
				anaplayer->maxtFitness=player[0]->tFitness;
			}
			anaplayer->unchangedGenerations=0;
			memcpy(anaplayer->Code[0],player[0]->Code[0],MAX_LENGTH*4);
			memcpy(anaplayer->Code[1],player[0]->Code[1],MAX_LENGTH*4);
			anaplayer->resetData();
			anaplayer->initLocations();
			anaplayer->calculate();
		}
	
		anaplayer->unchangedGenerations++;
		anaplayer->generation++;
		if(anaplayer->unchangedGenerations>settings->ga.maxGenerations)
		{
			for(i=MAX_PLAYER;i--;)
			{
				player[i]->resetGeneCode();
				player[i]->resetData();
				player[i]->initLocations();
			}
			anaplayer->run++;
			anaplayer->generation=0;
			anaplayer->maxpFitness=0;
			anaplayer->maxsFitness=0;
			anaplayer->maxtFitness=0;
			anaplayer->unchangedGenerations=0;
		}*/
	return(anaplayer[0]);
};
