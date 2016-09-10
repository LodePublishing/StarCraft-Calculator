#include "soup.h"
#include "settings.h"
#include "race.h"
#include "text.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "anarace.h"

SOUP::SOUP(SETTINGS *set)
{
	for(int i=MAX_PLAYER;i--;) 
		player[i]=&p[i];
			//new RACE(set);
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
        if(( (*(RACE*)a).pFitness<(*(RACE*)b).pFitness)||(((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness<=(*(RACE*)b).sFitness)))
                return (1);
        else if(( (*(RACE*)a).pFitness>(*(RACE*)b).pFitness)|| ((*(RACE*)a).sFitness>(*(RACE*)b).sFitness))
                return (-1);
        else return(0);
};

void SOUP::run()
{
	int n=0;
	int generation=0;
	int pfit=0;
	int sfit=0;
	int rfit=0;
	while(n<settings->ga.maxRuns)
	{
                for(int i=MAX_PLAYER;i--;)
                {
                        player[i]->resetData();
			player[i]->initLocations();
                        player[i]->mutateGeneCode();
		}


		for(int i=MAX_PLAYER;i--;)
			player[i]->calculate();
		for(int i=7;i--;)
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
		}
		qsort(player[0],MAX_PLAYER,sizeof(RACE),compare);

                for(int i=20;i--;)
                {
                        int t=rand()%(MAX_PLAYER/2)+MAX_PLAYER/2;
                        memcpy(player[t]->Code[0],player[0]->Code[0],MAX_LENGTH*4); 
                        memcpy(player[t]->Code[1],player[0]->Code[1],MAX_LENGTH*4);
//                        player[t]->pFitness=player[0]->pFitness;
  //                      player[t]->sFitness=player[0]->sFitness;
                }

		if((player[0]->pFitness>pfit)||((player[0]->pFitness>=pfit)&&(player[0]->sFitness>sfit)))
		{
			if(player[0]->sFitness>sfit)
				sfit=player[0]->sFitness;
			if(player[0]->pFitness>pfit)
			{
				pfit=player[0]->pFitness;
				sfit=player[0]->sFitness;
			}
			rfit=0;
			memcpy(anaplayer.Code[0],player[0]->Code[0],MAX_LENGTH*4);
                        memcpy(anaplayer.Code[1],player[0]->Code[1],MAX_LENGTH*4);
			anaplayer.resetData();
			anaplayer.initLocations();
			anaplayer.calculate();
			for(int i=1;i<anaplayer.length;i++)
			{
				//printf("STATS: %i %i %i\n",settings->ga.maxLength-i,anaplayer.Code[1][settings->ga.maxLength-i],anaplayer.Code[0][settings->ga.maxLength-i]);
				if(anaplayer.program[settings->ga.maxLength-i].time<settings->ga.maxTime)
				{
					if(anaplayer.program[settings->ga.maxLength-i].dominant)
						printf("%i: [%s/%s]",settings->ga.maxLength-i,anaplayer.pStats[anaplayer.genoToPhaenotype[anaplayer.Code[1][settings->ga.maxLength-i]]].name,anaplayer.pStats[anaplayer.genoToPhaenotype[anaplayer.Code[0][settings->ga.maxLength-i]]].name);
					else printf("%i: [%s/%s]",settings->ga.maxLength-i,anaplayer.pStats[anaplayer.genoToPhaenotype[anaplayer.Code[0][settings->ga.maxLength-i]]].name,anaplayer.pStats[anaplayer.genoToPhaenotype[anaplayer.Code[1][settings->ga.maxLength-i]]].name);
					printf(" (%i/%i) [%.2i:%.2i]\n",anaplayer.program[settings->ga.maxLength-i].needSupply,anaplayer.program[settings->ga.maxLength-i].haveSupply,anaplayer.program[settings->ga.maxLength-i].time/60,anaplayer.program[settings->ga.maxLength-i].time%60);
				}
			}
			printf("Generation %3i: ",generation);
			if(anaplayer.timer==settings->ga.maxTime)
				printf("new pFit: %5i",pfit);
			else printf("%2i:%2i",(settings->ga.maxTime-anaplayer.timer)/60,(settings->ga.maxTime-anaplayer.timer)%60);
			printf(", sFit: %5i (%5i)\n",sfit,anaplayer.harvestedGas);
		}

//		locations 0/1 checken... funzt sumup bei calcfitness nicht!

		rfit++;
		generation++;
		if(rfit>settings->ga.maxGenerations)
		{
			rfit=0;pfit=0;sfit=0;generation=0;
			for(int i=MAX_PLAYER;i--;)
			{
				player[i]->resetGeneCode();
				player[i]->resetData();
				player[i]->initLocations();
			}
			n++;
			printf("NEW RUN: %i...\n",n);
		}
	}
};
