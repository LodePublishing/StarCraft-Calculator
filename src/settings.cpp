#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "io.h"

void GOALLIST::addGoal(int unit, int count, int time, int location)
{
        allGoal[unit]+=count;

        globalGoal[location][unit]+=count;

        int i=0;
        for(i=0;i<goalCount;i++)
                if((goal[i].unit==unit)&&(goal[i].time==time)&&(goal[i].location==location))
                {
                        goal[i].count+=count;
                        i=goalCount;
                }
        if(i==goalCount)
        {
                goal[goalCount].unit=unit;
                goal[goalCount].time=time;
                goal[goalCount].location=location;
                goal[goalCount].count=count;
                goalCount++;
        }
};

GOALLIST::GOALLIST()
{
        goalCount=0;
        for(int i=0;i<MAX_GOALS;i++)
        {
                goal[i].count=0;
                goal[i].time=0;
                goal[i].unit=0;
                goal[i].location=0;
        }
      for(int i=0;i<UNIT_TYPE_COUNT;i++)
                    allGoal[i]=0;
      for(int i=0;i<MAX_LOCATIONS;i++)
              for(int j=0;j<UNIT_TYPE_COUNT;j++)
                      globalGoal[i][j]=0;
      for(int i=UNIT_TYPE_COUNT;i--;)
	        {
                  isVariable[i]=0;
                  isBuildable[i]=0;
	        }
};




int SETTINGS::loadGoals() //~~~
{
	char line[1024];
	FILE* pFile;
	char* buffer;
	char item[1024];
	char param1[1024];
	char param2[1024];
	char param3[1024];
	int ln=0;
	int m;
	int value1,value2,value3=0;
	printf("Checking goal file [%s]...\n",GOALFILE);
	item[0]='\0';param1[0]='\0';param2[0]='\0';param3[0]='\0';

	if((pFile = fopen (GOALFILE,"r"))==NULL)
	{
		printf("Could not open the goal file (%s)\nReturning ...\n", GOALFILE);
		return(1); 
	}
	
	printf("File found. Reading...\n");
	//"unit name" "count" "time" "location"
	while(fgets(line,sizeof(line),pFile)!=NULL)
	{
                ++ln;
                line[strlen(line)-1]='\0';
                if((line[0]=='#')||(line[0]=='\0')) continue;
                strcpy(item,"");
                strcpy(param1,"");
                strcpy(param2,"");

                if((buffer=strtok(line,"\""))!=NULL) strcpy(item,buffer);strtok(NULL,"\"");
                if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param1,buffer);strtok(NULL,"\"");
                if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param2,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param3,buffer);strtok(NULL,"\"");
                if((buffer=strtok(NULL,"\""))!=NULL)
                {
                        printf("Line %d: Too many entries (%s).\n",ln,buffer);continue;
                }
		value1=atoi(param1);value2=atoi(param2);value3=atoi(param3);
		
		#ifdef DEBUGSCC
		printf("Line %d: %s %s (%i) %s (%i) %s (%i)\n",ln,item,param1,value1,param2,value2,param3,value3);
		#endif

		if((value1<0)||(value2<0)||(value3<0))
		{
			printf("Line %d: Value below zero.\n",ln);continue;
		}

//Aufbau der goal datei: "Einheitname" LEER "Anzahl" LEER "Zeit" LEER "Ort"
		
		for(m=UNIT_TYPE_COUNT;m--;) 
			if((strstr(stats[race][m].name,item)!=NULL)&&(value2<=ga.maxTime)) //TODO: strcmp durch 'erstes auftauchen' vertauschen
			{
				//TODO: values checken!
			 	//TODO: evtl statt Ortsnummer einfach den Ortsnamen nehmen
				goalList.addGoal(m,value1,60*value2,value3); //TODO: evtl statt Ortsnummer einfach den Ortsnamen nehmen
				printf("Adding %s (%ix) [%i] (@%i)\n",item,value1,value2,value3);
				m=-1;
				break;
			}
		if(m!=-1)
			printf("Line %d: Unknown entry: %s\n",ln,item);
	}
        if(goalList.goalCount<=0) return -1;
        for(int j=6;j--;) // Nuclear Warhead needs 6 steps (?) ~~~~
                        for(int i=UNIT_TYPE_COUNT;i--;)
                        if((goalList.allGoal[i]>0)||(goalList.isBuildable[i]>0))
                                        {
                                                goalList.isBuildable[i]=1;
                                for(int k=0;k<3;k++)

                                                        if((pStats[i].prerequisite[k]>0)&&(goalList.allGoal[pStats[i].prerequisite[k]]==0))
                                                goalList.addGoal(pStats[i].prerequisite[k],1,0,0);
                                if((pStats[i].facility2>0)&&(goalList.allGoal[pStats[i].facility2]==0)&&(pStats[i].facility_type!=NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE)&&(pStats[i].facility_type!=NEEDED_UNTIL_COMPLETE_IS_LOST))
                                {
                                        goalList.isVariable[pStats[i].facility2]=1;
                                        if(pStats[i].facility_type!=IS_LOST) //do not set those morph-facilities as goals...
                                                goalList.addGoal(pStats[i].facility2,1,0,0);
                                        else goalList.isBuildable[pStats[i].facility2]=1;// ... but make them buildable :)
                                }
                                                if((pStats[i].facility[0]>0)&&(goalList.allGoal[pStats[i].facility[0]]==0)&&((pStats[i].facility[1]==0)||(goalList.allGoal[pStats[i].facility[1]]==0))&&((pStats[i].facility[2]==0)||(goalList.allGoal[pStats[i].facility[2]]==0)))
// only facility[0] is important
                                                {
                                                        goalList.isVariable[pStats[i].facility[0]]=1;
                                                        if((pStats[i].facility_type==NEEDED_ONCE)||(pStats[i].facility_type==NEEDED_UNTIL_COMPLETE)||(pStats[i].facility_type==NEEDED_ALWAYS))
                                                goalList.addGoal(pStats[i].facility[0],1,0,0);
                                        else goalList.isBuildable[pStats[i].facility[0]]=1; // ... same as above...
                                                }
                                        }
                        long Need_Gas=0;
                        for(int i=UNIT_TYPE_COUNT;i--;)
                                Need_Gas+=(goalList.allGoal[i]*pStats[i].gas);
                        if(Need_Gas>0)
                                {
                                                goalList.isBuildable[REFINERY]=1;
                                        if(goalList.allGoal[REFINERY]==0)
                                       goalList.addGoal(REFINERY,1,0,0); //ASSIMILATOR == EXTRACTOR == REFINERY
                                                       goalList.isBuildable[GAS_SCV]=1; //ONE_MINERAL_SCV... = ONE_MINERAL_PROBE... = ONE_MINERAL_DRONE...                                        isVariable[GAS_SCV]=1;
                        };
//      isBuildable[WINDOW_MOVE_ADD_3]=1;isVariable[WINDOW_MOVE_ADD_3]=1;        isBuildable[WINDOW_MOVE_ADD_1]=1;isVariable[WINDOW_MOVE_ADD_1]=1;        isBuildable[WINDOW_MOVE_SUB_1]=1;isVariable[WINDOW_MOVE_SUB_1]=1;//      isBuildable[WINDOW_MOVE_PREV]=1;isVariable[WINDOW_MOVE_PREV]=1;
        goalList.isBuildable[MOVE_FROM_HERE]=1;goalList.isVariable[MOVE_FROM_HERE]=1;
        goalList.isBuildable[MOVE_TO_HERE]=1;goalList.isVariable[MOVE_TO_HERE]=1;

        //TODO: ueberlegen ob nicht einfach Move+ und Move- reichen...

        switch(race)
        {
                case TERRA:
                        goalList.isBuildable[SCV]=1;goalList.isVariable[SCV]=1;goalList.addGoal(COMMAND_CENTER,1,0,1);
                        goalList.isBuildable[COMMAND_CENTER]=1;goalList.isVariable[COMMAND_CENTER]=1;
                        goalList.isBuildable[SUPPLY_DEPOT]=1;goalList.isVariable[SUPPLY_DEPOT]=1;break;
                case PROTOSS:
                        goalList.isBuildable[PROBE]=1;goalList.isVariable[PROBE]=1;goalList.addGoal(NEXUS,1,0,1);
                        goalList.isBuildable[NEXUS]=1;goalList.isVariable[NEXUS]=1;
                        goalList.isBuildable[PYLON]=1;goalList.isVariable[PYLON]=1;break;
                case ZERG:
                        goalList.isBuildable[OVERLORD]=1;goalList.isVariable[OVERLORD]=1;goalList.addGoal(HATCHERY,1,0,1); //~~~
                        goalList.isBuildable[DRONE]=1;goalList.isVariable[DRONE]=1;
                        goalList.isBuildable[HATCHERY]=1;goalList.isVariable[HATCHERY]=1;
                        goalList.isBuildable[BREAK_UP_BUILDING]=1;goalList.isVariable[BREAK_UP_BUILDING]=1;break;
//~~                    allGoal[BREAK_UP_BUILDING].count=0;break;
                default:break;
        }
	return(0);
}


/*void SETTINGS::Fatal(char * strn)
{ 
	setColor(31);
	printf("FATAL ERROR: ");
	setColor(37);
	printf("%s\nExiting...",strn);
}*/

int SETTINGS::init()
{
	char line[1024];
	FILE* pFile;
	char* buffer;
	char item[1024];
	char param1[1024];
	char param2[1024];
	int ln=0;
	int value1,value2=0;
	int mode=0;
	int i=0;
#ifdef DEBUGSCC		
	printf("Checking input file [%s]...\n",SETTINGSFILE);
#endif
	
	item[0]='\0';param1[0]='\0';param2[0]='\0';

	if((pFile = fopen (SETTINGSFILE,"r"))==NULL)
	{
#ifdef DEBUGSCC
		printf("Could not open the config file (%s)\nReturning ...\n", SETTINGSFILE);
#endif
		return(0); 
	}
	
#ifdef DEBUGSCC
	printf("File found. Reading...\n");
#endif
	while(fgets(line,sizeof(line),pFile)!=NULL)
	{
		++ln;
		line[strlen(line)-1]='\0';
		if((line[0]=='#')||(line[0]=='\0')) continue;
		strcpy(item,"");
		strcpy(param1,"");
		strcpy(param2,"");
		if((buffer=strtok(line,"\""))!=NULL) strcpy(item,buffer);strtok(NULL,"\"");
                if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param1,buffer);strtok(NULL,"\"");
                if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param2,buffer);
		if((buffer=strtok(NULL,"\""))!=NULL)
		{
			printf("Line %d: Too many entries (%s).\n",ln,buffer);continue;
		}
		value1=atoi(param1);value2=atoi(param2);
		
		#ifdef DEBUGSCC
		printf("Line %i: %s %s (%i) %s (%i).\n",ln,item,param1,value1,param2,value2); 
		#endif
		
		if((value1<0)||(value2<0))
		{
			printf("Line %d: Value below zero.\n",ln);continue;
		}
		if(mode==0)
		{
			//TODO: errors wenn parameter da sind wo keine benoetigt werden
			if(!strcmp(item,"@SETTINGS")) mode=10;
			else if(!strcmp(item,"@LOCATION"))
			{
				if((value1>0)&&(value1<21)) 
					mode=10+value1;
				else
					printf("Line %d: Location (%d) out of range.\n",ln,value1);
			}
			else if(!strcmp(item,"@PLAYER"))
			{
				if((value1>0)&&(value1<5)) 
					mode=value1;
				else
					printf("Line %d: Player (%d) out of range.\n",ln,value1);
			}
			else 
			{
				if(!strcmp(item,"@END")) printf("Line %d: Lonely @END.\n",ln);
				else printf("Line %d: Outside a block but neither a block marker nor a comment.\n",ln);
			}
			
		}
		else if(mode>0)		
		{
			if(!strcmp(item,"@END"))
				mode=0;
			else if(item[0]=='@')
				printf("Line %d: New block (%s) was found within another.\n",ln,item);
			else
			if(mode<5) // TODO spaeter... wenn mehrere player moeglich sind
			{
				if(!strcmp(item,"Race"))
				{
					if(!strcmp(param1,"Terra")) race=TERRA;
					else if(!strcmp(param1,"Protoss")) race=PROTOSS;
					else if(!strcmp(param1,"Zerg")) race=ZERG;
					else 
						printf("Line %d: Invalid race (%s).\n",ln,param1);
				}
				else if(!strcmp(item,"Starting Minerals"))
				{
					if(value1>=0) misc.mins=value1;
				}
				else if(!strcmp(item,"Starting Gas"))
				{
					if(value1>=0) misc.gas=value1;
				}
				else if(!strcmp(item,"Starttime"))
				{
					if(misc.timer>=0) misc.timer=value1;
				}//~~
				else if(!strcmp(item,"Needed supply"))
				{
					if(value1<=200) misc.supply=value1;
				}
				else if(!strcmp(item,"Max Supply Terra"))
				{
					if(race==TERRA)
					{
						if(value1<=200) 
							misc.maxSupply=value1;
						else printf("Line %d: max supply too high (%d).\n",ln,value1);
					}
				}
				else if(!strcmp(item,"Max Supply Protoss"))
				{
					if(race==PROTOSS)
					{
						if(value1<=200) 
							misc.maxSupply=value1;
						else printf("Line %d: max supply too high (%d).\n",ln,value1);
					}
				}
				else if(!strcmp(item,"Max Supply Zerg"))
				{
					if(race==ZERG)
					{
						if(value1<=200) 
							misc.maxSupply=value1;
						else printf("Line %d: max supply too high (%d).\n",ln,value1);
					}
				}
				else
				//TODO: MAPDaten in seperate Mapfiles!
				{
					for(i=UNIT_TYPE_COUNT;i--;) 
					//NAME LOCATION COUNT
						if(strstr(stats[race][i].name,item)!=NULL)
						{
							if((value1>0)&&(value1<21)&&(value2>0)&&(value2<200)&&(value2*stats[race][i].supply+misc.supply<=200))
							{
								if(stats[race][i].supply>0)
									misc.supply-=stats[race][i].supply*location[value1].force[i];
								else misc.maxSupply+=stats[race][i].supply*location[value1].force[i];
								location[0].force[i]=value2;
								location[0].availible[i]=value2;
								location[value1].force[i]=value2;
								location[value1].availible[i]=value2;
								if(stats[race][i].supply>0)
									misc.supply+=stats[race][i].supply*value2;
								else misc.maxSupply-=stats[race][i].supply*value2;
								//TODO: Begrenzungen bei researches und upgrades und nichtbaubaren Sachen!
							};
							i=-1;
							break;
						};
					if(i>-1) printf("Line %d: Unknown: %s\n",ln,item);
				}
			}
			else if(mode==10)
			{
				if(!strcmp(item,"Max Time"))
				{
					if(value1<5)
						printf("Line %d: %d for max time is too low.\n",ln,value1);
					else ga.maxTime=value1*60;
				}
				else if(!strcmp(item,"Preprocess Buildorder"))
				{
					if((!strcmp(param1,"YES"))||(!strcmp(param1,"Y")))
						ga.generateBuildOrder=1;
					else if((!strcmp(param1,"NO"))||(!strcmp(param1,"N")))
						ga.generateBuildOrder=0;
					else
						printf("Line %d: Unknown value: %s.\n",ln,param1);
				}
				else if(!strcmp(item,"Max Generations"))
				{
					if((value1<25)||(value1>500))
						printf("Line ?d: Max Generations (%d) too low or too high (%d).\n",ln,value1);
					else ga.maxGenerations=value1;
				}
				else
					printf("Line %d: Unknown: %s\n",ln,buffer);
			}
			else if((mode>10)&&(mode<=30))
			{
				if(!strcmp(item,"Name"))
					strcpy(map[mode-10].name,param1);
				else if(!strcmp(item,"Mineral Blocks"))
					map[mode-10].mineralCount=value1;
				else if(!strcmp(item,"Vespene Geysirs"))
					map[mode-10].geysirCount=value1;
				else if(!strcmp(item,"Distance to"))
				{
					if((value1>0)&&(value1<21)&&(value2<=250)) map[mode-10].distance[value1]=value2;
					else printf("Line %d: Out of range.\n",ln);
				}
				else
					printf("Line %d: Unknown: %s\n",ln,buffer);
			}
		}// END if(mode>0)
	}// END while
	if(misc.maxSupply<misc.supply)
		printf("Warning: max supply is lower than supply.\n");
	return(1);
}

void SETTINGS::initMap()
{
	map[0].mineralCount=0;map[0].geysirCount=0; // The wayne location... 
	map[1].mineralCount=8;map[1].geysirCount=1; //Main
	map[2].mineralCount=0;map[2].geysirCount=0; //Front
	map[3].mineralCount=8;map[3].geysirCount=1; //Exe
	map[4].mineralCount=0;map[4].geysirCount=0; //Center
	map[5].mineralCount=8;map[5].geysirCount=1; //EnemyExe
	map[6].mineralCount=0;map[6].geysirCount=0; //EnemyFront
	map[7].mineralCount=8;map[7].geysirCount=1; //EnemyMain
	map[8].mineralCount=0;map[8].geysirCount=0; //Air center
	
	map[0].distance[0]=0;map[0].distance[1]=0;map[0].distance[2]=0;map[0].distance[3]=0;map[0].distance[4]=0;map[0].distance[5]=0;map[0].distance[6]=0;map[1].distance[7]=0;map[0].distance[8]=0;

	map[1].distance[0]=0;map[1].distance[1]=0;map[1].distance[2]=15;map[1].distance[3]=25;map[1].distance[4]=50;map[1].distance[5]=75;map[1].distance[6]=85;map[1].distance[7]=100;map[1].distance[8]=35;

	map[2].distance[0]=0;map[2].distance[1]=15;map[2].distance[2]=0;map[2].distance[3]=10;map[2].distance[4]=35;map[2].distance[5]=60;map[2].distance[6]=70;map[2].distance[7]=85;map[2].distance[8]=25;

	map[3].distance[0]=0;map[3].distance[1]=25;map[3].distance[2]=10;map[3].distance[3]=0;map[3].distance[4]=40;map[3].distance[5]=65;map[3].distance[6]=75;map[3].distance[7]=90;map[3].distance[8]=30;//TODO: warum weiter?

	map[4].distance[0]=0;map[4].distance[1]=50;map[4].distance[2]=35;map[4].distance[3]=40;map[4].distance[4]=0;map[4].distance[5]=40;map[4].distance[6]=35;map[4].distance[7]=50;map[4].distance[8]=0;

	map[5].distance[0]=0;map[5].distance[1]=90;map[5].distance[2]=75;map[5].distance[3]=65;map[5].distance[4]=40;map[5].distance[5]=0;map[5].distance[6]=10;map[5].distance[7]=25;map[5].distance[8]=30;
	
	map[6].distance[0]=0;map[6].distance[1]=85;map[6].distance[2]=70;map[6].distance[3]=60;map[6].distance[4]=35;map[6].distance[5]=10;map[6].distance[6]=0;map[6].distance[7]=15;map[6].distance[8]=25;

	map[7].distance[0]=0;map[7].distance[1]=100;map[7].distance[2]=85;map[7].distance[3]=75;map[7].distance[4]=50;map[7].distance[5]=25;map[7].distance[6]=15;map[7].distance[7]=0;map[7].distance[8]=35;

	map[8].distance[0]=0;map[8].distance[1]=35;map[8].distance[2]=25;map[8].distance[3]=30;map[8].distance[4]=0;map[8].distance[5]=30;map[8].distance[6]=25;map[8].distance[7]=35;map[8].distance[8]=0;
//Lost Temple ohne Mins exen
}

void SETTINGS::initHarvest()
{
	switch(race)
	{
		case TERRA:misc.pMineralHarvestPerSecond=&(mining_t[0]);misc.pGasHarvestPerSecond=&(mining_t[0]);break;
		case PROTOSS:misc.pMineralHarvestPerSecond=&(mining_p[0]);misc.pGasHarvestPerSecond=&(mining_p[0]);break;
		case ZERG:misc.pMineralHarvestPerSecond=&(mining_z[0]);misc.pGasHarvestPerSecond=&(mining_z[0]);break;
		default:break;
	}
}


void SETTINGS::initLocations()
{
	for(int j=0;j<MAX_LOCATIONS;j++)
	{
		for(int i=UNIT_TYPE_COUNT;i--;)
		{
			location[j].force[i]=0;
			location[j].availible[i]=0;
		}
		location[j].force[MINERALS]=map[j].mineralCount;
		location[j].availible[MINERALS]=map[j].mineralCount;
		location[j].force[VESPENE_GEYSIR]=map[j].geysirCount;
		location[j].availible[VESPENE_GEYSIR]=map[j].geysirCount;
		location[0].force[MINERALS]+=map[j].mineralCount;
		location[0].availible[MINERALS]+=map[j].mineralCount;
		location[0].force[VESPENE_GEYSIR]+=map[j].geysirCount;
		location[0].availible[VESPENE_GEYSIR]+=map[j].geysirCount;
	}

switch(race)
	{
		case TERRA:
			location[1].force[COMMAND_CENTER]=1;
			location[1].availible[COMMAND_CENTER]=1;
			location[0].force[COMMAND_CENTER]=1;
			location[0].availible[COMMAND_CENTER]=1;
			for(int i=R_STIM_PACKS;i<=R_CHARON_BOOSTER;i++)
			{
				for(int j=MAX_LOCATIONS;j--;)
				{
					location[j].availible[i]=1;
					location[j].force[i]=1;
				}
			};
			for(int i=R_INFANTRY_ARMOR;i<=R_SHIP_WEAPONS;i++)
			{
				for(int j=MAX_LOCATIONS;j--;)
				{
					location[j].availible[i]=3;
					location[j].force[i]=3;
				}
			};
			break;
		case PROTOSS:
			location[1].force[NEXUS]=1;
			location[1].availible[NEXUS]=1;
			location[0].force[NEXUS]=1;
			location[0].availible[NEXUS]=1;
			   for(int i=R_PSIONIC_STORM;i<=R_ARGUS_TALISMAN;i++)
                           {
				for(int j=MAX_LOCATIONS;j--;)
                                {
                                        location[j].availible[i]=3;
                                        location[j].force[i]=3;
                                }
                           }
                           for(int i=R_ARMOR;i<=R_PLASMA_SHIELDS;i++)
                           {
				for(int j=MAX_LOCATIONS;j--;)
                                {
                                        location[j].availible[i]=3;
                                        location[j].force[i]=3;
                                }
                           }
			   break;
		case ZERG:
			   location[1].force[HATCHERY]=1;
			   location[1].availible[HATCHERY]=1;
			   location[0].force[HATCHERY]=1;
			   location[0].availible[HATCHERY]=1;
				
			   location[1].force[OVERLORD]=1;
                           location[1].availible[OVERLORD]=1;
                           location[0].availible[OVERLORD]=1;
                           location[0].force[OVERLORD]=1;

                           location[1].force[LARVA]=1;
                           location[1].availible[LARVA]=1;
                           location[0].availible[LARVA]=1;
                           location[0].force[LARVA]=1;
		   for(int i=R_VENTRAL_SACKS;i<=R_LURKER_ASPECT;i++)
                           {
				for(int j=MAX_LOCATIONS;j--;)
                                {
                                        location[j].availible[i]=3;
                                        location[j].force[i]=3;
                                }
                           }
                           for(int i=R_CARAPACE;i<=R_FLYER_ATTACKS;i++)
                           {
				for(int j=MAX_LOCATIONS;j--;)
                                {
                                        location[j].availible[i]=3;
                                        location[j].force[i]=3;
                                }
                           }
			break;
		default:
//TODO: Some sort of error
break;
	}
	location[1].availible[SCV]=4;
	location[1].force[SCV]=4;
 	location[0].force[SCV]=4;
	location[0].availible[SCV]=4;
//TODO: ueberlegen, wann race initialisiert werden soll
}

SETTINGS::SETTINGS()
{
#ifdef WIN32
	scr=CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
#endif	 //-> io
	race=TERRA;
	misc.mins=50;
	misc.gas=0;
	misc.timer=0;
	misc.supply=4;
	misc.maxSupply=10;
	printf("Initializing Map... ");
	initMap();
	setColor(33); //?
	printf("OK!\n");
	setColor(37);
	printf("Initializing Locations... ");
	initLocations();
	printf("OK!\nInitializing settings... ");
	if(!init()) 
	{
		setColor(31);
		printf("FAILED!\n");
		setColor(37);
		//...
	}
	else printf("OK!\n");
	pStats=&(stats[race][0]);	
	printf("Initializing harvest speed... ");
	initHarvest();
	printf("OK!\nLoading goals... ");
	loadGoals();
	printf("OK!\n");
}

SETTINGS::~SETTINGS()
{
#ifdef WIN32
	CloseHandle(scr);
#endif
}
