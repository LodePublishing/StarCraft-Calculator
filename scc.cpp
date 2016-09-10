// Protoss Templar Archive

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>
#include <malloc.h>
#include "main.h"

unsigned short run,rfit;
Player *player[MAX_PLAYER];
Player *tempp;
Player *Save[RUNNINGS];

const COORD coord={0,0},coord2={25,22},c11={3,8},c12={3,9},c13={3,10},c14={3,11},c15={3,12},c21={12,8},c22={12,9},c23={12,10},c24={12,11},c25={12,12},c31={22,8},c32={22,9},c33={22,10},c34={22,11},c35={22,12};
int main(int argc, char* argv[])
{
	unsigned char l;
	unsigned short k,n,pos;
	unsigned char * buffer;
	long size;

	generation=0;
	for(i=0;i<BUILDING_TYPES;i++)
	{
		goal[i].what=0;
		goal[i].time=0;
		Ziel[i]=0;

	}
	Goal_Harvested_Mins=0;
	Goal_Harvested_Gas=0;

	n=1;
	pos=0;
	Max_Time=0;
	Max_Generations=0;
	Max_Vespene=0;
	Mutations=0;
	Mut_Rate=0;
	Max_Build_Types=0;
	run=0;
	afit=0;
	rfit=0;

	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));  
	ifstream file ("goal_p.txt", ios::in|ios::binary|ios::ate);
	ofstream out_file("bo_p.txt");
	size = file.tellg();
	file.seekg (0, ios::beg);
	buffer = new unsigned char [size];
	file.read (buffer, size);
	file.close();

	while(n<size)
	{
		if((buffer[n]>=48)&&(buffer[n]<58))
		{
			if(Max_Time==0)
			{
				if((buffer[n+1]>=48)&&(buffer[n+1]<58))
				{
					Max_Time=(buffer[n]-48)*600+(buffer[n+1]-48)*60;
					n++;
				}
				else
					Max_Time=(buffer[n]-48)*60;
			}
			else if(Max_Generations==0)
				Max_Generations=(buffer[n]-48)*50+50;
			else if(Max_Vespene==0)
				Max_Vespene=(buffer[n]-48);
			else if(Mutations==0)
			{
				if((buffer[n+1]>=48)&&(buffer[n+1]<58))
				{
					Mutations=(buffer[n]-48)*10+(buffer[n+1]-48);
					n++;
				}
				else
					Mutations=(buffer[n]-48);
			}
			else if(Mut_Rate==0)
			{
				if((buffer[n+1]>=48)&&(buffer[n+1]<58))
				{
					Mut_Rate=(buffer[n]-48)*10+(buffer[n+1]-48);
					n++;
				}
				else
					Mut_Rate=(buffer[n]-48);
			}
			else
			{
				if((buffer[n+1]>=48)&&(buffer[n+1]<58))
				{
					goal[pos].what=(buffer[n]-48)*10+(buffer[n+1]-48);
					n++;
				}
				else
					goal[pos].what=buffer[n]-48;
				pos++;
			}
		}
		n++;
	}


//Air Defense, Ground Defense faktor noch rein

	for(i=0;i<BUILDING_TYPES;i++)
	{
		Goal_Harvested_Gas+=(goal[i].what*stats[i].gas);
		Goal_Harvested_Mins+=(goal[i].what*stats[i].mins);
	}

	for(i=0;i<BUILDING_TYPES;i++)
		if(goal[i].what>0)
			Ziel[i]=1;	

	Ziel[PYLON]=1;
	Ziel[PROBE]=1;
	Ziel[NEXUS]=1;
	Ziel[GATEWAY]=1;
	if(Goal_Harvested_Gas>0)
	{
		Ziel[ASSIMILATOR]=1;
		Ziel[ONE_MINERAL_PROBE_TO_GAS]=1;
		Ziel[ONE_GAS_PROBE_TO_MINERAL]=1;
	}


if((goal[ARBITER].what>0)||(goal[RECALL].what>0)||(goal[STASIS_FIELD].what>0)||(goal[KHAYDARIN_CORE].what>0))
{
	Ziel[CYBERNETICS_CORE]=1;
	Ziel[STARGATE]=1;
	Ziel[CITADEL_OF_ADUN]=1;
	Ziel[TEMPLAR_ARCHIVES]=1;
	Ziel[ARBITER_TRIBUNAL]=1;
}
if((goal[DARK_TEMPLAR].what>0)||(goal[HIGH_TEMPLAR].what>0)||(goal[PSIONIC_STORM].what>0)||(goal[HALLUCINATION].what>0)||(goal[ARGUS_TALISMAN].what>0)||(goal[KHAYDARIN_AMULET].what>0)||(goal[MIND_CONTROL].what>0)||(goal[MAELSTROM].what>0))
{
	Ziel[CYBERNETICS_CORE]=1;
	Ziel[CITADEL_OF_ADUN]=1;
	Ziel[TEMPLAR_ARCHIVES]=1;
}
if((goal[DRAGOON].what>0)||(goal[STARGATE].what>0)||(goal[ROBOTICS_FACILITY].what>0)||(goal[CITADEL_OF_ADUN].what>0)||(goal[AIR_WEAPONS].what>0)||(goal[PLATING].what>0)||(goal[SINGULARITY_CHARGE].what>0))
	Ziel[CYBERNETICS_CORE]=1;

if((goal[LEG_ENHANCEMENTS].what>0)||(goal[TEMPLAR_ARCHIVES].what>0))
{
	Ziel[CYBERNETICS_CORE]=1;
	Ziel[CITADEL_OF_ADUN]=1;
}

if(goal[DARK_ARCHON].what>0)
{
	Ziel[DARK_TEMPLAR]=1;
	Ziel[TEMPLAR_ARCHIVES]=1;
	Ziel[CITADEL_OF_ADUN]=1;
	Ziel[CYBERNETICS_CORE]=1;
}


if(goal[ARCHON].what>0)
{
	Ziel[HIGH_TEMPLAR]=1;
	Ziel[TEMPLAR_ARCHIVES]=1;
	Ziel[CITADEL_OF_ADUN]=1;
	Ziel[CYBERNETICS_CORE]=1;
}

if((goal[REAVER].what>0)||(goal[SCARAB_DAMAGE].what>0)||(goal[REAVER_CAPACITY].what>0)||(goal[GRAVITIC_DRIVE].what>0))
{
	Ziel[ROBOTICS_FACILITY]=1;
	Ziel[ROBOTICS_SUPPORT_BAY]=1;
	Ziel[CYBERNETICS_CORE]=1;
}
if((goal[OBSERVER].what>0)||(goal[SENSOR_ARRAY].what>0)||(goal[GRAVITIC_BOOSTERS].what>0))
{
	Ziel[ROBOTICS_FACILITY]=1;
	Ziel[OBSERVATORY]=1;
	Ziel[CYBERNETICS_CORE]=1;
}
if((goal[CARRIER].what>0)||(goal[ARGUS_JEWEL].what>0)||(goal[APIAL_SENSORS].what>0)||(goal[GRAVITIC_THRUSTERS].what>0)||(goal[DISRUPTION_WEB].what>0)||(goal[CARRIER_CAPACITY].what>0))
{
	Ziel[STARGATE]=1;
	Ziel[FLEET_BEACON]=1;
	Ziel[CYBERNETICS_CORE]=1;
}
if((goal[CORSAIR].what>0)||(goal[SCOUT].what>0)||(goal[FLEET_BEACON].what>0))
{
	Ziel[STARGATE]=1;
	Ziel[CYBERNETICS_CORE]=1;
}
if((goal[SHUTTLE].what>0)||(goal[OBSERVATORY].what>0)||(goal[ROBOTICS_SUPPORT_BAY].what>0))
{
	Ziel[CYBERNETICS_CORE]=1;
	Ziel[ROBOTICS_FACILITY]=1;
}
	
if(goal[ARBITER_TRIBUNAL].what>0)
{
	Ziel[CYBERNETICS_CORE]=1;
	Ziel[STARGATE]=1;
	Ziel[CITADEL_OF_ADUN]=1;
	Ziel[TEMPLAR_ARCHIVES]=1;
}

if((goal[ARMOR].what>0)||(goal[GROUND_WEAPONS].what>0)||(goal[PLASMA_SHIELDS].what>0)||(goal[PHOTON_CANNON].what>0))
	Ziel[FORGE]=1;

	for(i=0;i<BUILDING_TYPES;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}

	for(i=0;i<Max_Build_Types;i++)
		Build_Bv[Build_Av[i]]=i;

		for(l=0;l<MAX_PLAYER;l++)
	{
		player[l]=(Player*)malloc(sizeof(Player));
		player[l]->Restart();
	}
	for(l=0;l<RUNNINGS;l++)
	{
		Save[l]=(Player*)malloc(sizeof(Player));
		Save[l]->Restart();
	}


	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P
	SetConsoleCursorPosition(hStdOut,coord);

	printf("Welcome to the StarCraft Templar Archives!\n");
	printf("May the BO be with you ;-)\n");
	printf("Check the ""goal_p.txt"" file to change goals of the BO\n");
	if((Max_Time==0)||(Max_Time>1800))
	{
		printf("Max_Time out of Range, please check ""goal_p.txt"", first number in file (use at maximum 30 minutes))\n");
		printf("... Continuing using 30 minutes as maximum\n");
		Max_Time=1800;
	}
	else
	printf("Max Time        : %i   \n",Max_Time);
	printf("Max Generations : %i   \n",Max_Generations);
	printf("Max Vespene     : %i   \n",Max_Vespene);
	printf("Mutations       : %i   \n",Mutations);
	printf("Mutation Rate   : %i   \n",Mut_Rate);
	printf("\n");
	printf("Goals (as stated in ""goal_p.txt"")\n");
	for(i=0;i<BUILDING_TYPES;i++)
		if(goal[i].what>0)
			printf("- %s : %i    \n",stats[i].name,goal[i].what);
	printf("\n");
	printf(" Let the calculation begin . . . \n");
	printf(" (Please read the ""readme.txt"" for help)\n");

	l=getch();

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P

	SetConsoleCursorPosition(hStdOut,coord2);
	printf("This is Freeware. Brought to you by clawsoftware.de\n");
	printf("Press any key to cancel calculation. You will find then a solution in bo_terra.txt.");
	SetConsoleCursorPosition(hStdOut,coord);

	printf("Calculating [");
	for(l=0;l<MAX_PLAYER/4;l++)
		printf("%c",176);
	printf("]\n");

	while( (kbhit()==0) && (run<RUNNINGS))
	{
		SetConsoleCursorPosition(hStdOut,coord);
		Fitness_All=0;
		printf("Calculating [");
		x=0;

		for(l=0;l<MAX_PLAYER;l++)
			player[l]->Init();

		for(l=0;l<MAX_PLAYER;l++)
			player[l]->Mutate();
	
		
		for(l=0;l<MAX_PLAYER;l++)
		{
			player[l]->Calculate();
			if(l%4==0) printf("%c",rand()%3+176);
		}
		printf("]\n");

		for(i=0;i<MAX_PLAYER-3;i++)
			for(j=0;j<MAX_PLAYER-i-1;j++)
				if(player[j]->fitness<player[j+1]->fitness)
				{
					tempp=player[j];
					player[j]=player[j+1];
					player[j+1]=tempp;
				}	

		for(i=0;i<MAX_PLAYER;i++)
			Fitness_All+=player[i]->fitness*(MAX_PLAYER-i);
		Fitness_Average=2*Fitness_All/(MAX_PLAYER*MAX_PLAYER);
		if(Fitness_Average>afit)
		{
			afit=Fitness_Average;
			rfit=0;
		}
		
		generation++;
		rfit++;
		printf("\n");
		printf("%i runs remaining (this run at minimum %i generations remaining)   \n",RUNNINGS-run,Max_Generations-rfit);
		printf("\n");
		printf("Overview Generation %i / Average Fitness: %i  (Best: %i)  :         \n",generation,Fitness_Average,afit);
		printf("   \n");

		printf("[fitness]  [time]  [position]\n");
		printf("----------------------------------------\n");

		SetConsoleCursorPosition(hStdOut,c11);printf("%4.4i",player[0]->fitness);
		SetConsoleCursorPosition(hStdOut,c12);printf("%4.4i",player[MAX_PLAYER/16]->fitness);
		SetConsoleCursorPosition(hStdOut,c13);printf("%4.4i",player[MAX_PLAYER/8]->fitness);
		SetConsoleCursorPosition(hStdOut,c14);printf("%4.4i",player[MAX_PLAYER/4]->fitness);
		SetConsoleCursorPosition(hStdOut,c15);printf("%4.4i",player[MAX_PLAYER/2]->fitness);

		SetConsoleCursorPosition(hStdOut,c21);printf("%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);
		SetConsoleCursorPosition(hStdOut,c22);printf("%.2i:%.2i",player[MAX_PLAYER/16]->timer/60,player[MAX_PLAYER/16]->timer%60);
		SetConsoleCursorPosition(hStdOut,c23);printf("%.2i:%.2i",player[MAX_PLAYER/8]->timer/60,player[MAX_PLAYER/8]->timer%60);
		SetConsoleCursorPosition(hStdOut,c24);printf("%.2i:%.2i",player[MAX_PLAYER/4]->timer/60,player[MAX_PLAYER/4]->timer%60);
		SetConsoleCursorPosition(hStdOut,c25);printf("%.2i:%.2i",player[MAX_PLAYER/2]->timer/60,player[MAX_PLAYER/2]->timer%60);	

		SetConsoleCursorPosition(hStdOut,c31);printf("#1");
		SetConsoleCursorPosition(hStdOut,c32);printf("#%i",MAX_PLAYER/16);
		SetConsoleCursorPosition(hStdOut,c33);printf("#%i",MAX_PLAYER/8);
		SetConsoleCursorPosition(hStdOut,c34);printf("#%i",MAX_PLAYER/4);
		SetConsoleCursorPosition(hStdOut,c35);printf("#%i",MAX_PLAYER/2);

		printf("\n");
		printf("   [Build Order of the best individual]");
		//printf("\n");

		x=0;
		for(i=0;i<MAX_LENGTH;i++)
		{
			COORD c={((x/8)*10),14+x%8};
			x++;
			SetConsoleCursorPosition(hStdOut,c);
			if((Build_Av[player[0]->program[i]]<BUILDING_TYPES)&&((player[0]->timep[i]>0)||(i==0))&&(player[0]->timep[i]<player[0]->timer))
				printf("%2i.%s",x,kurz[Build_Av[player[0]->program[i]]].b);
			else printf("        ");

		}

// besser machen, mehr von relativer Fitness abhaengen lassen -> schnellere Evolution (mei... lokale Minima, was solls)
//		Bei den einzelnen Einheiten noch einen konstanten Faktor bei der Buildtime dazuzaehlen, abhaengig von Wegstrecke zum Gegner und Geschwindigkeit!
		for(k=1;k<MAX_PLAYER;k++)
			if(player[k]->fitness<player[0]->fitness)
				for(i=0;i<MAX_LENGTH;i++)
					player[k]->program[i]=player[0]->program[i];
	
	    if(rfit>=Max_Generations)
		{
			rfit=0;
			generation=0;
			for(i=0;i<MAX_LENGTH;i++)
				Save[run]->program[i]=player[0]->program[i];

			for(i=0;i<MAX_LENGTH;i++)
				Save[run]->timep[i]=player[0]->timep[i];

			Save[run]->fitness=player[0]->fitness;
			Save[run]->timer=player[0]->timer;
			Save[run]->harvested_mins=player[0]->harvested_mins;
			Save[run]->harvested_gas=player[0]->harvested_gas;

			for(i=0;i<BUILDING_TYPES;i++)
				Save[run]->force[i]=player[0]->force[i];

			for(l=0;l<MAX_PLAYER;l++)
				player[l]->Restart();
			run++;
		}
	} // end while...

	//Output

	if(run==0)
	{
		for(i=0;i<MAX_LENGTH;i++)
		{
			Save[run]->program[i]=player[0]->program[i];
			Save[run]->timep[i]=player[0]->timep[i];
		}	
		Save[run]->fitness=player[0]->fitness;
		Save[run]->timer=player[0]->timer;
		Save[run]->harvested_mins=player[0]->harvested_mins;
		Save[run]->harvested_gas=player[0]->harvested_gas;	
	
		for(i=0;i<BUILDING_TYPES;i++)
			Save[run]->force[i]=player[0]->force[i];
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P
	printf("Calculating completed.\n");
	printf(" You can find the Protoss Build Order in the ""bo_prot.txt""\n");
	printf(" Brought to you by clawsoftware.de\n");
	printf("\n\n\n\n\n\n\n\n");

	//Alle runs ausgeben!
	for(x=0;x<RUNNINGS;x++)
		if(Save[x]->timer<Max_Time)
		{
			out_file<<"Fitness: "<<Save[x]->fitness<<"\n";
			out_file<<"Time used: "<<Save[x]->timer/60<<":"<<Save[x]->timer%60<<"\n";	

			for(i=0;i<MAX_LENGTH;i++)
				if((Save[x]->timep[i]<Save[x]->timer)&&(Build_Av[Save[x]->program[i]]<BUILDING_TYPES)&&((Save[x]->timep[i]>0)||(i==0)))
						out_file<<"["<<(Save[x]->timep[i]+0)/60<<":"<<(Save[x]->timep[i]+0)%60<<"] "<<stats[Build_Av[Save[x]->program[i]]].name<<"\n";

			for(i=0;i<BUILDING_TYPES;i++)
				if(Save[x]->force[i]>0)
					out_file<<stats[i].name<<" : "<<(Save[x]->force[i]+0)<<"\n";

			out_file<<"Harvested Minerals: "<<(Save[x]->harvested_mins+0)<<"\n";
			out_file<<"Harvested Gas: "<<(Save[x]->harvested_gas+0)<<"\n";	
		}
	out_file.close();

	for(i=0;i<MAX_PLAYER;i++)
		free(player[i]);
	for(i=0;i<RUNNINGS;i++)
		free(Save[i]);
	tempp=NULL;
	x=getch();
	return 0;
}
