// Einmalige Updates auch nur einmal rein! Nur ueber austauschen rein !
// Todo: Debug messages in eigene Funktion!

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "terra.h"
#include "zerg.h"
#include "protoss.h"

using namespace std;

//TODO Kompatibilitaet zu DOS/LINUX!!!
#define clrscr() printf("\033[2J") /* Bildschirm löschen */      
#define gotoxy(x,y) printf("\033[%d;%dH",(y),(x))
#define setattr(a,v,b) printf("\033[%d;%d;%dm", (a), (v), (b))

RACE * player[MAX_PLAYER];

struct boLog
{
	unsigned char count;
	unsigned char order;
} bolog[MAX_LENGTH],forcelog[60];

void setAt(unsigned char cnt)
{
  if(setup.colors==0) return;
       if(cnt<4) setattr(0,37,40);//112212122
  else if(cnt<8) setattr(0,33,40);
  else if(cnt<16) setattr(0,32,40);
  else if(cnt<32) setattr(0,36,40);
  else if(cnt<64) setattr(0,31,40);
  else setattr(0,34,40);	
};

int main(int argc, char* argv[])
{	
	unsigned short run,rfit,afit,sfit;
	unsigned char counter,calc;
	char I[11],O[9],R[7];
	unsigned short old_time,old_fit,old,s,t,u,generation;
	unsigned char a;
	srand(time(NULL));
	clrscr();	
	
	race=5;
	
	if(argc>1)
	{
	if((argv[1][0]='T')||(argv[1][0]=='t'))
		race=0;
	else if((argv[1][0]=='P')||(argv[1][0]=='p'))
		race=1;
	else if((argv[1][0]=='Z')||(argv[1][0]=='z'))
		race=2;
	}
	
	// hier noch paar Parameter mehr rein
	// z.B. auch no scout oder so
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
	
	if(setup.Init(I)==1)
	{
		printf("Error during Setup. Repair / Reinstall the setting files!\n");				
		return(1);
	}

	generation=0;
	run=0;
	afit=0;
	rfit=0;
	sfit=0;
	
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

	for(s=0;s<Max_Build_Types;s++)
		Build_Bv[Build_Av[s]]=s;

	for(s=0;s<MAX_PLAYER;s++)
		player[s]->Restart(); //player[0] !???
	printf("\n\n OK! System is ready to start. Press Enter to continue...\n");
	a=getchar();

	clrscr();
	gotoxy(0,0);

	printf("Welcome to the StarCraft Evolution Chamber v1.02h!\n");
	printf("Check the ""%s"" file to change goals of the BO\n",I);
	printf("You may change additional settings in the ""settings.txt"" file.\n");
	printf("If you are new to this program, try to read the readme.txt\n");
	printf("After the calculation is complete, a new file called %s will be created.\n",O);
        printf("It contains the build order and some additional informations.\n");
	printf("\nRemember: You can compare all time indexes in this program only with a StarCraft game with speed 5.\n");

	printf("\nPress Enter to show the Goals and begin calculation...\n");	
        a=getchar();
	clrscr();
	gotoxy(0,0);
	printf("\n");
	printf("Goals (as stated in ""%s"")\n",I);
	for(s=0;s<building_types;s++)
		if(goal[s].what>0)
			printf("- %20s : %i   (%s) \n",stats[race][s].name,goal[s].what,kurz[race][s].b);

	calc=0;
	printf("\n\nPlease note: this may take a while. If the 'generations' counter keep jumping back you do not need to worry: That is exactly how it should be :)\n\n");
	printf("Enough words, press ENTER to let the calculation start!\n");
	
	a=getchar();
	clrscr();
	gotoxy(0,22);	
	
	printf("Evolution Chamber v1.02Beta - Brought to you by clawsoftware.de\n");
	printf("                 Press any key to cancel calculation.");
	gotoxy(0,0);
	old_time=setup.Max_Time;
	old_fit=0;

	sfit=0;
	while(run<RUNNINGS)
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
	generation++;
		rfit++;
	old_time=player[0]->timer;
		old_fit=player[0]->pFitness;
		calc++;
		
		
		if(player[0]->pFitness>afit)
		{
			afit=player[0]->pFitness;
			sfit=player[0]->sFitness;
			rfit=0;
		}
		else if(player[0]->sFitness>sfit)
		{
			sfit=player[0]->sFitness;
			rfit=0;
		}
		
		

		
		
		if(setup.Verbose==1)
		{
		printf("Calculating [");
		setattr(0,31+(calc%7),40);
		printf("%c",67+(calc%26));
		setattr(0,37,40);
		printf("]         Status:");
		if(player[0]->timer<setup.Max_Time)
		{
			if(old_time>player[0]->timer)
			printf(" found better solution . . .          ");
			else	
			printf(" optimizing build order . . .         ");
		}
		else			
		{
			if((old_fit/100)<(player[0]->pFitness/100))
			printf(" another goal completed . . .         ");
				else
			printf(" searching for possible solution . . .");
		}
		
		printf("\n%i runs remaining (this run %i+ generations remaining)   \n",RUNNINGS-run,setup.Max_Generations-rfit);
		printf("                           Overview Generation %i \n",generation);
		printf("[resources] [time]\n");
		printf("----------------\n");
		gotoxy(2,7);printf("  %5.4i",(int)(player[0]->harvested_mins+player[0]->harvested_gas));
		gotoxy(12,7);if(player[0]->timer<setup.Max_Time) printf("%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);else printf(" ---- ");
		printf("\n\n");
		printf("   [Build Order of the best individual]");
	
		t=0;

		for(s=0;s<60+(1-setup.numbers)*40;s++)
		{
			if(bolog[s].order==player[0]->program[s].order)
			{
				if(bolog[s].count<160)
					bolog[s].count++;
			}
			else
			{	bolog[s].count=0;
				bolog[s].order=player[0]->program[s].order;
			}
			if(setup.numbers==1) gotoxy((t/10)*10,11+t%10);
			else gotoxy((t/10)*7,11+t%10);
			t++;
			setattr(0,37,40);
			if((Build_Av[player[0]->program[s].order]<building_types)&&(player[0]->program[s].time<player[0]->timer))
			{
				setAt(bolog[s].count);
				if(setup.numbers==0)
					printf("%s ",kurz[race][Build_Av[player[0]->program[s].order]].b);
				else printf("%2i.%s ",t,kurz[race][Build_Av[player[0]->program[s].order]].b);
				setattr(0,37,40);
			}
			else { if(setup.numbers==0) printf(" ----  "); else printf("%2i. ---- ",t);}
		}

		setattr(0,37,40);

		t=4;
		gotoxy(63,3);printf("Force at the end:");
		for(s=0;s<building_types;s++)
			if(goal[s].what>0) 
			{
				if(forcelog[s].order==player[0]->force[s])
                        	{
		                      if(forcelog[s].count<160)
					      forcelog[s].count++;
			        }
                        	else
			        {
				 	forcelog[s].count=0;
				        forcelog[s].order=player[0]->force[s];			                }
				setAt(forcelog[s].count);
				gotoxy(70,t);				
				printf("%s:%2i",kurz[race][s].b,player[0]->force[s]);
				t++;
			}

		setattr(0,37,40);
	
		}
// Hier ende Verbose
		

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
	
	    if(rfit>=setup.Max_Generations)
		{
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
			{
				Save[run]->force[s]=player[0]->force[s];
				Save[run]->ftime[s]=player[0]->ftime[s];
			}

			for(s=0;s<MAX_PLAYER;s++)
				player[s]->Restart();
			afit=0;
			sfit=0;
			old_time=setup.Max_Time;
			old_fit=0;
			run++;
			for(s=0;s<MAX_LENGTH;s++)
				bolog[s].count=0;
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
		{
			Save[run]->force[s]=player[0]->force[s];
			Save[run]->ftime[s]=player[0]->ftime[s];
		}
	}
	
	t=0;
	if(run>0)
	{
		afit=0;
		sfit=0;
		for(s=0;s<RUNNINGS;s++)
		{
			if((Save[s]->pFitness>afit)&&(Save[s]->timer<setup.Max_Time))
			{
				afit=Save[s]->pFitness;
				t=s;
			}
			else if((Save[s]->pFitness==afit)&&(Save[s]->timer<setup.Max_Time)&&(Save[s]->sFitness>sfit))
			{
				sfit=Save[s]->sFitness;
				t=s;
			}
		}
	}
	clrscr();

	if(Save[t]->timer>=setup.Max_Time)
	{
		printf("NO Solution found. This should not happen.\n");
		printf("Please try the following:\n");
		printf(" - Reread all WARNINGS carefully.\n");
	        printf(" - Reduce the amount of goals in %s",I);
		printf(" - Increase Max Time and/or adjust other settings depending on your task\n");
		printf(" - Contact scc@clawsoftware.de. Please include all .txt files and a short description of the problem.\n");
		printf(" - You might also want to check www.clawsoftware.de for updates or read the Forum/SCC page.\n");
		printf(" Press ENTER to quit...\n");
		a=getchar();
		return(1);
	}
	
	FILE * pFile;
	pFile = fopen(O,"w");
	fprintf(pFile,"StarCraft Evolution Chamber by ClawSoftware.de\n");
	fprintf(pFile,"--------------------------------------------------\n\n");
	fprintf(pFile,"Build Order of best Individual:\n");
	
	fprintf(pFile,"Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[t]->timer%60);	
	if(race!=2) fprintf(pFile,"Scouting unit after %.2i:%.2i minutes\n",setup.Scout_Time/60,setup.Scout_Time%60);
	
	printf("Header saved...\n");
	
	old=200;
	counter=1;
	for(s=0;s<=Save[t]->length;s++)
	{
		if(setup.Detailed_Output==0)
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
			fprintf(pFile,"%s : %i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[t]->force[s],Save[t]->ftime[s]/60,Save[t]->ftime[s]%60);
	fprintf(pFile,"Harvested Minerals : %i\n",(short)(Save[t]->harvested_mins));
	fprintf(pFile,"Harvested Gas      : %i\n",(short)(Save[t]->harvested_gas));
	fprintf(pFile,"Minerals at the end: %i\n",(short)(Save[t]->mins));
	fprintf(pFile,"Gas at the end     : %i\n",(short)(Save[t]->gas));
	fprintf(pFile,"------------------------------\n\n");
	printf("First solution [%.2i:%.2i] succesfully saved...\n",Save[t]->timer/60,Save[t]->timer%60);
	printf("Checking for other solutions:\n");
	fprintf(pFile,"Other possible solutions: \n");
	unsigned char otherfound=0;
	unsigned char newone=0;
	if(run>0)
	//Alle runs ausgeben!
	for(u=0;u<run;u++)
	{
		newone=1;
		for(s=0;s<u;s++)
		{
			newone=newone&&(((short)Save[u]->harvested_mins!=(short)Save[s]->harvested_mins)||
				        ((short)Save[u]->harvested_gas!=(short)Save[s]->harvested_gas)||
				        ((short)Save[u]->timer!=(short)Save[s]->timer)||
				        ((short)Save[u]->mins!=(short)Save[s]->mins)||
				        ((short)Save[u]->gas!=(short)Save[s]->gas));
		}
			
		if((Save[u]->timer<setup.Max_Time)&&(t!=u)&&(newone==1))			
		{
			otherfound=1;
			fprintf(pFile,"Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[u]->timer%60);
			if(race!=2) fprintf(pFile,"Scouting unit after %.2i:%.2i minutes\n",setup.Scout_Time/60,setup.Scout_Time%60);
			printf("Header saved...\n");
			old=200;
			counter=1;
			for(s=0;s<=Save[u]->length;s++)
			{
				if(setup.Detailed_Output==0)
				{
					while(((Save[u]->program[s].time>=Save[u]->timer)||(Build_Av[Save[u]->program[s].order]>=building_types))&&(s<MAX_LENGTH-1))
						s++;
			if(old==Build_Av[Save[u]->program[s].order]) counter++;
			else if(old<200)
			{
				fprintf(pFile,"%.2i x %s\n",counter,stats[race][old].name);
				counter=1;
				old=Build_Av[Save[u]->program[s].order];
			}
			else
				old=Build_Av[Save[u]->program[s].order];
		}
		else
		if((Save[u]->program[s].time<Save[u]->timer)&&(Build_Av[Save[u]->program[s].order]<building_types)&&((s==0)||(Save[u]->program[s].time>0)))
				fprintf(pFile,"[%.2i:%.2i] %s\n",(Save[u]->program[s].time+0)/60,(Save[u]->program[s].time+0)%60,stats[race][Build_Av[Save[u]->program[s].order]].name);
	}

	printf("Build Order saved...\n");

	for(s=0;s<building_types;s++)
		if(Save[u]->force[s]>0)
			fprintf(pFile,"%s : %i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[u]->force[s],Save[u]->ftime[s]/60,Save[u]->ftime[s]%60);
	fprintf(pFile,"Harvested Minerals : %i\n",(short)(Save[u]->harvested_mins));
	fprintf(pFile,"Harvested Gas      : %i\n",(short)(Save[u]->harvested_gas));
	fprintf(pFile,"Minerals at the end: %i\n",(short)(Save[u]->mins));
	fprintf(pFile,"Gas at the end     : %i\n",(short)(Save[u]->gas));
	fprintf(pFile,"------------------------------\n\n");
	printf("%i. solution [%.2i:%.2i] succesfully saved...\n",u,Save[u]->timer/60,Save[u]->timer%60);
			printf("- [%.2i:%.2i] succesfully saved...\n",Save[u]->timer/60,Save[u]->timer%60);
		}
	}
	if(otherfound==0)
	{
		fprintf(pFile,"None found!\n");
		printf("None found!\n");
	}
       
	fclose (pFile);
	printf("%s closed. All Data were saved.\n\n Thank you for using StarCalc!\n",I);
	printf("Have a nice day and visit www.clawsoftware.de!\n");

	for(s=0;s<MAX_PLAYER;s++)
		player[s]=NULL;
	for(s=0;s<RUNNINGS;s++)
		Save[s]=NULL;
	return 0;
};

