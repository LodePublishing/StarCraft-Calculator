// TODO: replace '60' with the max buildings constant
// TODO: reorganize the CLASSes (private,protected,public entities...)
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "terra.h"
#include "zerg.h"
#include "protoss.h"

#include "namen.h"
#include "settings.h"
#define HEIGHT 16 // Number of entries (build order list)
#define WIDTH 11 // witdh of the entries
#define gizmowidth 35


//using namespace std;

inline unsigned char UpperCase(char x) {if(x>91) return (x-32); else return(x);}

// Here are some global variables (accessible by any class due to 'extern' declaration in 'main.h'
double mining[57],gasing[5];
unsigned short Ziel[60],Build_Av[60],Build_Bv[60],tgoal[60]; 
unsigned char Vespene_Av,Max_Build_Types,race;
unsigned short total_goals,building_types;
unsigned char num,Vespene_Extractors;
GOAL goal[MAX_GOALS]; // GOAL := what buildings should be there AT THE END

RACE * player[MAX_PLAYER];

struct UNIT
{
	char text[150];
} unit[60];


struct boLog
{
	unsigned char count;
	unsigned char order;
} bolog[MAX_LENGTH],forcelog[60];

// Ugly functions, have to change them later
void setAt(unsigned char cnt)
{
	if(setup.colors==0) return;
	if(cnt<4) setattr(0,37,40);
	else if(cnt<8) setattr(0,33,40);
	else if(cnt<16) setattr(0,32,40);
	else if(cnt<32) setattr(0,36,40);
	else if(cnt<64) setattr(0,31,40);
	else setattr(0,34,40);
};

void setAt2(unsigned char cnt)
{
	if(setup.colors==0) return;
        if(cnt<=1) setattr(0,37,40);
        else if(cnt<=2) setattr(0,33,40);
        else if(cnt<=4) setattr(0,32,40);
        else if(cnt<=8) setattr(0,36,40);
        else if(cnt<=16) setattr(0,31,40);
        else setattr(0,37,40);
};

struct myBO
{
	unsigned char type,race,length,count;
	unsigned short code[26];
	unsigned short tmp;
} bo[MAX_LENGTH];

struct mySTATS
{
	unsigned short code[26];
        unsigned char length;	
} mystats[3][60];


int main(int argc, char* argv[])
{	
// TODO: make some significant variables...	
	unsigned short run,rfit,afit,sfit;
	unsigned char counter,gcount;
	char I[11],O[9],R[7];
	unsigned short old_time,old_fit,old,old_t,old_sup,s,t,u,generation,calc;
	unsigned char a,Test,z,tunit,translate;
	char * buffer;
	char * IOp;
	char * gizmo;
	unsigned short size,zahl;
	int i,j,k,f,countr[3];


	Vespene_Extractors=0;
// TODO: maybe put them to settings	
	race=5;
	Test=0;
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
	translate=0;
	
	
	srand(time(NULL));
	clrscr();
	
	if(setup.InitSettings()==1)
	{
		printf("Error during Setup. Repair / Reinstall the settings.txt file!\n");
	        return(1);
	}

#define gizmolength 865
//The green gizmo text at the top
	gizmo = new char[gizmolength];
	sprintf(gizmo,"                                        Attention Defenders of the United Earth Directorate!                                        This is Admiral DuGalle.                                        You were all briefed before we left earth, so you know that we have come here to conquer this sector in the name of humanity.                                        Should any of you have second thoughts about performing your assigned duties, be reminded that if we fail in our mission here, not one of us will be going home.                                        We stand or fall together in this forsaken wasteland.                                        Serve the directorate serve humanity...                                       All other priorities are secondary to victory!                                        Dugall out.                                        ");
	
	char * helper;
	helper=new char[1447];

// TODO: Farben!	
   	 sprintf(helper,"\nYou may call 'scc' with the following parameters:\n\nscc T|P|Z                         : Calculate best build order (goals given by\n                                    goal_t.txt, goal_p.txt or goal_z.txt)     \nscc                               : Same as above but you may chose the race  \n				    manually                                  \nscc -i <file with goals>          : same as above but use this file instead of\n                                    goal_*.txt (NO times yet)                 \nscc -b <goals>                    : same as above but use goals given by the  \n                                    command line (i.e. 'scc -b 5 Marines      \n                                    supplydepot battlecruiser')               \nscc -i <file with build order> -t : Use the build order given by this file and\n                                    calculate the time it needs (in the scc - \n                                    environment)                              \nscc -b <build order> -t           : same as 'scc -i <file> -t' but use the    \n                                    command line parameters as build order    \n                                    (i.e. 'scc -b 4 scvs supplydepot refinery \n                                    barracks 3 onescvtogas 4 scvs factory') \n\nCheck 'goal_t.txt', 'goal_p.txt', 'goal_z.txt' and especially 'settings.txt,too!\n                                                                Version 1.02b\n"); 

	if(argc<=1)
	{
		printf("%s",helper);
		delete helper;
	}
	else
	{
		if(UpperCase(argv[1][0])=='T')
			race=0;
		else if(UpperCase(argv[1][0])=='P')
			race=1;
		else if(UpperCase(argv[1][0])=='Z')
			race=2;
		else if((argc>2)&&(argv[1][0]=='-'))
		{
			if(UpperCase(argv[1][1])=='I')
			{
				translate=1; // We need a translation of the data later
				IOp = new char [sizeof(argv[2])]; 
				IOp=argv[2];
				FILE * pFile2;
				pFile2 = fopen(IOp,"rb");
				if(pFile2==NULL)
				{
					printf("FATAL ERROR: Build Order File %s not found.\n",IOp);
					printf("Exiting...\n");
					return(1);
				}
				printf("Checking build order input file [%s]...\n",IOp);
				printf("File found. Opening...\n");
				printf("File opened... reading...\n");
			        fseek (pFile2, 0, SEEK_END);
				size = ftell (pFile2);
				buffer = new char [size];
				fseek (pFile2, 0, SEEK_SET);
				fread(buffer,1,size,pFile2);
				fclose(pFile2);
				printf("File closed, data saved [%i Bytes].\n",size);
			} else  // not 'I'
	// B? User called 'scc' with a goal / build order list as parameter
			if(UpperCase(argv[1][1])=='B')
			{
				translate=1; // we need a translation of the data later
				size=0;
				for(t=2;t<argc;t++)
					size+=sizeof(argv[t])+100;
			//TODO: Find a better formula for size (segmentation faults!)	
				buffer = new char [size];
				for(t=0;t<size;t++)
					buffer[t]=0;
				s=0;
// Analyze the parameters and copy them into a buffer
				for(t=2;t<argc;t++)
				{
					u=0;
					if((argv[t][0]>47)&&(argv[t][0]<58))
					{
						while((argv[t][u]>47)&&(argv[t][u]<58))
						{
							buffer[s+u]=argv[t][u];
							u++;
						}
						s+=u;
						t++;
						u=0;
					}
					if(t<argc)
					{
						while(argv[t][u]>64)
						{
							buffer[s]=argv[t][u];
							u++;s++;
						}
					}
					buffer[s]=10;
					s++;
				}
			} else //not 'B', not 'I'
			{
				printf("%s",helper);
			        delete helper;
				return(1);
			}
	         } else //not '-'
		 {
                 	printf("%s",helper);
			delete helper;
			return(1);
		 }			 
	} // end of 'not argc<=1'
		
				
//TODO!! inform the user about the abort...			
	if(translate==1)
	{
		printf("Translating data...");
		
		for(t=0;t<MAX_LENGTH;t++)
		{
			for(s=0;s<26;s++) bo[t].code[s]=0;
			bo[t].type=0;
			bo[t].race=5;
			bo[t].length=0;
		}
		s=0;t=0;
		zahl=0;	

		while(s<size)
		{		
			//TODO: DOS / LINUX compability, next line 1310 <=> 10
					
			//translate the parameter arguments buffer to actual goals	
			if(buffer[s]==10)
			{
				if(zahl==0)
					t++;
				else 				
					bo[t].count=0;
				zahl=0;
			}
			else if((buffer[s]>47)&&(buffer[s]<58))
			{
				if((s<size-2)&&(buffer[s+2]>47)&&(buffer[s+2]<58))
				{
					setattr(0,31,40);
					printf("FATAL ERROR: Count too high! Do not use larger numbers than 99!\n");
					setattr(0,37,40);
					printf("Exiting...\n");
					return(1);
				}
				if((s<size-1)&&(buffer[s+1]>47)&&(buffer[s+1]<58))
				{
					zahl=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}
				else zahl=buffer[s]-48;
			}
			else if(buffer[s]>64)
			{
				bo[t].code[(int)(UpperCase(buffer[s])-65)]++;
				bo[t].length++;
				if(zahl>0)
					bo[t].count=zahl;
				else if(bo[t].count==0)
					bo[t].count=1;
				zahl=0;
			}
			s++;
		} // end of buffer checking

		//calculate the relative frequency of letters
		for(t=0;t<MAX_LENGTH;t++)
       	        	if(bo[t].length>0)
				for(s=0;s<26;s++)
				{
					bo[t].code[s]*=100;
					bo[t].code[s]=bo[t].code[s]/bo[t].length;
				}
		delete buffer;
		
		//Create lists with numbers of chars of the names in stats 	
		for(i=0;i<3;i++)
			for(j=0;j<60;j++)
			{
				mystats[i][j].length=0;
				for(t=0;t<26;t++)
					mystats[i][j].code[t]=0;
				
				for(t=0;t<21;t++)
					if(stats[i][j].name[t]>64)
					{
						mystats[i][j].length++;
						mystats[i][j].code[(int)(UpperCase(stats[i][j].name[t])-65)]++;
					}
				for(t=0;t<26;t++)
				{
					mystats[i][j].code[t]*=100;
					mystats[i][j].code[t]=mystats[i][j].code[t]/mystats[i][j].length;
				}
			} // End of creating relative frequencies out of stats names
			
		// Calculate the distance between the parameter and the stats names
		int Distance;
		for(k=0;k<MAX_LENGTH;k++)
			if(bo[k].count>0)
			{
				f=60000;
				for(i=0;i<3;i++)
					for(j=0;j<60;j++)
					{
						Distance=0;
						for(t=0;t<26;t++)
							Distance+=bo[k].code[t]*bo[k].code[t]+mystats[i][j].code[t]*mystats[i][j].code[t]-2*bo[k].code[t]*mystats[i][j].code[t];
						if(f>Distance)
						{
							f=Distance;
							bo[k].race=i;
							bo[k].type=j;
							bo[k].tmp=f;
						}
					}
			} // end of calculating distance
		 
		countr[0]=0;
		countr[1]=0;
		countr[2]=0;
// Counter to determine the race on basis of the frequency of races in the accumulated bo-data...
		for(i=0;i<MAX_LENGTH;i++)
			if(bo[i].race<3)
				countr[bo[i].race]++;
		if((countr[0]>countr[1])&&(countr[0]>countr[2]))
			race=0;
		else if(countr[1]>countr[2])
			race=1;
		else race=2;
	
//... and recheck the whole data on basis of the new information ( so that all bo's are in the same race...

		for(i=0;i<MAX_LENGTH;i++)
			if((bo[i].race!=race)&&(bo[i].race<3))
			{
				f=60000;
				for(j=0;j<60;j++)
				{
					Distance=0;
					for(t=0;t<26;t++)
					Distance+=(mystats[race][j].code[t]-bo[i].code[t])*(mystats[race][j].code[t]-bo[i].code[t]);
					if(f>Distance)
					{
						f=Distance;
						bo[i].race=race;
						bo[i].type=j;
						bo[i].tmp=f;
					}
				}
			}
		//end of race-recheck
				
		if((argc>3)&&(argv[argc-1][0]=='-')&&(UpperCase(argv[argc-1][1])=='T'))
			Test=2;
		else Test=1;

		setattr(0,32,40);
		printf(" ok\n");
		setattr(0,37,40);
	
	}
	
	//TODO: input additional arguments (like 'using defaults', scouttime or everything in settings.txt
	//TODO: Improve the implementation of parameter checking... looks really confusing 
	//Especially the order of the parameters...
	
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
	printf("[%s]",R);
	setattr(0,32,40);
	printf(" ok\n");
	setattr(0,37,40);

	if(Test==0)
	{
		if(setup.InitGoal(I)==1)
		{
			printf("Error during Setup. Repair / Reinstall the %s file!\n",I);
		        return(1);
		}
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
// TODO: Looks pretty hacked... maybe implement a better method later to allow the virtual construction in RACE
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
	
	if(Test>0)
	{
		for(s=0;s<MAX_GOALS;s++)
		{
			goal[s].what=0;
			goal[s].time=0;
		}
		for(s=0;s<MAX_LENGTH;s++)
			if(bo[s].count>0)
				goal[bo[s].type].what+=bo[s].count;		
	}

	// Sets additional goals, say the user enters "Guardien" Set_Goals will also set Hive, Greater Spire, Lair, Queens Nest, Extractor and Spawning Pool as a goal
	player[0]->Set_Goals(); 
	// Maybe just do 3 different functions instead of a function for every member of the class as it affects only global variables
	
	//Translate from [0..Max_Build_Types] to [0..building_types]
	//Max_Build_Types is goal specific, building_types only depends on the race
	for(s=0;s<Max_Build_Types;s++)
		Build_Bv[Build_Av[s]]=s; 

	setup.AdjustMining();

	if(Test<2)
		for(s=0;s<MAX_PLAYER;s++)
			player[s]->Restart();
	//Test == 2 => "-T" Parameter, just run a single run to determine the time it needs
	else if(Test==2) 
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
			for(s=0;s<building_types;s++)
				if(player[0]->force[s]>0)
					goal[s].what+=player[0]->force[s];
			player[0]->readjust_goals(); // actually affects only zerg (and archon of the protoss)

			printf("Translated goals:\n");
			for(s=0;s<building_types;s++)
				if(goal[s].what>0)
					printf("%s : %i\n",stats[race][s].name,goal[s].what); 
			printf("\nPress Enter to show time\n");

			a=getchar();
			player[0]->timer=setup.Max_Time;
			player[0]->IP=0;

			player[0]->Calculate();

		//print out all orders that are executed without problems
			printf("Successful build order:           [Requirement fulfilled]\n");
			for(s=0;s<MAX_LENGTH;s++)
				if(player[0]->program[s].built==1)
			printf("    %s [%.2i:%.2i] %s\n",stats[race][Build_Av[player[0]->program[s].order]].name,player[0]->program[s].time/60,player[0]->program[s].time%60,error_m[player[0]->program[s].success]);
				else s=MAX_LENGTH;
				
			printf("Needed Time: ");	
			setattr(0,32,40);
			printf("[%.2i:%.2i] ",player[0]->timer/60,player[0]->timer%60);
			setattr(0,37,40);
	
		// no solution? probably forgot a tech building or supply
			if(player[0]->timer==setup.Max_Time)
			{
				printf("\n => invalid build order, goals not reached.\n");	
				s=0;
			//determine the order which could not be executed
				while(s<MAX_LENGTH)
					if((s+1<MAX_LENGTH)&&(player[0]->program[s+1].built==0))
					{
						printf("When trying to build ");
					        setattr(0,32,40);
				       		printf("%s",stats[race][Build_Av[player[0]->program[s].order]].name);
					        setattr(0,37,40);
				                printf(" the following requirement failed : \n");
						setattr(0,31,40);
						printf("%80s\n",error_m[player[0]->program[s].success]);
					        setattr(0,37,40);
						printf("\nCheck your build order, reread the readme and/or contact ClawSoftware :)\n");
						s=MAX_LENGTH;
					} else s++;
				}
			printf("\n");
			return(0);	
	}
        old_time=setup.Max_Time;

	// Creating Unit text... (right bottom corner)
	for(s=0;s<60;s++)
		sprintf(unit[s].text,"              Unit Name: %21s    Buildtime: %3i seconds    Minerals : %3i    Gas      : %3i    Supply   : %i    Type     : %i                     ",stats[race][s].name,stats[race][s].BT,stats[race][s].mins,stats[race][s].gas,stats[race][s].supply,stats[race][s].type);
                         
			for(s=0;s<MAX_LENGTH;s++)
                                bolog[s].count=0;

//some blabla
printf("\n\n OK! System is ready to start. Press Enter to continue...\n");
	a=getchar();

	clrscr();
	gotoxy(0,0);

	printf("Welcome to StarCraftCalculator v1.02 [3/30/03]!\n");
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
	printf("\n");
	if(translate==0)
		printf("Goals (as stated in ""%s"")\n",I);
	else printf("Goals (as received from command line)\n");
	
	for(s=0;s<building_types;s++)
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
			player[s]->Init();
		for(s=1;s<MAX_PLAYER;s++)
			player[s]->Mutate();
		
		for(s=0;s<MAX_PLAYER;s++)
			player[s]->Calculate();

// Determine the best build order depending on the primary fitness (needed time and completed goals) and the secondary fitness (gathered resources)		
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
		if(setup.Verbose==1)
		{
		printf("Calculating [");
		setattr(0,32,40);
		for(s=0;s<gizmowidth;s++)
			printf("%c",gizmo[(calc/2+s)%gizmolength]);
		setattr(0,37,40);
		printf("] Status:");

		if(gcount<160) gcount++;
		if(player[0]->timer<setup.Max_Time)
		{
			if(old_time>player[0]->timer) gcount=0;
			if(gcount<=16)
			printf(" got faster solution! ");
				else
			printf(" optimizing resources.");
		}
		else			
		{
			if((old_fit/100)<(player[0]->pFitness/100)) gcount=0;

			if(gcount<=16)
			printf(" another goal complete");
			else
			printf(" searching . . .      ");
		}
		
		setattr(0,37,40);
		printf("\n%i runs and %i+ generations remaining. [Total %i generations]      \n\n",RUNNINGS-run,setup.Max_Generations-rfit,generation);
		printf("[resources] [time]\n");
		printf("------------------\n");
		gotoxy(2,6);printf("  %5.4i",(int)(player[0]->harvested_mins+player[0]->harvested_gas));
		setAt(gcount);
		gotoxy(13,6);if(player[0]->timer<setup.Max_Time) printf("%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);else printf(" ---- ");
		setattr(0,37,40);
		
setattr(0,31,40);
if((calc%80==0)||(calc%80==1)) setattr(0,37,40); else setattr(0,31,40);
	gotoxy(20,3);printf("     ooo    ooo   ooo   o      oo    ooo ");
if((calc%80==2)||(calc%80==3)) setattr(0,37,40); else setattr(0,31,40);
	gotoxy(20,4);printf("   o      o     o      o     o  o       o");
if((calc%80==4)||(calc%80==5)) setattr(0,37,40); else setattr(0,31,40);
	gotoxy(20,5);printf("    o    o     o      o     o  o      o  ");
if((calc%80==6)||(calc%80==7)) setattr(0,37,40); else setattr(0,31,40);
	gotoxy(20,6);printf("    o   o     o      o     o  o     o    ");
if((calc%80==8)||(calc%80==9)) setattr(0,37,40); else setattr(0,31,40);
	gotoxy(20,7);printf("ooo     ooo   ooo   o  o   oo     ooooo  ");
		
		for(s=0;s<MAX_GOALS;s++)
			tgoal[s]=goal[s].what;
//bolog logs how long which build order stands there (you know, the colors ;-)
		//TODO: recognize moved blocks to stress real Mutations
		
		old=200;
		old_t=0;
		old_sup=0;
		counter=1;
		t=0;
		setattr(0,37,40);
			
		if(setup.Detailed_Output==1)
		{
			for(s=0;s<5;s++)
                	{
		       		t=0;
		                while((t<HEIGHT)&&(player[0]->program[(s+1)*HEIGHT-t].built==0)) t++;
		               	gotoxy(WIDTH*s+2,25);
				if((t<HEIGHT)||(player[0]->program[s*HEIGHT].built>0))
					printf("[%.2i:%.2i]",player[0]->program[(s+1)*HEIGHT-t].time/60,player[0]->program[(s+1)*HEIGHT-t].time%60);
				else printf("       ");
			}
			
			t=0;
			for(s=0;s<MAX_LENGTH;s++)
			{
				gotoxy((t/HEIGHT)*WIDTH,9+t%HEIGHT);
				t++;
				setattr(0,37,40);
				if(player[0]->program[s].built==1)
				{
					if(bolog[s].order==player[0]->program[s].order)
                                	{
				        	if(bolog[s].count<160)
							bolog[s].count++;
					} else
					{
						bolog[s].count=0;
						bolog[s].order=player[0]->program[s].order;
					}
					
					setattr(0,34,40);
					if(tgoal[Build_Av[player[0]->program[s].order]]>0)
					{
						printf("@");
						tgoal[Build_Av[player[0]->program[s].order]]--;
					} else printf(" ");
					setattr(0,35,40);
					printf("%c",error_sm[player[0]->program[s].success]);
					setAt(bolog[s].count);
					printf("%s",kurz[race][Build_Av[player[0]->program[s].order]].b);
					setattr(0,37,40);
					if(player[0]->program[s].need_Supply<100)
						printf(" %.2i",player[0]->program[s].need_Supply);
					else printf("%3i",player[0]->program[s].need_Supply);
				}
				else printf(" ------    "); 
			}
		}
		else
		{
		for(s=0;(s<MAX_LENGTH)&&(t<3*HEIGHT+3);s++)
		{
			while((player[0]->program[s].built==0)&&(s<MAX_LENGTH-1))
                        	s++;
                        if(old==Build_Av[player[0]->program[s].order]) counter++;
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
				
				gotoxy((t/(HEIGHT+1))*17,9+t%(HEIGHT+1));
				if(counter>1) printf("%2i",counter); else printf("  ");
				setAt(bolog[t].count);
				t++;
				printf("%s",kurz[race][old].b);
				setattr(0,37,40);
			        printf(" %.2i:%.2i ",old_t/60,old_t%60);
				setattr(0,35,40);
				if(old_sup<100) printf("%.2i",old_sup); else printf("%3i",old_sup);
				setattr(0,37,40);
				counter=1;
				old=Build_Av[player[0]->program[s].order];
				old_t=player[0]->program[s].time;
				old_sup=player[0]->program[s].need_Supply;
			}
			else
			{
				old=Build_Av[player[0]->program[s].order];
				old_t=player[0]->program[s].time;
				old_sup=player[0]->program[s].need_Supply;
			}
		}
		for(s=t;(s<=MAX_LENGTH)&&(s<3*(HEIGHT+1));s++)
		{
			gotoxy((s/(HEIGHT+1))*17,9+s%(HEIGHT+1));
			printf("  ------       x");
		}
		}

		setattr(0,37,40);

		t=4;
		gotoxy(66,3);printf("Force:");
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
				        forcelog[s].order=player[0]->force[s];
				}
				
				setAt(forcelog[s].count);
				gotoxy(70,t);				
				printf("%s:%2i ",kurz[race][s].b,player[0]->force[s]);
				t++;
			}
		gotoxy(66,t);
		// TODO: insert a check for t (for runs with many goals)
		setattr(0,37,40);
		printf("non-goals:");
		t++;
		for(s=0;s<building_types;s++)
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
					printf("%s:%2i ",kurz[race][s].b,player[0]->force[s]);
					t++;
			}
		for(s=0;s<23-t;s++)
		{
			gotoxy(70,t+s);
			printf("         ");
		}
		
		setattr(0,37,40);
		gotoxy(54,25);
	 	printf("[");
		setattr(0,33,40);
                for(s=0;s<25;s++)
			printf("%c",unit[tunit].text[(calc/2+s)%(sizeof(unit[tunit].text)-1)]);
		if((calc/2)%(sizeof(unit[tunit].text)-1)==0)
		{
			clrscr(); // <- hacked to reduce graphic errors...
			tunit=rand()%building_types;
			while(player[0]->force[tunit]==0)
				tunit=rand()%building_types;			
		}
		
                setattr(0,37,40);
                printf("]");
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
			player[t]->program[u].order=player[0]->program[u].order;
		}
		for(s=1;s<MAX_PLAYER;s++)
		{
			t=rand()%MAX_PLAYER;
			if((player[s]->pFitness<player[t]->pFitness)||((player[s]->pFitness==player[t]->pFitness)&&(player[s]->sFitness<player[t]->sFitness)))
			for(u=0;u<MAX_LENGTH;u++)
			{
			player[s]->program[u].order=player[t]->program[u].order;
			player[s]->pFitness=player[t]->pFitness;
			player[s]->sFitness=player[t]->sFitness;
			}
		}
	// Save the program when 'Max_Generations' Generations were no change
	    if(rfit>=setup.Max_Generations)
		{
			rfit=0;
			generation=0;
			for(s=0;s<MAX_LENGTH;s++)
			{
				Save[run]->program[s].order=player[0]->program[s].order;
				Save[run]->program[s].time=player[0]->program[s].time;
				Save[run]->program[s].need_Supply=player[0]->program[s].need_Supply;
				Save[run]->program[s].have_Supply=player[0]->program[s].have_Supply;
				Save[run]->program[s].success=player[0]->program[s].success;
				Save[run]->program[s].built=player[0]->program[s].built;
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

			if(Test<2)
		        	for(s=0;s<MAX_PLAYER;s++)
			        	player[s]->Restart();
         		else
		        {
				for(s=0;s<MAX_PLAYER;s++)
				{
					for(t=0;t<MAX_LENGTH;t++)
					{
						player[s]->program[t].order=bo[t].type;
						player[s]->program[t].time=20000;
					}
				player[s]->timer=setup.Max_Time;
				player[s]->IP=0;
				player[s]->length=MAX_LENGTH;
				}
			}
			
			afit=0;
			sfit=0;
			old_time=setup.Max_Time; 
			old_fit=0;
			run++;
			for(s=0;s<MAX_LENGTH;s++)
				bolog[s].count=0;
		}
	    if(player[0]->force[13]==255)
		    a=getchar();
	    
	} // end while...

	delete gizmo;

	//start of the file output block...

// Run canceled before all 5 runs were calculated? => Save the present run
	if(run<RUNNINGS)
	{
		for(s=0;s<MAX_LENGTH;s++)
		{
			Save[run]->program[s].order=player[0]->program[s].order;
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

		for(s=0;s<building_types;s++)
		{
			Save[run]->force[s]=player[0]->force[s];
			Save[run]->ftime[s]=player[0]->ftime[s];
		}
	}
	
	t=0;
//Determine the best run
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
	
// Even best run did not find a solution?
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

// Start saving the data	
	FILE * pFile;
	pFile = fopen(O,"w");
	fprintf(pFile,"---------------------------------------------------\n");
	fprintf(pFile,"---StarCraftCalculator by ClawSoftware.de [v1.02]--\n");
	fprintf(pFile,"---------------------------------------------------\n\n");
	fprintf(pFile,"Build Order of best Individual:\n");
	
	fprintf(pFile,"Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[t]->timer%60);	
	if(race!=2) fprintf(pFile,"Scouting unit after %.2i:%.2i minutes\n",setup.Scout_Time/60,setup.Scout_Time%60);
	
	printf("\nHeader saved...");
	
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
			if(Save[t]->program[s].built==1)
				fprintf(pFile,"[%.2i:%.2i] [%.2i/%.2i] %s [%s]\n",(Save[t]->program[s].time+0)/60,(Save[t]->program[s].time+0)%60,Save[t]->program[s].need_Supply,Save[t]->program[s].have_Supply,stats[race][Build_Av[Save[t]->program[s].order]].name,error_m[Save[t]->program[s].success]);
	}

	printf("Build Order saved...\n");
	
	fprintf(pFile,"\n----------------------------\n");
        fprintf(pFile,"------Force at the end------\n");
	fprintf(pFile,"----------------------------\n\n");
		 
	for(s=0;s<building_types;s++)
		if(Save[t]->force[s]>0)
			fprintf(pFile,"%21s : %2i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[t]->force[s],Save[t]->ftime[s]/60,Save[t]->ftime[s]%60);
	fprintf(pFile,"\nHarvested Minerals : %i\n",(short)(Save[t]->harvested_mins));
	fprintf(pFile,"Harvested Gas      : %i\n",(short)(Save[t]->harvested_gas));
	fprintf(pFile,"Minerals at the end: %i\n",(short)(Save[t]->mins));
	fprintf(pFile,"Gas at the end     : %i\n\n",(short)(Save[t]->gas));
	fprintf(pFile,"------------------------------\n\n");
	printf("First solution [%.2i:%.2i] succesfully saved...\n",Save[t]->timer/60,Save[t]->timer%60);
	printf("Checking for other solutions:\n");
	fprintf(pFile,"Other possible solutions: \n");
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
			
		if((Save[u]->timer<setup.Max_Time)&&(t!=u)&&(newone==1))			
		{
			otherfound=1;
			fprintf(pFile,"Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[u]->timer%60);
			if(race!=2) fprintf(pFile,"Scouting unit after %.2i:%.2i minutes\n",setup.Scout_Time/60,setup.Scout_Time%60);
			printf("Header saved... ");
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
			
		fprintf(pFile,"[%.2i:%.2i] [%.2i/%.2i] %s [%s]\n",(Save[u]->program[s].time+0)/60,(Save[u]->program[s].time+0)%60,Save[u]->program[s].need_Supply,Save[u]->program[s].have_Supply,stats[race][Build_Av[Save[u]->program[s].order]].name,error_m[Save[u]->program[s].success]);
	}

	printf("Build Order saved...\n");

	fprintf(pFile,"----------------------------\n");
	fprintf(pFile,"------Force at the end------\n");
	fprintf(pFile,"----------------------------\n\n");
	for(s=0;s<building_types;s++)
		if(Save[u]->force[s]>0)
			fprintf(pFile,"%21s : %3i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[u]->force[s],Save[u]->ftime[s]/60,Save[u]->ftime[s]%60);

	fprintf(pFile,"\nHarvested Minerals : %i\n",(short)(Save[u]->harvested_mins));
	fprintf(pFile,"Harvested Gas      : %i\n",(short)(Save[u]->harvested_gas));
	fprintf(pFile,"Minerals at the end: %i\n",(short)(Save[u]->mins));
	fprintf(pFile,"Gas at the end     : %i\n\n",(short)(Save[u]->gas));
	fprintf(pFile,"------------------------------\n\n");
	printf("%i. solution [%.2i:%.2i] succesfully saved...\n",u+1,Save[u]->timer/60,Save[u]->timer%60);
			printf("- [%.2i:%.2i] succesfully saved...\n",Save[u]->timer/60,Save[u]->timer%60);
		}
	}
	if(otherfound==0)
	{
		fprintf(pFile,"None found!\n");
		printf("None found!\n");
	}
       
	fclose (pFile);
	printf("%s closed. All Data were saved.\n\n Thank you for using StarCalc!\n",O);
	printf("Have a nice day and visit www.clawsoftware.de!\n");

	// Have a nice day
	
	//TODO: Recheck whether REALLY all pointers / data are deleted/freed...
	
	for(s=0;s<MAX_PLAYER;s++)
		player[s]=NULL;
	for(s=0;s<RUNNINGS;s++)
		Save[s]=NULL;
	return 0;
};

