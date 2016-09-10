#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>
#include <malloc.h>

#include "terra.h"
#include "zerg.h"
#include "protoss.h"

unsigned short run,rfit;

const COORD coord={0,0};
const coord2={20,22};
const c11={1,6};
const c12={1,7};
const c13={1,8};
const c14={1,9};
const c21={10,6};
const c22={10,7};
const c23={10,8};
const c24={10,9};
int main(int argc, char* argv[])
{
	unsigned char l,race,counter,Detailed_Info,calc;
	char I[11],O[9];
	unsigned short k,n,pos,old_time,old_fit,old;
	unsigned char * buffer;
	long size;
	signed char calc_i,error;
	srand(time(NULL));
	for(i=0;i<1000;i++)
		j=rand()%2;
	j=0;

/*		if(argc<2)
	{
		printf("Not enough arguments!\n");
		printf("Use: ""scc.exe P"" for Protoss, ""scc.exe T"" for Terran or ""scc.exe Z"" for Zerg\n");
		printf("Remember that the goals are in goal_p.txt, goal_t.txt and goal_z.txt\n");
		printf("At the end the program will create a bo_p.txt/bo_t.txt/bo_z.txt\n");
		printf("\n");
		printf("Press any key...\n");
		while(kbhit()==0);
		l=getch();
		return 1;
	}*/

	
	race=5;
	if(argc>1)
	{
	if((strcmp(argv[1],"T")==0)||(strcmp(argv[1],"t")==0))
		race=0;
	else if((strcmp(argv[1],"P")==0)||(strcmp(argv[1],"p")==0))
		race=1;
	else if((strcmp(argv[1],"Z")==0)||(strcmp(argv[1],"z")==0))
		race=2;
	}
	if(race==5)
	{
		printf("Press 1 for Terra, 2 for Protoss or 3 for Zerg.\n");
		printf("You could also call the program directly with a parameter (t,p,z).\n");
		while(race==5)
		{
				switch(getch()-48)
				{
					case 1:race=0;break;
					case 2:race=1;break;
					case 3:race=2;break;
				}
		}
	}
	switch(race)
	{
		case 0:sprintf(I,"goal_t.txt");sprintf(O,"bo_t.txt");break;
		case 1:sprintf(I,"goal_p.txt");sprintf(O,"bo_p.txt");break;
		case 2:sprintf(I,"goal_z.txt");sprintf(O,"bo_z.txt");break;
		default:printf("not enough arguments");return 0;break;
	}
	
/*		printf("Wrong arguments!\n");
		printf("Use: ""scc.exe P"" for Protoss, ""scc.exe T"" for Terran or ""scc.exe Z"" for Zerg\n");
		printf("Remember that the goals are in goal_p.txt, goal_t.txt and goal_z.txt\n");
		printf("At the end the program will create a bo_p.txt/bo_t.txt/bo_z.txt\n");
		printf("\n");
		printf("Press any key...\n");
		while(kbhit()==0);
		l=getch();
		return 1;
	}*/



	generation=0;
	for(i=0;i<60;i++)
	{
		goal[i].what=0;
		goal[i].time=0;
		Ziel[i]=0;
	}
	

	Attack=20;
	Time_to_Enemy=9999;
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

	ifstream file (I, ios::in|ios::binary|ios::ate);
	ofstream out_file(O);

	size = file.tellg();
	file.seekg (0, ios::beg);
	buffer = new unsigned char [size];
	file.read (buffer, size);
	file.close();

	Detailed_Info=20;

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
			{
				if((buffer[n+2]>=48)&&(buffer[n+2]<58))
				{
					Max_Generations=(buffer[n]-48)*100+(buffer[n+1]-48)*10+(buffer[n+2]-48);
					n+=2;
				} else
				
				if((buffer[n+1]>=48)&&(buffer[n+1]<58))
				{
					Max_Generations=(buffer[n]-48)*10+(buffer[n+1]-48);
					n++;
				}
				else
					Max_Generations=(buffer[n]-48);
			}
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
			else if(Detailed_Info==20)
				Detailed_Info=(buffer[n]-48);
			else if(Attack==20)
				Attack=(buffer[n]-48);
			else if(Time_to_Enemy==9999)
			{
				if((buffer[n+2]>=48)&&(buffer[n+2]<58))
				{
					Time_to_Enemy=(buffer[n]-48)*100+(buffer[n+1]-48)*10+(buffer[n+2]-48);
					n+=2;
				} else
				
				if((buffer[n+1]>=48)&&(buffer[n+1]<58))
				{
					Time_to_Enemy=(buffer[n]-48)*10+(buffer[n+1]-48);
					n++;
				}
				else
					Time_to_Enemy=(buffer[n]-48);
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

	error=0;

	for(i=0;i<60;i++)
	{
		if((stats[race][i].type==3)&&(goal[i].what>1))
		{
			printf("- Error in %s (Entry %s): Set researches to 1 at maximum.\n",I,stats[race][i].name);
			printf("               Taking ""1"" instead of %i...\n",goal[i].what);
			goal[i].what=1;
			error=1;
		}
	}

	if((Max_Time==0)||(Max_Time>2700))
	{
		printf(" - Max_Time out of Range, please check ""%s"", first number in file.\n",I);
			printf("               Taking ""45"" (maximum) instead of %i...\n",Max_Time);
		Max_Time=2700;
	}

	if(error==1)
	{
		printf("\n");
		printf("Press any key to continue . . .\n");
		error=getch();
	}


	Player_Terra playert[MAX_PLAYER];
	Player_Terra Savet[RUNNINGS];
	Player_Protoss playerp[MAX_PLAYER];
	Player_Protoss Savep[RUNNINGS];
	Player_Zerg playerz[MAX_PLAYER];
	Player_Zerg Savez[RUNNINGS];
	
	RACE * tempp;
	RACE * Save[RUNNINGS];
	RACE * player[MAX_PLAYER];
	
	if(race==0)
	{
		for(l=0;l<MAX_PLAYER;l++)
			player[l]=&playert[l];
		for(l=0;l<RUNNINGS;l++)
			Save[l]=&Savet[l];
	}
	else if(race==1)
	{
		for(l=0;l<MAX_PLAYER;l++)
			player[l]=&playerp[l];
		for(l=0;l<RUNNINGS;l++)
			Save[l]=&Savep[l];
	}
	else 
	{
		for(l=0;l<MAX_PLAYER;l++)
			player[l]=&playerz[l];
		for(l=0;l<RUNNINGS;l++)
			Save[l]=&Savez[l];
	}

	player[0]->Set_Goals();//~~~~ vielleicht 3 eigene funktionen machen :| braucht ja net jeder player


//Air Defense, Ground Defense faktor noch rein

	for(i=0;i<Max_Build_Types;i++)
		Build_Bv[Build_Av[i]]=i;

	for(l=0;l<MAX_PLAYER;l++)
		player[0]->Restart();



	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P
	SetConsoleCursorPosition(hStdOut,coord);

	printf("Welcome to the StarCraft Evolution Chamber v1.01a!\n");
	printf("Check the ""%s"" file to change goals of the BO\n",I);
	printf("If you are new to this program, try to read the readme.txt\n");
	printf("Oh and remember: all times are that of a speed 5 game...\n");
	printf("The program will need to run through all 5 runnings to get a good result.\n");
	if(Detailed_Info==1)
		printf("Detailed Information will be in the ""%s"" file.\n",O);
	if(Attack==1)
	{
		printf("Units will be send directly to the enemy (i.e. higher build time).\n");
		printf("A unit need %i seconds to reach the enemy.\n",Time_to_Enemy);
	}
	

	printf("\n");
	printf("Goals (as stated in ""%s"")\n",I);
	for(i=0;i<building_types;i++)
		if(goal[i].what>0)
			printf("- %20s : %i   (%s) \n",stats[race][i].name,goal[i].what,kurz[race][i].b);

	l=getch();
	calc=176;
	calc_i=1;

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P

	SetConsoleCursorPosition(hStdOut,coord2);
	printf("Evolution Chamber v1.01 - Brought to you by clawsoftware.de\n");
	printf("                 Press any key to cancel calculation.");
	SetConsoleCursorPosition(hStdOut,coord);

	old_time=1800;
	old_fit=0;

	while( (kbhit()==0) && (run<RUNNINGS))
	{
		SetConsoleCursorPosition(hStdOut,coord);

		x=0;

		for(l=0;l<MAX_PLAYER;l++)
			player[l]->Init();

		for(l=1;l<MAX_PLAYER;l++)
			player[l]->Mutate();
	
		for(l=0;l<MAX_PLAYER;l++)
			player[l]->Calculate();

		for(i=0;i<MAX_PLAYER-3;i++)
			for(j=0;j<MAX_PLAYER-i-1;j++)
				if(player[j]->fitness<player[j+1]->fitness)
				{
					tempp=player[j];
					player[j]=player[j+1];
					player[j+1]=tempp;
				}	

		printf("Calculating [%c]         Status:",(calc+0));
		if(player[0]->timer<1800)
		{
			if(old_time>player[0]->timer)
			printf(" found better solution . . .          \n");
				else
			printf(" optimizing build order . . .         \n");
		}
		else
		{
			if((old_fit/100)<(player[0]->fitness/100))
			printf(" another goal completed . . .		  \n");
				else
			printf(" searching for possible solution . . .\n");
		}
		
		old_time=player[0]->timer;
		old_fit=player[0]->fitness;
		calc+=calc_i;
		if(calc>178)
		{
			calc=177;
			calc_i=-calc_i;
		}
		if(calc<176)
		{
			calc=177;
			calc_i=-calc_i;
		}


		if(player[0]->fitness>afit)
		{
			afit=player[0]->fitness;
			rfit=0;
//			Mut_Rate=MRate;
		}
		
		generation++;
		rfit++;
//		if(Mut_Rate>10)
//			Mut_Rate--;
		

		printf("\n%i runs remaining (this run %i+ generations remaining)   \n",RUNNINGS-run,Max_Generations-rfit);
		printf("                           Overview Generation %i \n",generation);
		printf("[fitness] [time]\n");
		printf("----------------\n");

		SetConsoleCursorPosition(hStdOut,c11);printf("%4.4i",player[0]->fitness);
		SetConsoleCursorPosition(hStdOut,c12);printf("%4.4i",player[MAX_PLAYER/16]->fitness);
		SetConsoleCursorPosition(hStdOut,c13);printf("%4.4i",player[MAX_PLAYER/8]->fitness);
		SetConsoleCursorPosition(hStdOut,c14);printf("%4.4i",player[MAX_PLAYER/4]->fitness);

		SetConsoleCursorPosition(hStdOut,c21);if(player[0]->timer<1800) printf("%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);else printf(" ---- ");
		SetConsoleCursorPosition(hStdOut,c22);if(player[MAX_PLAYER/16]->timer<1800) printf("%.2i:%.2i",player[MAX_PLAYER/16]->timer/60,player[MAX_PLAYER/16]->timer%60);else printf(" ---- ");
		SetConsoleCursorPosition(hStdOut,c23);if(player[MAX_PLAYER/8]->timer<1800) printf("%.2i:%.2i",player[MAX_PLAYER/8]->timer/60,player[MAX_PLAYER/8]->timer%60);else printf(" ---- ");
		SetConsoleCursorPosition(hStdOut,c24);if(player[MAX_PLAYER/4]->timer<1800) printf("%.2i:%.2i",player[MAX_PLAYER/4]->timer/60,player[MAX_PLAYER/4]->timer%60);else printf(" ---- ");

		printf("\n\n");
		printf("   [Build Order of the best individual]");

		x=0;
		for(i=0;i<player[0]->length;i++)
		{
			COORD c={((x/10)*12),12+x%10};
			x++;
			SetConsoleCursorPosition(hStdOut,c);
			if((Build_Av[player[0]->program[i]]<building_types)&&(player[0]->timep[i]<player[0]->timer))
				printf("%2i.%s",x,kurz[race][Build_Av[player[0]->program[i]]].b);
			else printf("        ");
		}
		for(i=player[0]->length;i<MAX_LENGTH;i++)
		{
			COORD c={((x/10)*12),12+x%10};
			x++;
			SetConsoleCursorPosition(hStdOut,c);
			printf("        ");
		}

		for(k=1;k<MAX_PLAYER;k++)
			if(player[k]->fitness<player[0]->fitness)
				for(i=0;i<MAX_LENGTH;i++)
					player[k]->program[i]=player[0]->program[i];
	
	    if(rfit>=Max_Generations)
		{
//			Mut_Rate=MRate;
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
			Save[run]->mins=player[0]->mins;
			Save[run]->gas=player[0]->gas;
			Save[run]->length=player[0]->length;

			for(i=0;i<building_types;i++)
				Save[run]->force[i]=player[0]->force[i];

			for(l=0;l<MAX_PLAYER;l++)
				player[l]->Restart();

			old_time=1800;
			old_fit=0;
			run++;
		}
	} // end while...

	//Output

	if(run<RUNNINGS)
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
		Save[run]->mins=player[0]->mins;
		Save[run]->gas=player[0]->gas;
		Save[run]->length=player[0]->length;

		for(i=0;i<building_types;i++)
			Save[run]->force[i]=player[0]->force[i];
	}

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P
	printf("Calculating completed.\n\n");
	printf(" The build order was saved in the file ""%s"".\n\n",O);
	printf(" Brought to you by clawsoftware.de\n");
	printf("\n\n\n\n\n\n\n\n\n\n");

	y=0;
	if(run>0)
	{
		afit=0;
		for(x=0;x<RUNNINGS;x++)
			if((Save[x]->fitness>afit)&&(Save[x]->timer<Max_Time))
			{
				afit=Save[x]->fitness;
				y=x;
			}
	}

	out_file<<"StarCraft Evolution Chamber by ClawSoftware.de\n";
	out_file<<"--------------------------------------------------\n\n";
	out_file<<"Build Order of best Individual:\n";
	out_file<<"Time used: "<<Save[y]->timer/60<<":"<<Save[y]->timer%60<<"\n";	

	old=200;
	counter=1;
	for(i=0;i<=Save[y]->length;i++)
	{
		if(Detailed_Info==0)
		{
			while(((Save[y]->timep[i]>=Save[y]->timer)||(Build_Av[Save[y]->program[i]]>=building_types))&&(i<MAX_LENGTH-1))
				i++;
			if(old==Build_Av[Save[y]->program[i]]) counter++;
			else if(old<200)
			{
				out_file<<counter+0<<" "<<stats[race][old].name<<"\n";
				counter=1;
				old=Build_Av[Save[y]->program[i]];
			}
			else
				old=Build_Av[Save[y]->program[i]];
		}
		else
		if((Save[y]->timep[i]<Save[y]->timer)&&(Build_Av[Save[y]->program[i]]<building_types)&&((i==0)||(Save[y]->timep[i]>0)))
				out_file<<"["<<(Save[y]->timep[i]+0)/60<<":"<<(Save[y]->timep[i]+0)%60<<"] "<<stats[race][Build_Av[Save[y]->program[i]]].name<<"\n";
	}

	for(i=0;i<building_types;i++)
		if(Save[y]->force[i]>0)
			out_file<<stats[race][i].name<<" : "<<(Save[y]->force[i]+0)<<"\n";
	out_file<<"Harvested Minerals: "<<(unsigned short)(Save[y]->harvested_mins+0)<<"\n";
	out_file<<"Harvested Gas: "<<(unsigned short)(Save[y]->harvested_gas+0)<<"\n";		
	out_file<<"Minerals after completing last task: "<<(unsigned short)(Save[y]->mins+0)<<"\n";
	out_file<<"Gas after completing last task: "<<(unsigned short)(Save[y]->gas+0)<<"\n";
	out_file<<"\n";
	out_file<<"Other possible solutions: \n";
	if(run>0)
	//Alle runs ausgeben!
	for(x=0;x<run;x++)
		if((Save[x]->timer<Max_Time)&&(y!=x)&&(Save[x]->timer!=Save[y]->timer))			
		{
			out_file<<"\n";
			out_file<<"\n----------------------------------------------------------\n\n";
			out_file<<"Time used: "<<Save[x]->timer/60<<":"<<Save[x]->timer%60<<"\n";	

			old=200;
			counter=1;
			for(i=0;i<=Save[x]->length;i++)
			{
				if(Detailed_Info==0)
				{
					while(((Save[x]->timep[i]>=Save[x]->timer)||(Build_Av[Save[x]->program[i]]>=building_types))&&(i<MAX_LENGTH-1))
						i++;
					if(old==Build_Av[Save[x]->program[i]]) counter++;
					else if(old<200)
					{
						out_file<<counter+0<<" "<<stats[race][old].name<<"\n";
						counter=1;
						old=Build_Av[Save[x]->program[i]];
					}
					else
						old=Build_Av[Save[x]->program[i]];
				}
				else
				if((Save[x]->timep[i]<Save[x]->timer)&&(Build_Av[Save[x]->program[i]]<building_types)&&((i==0)||(Save[x]->timep[i]>0)))
					out_file<<"["<<(Save[x]->timep[i]+0)/60<<":"<<(Save[x]->timep[i]+0)%60<<"] "<<stats[race][Build_Av[Save[x]->program[i]]].name<<"\n";
			}
			
			for(i=0;i<building_types;i++)
				if(Save[x]->force[i]>0)
					out_file<<stats[race][i].name<<" : "<<(Save[x]->force[i]+0)<<"\n";

			out_file<<"Harvested Minerals: "<<(unsigned short)(Save[x]->harvested_mins+0)<<"\n";
			out_file<<"Harvested Gas: "<<(unsigned short)(Save[x]->harvested_gas+0)<<"\n";	
			out_file<<"Minerals after completing last task: "<<(unsigned short)(Save[x]->mins+0)<<"\n";
			out_file<<"Gas after completing last task: "<<(unsigned short)(Save[x]->gas+0)<<"\n";
		}

	out_file.close();

	for(l=0;l<MAX_PLAYER;l++)
		player[l]=NULL;
	for(l=0;l<RUNNINGS;l++)
		Save[l]=NULL;
	tempp=NULL;

	x=getch();
	x=getch();
	return 0;
}


//In Output noch Supply, uebriges Gas, Mins rein