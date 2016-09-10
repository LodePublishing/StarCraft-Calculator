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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "io.h"
#include "race.h"
#include "text.h"
#include "settings.h"

#define COLOR_1 34
#define COLOR_2 36
#define COLOR_3 37

// Here are some global variables (accessible by any class due to 'extern' declaration in 'main.h'
int gRace,gColors;
MAP gMap[MAX_LOCATIONS];

int RACE::isBuildable[UNIT_TYPE_COUNT];
int RACE::isVariable[UNIT_TYPE_COUNT];
int RACE::genoToPhaenotype[UNIT_TYPE_COUNT];
int RACE::phaenoToGenotype[UNIT_TYPE_COUNT];
int RACE::maxBuildTypes;
int RACE::goalCount;
int RACE::allGoal[UNIT_TYPE_COUNT]; //former goal...
int  RACE::globalGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT];
GOAL RACE::goal[MAX_GOALS];
int RACE::basicBuildOrder[2][MAX_LENGTH];
int RACE::basicLength;



const Stats* gpStats;

int compare(const void* a,const void* b)
{
	if(( (*(RACE*)a).pFitness<(*(RACE*)b).pFitness)||(((*(RACE*)a).pFitness==(*(RACE*)b).pFitness)&&((*(RACE*)a).sFitness<=(*(RACE*)b).sFitness)))
		return (1);
	else if(( (*(RACE*)a).pFitness>(*(RACE*)b).pFitness)|| ((*(RACE*)a).sFitness>(*(RACE*)b).sFitness))
		return (-1);
	else return(0);
};

int determine(int g1,int y1,int g2,int y2,int g3,int y3)
{
	if((y2-y1)*(g3-g2)==(g2-g1)*(y3-y2)) return(0);
	return (((y3-y2)*(2*g2-g1-g3)*(g2-g1))/((y2-y1)*(g3-g2)-(g2-g1)*(y3-y2)));
}

int main(int argc, char* argv[])
{	
        RACE * Save[RUNNINGS];
        RACE Savet[RUNNINGS];
        RACE playert[MAX_PLAYER];
        RACE* pPlayer[MAX_PLAYER];

	int tgGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT];
	struct boLog
	{
	        int count;
		int order;
	} bolog[MAX_LENGTH],globalForcelog[MAX_GOALS];
	

	// TODO: make some significant variables...	
	int run,rfit,afit,sfit;
	int counter;
	int time_graphics_counter, resources_graphics_counter;
	
	char I[11],O[9],R[7];
	char tmp[255];
	int old_time,old_pFitness,old_sFitness,old,old_t,old_sup,generation,calc,t,time_difference,resources_difference;

	int race_size;

	unsigned char a;
// TODO: maybe put them to settings	
	time_graphics_counter=16;time_difference=0;
	resources_graphics_counter=16;resources_difference=0;
	generation=0;
    	run=0;
    	afit=0;
    	rfit=0;
    	sfit=0;
	old=200;
	counter=1;
	old_pFitness=0;
	old_sFitness=0;

        for(int i=0;i<RUNNINGS;i++) Save[i]=&Savet[i];
        for(int i=0;i<MAX_PLAYER;i++) pPlayer[i]=&playert[i];



	gMap[0].mineralCount=0;gMap[0].geysirCount=0; // The wayne location... 
	gMap[1].mineralCount=8;gMap[1].geysirCount=1; //Main
	gMap[2].mineralCount=0;gMap[2].geysirCount=0; //Front
	gMap[3].mineralCount=8;gMap[3].geysirCount=1; //Exe
	gMap[4].mineralCount=0;gMap[4].geysirCount=0; //Center
	gMap[5].mineralCount=8;gMap[5].geysirCount=1; //EnemyExe
	gMap[6].mineralCount=0;gMap[6].geysirCount=0; //EnemyFront
	gMap[7].mineralCount=8;gMap[7].geysirCount=1; //EnemyMain

	gMap[1].distance[0]=0;gMap[1].distance[1]=15;gMap[1].distance[2]=25;gMap[1].distance[3]=50;gMap[1].distance[4]=75;gMap[1].distance[5]=85;gMap[1].distance[6]=100;

	gMap[2].distance[0]=15;gMap[2].distance[1]=0;gMap[2].distance[2]=10;gMap[2].distance[3]=35;gMap[2].distance[4]=60;gMap[2].distance[5]=70;gMap[2].distance[6]=85;

	gMap[3].distance[0]=25;gMap[3].distance[1]=10;gMap[3].distance[2]=0;gMap[3].distance[3]=40;gMap[3].distance[4]=65;gMap[3].distance[5]=75;gMap[3].distance[6]=90;

	gMap[4].distance[0]=50;gMap[4].distance[1]=35;gMap[4].distance[2]=40;gMap[4].distance[3]=0;gMap[4].distance[4]=40;gMap[4].distance[5]=35;gMap[4].distance[6]=50;

        gMap[5].distance[0]=90;gMap[5].distance[1]=75;gMap[5].distance[2]=65;gMap[5].distance[3]=40;gMap[5].distance[4]=0;gMap[5].distance[5]=10;gMap[5].distance[6]=25;
	
	gMap[6].distance[0]=85;gMap[6].distance[1]=70;gMap[6].distance[2]=60;gMap[6].distance[3]=35;gMap[6].distance[4]=10;gMap[6].distance[5]=0;gMap[6].distance[6]=15;

	gMap[7].distance[0]=100;gMap[7].distance[1]=85;gMap[7].distance[2]=75;gMap[7].distance[3]=50;gMap[7].distance[4]=25;gMap[7].distance[5]=15;gMap[7].distance[6]=0;
//Lost Temple ohne Mins exen
	
	srand(time(NULL));
	clrscr();
	
	if(settings.Init()==1)
	{
		printf("Error during settings. Repair / Reinstall the settings.txt file!\n");
	        return(1);
	}

	gRace=5;
        printf("Press '1' for Terran, '2' for Protoss or '3' for Zerg.\n");
        while(gRace==5)
                {
                        gRace=TERRA;
                        a=getchar();
                        if(((a-49)>=0)&&((a-49)<3)) gRace=a-49;
                }
        printf("RACE: %i",gRace);

	
	printf("Setting Race and initializing player models... ");
	
	switch(gRace)
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

	gpStats=&(stats[gRace][0]);

	race_size=sizeof(RACE);
	
	// Sets additional gGoals, say the user enters "Guardien" Set_Goals will also set Hive, Greater Spire, Lair, Queens Nest, Extractor and Spawning Pool as a gGoal 
	
	pPlayer[0]->Set_Goals(I);
	pPlayer[0]->AdjustMining();	
	pPlayer[0]->generateBasicBuildorder();

	for(int s=MAX_PLAYER;s--;)
		pPlayer[s]->Restart();
        old_time=settings.Max_Time;

	for(int s=MAX_LENGTH;s--;) bolog[s].count=0;

	//some blabla
	printf("\n\n OK! System is ready to start. Press Enter to continue...\n");
	a=getchar();
	clrscr();
	printf("Welcome to StarCraftCalculator v1.03 [August/14/2003]!\n");
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
	printf("Buildable items:\n");
	
	for(int s=0;s<UNIT_TYPE_COUNT;s++)
		if((pPlayer[0]->allGoal[s]==0)&&(pPlayer[0]->isBuildable[s]>0))
			printf("- %20s : %2i (%s)\n",gpStats[s].name,pPlayer[0]->allGoal[s],kurz[gRace][s].b);
	
	printf("\nGoals:\n");
	
	for(int s=0;s<MAX_GOALS;s++)
		if(pPlayer[0]->goal[s].count>0)
		{
			printf("- %20s : %2i (%s) [at %2i]",gpStats[pPlayer[0]->goal[s].unit].name,pPlayer[0]->goal[s].count,kurz[gRace][pPlayer[0]->goal[s].unit].b,pPlayer[0]->goal[s].location);
			if(pPlayer[0]->goal[s].time>0)
				printf(" [%.2i:%.2i]",pPlayer[0]->goal[s].time/60,pPlayer[0]->goal[s].time%60);
			printf("\n");
		}

	printf("\n\n");
	printf("Press ENTER to let the calculation start!\n");
	a=getchar();
	clrscr();

// OK, lets start the main loop :)
#ifdef WIN32
	SetConsoleActiveScreenBuffer(scr);
#endif
	calc=0;

	while(run<RUNNINGS)
	{
	  	generation++;
                rfit++;
		old_time=pPlayer[0]->timer;
		old_pFitness=pPlayer[0]->pFitness;
	        old_sFitness=pPlayer[0]->sFitness;	
		for(int s=MAX_PLAYER;s--;)
			(*pPlayer[s]).Init();
		for(int s=1;s<MAX_PLAYER;s++)
			(*pPlayer[s]).Mutate();
		for(int s=MAX_PLAYER;s--;)
			(*pPlayer[s]).Calculate();
		
// Determine the best build order depending on the primary fitness (needed time and completed gGoals) and the secondary fitness (gathered resources)
		qsort(*pPlayer,MAX_PLAYER,race_size,compare);


		// bigger than afit or sfit? good! We completed another gGoal or at least a part of it
		// Maybe implement another parameter to deactivate sFitness... will (maybe!) cause faster calculation but worse build orders (in terms of resources)
		if((pPlayer[0]->sFitness>sfit)||(pPlayer[0]->pFitness>afit))
		{
			sfit=pPlayer[0]->sFitness;
			if(pPlayer[0]->pFitness>afit)
				afit=pPlayer[0]->pFitness;
			rfit=0;
		}
		
		//Print the screen :)
		if(settings.Verbose==1)
		{
			gotoxy(0,0);
			setColor(37);
		   	print("Calculating Status:");

			if(time_graphics_counter<160) time_graphics_counter++;
			if(resources_graphics_counter<160) resources_graphics_counter++;
			if(old_sFitness<pPlayer[0]->sFitness)
			{
				resources_graphics_counter=0;
				resources_difference=pPlayer[0]->sFitness-old_sFitness;
			}
			
			if(pPlayer[0]->timer<settings.Max_Time)
			{
				if(old_time>pPlayer[0]->timer) 
				{
					time_graphics_counter=0;
					time_difference=old_time-pPlayer[0]->timer;
				}
				if(time_graphics_counter<resources_graphics_counter)
					setAt(time_graphics_counter);
				else setAt(resources_graphics_counter);
									
				if(time_graphics_counter<=16)
					printf(" got faster solution! [-%2i]  ",time_difference);
				else
				if(resources_graphics_counter<=16)
					printf(" improved resources! [+%2i]   ",resources_difference/100);
				else
					 print(" optimizing resources...      ");
			}
			else			
			{
				if((old_pFitness/100)<(pPlayer[0]->pFitness/100)) 
				{
					time_graphics_counter=0;
					time_difference=(pPlayer[0]->pFitness/100)-(old_pFitness/100);
				}

				if(time_graphics_counter<resources_graphics_counter)
					setAt(time_graphics_counter);
				else setAt(resources_graphics_counter);
				
				if(time_graphics_counter<=16)
					printf(" another gGoal complete! [+%2i]",time_difference);
				else
				if(resources_graphics_counter<=16)
				        printf(" improved resources! [+%4i]",resources_difference/100);
				else
					 print(" searching . . .              ");
			}
		setColor(37);
		gotoxy(1,2);sprintf(tmp,"%i runs and %i+ generations remaining. [Total %i generations]      ",RUNNINGS-run,settings.Max_Generations-rfit,generation);
		print(tmp);
		
		gotoxy(0,4);
		print("[resources] [time]");
		gotoxy(0,5);
		print("------------------");
		setAt(resources_graphics_counter);
		gotoxy(2,6);sprintf(tmp,"  %5.4i",(pPlayer[0]->harvested_mins+pPlayer[0]->harvested_gas)/100);
		print(tmp);
		
		setAt(time_graphics_counter);
		gotoxy(13,6);if(pPlayer[0]->timer<settings.Max_Time) { sprintf(tmp,"%.2i:%.2i",pPlayer[0]->timer/60,pPlayer[0]->timer%60);print(tmp);} else { sprintf(tmp," %i ",pPlayer[0]->pFitness);print(tmp);};
		
	setColor(COLOR_1);
if((calc%80==0)||(calc%80==1)) setColor(COLOR_3); else if((calc%80==78)||(calc%80==79)||(calc%80==2)||(calc%80==3)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,3);print("     ***    ***   ***   *      **     ***");
if((calc%80==2)||(calc%80==3)) setColor(COLOR_3); else if((calc%80==0)||(calc%80==1)||(calc%80==4)||(calc%80==5)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,4);print("   *      *     *      *     *  *       *");
if((calc%80==4)||(calc%80==5)) setColor(COLOR_3); else if((calc%80==2)||(calc%80==3)||(calc%80==6)||(calc%80==7)) setColor(COLOR_2); else setColor(COLOR_1);
	gotoxy(20,5);print("    *    *     *      *     *  *      *  ");
if((calc%80==6)||(calc%80==7)) setColor(COLOR_3); else if((calc%80==4)||(calc%80==5)||(calc%80==8)||(calc%80==9)) setColor(COLOR_2); else setColor(COLOR_1);
	gotoxy(20,6);print("    *   *     *      *     *  *       * ");
if((calc%80==8)||(calc%80==9)) setColor(COLOR_3); else if((calc%80==6)||(calc%80==7)||(calc%80==10)||(calc%80==11)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,7);print("***     ***   ***   *  *   **     ***  ");
		
	for(int s=1;s<MAX_LOCATIONS;s++)
		for(int t=UNIT_TYPE_COUNT;t--;)
			tgGoal[s][t]=pPlayer[0]->globalGoal[s][t]; //reset the goals (to sign @ the unit list)

	
		//bolog logs how long which build order stands there (you know, the gColors ;-)
		//TODO: recognize moved blocks to stress real Mutations
		
		old=200;
		old_t=0;
		old_sup=0;
		counter=1;
		t=0;
		setColor(37);

//The Build order List		
		if(settings.Detailed_Output==1)
		{
			for(int s=0;s<5;s++)
                	{
				t=0;
		                while((t<HEIGHT)&&(pPlayer[0]->program[(s+1)*HEIGHT-t].built==0)) t++;
		               	gotoxy(WIDTH*s+2,25-settings.Console24Lines);//WIN32 1 <> LINUX 0
				if((t<HEIGHT)||(pPlayer[0]->program[s*HEIGHT].built>0))
				{
					sprintf(tmp,"[%.2i:%.2i]",pPlayer[0]->program[(s+1)*HEIGHT-t].time/60,pPlayer[0]->program[(s+1)*HEIGHT-t].time%60);
					print(tmp);
				}
				else print("       ");
			}
			
			t=0;
			for(int s=0;s<MAX_LENGTH;s++)
			{
				gotoxy((t/HEIGHT)*WIDTH,9+t%HEIGHT-settings.Console24Lines);
				t++;
				setColor(37);
				if(pPlayer[0]->program[s].built==1)
				{
					if(bolog[s].order==pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s])
        		           	{
				        	if(bolog[s].count<160)
							bolog[s].count++;
					} else
					{
						bolog[s].count=0;
						bolog[s].order=pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s];
					}
					
					if(tgGoal[pPlayer[0]->program[s].location][pPlayer[0]->genoToPhaenotype[pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s]]]>0) //~~~~~~ location=0?
					{
						setColor(34);
						tgGoal[pPlayer[0]->program[s].location][pPlayer[0]->genoToPhaenotype[pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s]]]--;
						print("@");
					} else print(" ");
					setColor(35);
					sprintf(tmp,"%c",error_sm[pPlayer[0]->program[s].success]);
					print(tmp);
					setAt(bolog[s].count);
					sprintf(tmp,"%s",kurz[gRace][pPlayer[0]->genoToPhaenotype[pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s]]].b);
					print(tmp);
					setColor(37);
					if(pPlayer[0]->program[s].need_Supply<100)
						sprintf(tmp," %.2i",pPlayer[0]->program[s].need_Supply);
					else sprintf(tmp,"%3i",pPlayer[0]->program[s].need_Supply);
					print(tmp);
				}
				else print(" ------    "); 
			}
		}
		else
		{
		for(int s=0;(s<MAX_LENGTH)&&(t<3*HEIGHT+3);s++)
		{
			while((pPlayer[0]->program[s].built==0)&&(s<MAX_LENGTH-1))
                        	s++;
                        if(old==pPlayer[0]->genoToPhaenotype[pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s]]) counter++;
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
				sprintf(tmp,"%s",kurz[gRace][old].b);
				print(tmp);
				setColor(37);
				sprintf(tmp," %.2i:%.2i ",old_t/60,old_t%60);
				print(tmp);
				setColor(35);
				if(old_sup<100) sprintf(tmp,"%.2i",old_sup); else sprintf(tmp,"%3i",old_sup);
				print(tmp);
				setColor(37);
				counter=1;
				old=pPlayer[0]->genoToPhaenotype[pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s]];
				old_t=pPlayer[0]->program[s].time;
				old_sup=pPlayer[0]->program[s].need_Supply;
			}
			else
			{
				old=pPlayer[0]->genoToPhaenotype[pPlayer[0]->Code[pPlayer[0]->program[s].dominant][s]];
				old_t=pPlayer[0]->program[s].time;
				old_sup=pPlayer[0]->program[s].need_Supply;
			}
		}
		for(int s=t;(s<=MAX_LENGTH)&&(s<3*(HEIGHT+1));s++)
		{
			gotoxy((s/(HEIGHT+1))*17,9+s%(HEIGHT+1)-settings.Console24Lines);
			print("  ------       x");
		}
		}
		//TODO: In io rein!

		setColor(37);

		t=4;
		gotoxy(66,3);print("Force:");
		for(int s=0;s<EXTRACTOR+2;s++)
			if(pPlayer[0]->allGoal[s]>0)
			{
				if(globalForcelog[s].order==pPlayer[0]->location[0].force[s])
                        	{
		                      if(globalForcelog[s].count<160)
								globalForcelog[s].count++;
			        }
                        	else
			        {
				 	globalForcelog[s].count=0;
				        globalForcelog[s].order=pPlayer[0]->location[0].force[s];
				}
				
				setAt(globalForcelog[s].count);
				gotoxy(70,t);				
				sprintf(tmp,"%s:%2i ",kurz[gRace][s].b,pPlayer[0]->location[0].force[s]);
				print(tmp);
				t++;
				if(t>23-settings.Console24Lines) s=EXTRACTOR+2;
				
				//Well... it can't print out more than ~20 goals :/ 
			}
		if(t<=23-settings.Console24Lines)
		{
			gotoxy(66,t);
			setColor(37);
			print("non-goals:");
			t++;
			for(int s=0;s<EXTRACTOR+2;s++)
				if((pPlayer[0]->allGoal[s]==0)&&(pPlayer[0]->location[0].force[s]))
				{
					if(globalForcelog[s].order==pPlayer[0]->location[0].force[s])
					{
						if(globalForcelog[s].count<160)
							globalForcelog[s].count++;
					}
					else
					{
						globalForcelog[s].count=0;
						globalForcelog[s].order=pPlayer[0]->location[0].force[s];
					}
					setAt(globalForcelog[s].count);
					gotoxy(70,t);
					sprintf(tmp,"%s:%2i ",kurz[gRace][s].b,pPlayer[0]->location[0].force[s]);
					print(tmp);
					t++;
					if(t>23-settings.Console24Lines) s=EXTRACTOR+2;
				}
		for(int s=23-t-settings.Console24Lines;s--;)
		{
			gotoxy(70,t+s);
			print("         ");
		}
		}
		calc++; //Graphics counter
	}

// End of Verbose
		
		for(int s=10;s--;)
		{
			t=rand()%(MAX_PLAYER-1)+1;
			memcpy(pPlayer[t]->Code[0],pPlayer[0]->Code[0],MAX_LENGTH*4);    
			memcpy(pPlayer[t]->Code[1],pPlayer[0]->Code[1],MAX_LENGTH*4);
			pPlayer[t]->pFitness=pPlayer[0]->pFitness;
			pPlayer[t]->sFitness=pPlayer[0]->sFitness;
		}

		for(int s=1;s<MAX_PLAYER/2;s++)
		{
			t=rand()%MAX_PLAYER;
			if((pPlayer[s]->pFitness<pPlayer[t]->pFitness)||((pPlayer[s]->pFitness==pPlayer[t]->pFitness)&&(pPlayer[s]->sFitness<pPlayer[t]->sFitness)))
			{
				memcpy(pPlayer[s]->Code[0],pPlayer[t]->Code[0],MAX_LENGTH*4);
                        	memcpy(pPlayer[s]->Code[1],pPlayer[t]->Code[1],MAX_LENGTH*4);
			}
			pPlayer[s]->pFitness=pPlayer[t]->pFitness;
			pPlayer[s]->sFitness=pPlayer[t]->sFitness;
		}
		
		for(int s=0;s<MAX_PLAYER/4;s++)
		{
			t=rand()%(MAX_PLAYER/2);
			int c1=rand()%(MAX_PLAYER/2)+MAX_PLAYER/2;
			int c2=rand()%(MAX_PLAYER/2)+MAX_PLAYER/2;
			pPlayer[s]->crossOver(pPlayer[t],pPlayer[c1],pPlayer[c2]);
		}

	
		// Save the program when 'Max_Generations' Generations were no change
	    if(rfit>=settings.Max_Generations)
		{
			rfit=0;
			generation=0;
			//evtl ==operator definieren in race.h/cpp
			
			memcpy(Save[run]->Code[0],pPlayer[0]->Code[0],MAX_LENGTH*4);
	                memcpy(Save[run]->Code[1],pPlayer[0]->Code[1],MAX_LENGTH*4);
			for(int s=MAX_LENGTH;s--;)
			{
				Save[run]->program[s].time=pPlayer[0]->program[s].time;
				Save[run]->program[s].need_Supply=pPlayer[0]->program[s].need_Supply;
				Save[run]->program[s].have_Supply=pPlayer[0]->program[s].have_Supply;
				Save[run]->program[s].success=pPlayer[0]->program[s].success;
				Save[run]->program[s].built=pPlayer[0]->program[s].built;
				Save[run]->program[s].dominant=pPlayer[0]->program[s].dominant;
			}

			Save[run]->pFitness=pPlayer[0]->pFitness;
			Save[run]->timer=pPlayer[0]->timer;
			Save[run]->harvested_mins=pPlayer[0]->harvested_mins;
			Save[run]->harvested_gas=pPlayer[0]->harvested_gas;
			Save[run]->mins=pPlayer[0]->mins;
			Save[run]->gas=pPlayer[0]->gas;
			Save[run]->length=pPlayer[0]->length;
			Save[run]->mutationRate=pPlayer[0]->mutationRate;

			for(int s=0;s<MAX_LOCATIONS;s++)
				memcpy(Save[run]->location[s].force,pPlayer[0]->location[s].force,MAX_GOALS*4);
			memcpy(Save[run]->ftime,pPlayer[0]->ftime,MAX_GOALS*4);

		        for(int s=MAX_PLAYER;s--;)
			       	pPlayer[s]->Restart();
			
			afit=0;
			sfit=0;
			old_time=settings.Max_Time; 
			old_pFitness=0;
			old_sFitness=0;
			run++;
			for(int s=MAX_LENGTH;s--;)
				bolog[s].count=0;
		}
//	    if(pPlayer[0]->location[0].force[13]==255)
//		    a=getchar();
	    
	} // end while...

	//start of the file output block...

// Run canceled before all 5 runs were calculated? => Save the present run
/*	if(run<RUNNINGS)
	{
		for(int s=0;s<MAX_LENGTH;s++)
		{
			Save[run]->Codeprogram[s].order=pPlayer[0]->Code[s][pPlayer[0]->program[s].dominant];
			Save[run]->program[s].time=pPlayer[0]->program[s].time;
			Save[run]->program[s].have_Supply=pPlayer[0]->program[s].have_Supply;
			Save[run]->program[s].need_Supply=pPlayer[0]->program[s].need_Supply;
			Save[run]->program[s].success=pPlayer[0]->program[s].success;
		}	
		Save[run]->pFitness=pPlayer[0]->pFitness;
		Save[run]->timer=pPlayer[0]->timer;
		Save[run]->harvested_mins=pPlayer[0]->harvested_mins;
		Save[run]->harvested_gas=pPlayer[0]->harvested_gas;	
		Save[run]->mins=pPlayer[0]->mins;
		Save[run]->gas=pPlayer[0]->gas;
		Save[run]->length=pPlayer[0]->length;

		for(int s=0;s<MAX_GOALS;s++)
		{
			Save[run]->location[0].force[s]=pPlayer[0]->location[0].force[s];
			Save[run]->ftime[s]=pPlayer[0]->ftime[s];
		}
	}*/
	
	t=0;
//Determine the best run
	if(run>0)
	{
		afit=0;
		sfit=0;
		for(int s=RUNNINGS;s--;)
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
	        printf(" - Reduce the amount of goals\n");
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
	fprintf(pFile,"---StarCraftCalculator by ClawSoftware.de [v1.03 ALPHA]--\n");
	fprintf(pFile,"---------------------------------------------------\n\n");
	for(int u=0;u<run;u++)
	{
		int newone=1;// tatsaechlich neue Loesung?
		for(int s=0;s<u;s++)
		{
			newone=newone&&(((short)Save[u]->harvested_mins!=(short)Save[s]->harvested_mins)||
				        ((short)Save[u]->harvested_gas!=(short)Save[s]->harvested_gas)||
				        ((short)Save[u]->timer!=(short)Save[s]->timer)||
				        ((short)Save[u]->mins!=(short)Save[s]->mins)||
				        ((short)Save[u]->gas!=(short)Save[s]->gas));
		}
			
		if((Save[u]->timer<settings.Max_Time)&&(t!=u)&&(newone==1))			
		{
			fprintf(pFile,"[-----%2i. solution---]\n\n",u+1);
			fprintf(pFile,"MutationRate: %i\n",Save[t]->mutationRate);
			fprintf(pFile,"     Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[u]->timer%60);
			printf("Header saved... ");
			old=200;
			counter=1;
			for(int s=0;s<=Save[u]->length;s++)
			{
				if(settings.Detailed_Output==0)
				{
					while(((Save[u]->program[s].time>=Save[u]->timer)||(pPlayer[0]->genoToPhaenotype[Save[t]->Code[Save[t]->program[s].dominant][s]]>=MAX_GOALS))&&(s<MAX_LENGTH-1))
						s++;
			if(old==pPlayer[0]->genoToPhaenotype[Save[t]->Code[Save[t]->program[s].dominant][s]]) counter++;
			else if(old<200)
			{
				fprintf(pFile,"     %.2i x %s\n",counter,gpStats[old].name);
				counter=1;
				old=pPlayer[0]->genoToPhaenotype[Save[t]->Code[Save[t]->program[s].dominant][s]];
			}
			else
				old=pPlayer[0]->genoToPhaenotype[Save[t]->Code[Save[t]->program[s].dominant][s]];
		}
		else
		if((Save[u]->program[s].time<Save[u]->timer)&&(pPlayer[0]->genoToPhaenotype[Save[t]->Code[Save[t]->program[s].dominant][s]]<UNIT_TYPE_COUNT)&&((s==0)||(Save[u]->program[s].time>0)))
			
		fprintf(pFile,"     [%.2i:%.2i] [%.2i/%.2i] %s [%s] (%i)\n",(Save[u]->program[s].time+0)/60,(Save[u]->program[s].time+0)%60,Save[u]->program[s].need_Supply,Save[u]->program[s].have_Supply,gpStats[pPlayer[0]->genoToPhaenotype[Save[t]->Code[Save[t]->program[s].dominant][s]]].name,error_m[Save[u]->program[s].success],Save[u]->program[s].location);
	}

	printf("Build Order saved...\n");

	fprintf(pFile,"\n     ---Force at the end---\n");
	for(int s=0;s<MAX_GOALS;s++)
		if(Save[u]->location[pPlayer[0]->goal[s].location].force[pPlayer[0]->goal[s].unit]>0)
			fprintf(pFile,"     %21s : %3i [Last one: %.2i:%.2i]\n",gpStats[pPlayer[0]->goal[s].unit].name,Save[u]->location[pPlayer[0]->goal[s].location].force[pPlayer[0]->goal[s].unit],Save[u]->ftime[s]/60,Save[u]->ftime[s]%60);

	fprintf(pFile,"\n     ---Overview locations---\n");
	for(int s=0;s<MAX_LOCATIONS;s++)
	{
		fprintf(pFile," Location %i:\n",s);
		for(int v=0;v<UNIT_TYPE_COUNT;v++)
			if(Save[u]->location[s].force[v]>0)
				fprintf(pFile,"     %21s : %3i \n",gpStats[v].name,Save[u]->location[s].force[v]);
	}

	fprintf(pFile,"\n     Harvested Minerals : %i\n",(short)(Save[u]->harvested_mins));
	fprintf(pFile,"     Harvested Gas      : %i\n",(short)(Save[u]->harvested_gas));
	fprintf(pFile,"     Minerals at the end: %i\n",(short)(Save[u]->mins));
	fprintf(pFile,"     Gas at the end     : %i\n",(short)(Save[u]->gas));
	fprintf(pFile,"[---------end--------]\n\n");
	printf("%i. solution [%.2i:%.2i] succesfully saved...\n",u+1,Save[u]->timer/60,Save[u]->timer%60);
		}
	}
	fclose (pFile);
	printf("%s closed. All Data were saved.\n\n Thank you for using StarCalc!\n",O);
	printf("Have a nice day and visit www.clawsoftware.de!\n");

	// Have a nice day
	
	//TODO: Recheck the code whether REALLY all pointers / data are deleted/freed...
	
	for(int s=0;s<MAX_PLAYER;s++)
		pPlayer[s]=NULL;
	for(int s=0;s<RUNNINGS;s++)
		Save[s]=NULL;
 
	return 0;
};

