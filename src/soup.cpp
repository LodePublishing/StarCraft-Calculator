#include "soup.h"
#include <stdlib.h>
#include <cstring>
#include <time.h>

SOUP::SOUP(SETTINGS *set)
{
	srand(time(NULL));
	for(int i=MAX_PLAYER;i--;) 
		player[i]=&p[i];
//TODO!!! static pSet hier initialisieren! race und anarace noch nicht initialisieren sondern ueber new hier aufrufen!
//	for(int i=RUNNINGS;i--;) statistics[i]=new STATISTICS;
	settings=set;
};

SOUP::~SOUP()
{
	delete [] player;
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

int SOUP::newGeneration()
{
	if(anaplayer.run>=settings->ga.maxRuns) return(0);
		for(int i=MAX_PLAYER;i--;)
		{
			player[i]->resetData();
			player[i]->initLocations();
			if(i>0) player[i]->mutateGeneCode();
		}

		for(int i=MAX_PLAYER;i--;)
			player[i]->calculate();
		/*for(int i=7;i--;)
			qsort(player[i*16],MAX_PLAYER/16,sizeof(RACE),compare);
		for(int i=7;i--;)
		{
			int p1=rand()%(MAX_PLAYER/16);
			int p2=rand()%(MAX_PLAYER/16);
			int c1=rand()%(MAX_PLAYER/16);
			int c2=c1;
			while(c1==c2)
				c2=rand()%(MAX_PLAYER/16);
			player[p1*16]->crossOver(player[p2*16],player[c1*16+7],player[c2*16+7]);
		}*/
		qsort(player[0],MAX_PLAYER,sizeof(RACE),compare);

		  for(int i=20;i--;)
		{
			int t=rand()%(MAX_PLAYER/2)+MAX_PLAYER/2;
			memcpy(player[t]->Code[0],player[0]->Code[0],MAX_LENGTH*4); 
			memcpy(player[t]->Code[1],player[0]->Code[1],MAX_LENGTH*4);
		}  

		if((player[0]->pFitness>anaplayer.maxpFitness)||((player[0]->pFitness>=anaplayer.maxpFitness)&&(player[0]->sFitness>anaplayer.maxsFitness))|| ((player[0]->pFitness>=anaplayer.maxpFitness)&&(player[0]->sFitness>=anaplayer.maxsFitness)&&(player[0]->tFitness>anaplayer.maxtFitness)))
		{
			if(player[0]->tFitness>anaplayer.maxtFitness)
				anaplayer.maxtFitness=player[0]->tFitness;
			if(player[0]->sFitness>anaplayer.maxsFitness)
			{
				anaplayer.maxsFitness=player[0]->sFitness;
				anaplayer.maxtFitness=player[0]->tFitness;
			}
			if(player[0]->pFitness>anaplayer.maxpFitness)
			{
				anaplayer.maxpFitness=player[0]->pFitness;
				anaplayer.maxsFitness=player[0]->sFitness;
				anaplayer.maxtFitness=player[0]->tFitness;
			}
			anaplayer.unchangedGenerations=0;
			memcpy(anaplayer.Code[0],player[0]->Code[0],MAX_LENGTH*4);
			memcpy(anaplayer.Code[1],player[0]->Code[1],MAX_LENGTH*4);
			anaplayer.resetData();
			anaplayer.initLocations();
			anaplayer.calculate();
		}

		
		io.screen(&anaplayer);
		

		anaplayer.unchangedGenerations++;
		anaplayer.generation++;
		if(anaplayer.unchangedGenerations>settings->ga.maxGenerations)
		{
			for(int i=MAX_PLAYER;i--;)
			{
				player[i]->resetGeneCode();
				player[i]->resetData();
				player[i]->initLocations();
			}
			anaplayer.run++;
			anaplayer.generation=0;
			anaplayer.maxpFitness=0;
			anaplayer.maxsFitness=0;
			anaplayer.maxtFitness=0;
			anaplayer.unchangedGenerations=0;
		}
	return(1);
};
