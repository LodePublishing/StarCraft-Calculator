// Einmalige Updates auch nur einmal rein! Nur ueber austauschen rein !
// Todo: Debug messages in eigene Funktion!

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "terra.h"
#include "zerg.h"
#include "protoss.h"

using namespace std;

#define clrscr() printf("\033[2J") /* Bildschirm löschen */      
#define gotoxy(x,y) printf("\033[%d;%dH",(y),(x))

RACE * player[MAX_PLAYER];


int main(int argc, char* argv[])
{	
	unsigned short run,rfit,afit;
	unsigned char race,counter,Detailed_Info,calc;
	char I[11],O[9],R[7];
	unsigned short old_time,old_fit,old,s,t,u,generation;
	char * buffer;
	long size;
	unsigned char a,verbose,h1,h2;
	signed char calc_i,error;
	unsigned char timetmp;
	srand(time(NULL));
	clrscr();	
	Init();
	race=5;
	verbose=0;
	h1=argv[1][0];
	h2=argv[2][0];
	
	if(argc>1)
	{
	if((h1=='T')||(h1=='t'))
		race=0;
	else if((h1=='P')||(h1=='p'))
		race=1;
	else if((h1=='Z')||(h1=='z'))
		race=2;
	if((h2=='V')||(h2=='v')||(h1=='V')||(h1=='v'))
		verbose=1;
	}
	
	if(race==5)
	{
		printf("Press 1 for Terra, 2 for Protoss or 3 for Zerg.\n");
		printf("You could also call the program directly with a parameter (t,p,z).\n");
		
		while(race==5)
		{
			a=getchar();		
				switch(a-48)
				{
					case 1:race=0;break;
					case 2:race=1;break;
					case 3:race=2;break;
				}
		}
	}

	printf("Setting Race ... ");
	
	switch(race)
	{
		case 0:sprintf(I,"goal_t.txt");sprintf(O,"bo_t.txt");sprintf(R,"Terran");break;
		case 1:sprintf(I,"goal_p.txt");sprintf(O,"bo_p.txt");sprintf(R,"Protoss");break;
		case 2:sprintf(I,"goal_z.txt");sprintf(O,"bo_z.txt");sprintf(R,"Zerg");break;
		default:printf("not enough arguments");return 0;break;
	}
	printf("[%s] OK\n",R);
	printf("Checking input file [%s]:\n",I);
	generation=0;
	for(s=0;s<60;s++)
	{
		goal[s].what=0;
		goal[s].time=0;
		Ziel[s]=0;
	}
	

	run=0;
	afit=0;
	rfit=0;

	FILE * pFileI;
        pFileI = fopen (I,"rb");
	// Auf Error checken! Evtl nciht da!
	
	printf("File opened... reading...");
	
	fseek (pFileI, 0, SEEK_END);
	size = ftell (pFileI);
	buffer = new char [size];
	fseek (pFileI, 0, SEEK_SET);
	fread(buffer,1,size,pFileI);
	fclose(pFileI);
	printf("File closed, data saved.\n");
	printf("Checking data:\n");
	
	Detailed_Info=20;
	
	s=0;t=0;u=0;
	timetmp=0;

	// auf 3 oder mehr Zahlen checken!
	
	while(s<size)
	{
		if((buffer[s]>=48)&&(buffer[s]<58))
		{
			if(Max_Time==0)
			{
				if((buffer[s+1]>=48)&&(buffer[s+1]<58))
				{
					Max_Time=(buffer[s]-48)*600+(buffer[s+1]-48)*60;
					s++;
				}
				else
					Max_Time=(buffer[s]-48)*60;
				printf("Max Time initialized: %i\n",Max_Time);
			}
			else if(Max_Generations==0)
			{
				if((buffer[s+2]>=48)&&(buffer[s+2]<58))
				{
					Max_Generations=(buffer[s]-48)*100+(buffer[s+1]-48)*10+(buffer[s+2]-48);
					s+=2;
				} else
				
				if((buffer[s+1]>=48)&&(buffer[s+1]<58))
				{
					Max_Generations=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}
				else
					Max_Generations=(buffer[s]-48);
				printf("Max Generations initialized: %i\n",Max_Generations);
			}
			else if(Max_Vespene==0)
			{
				Max_Vespene=(buffer[s]-48);
				printf("Max Vespene Geysirs initialized %i\n", Max_Vespene);
			}
			else if(Mutations==0)
			{
				if((buffer[s+1]>=48)&&(buffer[s+1]<58))
				{
					Mutations=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}
				else
					Mutations=(buffer[s]-48);
				printf("Mutations initialized %i\n", Mutations);
			}
			else if(Mut_Rate==0)
			{
				if((buffer[s+1]>=48)&&(buffer[s+1]<58))
				{
					Mut_Rate=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}
				else
					Mut_Rate=(buffer[s]-48);
				printf("Mutation rate initalized: %i\n",Mut_Rate);
			}
			else if(Detailed_Info==20)
			{
				Detailed_Info=(buffer[s]-48);
				printf("Detailed informations initialized: %i\n",Detailed_Info);
			}
			else if(Attack==20)
			{
				Attack=(buffer[s]-48);
				printf("Attack initialized: %i\n", Attack);
			}
			else if(Time_to_Enemy==9999)
			{
				if((buffer[s+2]>=48)&&(buffer[s+2]<58))
				{
					Time_to_Enemy=(buffer[s]-48)*100+(buffer[s+1]-48)*10+(buffer[s+2]-48);
					s+=2;
				} else
				
				if((buffer[s+1]>=48)&&(buffer[s+1]<58))
				{
					Time_to_Enemy=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}

				else
					Time_to_Enemy=(buffer[s]-48);
				printf("Time to Enemy initialized: %i\n",Time_to_Enemy);
				printf("Reading goals\n");
			}
			else if(timetmp==0)
			{
				printf(".");
				if((buffer[s+1]>=48)&&(buffer[s+1]<58))
				{
					goal[u].what=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}
				else
					goal[u].what=buffer[s]-48;
				timetmp=1;
			}
			else if(timetmp==1)
			{		
			      		
			      if((buffer[s+1]>=48)&&(buffer[s+1]<58))
                              {
                                        goal[u].time=(buffer[s]-48)*10+(buffer[s+1]-48);
                                        s++;
                              }
                              else
	                              goal[u].time=buffer[s]-48;
			      u++;
			      timetmp=0;
			}
		}
		s++;
	}
	free(buffer);
	printf("\nAll data initialized, buffer freed, starting analyzing data:\n");
	error=0;


	for(s=0;s<60;s++)
	{
		if((stats[race][s].type==3)&&(goal[s].what>1))
		{
			printf("- Error in %s (Entry %s): Set researches to 1 at maximum.\n",I,stats[race][s].name);
			printf("               Taking ""1"" instead of %i...\n",goal[s].what);
			goal[s].what=1;
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
	}

	printf("Initializing player models...\n");
	Player_Terra playert[MAX_PLAYER];
	Player_Terra Savet[RUNNINGS];
	Player_Protoss playerp[MAX_PLAYER];
	Player_Protoss Savep[RUNNINGS];
	Player_Zerg playerz[MAX_PLAYER];
	Player_Zerg Savez[RUNNINGS];
	
	RACE * Save[RUNNINGS];
	RACE * tempp; 	
	
	if(race==0)
	{
		for(s=0;s<MAX_PLAYER;s++)
			player[s]=&playert[s];
		for(s=0;s<RUNNINGS;s++)
			Save[s]=&Savet[s];
	}
	else if(race==1)
	{
		for(s=0;s<MAX_PLAYER;s++)
			player[s]=&playerp[s];
		for(s=0;s<RUNNINGS;s++)
			Save[s]=&Savep[s];
	}
	else 
	{
		for(s=0;s<MAX_PLAYER;s++)
			player[s]=&playerz[s];
		for(s=0;s<RUNNINGS;s++)
			Save[s]=&Savez[s];
	}

	Max_Build_Types=0;
	player[0]->Set_Goals();//~~~~ vielleicht 3 eigene funktionen machen :| braucht ja net jeder player
	
	
//Air Defense, Ground Defense faktor noch rein

	printf("Done. Rechecking data.\n");
	for(s=0;s<Max_Build_Types;s++)
		Build_Bv[Build_Av[s]]=s;

	if(u<building_types-2-(race==2))
	{
		printf("Error: %s is damaged. Please reread the specifications / reload the file.\n",I);
		printf("Reason: You probably deleted one entry or mixed up count/time in the data file...\n");
		printf("Expected data length: %i\nData length found: %i\n",building_types-2-(race==2),u);
	} else printf("OK. Press Enter to continue.\n");
	a=getchar();	
	for(s=0;s<MAX_PLAYER;s++)
		player[s]->Restart(); //player[0] !???

	
	afit=0;


	clrscr();
	gotoxy(0,0);

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
	for(s=0;s<building_types;s++)
		if(goal[s].what>0)
			printf("- %20s : %i   (%s) \n",stats[race][s].name,goal[s].what,kurz[race][s].b);

	calc=176;
	calc_i=1;
	printf("\n\nPress Enter to start calculation\n");
	printf("Please note: this may take a while.\n");
	a=getchar();
	clrscr();
	gotoxy(0,22);	
	
	printf("Evolution Chamber v1.02BETA - Brought to you by clawsoftware.de\n");
	printf("                 Press any key to cancel calculation.");
	gotoxy(0,0);
	old_time=Max_Time;
	old_fit=0;

	while( (run<RUNNINGS))
	{
		gotoxy(0,0);

		for(s=0;s<MAX_PLAYER;s++)
			player[s]->Init();
		for(s=1;s<MAX_PLAYER;s++)
			player[s]->Mutate();
		for(s=0;s<MAX_PLAYER;s++)
			player[s]->Calculate();

		for(s=1;s<MAX_PLAYER-1;s++)
			if(player[s]->pFitness>player[0]->pFitness)
			{
				tempp=player[s];
				player[s]=player[0];
				player[0]=tempp;
			}
			else if((player[s]->pFitness==player[0]->pFitness)&&(player[s]->sFitness>player[0]->sFitness))
			 {
				 tempp=player[s];
				 player[s]=player[0];
				 player[0]=tempp;
			 }
				
		// eigentlich brauch ich ja nur player[0] ...

		printf("Calculating [%c]         Status:",(calc+0));
		if(player[0]->timer<Max_Time)
		{
			if(old_time>player[0]->timer)
			printf(" found better solution . . .          \n");
			else	
			printf(" optimizing build order . . .         \n");
		}
		else			
		{
			if((old_fit/100)<(player[0]->pFitness/100))
			printf(" another goal completed . . .		  \n");
				else
			printf(" searching for possible solution . . .\n");
		}
		
		old_time=player[0]->timer;
		old_fit=player[0]->pFitness;
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


		if(player[0]->pFitness>afit)
		{
			afit=player[0]->pFitness;
			rfit=0;
//			Mut_Rate=MRate;
		}
		
		generation++;
		rfit++;
//		if(Mut_Rate>10)
//			Mut_Rate--;
		
//clrscr();
		printf("\n%i runs remaining (this run %i+ generations remaining)   \n",RUNNINGS-run,Max_Generations-rfit);
		if(verbose==1) 
		{
		printf("                           Overview Generation %i \n",generation);
		printf("[resources] [time]\n");
		printf("----------------\n");
		gotoxy(2,7);printf("  %5.4i",(int)(player[0]->harvested_mins+player[0]->harvested_gas));
		gotoxy(12,7);if(player[0]->timer<Max_Time) printf("%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);else printf(" ---- ");
		printf("\n\n");
		printf("   [Build Order of the best individual]");
	
		t=0;
		
		for(s=0;s<player[0]->length;s++)
		{
			gotoxy((t/10)*10,12+t%10);
			t++;
			if((Build_Av[player[0]->program[s].order]<building_types)&&(player[0]->program[s].time<player[0]->timer))
			printf("%2i.%s ",t,kurz[race][Build_Av[player[0]->program[s].order]].b);
			else printf("         ");
		}

		for(s=0;s<15;s++)
		{
			gotoxy(60,s+5);
			printf("         ");
		}
		t=0;
		for(s=0;s<building_types;s++)
			if((player[0]->force[s]>0)&&(goal[s].what>0)) 
			{
				gotoxy(60,t+5);				
				printf("%s:%2i  ",kurz[race][s].b,player[0]->force[s]);
				t++;
			}
		
		

		
		}
//wheee das abaendern!!!
		for(s=1;s<MAX_PLAYER/5;s++)
		{
			t=rand()%(MAX_PLAYER-1)+1;
			for(u=0;u<MAX_LENGTH;u++)
				player[t]->program[u]=player[0]->program[u];
		}
		for(s=1;s<MAX_PLAYER;s++)
		{
			t=rand()%MAX_PLAYER;
			if((player[s]->pFitness<player[t]->pFitness)||((player[s]->pFitness==player[t]->pFitness)&&(player[s]->sFitness<player[t]->sFitness)))	
				for(u=0;u<MAX_LENGTH;u++)		                                        player[s]->program[u]=player[t]->program[u];
		}
	
	    if(rfit>=Max_Generations)
		{
//			Mut_Rate=MRate;
			rfit=0;
			generation=0;
			for(s=0;s<MAX_LENGTH;s++)
				Save[run]->program[s]=player[0]->program[s];

			for(s=0;s<MAX_LENGTH;s++)
				Save[run]->program[s].time=player[0]->program[s].time;

			Save[run]->pFitness=player[0]->pFitness;
			Save[run]->timer=player[0]->timer;
			Save[run]->harvested_mins=player[0]->harvested_mins;
			Save[run]->harvested_gas=player[0]->harvested_gas;
			Save[run]->mins=player[0]->mins;
			Save[run]->gas=player[0]->gas;
			Save[run]->length=player[0]->length;

			for(s=0;s<building_types;s++)
				Save[run]->force[s]=player[0]->force[s];

			for(s=0;s<MAX_PLAYER;s++)
				player[s]->Restart();
			afit=0;
			old_time=Max_Time;
			old_fit=0;
			run++;
		}
	} // end while...

	//Output

	if(run<RUNNINGS)
	{
		for(s=0;s<MAX_LENGTH;s++)
		{
			Save[run]->program[s].order=player[0]->program[s].order;
			Save[run]->program[s].time=player[0]->program[s].time;
		}	
		Save[run]->pFitness=player[0]->pFitness;
		Save[run]->timer=player[0]->timer;
		Save[run]->harvested_mins=player[0]->harvested_mins;
		Save[run]->harvested_gas=player[0]->harvested_gas;	
		Save[run]->mins=player[0]->mins;
		Save[run]->gas=player[0]->gas;
		Save[run]->length=player[0]->length;

		for(s=0;s<building_types;s++)
			Save[run]->force[s]=player[0]->force[s];
	}
	
	clrscr();
	printf("Calculating completed.\n\n");
	printf(" The build order was saved in the file ""%s"".\n\n",O);
	printf(" Brought to you by clawsoftware.de\n");
	printf("\n\n\n\n\n\n\n\n\n\n");

	t=0;
	if(run>0)
	{
		afit=0;
		for(s=0;s<RUNNINGS;s++)
			if((Save[s]->pFitness>afit)&&(Save[s]->timer<Max_Time))
			{
				afit=Save[s]->pFitness;
				t=s;
			}
	}
	clrscr();
	
	FILE * pFile;
	pFile = fopen(O,"w");
	fprintf(pFile,"StarCraft Evolution Chamber by ClawSoftware.de\n");
	fprintf(pFile,"--------------------------------------------------\n\n");
	fprintf(pFile,"Build Order of best Individual:\n");
	fprintf(pFile,"Time used: %.2i:%.2i\n",Save[t]->timer/60,Save[t]->timer%60);	

	printf("Header saved...\n");
	
	old=200;
	counter=1;
	for(s=0;s<=Save[t]->length;s++)
	{
		if(Detailed_Info==0)
		{
			while(((Save[t]->program[s].time>=Save[t]->timer)||(Build_Av[Save[t]->program[s].order]>=building_types))&&(s<MAX_LENGTH-1))
				s++;
			if(old==Build_Av[Save[t]->program[s].order]) counter++;
			else if(old<200)
			{
				fprintf(pFile,"%.2i x %s\n",counter,stats[race][old].name);
				counter=1;
				old=Build_Av[Save[t]->program[s].order];
			}
			else
				old=Build_Av[Save[t]->program[s].order];
		}
		else
		if((Save[t]->program[s].time<Save[t]->timer)&&(Build_Av[Save[t]->program[s].order]<building_types)&&((s==0)||(Save[t]->program[s].time>0)))
				fprintf(pFile,"[%.2i:%.2i] %s\n",(Save[t]->program[s].time+0)/60,(Save[t]->program[s].time+0)%60,stats[race][Build_Av[Save[t]->program[s].order]].name);
	}

	printf("Build Order saved...\n");

	for(s=0;s<building_types;s++)
		if(Save[t]->force[s]>0)
			fprintf(pFile,"%s : %i\n",stats[race][s].name,Save[t]->force[s]);
	fprintf(pFile,"Harvested Minerals : %i\n",(short)(Save[t]->harvested_mins));
	fprintf(pFile,"Harvested Gas      : %i\n",(short)(Save[t]->harvested_gas));
	fprintf(pFile,"Minerals at the end: %i\n",(short)(Save[t]->mins));
	fprintf(pFile,"Gas at the end     : %i\n",(short)(Save[t]->gas));
	printf("First Solution succesfully saved...\n");
/*	out_file<<"Other possible solutions: \n";
	if(run>0)
	//Alle runs ausgeben!
	for(x=0;x<run;x++)
		if((Save[x]->timer<Max_Time)&&(y!=x)&&(Save[x]->timer!=Save[y]->timer))			
		{
			out_file<<"\n";
			out_file<<"\n----------------------------------------------------------\n\n";
			out_file<<"Time used: "<<Save[x]->timer/60<<":"<<Save[x]->timer%60<<"\n";	
			printf("Start saving %i. Solution...\n",x);
			printf("%i\n",Save[x]->length);
			old=200;
			counter=1;
			for(i=0;i<=Save[x]->length;i++)
			{
				printf("XXX\n");
				if(Detailed_Info==0)
				{
					while(((Save[x]->program[i].time>=Save[x]->timer)||(Build_Av[Save[x]->program[i].order]>=building_types))&&(i<MAX_LENGTH-1))
						i++;
					if(old==Build_Av[Save[x]->program[i].order]) counter++;
					else if(old<200)
					{
						printf("writing name...\n");
						out_file<<counter+0<<" "<<stats[race][old].name<<"\n";
						counter=1;
						old=Build_Av[Save[x]->program[i].order];
					}
					else
						old=Build_Av[Save[x]->program[i].order];
				}
				else
				if((Save[x]->program[i].time<Save[x]->timer)&&(Build_Av[Save[x]->program[i].order]<building_types)&&((i==0)||(Save[x]->program[i].time>0)))
					printf("writing time...\n");
					out_file<<"["<<(Save[x]->program[i].time+0)/60<<":"<<(Save[x]->program[i].time+0)%60<<"] "<<stats[race][Build_Av[Save[x]->program[i].time]].name<<"\n";
			}
			printf("Saving Force List\n");
			for(i=0;i<building_types;i++)
				if(Save[x]->force[i]>0)
					out_file<<stats[race][i].name<<" : "<<(Save[x]->force[i]+0)<<"\n";
 			printf("Saving additional Data\n");
			out_file<<"Harvested Minerals: "<<(unsigned short)(Save[x]->harvested_mins+0)<<"\n";
			out_file<<"Harvested Gas: "<<(unsigned short)(Save[x]->harvested_gas+0)<<"\n";	
			out_file<<"Minerals after completing last task: "<<(unsigned short)(Save[x]->mins+0)<<"\n";
			out_file<<"Gas after completing last task: "<<(unsigned short)(Save[x]->gas+0)<<"\n";
		}*/
       
	fclose (pFile);
	printf("File closed. All Data were saved.\n Thank you for using StarCalc!\n");

	for(s=0;s<MAX_PLAYER;s++)
		player[s]=NULL;
	for(s=0;s<RUNNINGS;s++)
		Save[s]=NULL;
	return 0;
};


