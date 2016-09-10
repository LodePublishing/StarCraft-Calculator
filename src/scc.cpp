// StarCraft Calculator - Calculates and optimizes build orders
// Copyright (C) 2003 Clemens Lode
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

// See www.clawsoftware.de for updates/news/faq/tutorials etc.

// TODO: reorganize the CLASSes (private,protected,public entities...)
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "terra.h"
#include "zerg.h"
#include "protoss.h"
#include "io.h"
#include "init.h"

#include "namen.h"
#include "settings.h"

#define gizmowidth 35

// Here are some global variables (accessible by any class due to 'extern' declaration in 'main.h'
int mining[45],gasing[5];
unsigned char buildable[MAX_GOALS],Build_Av[MAX_GOALS],Build_Bv[MAX_GOALS],tgoal[MAX_GOALS],Variabel[MAX_GOALS]; 
unsigned char Vespene_Av,Max_Build_Types,race,colors;
unsigned short total_goals;
unsigned char num,Vespene_Extractors,need_Gas;
GOAL goal[MAX_GOALS]; // GOAL := what buildings should be there AT THE END
unsigned char Basic[MAX_LENGTH][2],Basic_Length;



int compare(const void * a,const void * b)
{
	if(( (*(RACE*)a).pFitness<(*(RACE*)b).pFitness)||(((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness<=(*(RACE*)b).sFitness)))
		return (1);
	else if(( (*(RACE*)a).pFitness>(*(RACE*)b).pFitness)|| ((*(RACE*)a).sFitness>(*(RACE*)b).sFitness))
		return (-1);
	else return(0);
};

struct UNITT
{
	char text[162]; //or 161?
} unit[MAX_GOALS];


struct boLog
{
	unsigned char count;
	unsigned char order;
} bolog[MAX_LENGTH],forcelog[MAX_GOALS];

	RACE * player[MAX_PLAYER];


int main(int argc, char* argv[])
{	


	// TODO: make some significant variables...	
	unsigned short run,rfit,afit,sfit;
	unsigned char counter,gcount;
	char I[11],O[9],R[7];
	char tmp[255];
	int old_time,old_fit,old,old_t,old_sup,s,t,u,generation,calc;

	int race_size;

	//TODO: Check unsigned char <> unsigned short counting variables (especially s,t,u)
	
	unsigned char a,tunit;//,Test;
	char * gizmo;


	Vespene_Extractors=0;
// TODO: maybe put them to settings	
	race=5;
	gcount=16;
	tunit=0;
	generation=0;
    run=0;
    afit=0;
    rfit=0;
    sfit=0;
	old=200;
    counter=1;
	old_fit=0;

	
	srand(time(NULL));
	clrscr();
	
	if(settings.Init()==1)
	{
		printf("Error during settings. Repair / Reinstall the settings.txt file!\n");
	        return(1);
	}

	TranslateData(argc,argv);
	

#define gizmolength 879
//The green gizmo text at the top
	gizmo = new char[gizmolength];
	sprintf(gizmo,"                                        Attention Defenders of the United Earth Directorate!                                        This is Admiral DuGalle.                                        You were all briefed before we left earth, so you know that we have come here to conquer this sector in the name of humanity.                                        Should any of you have second thoughts about performing your assigned duties, be reminded that if we fail in our mission here, not one of us will be going home.                                        We stand or fall together in this forsaken wasteland.                                        Serve the directorate serve humanity...                                       All other priorities are secondary to victory!                                        Dugall out.                                        ");
	
	printf("Setting Race and initializing player models... ");
	
	switch(race)
	{
		case 0:sprintf(I,"goal_t.txt");sprintf(O,"bo_t.txt");sprintf(R,"Terran");break;
		case 1:sprintf(I,"goal_p.txt");sprintf(O,"bo_p.txt");sprintf(R,"Protoss");break;
		case 2:sprintf(I,"goal_z.txt");sprintf(O,"bo_z.txt");sprintf(R,"Zerg");break;
		default:printf("not enough arguments");return 0;break;
	}
	printf("[%s]",R);
	setColor(32);
	printf(" ok\n");
	setColor(37);

//	if(Test==0)
//	{
		if(settings.InitGoal(I)==1)
		{
			printf("Error during settings. Repair / Reinstall the %s file!\n",I);
		        return(1);
		}
//	}

	

	RACE * Save[RUNNINGS];
// TODO: Looks pretty hacked... maybe implement a better method later to allow the virtual construction in RACE
	if(race==TERRA)
	{
		Player_Terra playert[MAX_PLAYER];
		Player_Terra Savet[RUNNINGS];

		for(s=0;s<MAX_PLAYER;s++) player[s]=&playert[s];
		for(s=0;s<RUNNINGS;s++) Save[s]=&Savet[s];
		race_size=sizeof(Player_Terra);
	}
	else if(race==PROTOSS)
	{
	Player_Protoss playerp[MAX_PLAYER];
	Player_Protoss Savep[RUNNINGS];

		for(s=0;s<MAX_PLAYER;s++) player[s]=&playerp[s];
		for(s=0;s<RUNNINGS;s++) Save[s]=&Savep[s];
		race_size=sizeof(Player_Protoss);
	}
	else if(race==ZERG)
	{
	Player_Zerg playerz[MAX_PLAYER];
	Player_Zerg Savez[RUNNINGS];

		for(s=0;s<MAX_PLAYER;s++) player[s]=&playerz[s];
		for(s=0;s<RUNNINGS;s++) Save[s]=&Savez[s];
		race_size=sizeof(Player_Zerg);
	}

	Max_Build_Types=0;
	
//	if(Test>0)
//	{
/*		for(s=0;s<MAX_GOALS;s++)
		{
			goal[s].what=0;
			goal[s].time=0;
		}
		for(s=0;s<MAX_LENGTH;s++)
			if(bo[s].count>0)
				goal[bo[s].type].what+=bo[s].count;		*/
//	}

	// Sets additional goals, say the user enters "Guardien" Set_Goals will also set Hive, Greater Spire, Lair, Queens Nest, Extractor and Spawning Pool as a goal
	player[0]->Set_Goals(); 
	Init();

	// Maybe just do 3 different functions instead of a function for every member of the class as it affects only global variables

	settings.AdjustMining();

	player[0]->generateBasicBuildorder();

//	if(Test<2)
		for(s=0;s<MAX_PLAYER;s++)
			player[s]->Restart();
	//Test == 2 => "-T" Parameter, just run a single run to determine the time it needs
/*	else if(Test==2) 
	{
		z=0;
		player[0]->Init();

		for(t=0;t<MAX_LENGTH;t++)
			if(bo[t-z].count>0)
			{
				u=bo[t-z].count; //Translate the build order say 1: "5 marines" in 1: Marine, 2: Marine, ..., 5: Marine
				while((t<MAX_LENGTH)&&(u>0))
				{
					player[0]->program[t].order=Build_Bv[bo[t-z].type];
					u--;z++;
					player[0]->program[t].time=20000;
					player[0]->program[t].built=0;
					t++;

					//~~~~
				}
				z--;t--;
			}
				else 
				{
					player[0]->program[t].order=255;
					player[0]->program[t].time=20000;
					player[0]->program[t].built=0;	
				}
		
		// "scc -b Drone" results in a goal[DRONE].what == 5
			for(s=0;s<MAX_GOALS;s++)
				if(player[0]->force[s]>0)
					goal[s].what+=player[0]->force[s];
			player[0]->readjust_goals(); // actually affects only zerg (and archon of the protoss)

			printf("Translated goals:\n");
			for(s=0;s<MAX_GOALS;s++)
				if(goal[s].what>0)
					printf("%s : %i\n",stats[race][s].name,goal[s].what); 
			printf("\nPress Enter to show time\n");

			a=getchar();
			player[0]->timer=settings.Max_Time;
			player[0]->IP=0;

			player[0]->Calculate();

		//print out all orders that are executed without problems
			printf("Successful build order:           [Requirement fulfilled]\n");
			for(s=0;s<MAX_LENGTH;s++)
				if(player[0]->program[s].built==1)
			printf("    %s [%.2i:%.2i] %s\n",stats[race][Build_Av[player[0]->Code[s][player[0]->program[s].dominant]]].name,player[0]->program[s].time/60,player[0]->program[s].time%60,error_m[player[0]->program[s].success]);
				else s=MAX_LENGTH;
				
			printf("Needed Time: ");	
			setColor(32);
			printf("[%.2i:%.2i] ",player[0]->timer/60,player[0]->timer%60);
			setColor(37);
	
		// no solution? probably forgot a tech building or supply
			if(player[0]->timer==settings.Max_Time)
			{
				printf("\n => invalid build order, goals not reached.\n");	
				s=0;
			//determine the order which could not be executed
				while(s<MAX_LENGTH)
					if((s+1<MAX_LENGTH)&&(player[0]->program[s+1].built==0))
					{
						printf("When trying to build ");
					        setColor(32);
				       		printf("%s",stats[race][Build_Av[player[0]->Code[s][player[0]->program[s].dominant]]].name);
					        setColor(37);
				                printf(" the following requirement failed : \n");
						setColor(31);
						printf("%80s\n",error_m[player[0]->program[s].success]);
					        setColor(37);
						printf("\nCheck your build order, reread the readme and/or contact ClawSoftware :)\n");
						s=MAX_LENGTH;
					} else s++;
				}
			printf("\n");
			return(0);	
	}*/
        old_time=settings.Max_Time;

	// Creating Unit text... (right bottom corner)
	for(s=0;s<MAX_GOALS;s++)
sprintf(unit[s].text,"              Unit Name: %21s    Buildtime: %3i seconds    Minerals : %3i    Gas      : %3i    Supply   : %i    Type     : %i                     ",stats[race][s].name,stats[race][s].BT,stats[race][s].mins,stats[race][s].gas,stats[race][s].supply,stats[race][s].type);

	
	for(s=0;s<MAX_LENGTH;s++) bolog[s].count=0;
	for(s=0;s<MAX_GOALS;s++) Variabel[s]=0;

	
//some blabla
printf("\n\n OK! System is ready to start. Press Enter to continue...\n");

	a=getchar();



	
	clrscr();
	gotoxy(0,0);

	printf("Welcome to StarCraftCalculator v1.02 [April/07/2003]!\n");
	printf("-------------------------------------\n\n");
	printf("- Check the ""%s"" file to change goals of the BO\n",I);
	printf("  You may change additional settings in the ""settings.txt"" file.\n");
	printf("- If you are new to this program, try to read the readme.txt\n");
	printf("- After the calculation is complete, a new file called %s will be created.\n",O);
        printf("  It contains the build order and some additional informations.\n");
	printf("- Remember: SCC is based on a speed 5 game.\n");

	printf("\n\n");
        printf("Please note:\n");
	printf("            This may take a while.\n");
	printf("            If the 'generations' counter keep jumping back\n");
	printf("            you do not need to worry:\n");
	printf("That is exactly how it should be :)\n\n");
	printf("\nPress Enter to show the goals...\n");	
    a=getchar();
	clrscr();
	gotoxy(0,0);
printf("Goals\n");
	for(s=0;s<MAX_GOALS;s++)
		if(goal[s].what>0)
		{
			if(goal[s].time==0)
				printf("- %20s : %2i   (%s) \n",stats[race][s].name,goal[s].what,kurz[race][s].b);
			else printf("- %20s : %2i   (%s) [%.2i:%.2i] \n",stats[race][s].name,goal[s].what,kurz[race][s].b,goal[s].time/60,goal[s].time%60);
		}

	calc=0;
	printf("\n\n");
	printf("Press ENTER to let the calculation start!\n");
	
	a=getchar();
	clrscr();

// OK, lets start the main loop :)
#ifdef WIN32
	SetConsoleActiveScreenBuffer(scr);
#endif

	while(run<RUNNINGS)
	{
		gotoxy(0,0);
	
	  	generation++;
                rfit++;
	        calc++;
		  	  
//TODO: player[0] is not yet initialized as the best build order ... (in the very first run)
// probably the best thing to do is to move the block to the end 
		old_time=player[0]->timer;
		old_fit=player[0]->pFitness; 

		for(s=0;s<MAX_PLAYER;s++)
			(*player[s]).Init();
		for(s=1;s<MAX_PLAYER;s++)
			(*player[s]).Mutate();
		
		for(s=0;s<MAX_PLAYER;s++)
			(*player[s]).Calculate();

// Determine the best build order depending on the primary fitness (needed time and completed goals) and the secondary fitness (gathered resources)		
		qsort(*player,MAX_PLAYER,race_size,compare);

		// bigger than afit or sfit? good! We completed another goal or at least a part of it
		// Maybe implement another parameter to deactivate sFitness... will (maybe!) cause faster calculation but worse build orders (in terms of resources)
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
		
		//Print the screen :)
		if(settings.Verbose==1)
		{
			gotoxy(0,0);

	   	print("Calculating ");

		if(settings.Gizmo==1)
		{
			print("[");
			setColor(32);
			for(s=0;s<gizmowidth;s++)
			{
				sprintf(tmp,"%c",gizmo[(calc/2+s)%gizmolength]);
				print(tmp);
			}
			setColor(37);
			print("]");
		}
		print("  Status:");

		if(gcount<160) gcount++;
		if(player[0]->timer<settings.Max_Time)
		{
			if(old_time>player[0]->timer) gcount=0;
			if(gcount<=16)
			print(" got faster solution! ");
				else
			print(" optimizing resources.");
		}
		else			
		{
			if((old_fit/100)<(player[0]->pFitness/100)) gcount=0;

			if(gcount<=16)
			print(" another goal complete");
			else
			print(" searching . . .      ");
		}
		
		setColor(37);
		gotoxy(1,2);sprintf(tmp,"%i runs and %i+ generations remaining. [Total %i generations]      ",RUNNINGS-run,settings.Max_Generations-rfit,generation);
		print(tmp);
		gotoxy(0,4);
		print("[resources] [time]");
		gotoxy(0,5);
		print("------------------");
		gotoxy(2,6);sprintf(tmp,"  %5.4i",(int)(player[0]->harvested_mins+player[0]->harvested_gas));
		print(tmp);
		setAt(gcount);
		gotoxy(13,6);if(player[0]->timer<settings.Max_Time) { sprintf(tmp,"%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);print(tmp);} else print(" ---- ");
		
	setColor(31);
if((calc%80==0)||(calc%80==1)) setColor(37); else setColor(31);
	gotoxy(20,3);print("     ooo    ooo   ooo   o      oo    ooo ");
if((calc%80==2)||(calc%80==3)) setColor(37); else setColor(31);
	gotoxy(20,4);print("   o      o     o      o     o  o       o");
if((calc%80==4)||(calc%80==5)) setColor(37); else setColor(31);
	gotoxy(20,5);print("    o    o     o      o     o  o      o  ");
if((calc%80==6)||(calc%80==7)) setColor(37); else setColor(31);
	gotoxy(20,6);print("    o   o     o      o     o  o     o    ");
if((calc%80==8)||(calc%80==9)) setColor(37); else setColor(31);
	gotoxy(20,7);print("ooo     ooo   ooo   o  o   oo     ooooo  ");
		
		for(s=0;s<MAX_GOALS;s++)
			tgoal[s]=goal[s].what;
//bolog logs how long which build order stands there (you know, the colors ;-)
		//TODO: recognize moved blocks to stress real Mutations
		
		old=200;
		old_t=0;
		old_sup=0;
		counter=1;
		t=0;
		setColor(37);
			
		if(settings.Detailed_Output==1)
		{
			for(s=0;s<5;s++)
                	{
		       			t=0;
		                while((t<HEIGHT)&&(player[0]->program[(s+1)*HEIGHT-t].built==0)) t++;
		               	gotoxy(WIDTH*s+2,25-settings.Console24Lines);//WIN32 1 <> LINUX 0
				if((t<HEIGHT)||(player[0]->program[s*HEIGHT].built>0))
				{
					sprintf(tmp,"[%.2i:%.2i]",player[0]->program[(s+1)*HEIGHT-t].time/60,player[0]->program[(s+1)*HEIGHT-t].time%60);
					print(tmp);
				}
				else print("       ");
			}
			
			t=0;
			for(s=0;s<MAX_LENGTH;s++)
			{
				gotoxy((t/HEIGHT)*WIDTH,9+t%HEIGHT-settings.Console24Lines);
				t++;
				setColor(37);
				if(player[0]->program[s].built==1)
				{
					if(bolog[s].order==player[0]->Code[s][player[0]->program[s].dominant])
                   	{
				        	if(bolog[s].count<160)
							bolog[s].count++;
					} else
					{
						bolog[s].count=0;
						bolog[s].order=player[0]->Code[s][player[0]->program[s].dominant];
					}
					
					setColor(34);
					if(tgoal[Build_Av[player[0]->Code[s][player[0]->program[s].dominant]]]>0)
					{
						print("@");
						tgoal[Build_Av[player[0]->Code[s][player[0]->program[s].dominant]]]--;
					} else print(" ");
					setColor(35);
					sprintf(tmp,"%c",error_sm[player[0]->program[s].success]);
					print(tmp);
					setAt(bolog[s].count);
					sprintf(tmp,"%s",kurz[race][Build_Av[player[0]->Code[s][player[0]->program[s].dominant]]].b);
					print(tmp);
					setColor(37);
					if(player[0]->program[s].need_Supply<100)
						sprintf(tmp," %.2i",player[0]->program[s].need_Supply);
					else sprintf(tmp,"%3i",player[0]->program[s].need_Supply);
					print(tmp);
				}
				else print(" ------    "); 
			}
		}
		else
		{
		for(s=0;(s<MAX_LENGTH)&&(t<3*HEIGHT+3);s++)
		{
			while((player[0]->program[s].built==0)&&(s<MAX_LENGTH-1))
                        	s++;
                        if(old==Build_Av[player[0]->Code[s][player[0]->program[s].dominant]]) counter++;
			else if(old<200)
			{
				if(bolog[t].order==old)
	                        {
					if(bolog[t].count<160)
					bolog[t].count++;
				}
                                else
				{
					bolog[t].count=0;
					bolog[t].order=old;
				}
				
				gotoxy((t/(HEIGHT+1))*17,9+t%(HEIGHT+1)-settings.Console24Lines);
				if(counter>1) { sprintf(tmp,"%2i",counter);setColor(35);print(tmp);} else print("  ");
					setAt(bolog[t].count);
				t++;
				sprintf(tmp,"%s",kurz[race][old].b);
				print(tmp);
				setColor(37);
			    sprintf(tmp," %.2i:%.2i ",old_t/60,old_t%60);
				print(tmp);
				setColor(35);
				if(old_sup<100) sprintf(tmp,"%.2i",old_sup); else sprintf(tmp,"%3i",old_sup);
				print(tmp);
				setColor(37);
				counter=1;
				old=Build_Av[player[0]->Code[s][player[0]->program[s].dominant]];
				old_t=player[0]->program[s].time;
				old_sup=player[0]->program[s].need_Supply;
			}
			else
			{
				old=Build_Av[player[0]->Code[s][player[0]->program[s].dominant]];
				old_t=player[0]->program[s].time;
				old_sup=player[0]->program[s].need_Supply;
			}
		}
		for(s=t;(s<=MAX_LENGTH)&&(s<3*(HEIGHT+1));s++)
		{
			gotoxy((s/(HEIGHT+1))*17,9+s%(HEIGHT+1)-settings.Console24Lines);
			print("  ------       x");
		}
		}

		setColor(37);

		t=4;
		gotoxy(66,3);print("Force:");
		for(s=0;s<MAX_GOALS;s++)
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
				        forcelog[s].order=player[0]->force[s];
				}
				
				setAt(forcelog[s].count);
				gotoxy(70,t);				
				sprintf(tmp,"%s:%2i ",kurz[race][s].b,player[0]->force[s]);
				print(tmp);
				t++;
				if(t>23-settings.Console24Lines) s=MAX_GOALS;
				
				//Well... it can't print out more than ~20 goals :/ 
			}
		if(t<=23-settings.Console24Lines)
		{
			gotoxy(66,t);
			setColor(37);
			print("non-goals:");
			t++;
			for(s=0;s<MAX_GOALS;s++)
				if((goal[s].what==0)&&(player[0]->force[s]))
				{
					if(forcelog[s].order==player[0]->force[s])
					{
						if(forcelog[s].count<160)
							forcelog[s].count++;
					}
					else
					{
						forcelog[s].count=0;
						forcelog[s].order=player[0]->force[s];
					}
						setAt(forcelog[s].count);
						gotoxy(70,t);
						sprintf(tmp,"%s:%2i ",kurz[race][s].b,player[0]->force[s]);
						print(tmp);
						t++;
						if(t>23-settings.Console24Lines) s=MAX_GOALS;
				}
		for(s=0;s<23-t-settings.Console24Lines;s++)
		{
			gotoxy(70,t+s);
			print("         ");
		}
		}
		
		if(settings.Gizmo==1)
		{
			setColor(37);
			gotoxy(54,25-settings.Console24Lines);
		 	print("[");
			setColor(33);
	     for(s=0;s<23;s++)
			{
				sprintf(tmp,"%c",unit[tunit].text[(calc/2+s)%(sizeof(unit[tunit].text)-1)]);
				//sizeof correct? mmmh...
				print(tmp);
			}	

			if((calc/2+1)%(sizeof(unit[tunit].text)-1)==0)
			{
//				clrscr(); // <- hacked to reduce graphic errors... D:
				tunit=rand()%MAX_GOALS;
				while(player[0]->force[tunit]==0)
					tunit=rand()%MAX_GOALS;
			}
		
                setColor(37);
                print("]");
			}
		}

// End of Verbose
		
// Core of the Program
// It *works*... though there is probably a better algorithm (exchange of parts of the program instead of just overwriting other build orders that are worse)
		// It's just a hill climbing algorithm... If the Fitness of one program is higher than the other, it is overwritten.
		// Secondary fitness just comes in when primary fitness is equal
// TODO: Test and implement better algorithms for reproduction		
		for(s=1;s<10;s++)
		{
			t=rand()%(MAX_PLAYER-1)+1;
			for(u=0;u<MAX_LENGTH;u++)
			{
				player[t]->Code[u][0]=player[0]->Code[u][0];
				player[t]->Code[u][1]=player[0]->Code[u][1];
			}
			player[t]->pFitness=player[0]->pFitness;
			player[t]->sFitness=player[0]->sFitness;
		}
		for(s=1;s<MAX_PLAYER;s++)
		{
			t=rand()%MAX_PLAYER;
			if((player[s]->pFitness<player[t]->pFitness)||((player[s]->pFitness==player[t]->pFitness)&&(player[s]->sFitness<player[t]->sFitness)))
			{
			for(u=0;u<MAX_LENGTH;u++)
			{
				player[s]->Code[u][0]=player[t]->Code[u][0];
				player[s]->Code[u][1]=player[t]->Code[u][1];
			}
			
			player[s]->pFitness=player[t]->pFitness;
			player[s]->sFitness=player[t]->sFitness;
			}
			
		}
	// Save the program when 'Max_Generations' Generations were no change
	    if(rfit>=settings.Max_Generations)
		{
			rfit=0;
			generation=0;
			for(s=0;s<MAX_LENGTH;s++)
			{
				Save[run]->Code[s][0]=player[0]->Code[s][0];
				Save[run]->Code[s][1]=player[0]->Code[s][1];
				Save[run]->program[s].time=player[0]->program[s].time;
				Save[run]->program[s].need_Supply=player[0]->program[s].need_Supply;
				Save[run]->program[s].have_Supply=player[0]->program[s].have_Supply;
				Save[run]->program[s].success=player[0]->program[s].success;
				Save[run]->program[s].built=player[0]->program[s].built;
				Save[run]->program[s].dominant=player[0]->program[s].dominant;
			}

			Save[run]->pFitness=player[0]->pFitness;
			Save[run]->timer=player[0]->timer;
			Save[run]->harvested_mins=player[0]->harvested_mins;
			Save[run]->harvested_gas=player[0]->harvested_gas;
			Save[run]->mins=player[0]->mins;
			Save[run]->gas=player[0]->gas;
			Save[run]->length=player[0]->length;

			for(s=0;s<MAX_GOALS;s++)
			{
				Save[run]->force[s]=player[0]->force[s];
				Save[run]->ftime[s]=player[0]->ftime[s];
			}

//			if(Test<2)
		        	for(s=0;s<MAX_PLAYER;s++)
			        	player[s]->Restart();
/*         	else
		   {
				for(s=0;s<MAX_PLAYER;s++)
				{
					for(t=0;t<MAX_LENGTH;t++)
					{
						player[s]->program[t].order=bo[t].type;
						player[s]->program[t].time=20000;
					}
				player[s]->timer=settings.Max_Time;
				player[s]->IP=0;
				player[s]->length=MAX_LENGTH;
				}
			}*/
			
			afit=0;
			sfit=0;
			old_time=settings.Max_Time; 
			old_fit=0;
			run++;
			for(s=0;s<MAX_LENGTH;s++)
				bolog[s].count=0;
		}
//	    if(player[0]->force[13]==255)
//		    a=getchar();
	    
	} // end while...

	delete gizmo;

	//start of the file output block...

// Run canceled before all 5 runs were calculated? => Save the present run
/*	if(run<RUNNINGS)
	{
		for(s=0;s<MAX_LENGTH;s++)
		{
			Save[run]->Codeprogram[s].order=player[0]->Code[s][player[0]->program[s].dominant];
			Save[run]->program[s].time=player[0]->program[s].time;
			Save[run]->program[s].have_Supply=player[0]->program[s].have_Supply;
			Save[run]->program[s].need_Supply=player[0]->program[s].need_Supply;
			Save[run]->program[s].success=player[0]->program[s].success;
		}	
		Save[run]->pFitness=player[0]->pFitness;
		Save[run]->timer=player[0]->timer;
		Save[run]->harvested_mins=player[0]->harvested_mins;
		Save[run]->harvested_gas=player[0]->harvested_gas;	
		Save[run]->mins=player[0]->mins;
		Save[run]->gas=player[0]->gas;
		Save[run]->length=player[0]->length;

		for(s=0;s<MAX_GOALS;s++)
		{
			Save[run]->force[s]=player[0]->force[s];
			Save[run]->ftime[s]=player[0]->ftime[s];
		}
	}*/
	
	t=0;
//Determine the best run
	if(run>0)
	{
		afit=0;
		sfit=0;
		for(s=0;s<RUNNINGS;s++)
		{
			if((Save[s]->pFitness>afit)&&(Save[s]->timer<settings.Max_Time))
			{
				afit=Save[s]->pFitness;
				t=s;
			}
			else if((Save[s]->pFitness==afit)&&(Save[s]->timer<settings.Max_Time)&&(Save[s]->sFitness>sfit))
			{
				sfit=Save[s]->sFitness;
				t=s;
			}
		}
	}
	clrscr();
	
#ifdef WIN32
	CloseHandle(scr);
#endif

// Even best run did not find a solution?
	if(Save[t]->timer>=settings.Max_Time)
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

// Start saving the data	
	FILE * pFile;
	pFile = fopen(O,"w");
	fprintf(pFile,"---------------------------------------------------\n");
	fprintf(pFile,"---StarCraftCalculator by ClawSoftware.de [v1.02]--\n");
	fprintf(pFile,"---------------------------------------------------\n\n");
	fprintf(pFile,"[----Best solution---]\n\n");
	fprintf(pFile,"     Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[t]->timer%60);	
	if(race!=2) fprintf(pFile,"     Scouting unit after %.2i:%.2i minutes\n",settings.Scout_Time/60,settings.Scout_Time%60);
	if(settings.Time_to_Enemy>0) fprintf(pFile,"     Time to Enemy: %i seconds\n\n",settings.Time_to_Enemy);
	
	printf("\nHeader saved...");
	
	old=200;
	counter=1;
	for(s=0;s<=Save[t]->length;s++)
	{
		if(settings.Detailed_Output==0)
		{
			while(((Save[t]->program[s].time>=Save[t]->timer)||(Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]]>=MAX_GOALS))&&(s<MAX_LENGTH-1))
				s++;
			if(old==Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]]) counter++;
			else if(old<200)
			{
				fprintf(pFile,"     %.2i x %s\n",counter,stats[race][old].name);
				counter=1;
				old=Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]];
			}
			else
				old=Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]];
		}
		else
			if(Save[t]->program[s].built==1)
				fprintf(pFile,"     [%.2i:%.2i] [%.2i/%.2i] %s [%s]\n",(Save[t]->program[s].time+0)/60,(Save[t]->program[s].time+0)%60,Save[t]->program[s].need_Supply,Save[t]->program[s].have_Supply,stats[race][Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]]].name,error_m[Save[t]->program[s].success]);
	}

	printf("Build Order saved...\n");
	
        fprintf(pFile,"\n     ---Force at the end---\n");
		 
	for(s=0;s<MAX_GOALS;s++)
		if(Save[t]->force[s]>0)
			fprintf(pFile,"     %21s : %2i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[t]->force[s],Save[t]->ftime[s]/60,Save[t]->ftime[s]%60);
	fprintf(pFile,"\n     Harvested Minerals : %i\n",(short)(Save[t]->harvested_mins));
	fprintf(pFile,"     Harvested Gas      : %i\n",(short)(Save[t]->harvested_gas));
	fprintf(pFile,"     Minerals at the end: %i\n",(short)(Save[t]->mins));
	fprintf(pFile,"     Gas at the end     : %i\n",(short)(Save[t]->gas));
	fprintf(pFile,"[---------end--------]\n\n");
	printf("First solution [%.2i:%.2i] succesfully saved...\n",Save[t]->timer/60,Save[t]->timer%60);
	printf("Checking for other solutions:\n");
	fprintf(pFile,"Other solutions: \n\n");
	unsigned char otherfound=0;
	unsigned char newone=0;
	
	// print out other runs
	if(run>0)
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
			
		if((Save[u]->timer<settings.Max_Time)&&(t!=u)&&(newone==1))			
		{
			otherfound=1;
			fprintf(pFile,"[-----%2i. solution---]\n\n",u+1);
			fprintf(pFile,"     Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[u]->timer%60);
			if(race!=2) fprintf(pFile,"     Scouting unit after %.2i:%.2i minutes\n",settings.Scout_Time/60,settings.Scout_Time%60);
			if(settings.Time_to_Enemy>0) fprintf(pFile,"     Time to Enemy: %i seconds\n\n",settings.Time_to_Enemy);
			printf("Header saved... ");
			old=200;
			counter=1;
			for(s=0;s<=Save[u]->length;s++)
			{
				if(settings.Detailed_Output==0)
				{
					while(((Save[u]->program[s].time>=Save[u]->timer)||(Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]]>=MAX_GOALS))&&(s<MAX_LENGTH-1))
						s++;
			if(old==Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]]) counter++;
			else if(old<200)
			{
				fprintf(pFile,"     %.2i x %s\n",counter,stats[race][old].name);
				counter=1;
				old=Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]];
			}
			else
				old=Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]];
		}
		else
		if((Save[u]->program[s].time<Save[u]->timer)&&(Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]]<MAX_GOALS)&&((s==0)||(Save[u]->program[s].time>0)))
			
		fprintf(pFile,"     [%.2i:%.2i] [%.2i/%.2i] %s [%s]\n",(Save[u]->program[s].time+0)/60,(Save[u]->program[s].time+0)%60,Save[u]->program[s].need_Supply,Save[u]->program[s].have_Supply,stats[race][Build_Av[Save[t]->Code[s][Save[t]->program[s].dominant]]].name,error_m[Save[u]->program[s].success]);
	}

	printf("Build Order saved...\n");

	fprintf(pFile,"\n     ---Force at the end---\n");
	for(s=0;s<MAX_GOALS;s++)
		if(Save[u]->force[s]>0)
			fprintf(pFile,"     %21s : %3i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[u]->force[s],Save[u]->ftime[s]/60,Save[u]->ftime[s]%60);

	fprintf(pFile,"\n     Harvested Minerals : %i\n",(short)(Save[u]->harvested_mins));
	fprintf(pFile,"     Harvested Gas      : %i\n",(short)(Save[u]->harvested_gas));
	fprintf(pFile,"     Minerals at the end: %i\n",(short)(Save[u]->mins));
	fprintf(pFile,"     Gas at the end     : %i\n",(short)(Save[u]->gas));
	fprintf(pFile,"[---------end--------]\n\n");
	printf("%i. solution [%.2i:%.2i] succesfully saved...\n",u+1,Save[u]->timer/60,Save[u]->timer%60);
		}
	}
	if(otherfound==0)
	{
		fprintf(pFile,"None found\n");
		printf("None found!\n");
	}
       
	fclose (pFile);
	printf("%s closed. All Data were saved.\n\n Thank you for using StarCalc!\n",O);
	printf("Have a nice day and visit www.clawsoftware.de!\n");

	// Have a nice day
	
	//TODO: Recheck the code whether REALLY all pointers / data are deleted/freed...
	
	for(s=0;s<MAX_PLAYER;s++)
		player[s]=NULL;
	for(s=0;s<RUNNINGS;s++)
		Save[s]=NULL;
 
	return 0;
};

