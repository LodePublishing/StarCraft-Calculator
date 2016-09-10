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
	if((!mapInitialized)||(player<=0)||(player>=pMap->getMaxPlayer())) // 0 not allowed because this is temporary player
		return(0);
//	if(!this->goal[player]) ~~~~~~~~
//	{
		goalCount++;
		if(goalCount==pMap->getMaxPlayer()-1)
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
	PRERACE::resetMapInitialized();
	if(!(PRERACE::setMap(pMap)))
		return(-4);

	for(i=MAX_PROGRAMS;i--;)
	{
		player[i]=new RACE();
		if(i>MAX_PROGRAMS/2)
		{

//Problem: Mins werden net richtig initialisiert!
			if(!player[i]->loadPlayer(2)) //~~
			{
				for(int j=i;j>=0;j--)
					delete player[j];
				return(-5);
			}
		}
		else
		{
			if(!player[i]->loadPlayer(1)) //~~
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
		if(!(anaplayer[i]->loadPlayer(i+1))) 
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


/*int compare(const void* a,const void* b)
{
	if(( (*(RACE*)a).pFitness<(*(RACE*)b).pFitness)||(((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness<(*(RACE*)b).sFitness)) || ( ((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness==(*(RACE*)b).sFitness)&& ((*(RACE*)a).tFitness>=(*(RACE*)b).tFitness)) )
		return (1);
	else if(( (*(RACE*)a).pFitness>(*(RACE*)b).pFitness)|| ((*(RACE*)a).sFitness>(*(RACE*)b).sFitness))
		return (-1);
	else return(0);
};*/

//TODO: Ueber Optionen einstellen, welche Fitness ueberhaupt bzw. wie stark gewertet wird (oder ob z.B. die Fitnesswerte zusammengeschmissen werden sollen etc.)

ANARACE* SOUP::newGeneration()
{
	int i,j,t;
	if(!mapInitialized)
		return(0);
	if(!goalsInitialized)
		return(0);
	if(!gaInitialized)
		return(0);
	if(anaplayer[0]->getRun()>=ga->maxRuns) //~~
		return(0);

	for(i=0;i<MAX_PROGRAMS;i++)
	{
		player[i]->resetData();
		player[i]->resetLocations();
		if((i!=0)||(i!=MAX_PROGRAMS/2))
			player[i]->mutateGeneCode();
		player[i]->calculate();
	}

/*	for(t=7;t--;)
		for(i=t*16;i<t*16+MAX_PROGRAMS/16;i++)
			for(j=t*16;j<i;j++)
				if((player[j]->getpFitness()>player[i]->getpFitness())||
				  ((player[j]->getpFitness()==player[i]->getpFitness())&&(player[j]->getsFitness()>player[i]->getsFitness()))||
				  ((player[j]->getpFitness()==player[i]->getpFitness())&&(player[j]->getsFitness()==player[i]->getsFitness())&&(player[j]->gettFitness()>player[i]->gettFitness())) )
				{
					RACE* temp;
					temp=player[i];
					player[i]=player[j];
					player[j]=temp;
				}*/


//		qsort(player[i*16],MAX_PROGRAMS/16,sizeof(RACE),compare);

/*	for(i=7;i--;)
	{
		int p1=rand()%(MAX_PROGRAMS/16);
		int p2=rand()%(MAX_PROGRAMS/16);
		int c1=rand()%(MAX_PROGRAMS/16);
		int c2=c1;
		while(c1==c2)
			c2=rand()%(MAX_PROGRAMS/16);
		player[p1*16]->crossOver(player[p2*16],player[c1*16+7],player[c2*16+7]);
	}*/
	
		for(i=0;i<MAX_PROGRAMS/2;i++)
			for(j=0;j<i;j++)
				if((player[i]->getpFitness()>player[j]->getpFitness())||
				  ((player[i]->getpFitness()==player[j]->getpFitness())&&(player[i]->getsFitness()>player[j]->getsFitness()))||
				  ((player[i]->getpFitness()==player[j]->getpFitness())&&(player[i]->getsFitness()==player[j]->getsFitness())&&(player[i]->gettFitness()>player[j]->gettFitness())) )
				{
					RACE* temp;
					temp=player[i];
					player[i]=player[j];
					player[j]=temp;
				}

		for(i=MAX_PROGRAMS/2;i<MAX_PROGRAMS;i++)
			for(j=MAX_PROGRAMS/2;j<i;j++)
				if((player[i]->getpFitness()>player[j]->getpFitness())||
				  ((player[i]->getpFitness()==player[j]->getpFitness())&&(player[i]->getsFitness()>player[j]->getsFitness()))||
				  ((player[i]->getpFitness()==player[j]->getpFitness())&&(player[i]->getsFitness()==player[j]->getsFitness())&&(player[i]->gettFitness()>player[j]->gettFitness())) )
				{
					RACE* temp;
					temp=player[i];
					player[i]=player[j];
					player[j]=temp;
				}

//		qsort(player[0],MAX_PROGRAMS/2,sizeof(RACE),compare);
//		qsort(player[MAX_PROGRAMS/2],MAX_PROGRAMS/2,sizeof(RACE),compare);

		for(i=10;i--;)
		{
			t=rand()%(MAX_PROGRAMS/4)+MAX_PROGRAMS/4;
			for(j=0;j<MAX_LENGTH;j++)
			{
				player[t]->Code[0][j]=player[0]->Code[0][j];
				player[t]->Code[1][j]=player[0]->Code[1][j];
//				memcpy(player[t]->Code[0],player[0]->Code[0],MAX_LENGTH); 
//				memcpy(player[t]->Code[1],player[0]->Code[1],MAX_LENGTH);
			}
		}  

		for(i=10;i--;)
		{
			t=rand()%(MAX_PROGRAMS/4)+MAX_PROGRAMS/4+MAX_PROGRAMS/2;
			for(j=0;j<MAX_LENGTH;j++)
			{
				player[t]->Code[0][j]=player[MAX_PROGRAMS/2]->Code[0][j];
				player[t]->Code[1][j]=player[MAX_PROGRAMS/2]->Code[1][j];
			}
//			memcpy(player[t]->Code[0],player[0]->Code[0],MAX_LENGTH); 
//			memcpy(player[t]->Code[1],player[0]->Code[1],MAX_LENGTH);
		}

		for(j=0;j<2;j++)
		{
			if((player[j*MAX_PROGRAMS/2]->getpFitness()>anaplayer[j]->getMaxpFitness())||((player[j*MAX_PROGRAMS/2]->getpFitness()>=anaplayer[j]->getMaxpFitness())&&(player[j*MAX_PROGRAMS/2]->getsFitness()>anaplayer[j]->getMaxsFitness()))|| ((player[j*MAX_PROGRAMS/2]->getpFitness()>=anaplayer[j]->getMaxpFitness())&&(player[j*MAX_PROGRAMS/2]->getsFitness()>=anaplayer[j]->getMaxsFitness())&&(player[j*MAX_PROGRAMS/2]->gettFitness()>anaplayer[j]->getMaxtFitness())))
			{
				if(player[j*MAX_PROGRAMS/2]->gettFitness()>anaplayer[j]->getMaxtFitness())
					anaplayer[j]->setMaxtFitness(player[j*MAX_PROGRAMS/2]->gettFitness());
				if(player[j*MAX_PROGRAMS/2]->getsFitness()>anaplayer[j]->getMaxsFitness())
				{
					anaplayer[j]->setMaxsFitness(player[j*MAX_PROGRAMS/2]->getsFitness());
					anaplayer[j]->setMaxtFitness(player[j*MAX_PROGRAMS/2]->gettFitness());
				}
				if(player[j*MAX_PROGRAMS/2]->getpFitness()>anaplayer[j]->getMaxpFitness())
				{
					anaplayer[j]->setMaxpFitness(player[j*MAX_PROGRAMS/2]->getpFitness());
					anaplayer[j]->setMaxsFitness(player[j*MAX_PROGRAMS/2]->getsFitness());
					anaplayer[j]->setMaxtFitness(player[j*MAX_PROGRAMS/2]->gettFitness());
				}
				anaplayer[j]->setUnchangedGenerations(0);
				for(t=0;t<MAX_LENGTH;t++)
				{
					anaplayer[j]->Code[0][t]=player[j*MAX_PROGRAMS/2]->Code[0][t];
					anaplayer[j]->Code[1][t]=player[j*MAX_PROGRAMS/2]->Code[1][t];
					//memcpy(anaplayer[j]->Code[0],player[j*MAX_PROGRAMS/2]->Code[0],MAX_LENGTH*4);
					//memcpy(anaplayer[j]->Code[1],player[j*MAX_PROGRAMS/2]->Code[1],MAX_LENGTH*4);
				}
				anaplayer[j]->resetData();
				anaplayer[j]->resetLocations();
				anaplayer[j]->calculate();
			}
			anaplayer[j]->setUnchangedGenerations(anaplayer[j]->getUnchangedGenerations()+1);
			anaplayer[j]->setGeneration(anaplayer[j]->getGeneration()+1);
			if(anaplayer[j]->getUnchangedGenerations()>ga->maxGenerations)
			{
				for(i=MAX_PROGRAMS/2;i--;)
					player[i+j*MAX_PROGRAMS/2]->resetGeneCode();
				anaplayer[j]->setRun(anaplayer[j]->getRun()+1);
				anaplayer[j]->setGeneration(0);
				anaplayer[j]->setMaxpFitness(0);
				anaplayer[j]->setMaxsFitness(0);
				anaplayer[j]->setMaxtFitness(0);
				anaplayer[j]->setUnchangedGenerations(0);		
				//TODO: Saven!
			}
		}
//TODO: Fehler: Die Commandcenter sammeln sich aus irgend einem Grunde an!

if((anaplayer[0]->getMaxpFitness()>anaplayer[1]->getMaxpFitness())||((anaplayer[0]->getMaxpFitness()>=anaplayer[1]->getMaxpFitness())&&(anaplayer[0]->getMaxsFitness()>anaplayer[1]->getMaxsFitness()))|| ((anaplayer[0]->getMaxpFitness()>=anaplayer[1]->getMaxpFitness())&&(anaplayer[0]->getMaxsFitness()>=anaplayer[1]->getMaxsFitness())&&(anaplayer[0]->getMaxtFitness()>anaplayer[1]->getMaxtFitness())))
	return(anaplayer[0]);
else return(anaplayer[1]);
};

SOUP::SOUP()
{
	run_number=0;
	playerInitialized=0;
	mapInitialized=0;
	goalCount=0;
	gaInitialized=0;
	goalsInitialized=0;

};

SOUP::~SOUP()
{
	int i;
	if(playerInitialized)
	{
		for(i=0;i<MAX_PROGRAMS;i++)
			delete player[i];
		delete anaplayer[0];
		delete anaplayer[1];
	};

};
