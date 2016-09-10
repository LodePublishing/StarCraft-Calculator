#include "population.h"
#include "stdlib.h"


static int compare(const void * a,const void * b)
{
        if(( (*(RACE*)a).pFitness<(*(RACE*)b).pFitness)||(((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness<=(*(RACE*)b).sFitness)))
                return (1);
        else if(( (*(RACE*)a).pFitness>(*(RACE*)b).pFitness)|| ((*(RACE*)a).sFitness>(*(RACE*)b).sFitness))
                return (-1);
        else return(0);
}

void POPULATION::sortAndSelect()
{
	qsort(player,MAX_PLAYER,sizeof(player[0]),compare);
	player[0]->crossOver(player[1],player[MAX_PLAYER-1],player[MAX_PLAYER-2]);
}

POPULATION::POPULATION()
{
}

POPULATION::~POPULATION()
{
	int i;
	for(i=0;i<MAX_PLAYER;i++)
		player[i]=NULL;
}
