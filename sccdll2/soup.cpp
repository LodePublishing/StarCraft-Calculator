#include "soup.h"
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <windows.h>

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

SOUP::SOUP(MAP* map,GOAL_ENTRY* goal, ...)
{
	va_list args;
	va_start(args,goal);
	GOAL_ENTRY* tGoal[MAX_PLAYER];
	tGoal[0]=goal;
	int i;
	for(i=0;i<map->getMaxPlayer();i++)
		tGoal[i+1]=va_arg(args,GOAL_ENTRY*);

/*	settings=data;
    RACE::pSet=settings;
	RACE::pMap=data->pMap;
    ANARACE::pSet=settings;
	ANARACE::pMap=data->pMap;
	srand(time(NULL));
	for(i=MAX_PLAYER;i--;)
		player[i]=new RACE();
	anaplayer=new ANARACE();*/

//TODO!!! static pSet hier initialisieren! race und anarace noch nicht initialisieren sondern ueber new hier aufrufen!
//	for(i=RUNNINGS;i--;) statistics[i]=new STATISTICS;
};

SOUP::~SOUP()

{
	int i;
	for(i=0;i<MAX_PLAYER;i++)
		delete player[i];
//	delete settings;
//	delete [] statistics;
};

/*int compare(const void* a,const void* b)
{
	if(( (*(RACE*)a).pFitness<(*(RACE*)b).pFitness)||(((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness<(*(RACE*)b).sFitness)) || ( ((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness==(*(RACE*)b).sFitness)&& ((*(RACE*)a).tFitness>=(*(RACE*)b).tFitness)) )
		return (1);
	else if(( (*(RACE*)a).pFitness>(*(RACE*)b).pFitness)|| ((*(RACE*)a).sFitness>(*(RACE*)b).sFitness))
		return (-1);
	else return(0);
};

//TODO: Ueber Optionen einstellen, welche Fitness ueberhaupt bzw. wie stark gewertet wird (oder ob z.B. die Fitnesswerte zusammengeschmissen werden sollen etc.)

ANARACE* SOUP::newGeneration()
{
	int i;
	if(anaplayer->run>=settings->ga.maxRuns) return(0);
		for(i=MAX_PLAYER;i--;)
		{
			player[i]->resetData();
			player[i]->initLocations();
			if(i>0) player[i]->mutateGeneCode();
		}

		for(i=MAX_PLAYER;i--;)
			player[i]->calculate();

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
		}
	return(anaplayer);
};*/
