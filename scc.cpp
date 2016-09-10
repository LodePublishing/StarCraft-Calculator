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
	ifstream file ("goal_z.txt", ios::in|ios::binary|ios::ate);
	ofstream out_file("bo_z.txt");

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
		Goal_Harvested_Mins+=(goal[i].what*stats[i].mins)+(stats[goal[i].what].need==2)*50;
	}

	for(i=0;i<BUILDING_TYPES;i++)
		if(goal[i].what>0)
		{
			if(stats[i].extractor==1) Ziel[EXTRACTOR]=1;
			if(stats[i].lair==1) Ziel[LAIR]=1;
			if(stats[i].den==1) Ziel[HYDRALISK_DEN]=1;
			if(stats[i].evo==1)	Ziel[EVOLUTION_CHAMBER]=1;
			if(stats[i].queens==1) Ziel[QUEENS_NEST]=1;
			if(stats[i].spire==1) Ziel[SPIRE]=1;
			if(stats[i].hive==1) Ziel[HIVE]=1;
			if(stats[i].ultra==1) Ziel[ULTRALISK_CAVERN]=1;
			if(stats[i].defiler==1) Ziel[DEFILER_MOUND]=1;
			if(stats[i].greaterspire==1) Ziel[GREATER_SPIRE]=1;
		}

	for(i=0;i<BUILDING_TYPES;i++)
		if(goal[i].what>0)
			Ziel[i]=1;	

	if(goal[SUNKEN_COLONY].what>0) Ziel[CREEP_COLONY]=1;
	if(goal[SPORE_COLONY].what>0)
	{
		Ziel[CREEP_COLONY]=1;
		Ziel[EVOLUTION_CHAMBER]=1;
	}

	Ziel[OVERLORD]=1;
	Ziel[DRONE]=1;
	Ziel[SPAWNING_POOL]=1;
	Ziel[EXTRACTOR]=1;
	Ziel[HATCHERY]=1;
	Ziel[CREEP_COLONY]=1;
	Ziel[ONE_MINERAL_DRONE_TO_GAS]=1;
	Ziel[ONE_GAS_DRONE_TO_MINERAL]=1;
	Ziel[BREAK_UP_BUILDING]=1;

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

	printf("Welcome to the StarCraft Evolution Chamber!\n");
	printf("May the BO be with you ;-)\n");
	printf("Check the ""goal_z.txt"" file to change goals of the BO\n");
	if((Max_Time==0)||(Max_Time>1800))
	{
		printf("Max_Time out of Range, please check ""goal_z.txt"", first number in file (use at maximum 30 minutes))\n");
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
	printf("Goals (as stated in ""goal_z.txt"")\n");
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
	printf("Press any key to cancel calculation. You will find then a solution in bo_z.txt.");
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
		//printf("                                                                               \n");
		//printf("                                                                               ");

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
	printf(" You can find the Zerg Build Order in the ""bo_z.txt""\n");
	printf(" Brought to you by clawsoftware.de\n");
	printf("  Give it to all your friends :-)");
	printf("\n\n\n\n\n\n\n\n");

	y=0;
	if(run>0)
	{
		afit=0;
		for(x=0;x<RUNNINGS;x++)
			if((Save[x]->fitness>afit)&&(Save[y]->timer<Max_Time))
			{
				afit=Save[x]->fitness;
				y=x;
			}
	}

	out_file<<"StarCraft Evolution Chamber by ClawSoftware.de\n\n";
	out_file<<"Build Order of best Individual:\n";
	out_file<<"Fitness: "<<Save[y]->fitness<<"\n";
	out_file<<"Time used: "<<Save[y]->timer/60<<":"<<Save[y]->timer%60<<"\n";	

	for(i=0;i<MAX_LENGTH;i++)
		if((Save[y]->timep[i]<Save[y]->timer)&&(Build_Av[Save[y]->program[i]]<BUILDING_TYPES)&&((Save[y]->timep[i]>0)||(i==0)))
				out_file<<"["<<(Save[y]->timep[i]+0)/60<<":"<<(Save[y]->timep[i]+0)%60<<"] "<<stats[Build_Av[Save[y]->program[i]]].name<<"\n";

	for(i=0;i<BUILDING_TYPES;i++)
		if(Save[y]->force[i]>0)
			out_file<<stats[i].name<<" : "<<(Save[y]->force[i]+0)<<"\n";
	out_file<<"Harvested Minerals: "<<(Save[y]->harvested_mins+0)<<"\n";
	out_file<<"Harvested Gas: "<<(Save[y]->harvested_gas+0)<<"\n";		

if(run>0)
	//Alle runs ausgeben!
	for(x=0;x<run;x++)
		if((Save[x]->timer<Max_Time)||(y!=x))			
		{
			out_file<<"\n----------------------------------------------------------\n\n";
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
