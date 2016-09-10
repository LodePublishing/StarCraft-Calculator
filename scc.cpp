#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>


#define RUNNINGS 10


#define MAX_PLAYER 200
#define MAX_BUILDINGS 10 // How many buildings can you built simultaneously?
#define BUILDING_TYPES 58
#define MAX_LENGTH 85
#define MAX_TIME 500

#define MAX_GENERATIONS 100
#define MAX_VESPENE 1


// reading binary file

#define SRESTART 0
// 0: Initialize all random
// 1: Initialize all 0
// 2: Initialize all with standard bo

#define MUTATIONS 100
#define MUTATION_FAKTOR 500

#define MAX_CHILDREN 5

#define ZERGLING 0
#define HYDRALISK 1
#define ULTRALISK 2
#define DRONE 3
#define DEFILER 4
#define LURKER 5
#define OVERLORD 6
#define MUTALISK 7
#define GUARDIEN 8
#define QUEEN 9
#define SCOURGE 10
#define DEVOURER 11

#define HATCHERY 12
#define LAIR 13
#define HIVE 14
#define NYDUS_CANAL 15
#define HYDRALISK_DEN 16
#define DEFILER_MOUND 17
#define GREATER_SPIRE 18
#define QUEENS_NEST 19
#define EVOLUTION_CHAMBER 20
#define ULTRALISK_CAVERN 21
#define SPIRE 22
#define SPAWNING_POOL 23
#define CREEP_COLONY 24
#define SPORE_COLONY 25
#define SUNKEN_COLONY 26
#define EXTRACTOR 27

#define VENTRAL_SACKS 28
#define ANTENNAE 29
#define PNEUMATIZED_CARAPACE 30
#define METABOLIC_BOOST 31
#define ADRENAL_GLANDS 32
#define MUSCULAR_AUGMENTS 33
#define GROOVED_SPINES 34
#define GAMETE_MEIOSIS 35
#define METASYNAPTIC_NODE 36
#define CHITINOUS_PLATING 37
#define ANABOLIC_SYNTHESIS 38



//dumm...
//program nochmal checken wegen unsigned char // unsigned long :\/
//
  //bloed bloed
  //mal im web nachguggn


#define BURROWING 39
#define SPAWN_BROODLING 40
#define DARK_SWARM 41
#define PLAGUE 42
#define CONSUME 43
#define ENSNARE 44
#define PARASITE 45
#define LURKER_ASPECT 46

#define CARAPACE 47
#define FLYER_CARAPACE 48
#define MELEE_ATTACKS 49
#define MISSILE_ATTACKS 50
#define FLYER_ATTACKS 51

#define ONE_MINERAL_DRONE_TO_GAS 52
#define ONE_GAS_DRONE_TO_MINERAL 53

#define WAIT_FOR_NEXT 54
#define WAIT_FOR_LAST 55
#define BREAK_UP_BUILDING_LAST 56
#define BREAK_UP_BUILDING_FIRST 57



struct Stats
{
	char name[35];
	unsigned short BT; // Build Time
	unsigned short mins,gas;
	unsigned char supply;
	unsigned char need; // 0: nothing, 1: larvae, 2: drone
};

const Stats stats[BUILDING_TYPES]=
{
	{"Zergling",28,50,0,1,1},
	{"Hydralisk",28,75,0,1,1},
	{"Ultralisk",60,200,200,6,1},
	{"Drone",20,50,0,1,1},
	{"Defiler",50,50,150,2,1},
	{"Lurker",40,50,100,2,0},
	{"Overlord",40,100,0,0,1},
	{"Mutalisk",40,100,100,2,1},
	{"Guardien",40,50,100,2,0},
	{"Queen",50,100,100,2,1},
	{"Scourge",30,25,75,1,1},
	{"Devourer",40,100,50,2,0},

	{"Hatchery",120,300,0,0,2},
	{"Lair",100,150,100,0,0},
	{"Hive",120,200,150,0,0},
	{"Nydus Canal",40,150,0,0,2},
	{"Hydralisk den",40,100,50,0,2},
	{"Defiler mound",60,100,100,0,2},
	{"Greater Spire",120,100,150,0,0},
	{"Queen's Nest",60,150,100,0,2},
	{"Evolution Chamber",40,75,0,0,2},
	{"Ultralisk Cavern",80,150,200,0,2},
	{"Spire",120,200,150,0,2},
	{"Spawning Pool",80,50,0,0,2},
	{"Creep Colony",20,50,0,0,2},
	{"Spore Colony",20,50,0,0,0},
	{"Sunken Colony",20,50,0,0,0},
	{"Extractor",40,50,0,0,2},

	{"Ventral Sacs",160,200,200,0,0},
	{"Antennae",133,150,150,0,0},
	{"Pneumatized Carapace",133,150,150,0,0},
	{"Metabolic Boost",100,100,100,0,0},
	{"Adrenal Glands",100,200,200,0,0},
	{"Muscular Augments",100,150,150,0,0},
	{"Grooved Spines",100,150,150,0,0},
	{"Gamete Meiosis",166,150,150,0,0},
	{"Metasynaptic node",166,150,150,0,0},
	{"Chitinous Plating",133,150,150,0,0},
	{"Anabolic Synthesis",133,200,200,0,0},

	{"Burrowing",80,100,100,0,0},
	{"Spawn Broodling",80,100,100,0,0},
	{"Dark Swarm",80,100,100,0,0},
	{"Plague",100,200,200,0,0},
	{"Consume",100,100,100,0,0},
	{"Ensnare",80,100,100,0,0},
	{"Parasite",80,100,100,0,0},
	{"Lurker Aspect",120,200,200,0,0},

	{"Carapace",266,150,150,0,0},
	{"Flyer Carapace",266,150,150,0,0},
	{"Melee Attacks",266,100,100,0,0},
	{"Missile Attacks",266,100,100,0},
	{"Flyer Attacks",266,100,100,0},
	{"Bring one Mineral Drone to Gas",330,200,200,0},
	{"Bring one Gas Drone to Mineral",266,100,100,0},
	{"Wait for next",0,0,0,0},
	{"Wait for last",0,0,0,0},
	{"Cancel Building Last",0,0,0,0},
	{"Cancel Building First",0,0,0,0}
};


const double gasing[5]=
{
	0,
	0.89,
	1.76,
	2.30,
	2.45
};

const double mining[57]=
{
	0,
	0.66,
	1.33,
	2,
	2.66,
	3.34,
	4.01,
	4.67,
	5.35,
	6, //9
	6.19,
	6.37,
	6.53,
	6.67,
	6.78, //14
	7.02,
	7.24,
	7.44,
	7.58, //18
	7.78,
	7.96,
	8.12,
	8.26,
	8.37, //23
	8.41,
	8.45,
	8.49,
	8.52,
	8.55, //28
	8.58,
	8.60,
	8.62,
	8.64,
	8.66, //33
	8.81,
	8.96,
	9.13,
	9.30,
	9.49,
	9.69,
	9.87, //40
	10.94,
	11,
	11.06,
	11.12,
	11.17,
	11.22,
	11.27,
	11.32,
	11.37,
	11.42,
	11.47,
	11.51,
	11.55,
	11.59,
	10.63,//55
	11
};


unsigned char run,y,rfit;
unsigned short afit;

struct save
{
	unsigned short fitness,timer;
	unsigned char program[MAX_LENGTH];
} Save[RUNNINGS];



unsigned short generation;
unsigned char num;


unsigned char x,i,j,A,B;
unsigned long templ;
unsigned short tempw;
long n;

unsigned short probability[BUILDING_TYPES+1];

unsigned char goal[BUILDING_TYPES];

class Player
{
public:
	unsigned char nr,ok;
	unsigned char force[BUILDING_TYPES];
	unsigned char availible[BUILDING_TYPES];
	unsigned short harvested_gas,harvested_mins;
	unsigned short oldgas,oldmins;

	struct Building
	{
		unsigned short RB; // Remaining Buildtime
		unsigned char type; // Type of Building
	} building[MAX_BUILDINGS];

	unsigned char IP,program[MAX_LENGTH];
	unsigned char larva[1000]; // larvacounter for producing larvas
	unsigned short fitness,timer,mins,gas,larvae;

	unsigned char NewBuildingReady,LastBuildingReady,dronemins,dronegas,larvacounter;
	short Supply;


unsigned char ChooseInstr()
{
	unsigned char h;
	unsigned short m;
	m=(rand()%probability[BUILDING_TYPES])+1;
	if(probability[0]>=m)
		return(0);
	else
	for(h=1;h<BUILDING_TYPES+1;h++)
		if((probability[h]>=m)&&(probability[h-1]<m))
			return(h);
//	return( (unsigned char(rand()%(BUILDING_TYPES+5))) );
}

void Produce(unsigned char who)
	{
		if((who>=CARAPACE)&&(who<=FLYER_ATTACKS))
		{
			building[nr].RB=stats[who].BT+force[who]*32;
			switch(who)
			{
				case CARAPACE:
				case FLYER_CARAPACE:
				case FLYER_ATTACKS:mins-=stats[who].mins+force[who]*75;gas-=stats[who].gas+force[who]*75;break;

				case MELEE_ATTACKS:
				case MISSILE_ATTACKS:mins-=stats[who].mins+force[who]*75;gas-=stats[who].gas+force[who]*75;break;
				default:break;
			}
		}	
	else
		{
			building[nr].RB=stats[who].BT+(stats[who].need==2)*3; // 3 Spielsekunden um zum Bauplatz zu fahren 
			mins-=stats[who].mins;
		    gas-=stats[who].gas;
		}

	     building[nr].type=who;
		 Supply-=stats[who].supply;
		 if(stats[who].need==1)
			 larvae--;
		 else
	     if(stats[who].need==2)
		 {
			 force[DRONE]--;
			 Supply++;
			 if(dronemins>0)
				 dronemins--;
			 else if(dronegas>0)
				 dronegas--;
		 }
		 ok=1;
	}

void Build(unsigned char what)
	{
		nr=255;ok=0;
		for(j=0;j<MAX_BUILDINGS;j++)
			if(building[j].RB==0)
			{
				nr=j;
				j=MAX_BUILDINGS;			
			}

		if( ((Supply>stats[what].supply) || (stats[what].supply==0)) &&
			( mins>=stats[what].mins+((what==CARAPACE)||(what==FLYER_CARAPACE)||(what==FLYER_ATTACKS))*force[what]*75+((what==MELEE_ATTACKS)||(what==MISSILE_ATTACKS))*force[what]*50 ) &&
			( gas>=stats[what].gas+((what==CARAPACE)||(what==FLYER_CARAPACE)||(what==FLYER_ATTACKS))*force[what]*75+((what==MELEE_ATTACKS)||(what==MISSILE_ATTACKS))*force[what]*50 ) &&
			(nr<255) && 
			(dronemins+dronegas>=1*(stats[what].need==2)) &&
			(larvae>=1*(stats[what].need==1))
		  )

		{
	


		switch(what)
		{
			case ZERGLING:if(force[SPAWNING_POOL]>0) Produce(what);break;
			case HYDRALISK:if(force[HYDRALISK_DEN]>0) Produce(what);break;
			case ULTRALISK:if(force[ULTRALISK_CAVERN]>0) Produce(what);break;
			case DRONE:Produce(what);break;
			case DEFILER:if(force[DEFILER_MOUND]>0) Produce(what);break;
			case LURKER:if((force[LURKER_ASPECT]>0)&&(force[HYDRALISK]>0))
						{
							force[HYDRALISK]--;
							Produce(what);
						}				
						break;
			case OVERLORD:Produce(what);break;
			case MUTALISK:if(force[SPIRE]+force[GREATER_SPIRE]>0) Produce(what);
							  break;
			case GUARDIEN:if((force[GREATER_SPIRE]>0)&&(force[MUTALISK]>0))
						  {
							  force[MUTALISK]--;
							  Produce(what);
						  }
							  break;
			case QUEEN:if(force[QUEENS_NEST]>0) Produce(what);
						   break;
			case SCOURGE:if(force[SPIRE]+force[GREATER_SPIRE]>0) Produce(what);
							 break;
			case HATCHERY:Produce(what);break;
			case LAIR:if((force[HATCHERY]>0)&&(force[SPAWNING_POOL]>0) ) 
					  {
						  availible[HATCHERY]--;	  
						  Produce(what);
					  }
						  break;
			case HIVE:if((force[LAIR]>0)&&(force[QUEENS_NEST]>0))
					  {
						  availible[LAIR]--;
						  Produce(what);
					  }
						  break;
			case NYDUS_CANAL:if(force[HIVE]>0) Produce(what);
								 break;
			case HYDRALISK_DEN:if(force[SPAWNING_POOL]>0) Produce(what);
								   break;
			case DEFILER_MOUND:if(force[HIVE]>0) Produce(what);
								   break;
			case GREATER_SPIRE:if((force[SPIRE]>0)&&(availible[SPIRE]>0)&&(force[HIVE]>0)) 
							   {
								   availible[SPIRE]--;
								   Produce(what);
							   }
							   break;
			case QUEENS_NEST:if(force[LAIR]>0) Produce(what);
				break;
			case EVOLUTION_CHAMBER:Produce(what);
				break;
			case ULTRALISK_CAVERN:if(force[HIVE]>0) Produce(what);
									  break;
			case SPIRE:if(force[LAIR]>0) Produce(what);
						   break;
			case SPAWNING_POOL:Produce(what);break;
			case CREEP_COLONY:Produce(what);break;
			case SPORE_COLONY:if((force[EVOLUTION_CHAMBER]>0)&&(force[CREEP_COLONY]>0))
							  {
								  force[CREEP_COLONY]--;
								  Produce(what);
							  }
							  break;
			case SUNKEN_COLONY:if((force[SPAWNING_POOL]>0)&&(force[CREEP_COLONY]>0))
							   {
								   force[CREEP_COLONY]--;
								   Produce(what);
							   }
								   break;
			case EXTRACTOR:if(force[EXTRACTOR]<MAX_VESPENE) Produce(what);
							   break;
			case VENTRAL_SACKS:if((force[VENTRAL_SACKS]==0)&&(force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
							   {
								   if(availible[LAIR]>0) availible[LAIR]--;
								   else availible[HIVE]--;
								   Produce(what);
							   }
								   break;
			case ANTENNAE:if((force[ANTENNAE]==0)&&(force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
						   {
								   if(availible[LAIR]>0) availible[LAIR]--;
								   else availible[HIVE]--;
								   Produce(what);
							}
							break;
			case PNEUMATIZED_CARAPACE:if((force[PNEUMATIZED_CARAPACE]==0)&&(force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
							{
								   if(availible[LAIR]>0) availible[LAIR]--;
								   else availible[HIVE]--;
								   Produce(what);
							   }
				break;
			case METABOLIC_BOOST:if((force[METABOLIC_BOOST]==0)&&(force[SPAWNING_POOL]>0)&&(availible[SPAWNING_POOL]>0))
								 {
									 availible[SPAWNING_POOL]--;
									 Produce(what);
								 }
				break;
			case ADRENAL_GLANDS:if((force[ADRENAL_GLANDS]==0)&&(force[HIVE]>0)&&(force[SPAWNING_POOL]>0)&&(availible[SPAWNING_POOL]>0))
								{
									availible[SPAWNING_POOL]--;
									Produce(what);
								}
								break;
			case MUSCULAR_AUGMENTS:break;
			case GROOVED_SPINES:break;
			case GAMETE_MEIOSIS:break;
			case METASYNAPTIC_NODE:break;
			case CHITINOUS_PLATING:if( (force[CHITINOUS_PLATING]==0)&&(force[ULTRALISK_CAVERN]>0)&&(availible[ULTRALISK_CAVERN]>0)) 
								   {
									   availible[ULTRALISK_CAVERN]--;
									   Produce(what);
								   }
									break;
			case ANABOLIC_SYNTHESIS:if( (force[ANABOLIC_SYNTHESIS]==0)&&(force[ULTRALISK_CAVERN]>0)&&(availible[ULTRALISK_CAVERN]>0)) 
								   {
									   availible[ULTRALISK_CAVERN]--;
									   Produce(what);
								   }
								break;
			case BURROWING:if((force[ANTENNAE]==0)&&(force[HATCHERY]+force[LAIR]+force[HIVE]>0)&&(availible[HATCHERY]+availible[LAIR]+availible[HIVE]>0)) 
						   {
							   if(availible[HATCHERY]>0)
								   availible[HATCHERY]--;
							   else if(availible[LAIR]>0)
								   availible[LAIR]--;
							   else availible[HIVE]--;
							   Produce(what);
						   }
							   break;
			case SPAWN_BROODLING:if((force[SPAWN_BROODLING]==0)&&(force[QUEENS_NEST]>0)&&(availible[QUEENS_NEST]>0))
								 {
									 availible[QUEENS_NEST]--;
									 Produce(what);
								 }
									 break;
			case DARK_SWARM:
			case PLAGUE:
			case CONSUME:if((force[what]==0)&&(force[DEFILER_MOUND]>0)&&(availible[DEFILER_MOUND]>0))
						 {
								availible[DEFILER_MOUND]--;
								Produce(what);
							}
							 break;


			case ENSNARE:
			case PARASITE:if((force[what]==0)&&(force[QUEENS_NEST]>0)&&(availible[QUEENS_NEST]>0))
						  {
							  availible[QUEENS_NEST]--;
							  Produce(what);
						  }
							  break;

			case LURKER_ASPECT:if((force[LURKER_ASPECT]==0)&&(force[HYDRALISK_DEN]>0)&&(force[LAIR]>0)&&(availible[HYDRALISK_DEN]>0))
							   {
								   availible[HYDRALISK_DEN]--;
								   Produce(what);
							   }
								   break;
			case CARAPACE:
			case MELEE_ATTACKS:
			case MISSILE_ATTACKS:if((force[what]<3)&&(force[EVOLUTION_CHAMBER]>0)&&(availible[EVOLUTION_CHAMBER]>0)&&(force[HATCHERY+force[what]]>0))
									 {
									  availible[EVOLUTION_CHAMBER]--;
									  Produce(what);
									  }
									 break;
			case FLYER_CARAPACE:
			case FLYER_ATTACKS:if((force[what]<3)&&(force[SPIRE]>0)&&(availible[SPIRE]>0)&&(force[HATCHERY+force[what]]>0))
						 {
							  if(availible[SPIRE]>0)
								  availible[SPIRE]--;
							  else availible[GREATER_SPIRE]--;
							  Produce(what);
						  }
							   break;

			case ONE_MINERAL_DRONE_TO_GAS:if((dronemins>0)&&(force[EXTRACTOR]>0))
										  {
											  dronemins--;
											  dronegas++;
										  }
											  break;
			case ONE_GAS_DRONE_TO_MINERAL:if(dronegas>0)
										  {
											  dronegas--;
											  dronemins++;
										  }
				break;
			case WAIT_FOR_NEXT:break;
			case WAIT_FOR_LAST:break;
			case BREAK_UP_BUILDING_LAST:break;
			case BREAK_UP_BUILDING_FIRST:break;
			default:break;
		}

	}
}

	
	void Calculate()
	{
		unsigned char ready,BuildingRunning;
		unsigned short min,n;
		ready=0;
		timer=0;
		IP=0;
		harvested_gas=0;
		harvested_mins=0;
		while( (IP<MAX_LENGTH) && (timer<MAX_TIME) && (ready==0))
		{
		
			NewBuildingReady=0;
			BuildingRunning=0;
			for(j=0;j<MAX_BUILDINGS;j++)
			{
				if(building[j].RB>0)
				{
					BuildingRunning=1;
					building[j].RB--;
					if(building[j].RB==0)
					{
						NewBuildingReady=1;
						LastBuildingReady=1;
						for(i=0;i<MAX_BUILDINGS;i++)
							LastBuildingReady&=(building[i].RB==0);
						force[building[j].type]++;
						availible[building[j].type]++;
//						`~~~~~
						switch(building[j].type)
						{
							case DRONE:dronemins++;break;
							case OVERLORD:Supply+=8;break;
							case HATCHERY:larvacounter++;larvae++;larva[larvacounter]=21;Supply++;break;
							case LAIR:force[HATCHERY]--;break;
							case HIVE:force[LAIR]--;break;
							case GREATER_SPIRE:force[SPIRE]--;break;
							case VENTRAL_SACKS:
							case ANTENNAE:
							case PNEUMATIZED_CARAPACE:
  								   if(availible[LAIR]<force[LAIR])
										availible[LAIR]++;
								   else availible[HIVE]++;
								   break;
							case METABOLIC_BOOST:
							case ADRENAL_GLANDS:availible[SPAWNING_POOL]++;break;
							case MUSCULAR_AUGMENTS:break;
							case GROOVED_SPINES:break;
							case GAMETE_MEIOSIS:break;
							case METASYNAPTIC_NODE:break;
							case CHITINOUS_PLATING:
							case ANABOLIC_SYNTHESIS:availible[ULTRALISK_CAVERN]++;break;

							case BURROWING:
							   if(availible[HATCHERY]<force[HATCHERY])
								   availible[HATCHERY]++;
							   else if(availible[LAIR]<force[LAIR])
								   availible[LAIR]++;
							   else availible[HIVE]++;
							   break;
							case SPAWN_BROODLING:availible[QUEENS_NEST]++;break;
							case DARK_SWARM:
							case PLAGUE:
							case CONSUME:availible[DEFILER_MOUND]++;break;
							case ENSNARE:
							case PARASITE:availible[QUEENS_NEST]++;break;
							case LURKER_ASPECT:availible[HYDRALISK_DEN]++;break;
							
							case CARAPACE:
							case MELEE_ATTACKS:
							case MISSILE_ATTACKS:availible[EVOLUTION_CHAMBER]++;break;

							case FLYER_CARAPACE:
							case FLYER_ATTACKS:
								if(availible[SPIRE]<force[SPIRE])
									availible[SPIRE]++;
								else availible[GREATER_SPIRE]++;break;
							default:break;
					}

					}
				}
			}

			for(i=0;i<larvacounter;i++)
			{
				if(larva[i]==1)
				{
					larvae++;
					larva[i]=20;
				}
				else larva[i]--;
				if(larvae>=(force[HATCHERY]+force[LAIR]+force[HIVE])*3) larva[i]=20;
			}


			if((program[IP]>ONE_GAS_DRONE_TO_MINERAL)&&(program[IP]<=BREAK_UP_BUILDING_LAST)&&(BuildingRunning==1))
			{
				switch(program[IP])
				{
					case WAIT_FOR_NEXT:if(NewBuildingReady==1) IP++;break;
					case WAIT_FOR_LAST:if(LastBuildingReady==1) IP++;break;
					case BREAK_UP_BUILDING_FIRST:	// am weitesten fortgeschritten
									min=5000;
									n=0;
									for(i=0;i<MAX_BUILDINGS;i++)
									if(building[i].RB>0)									
									{
										if((stats[building[i].type].need==2) && (building[i].RB<min)) // warum need=2? nur bei gebaeuden sinnvoll!
										{
											min=building[i].RB;
											n=i;
										}
									}
									if(min<5000)
										{
											dronemins++;
											mins+=stats[building[n].type].mins*0.75;
											gas+=stats[building[n].type].gas*0.75;
											Supply--;
											force[DRONE]++;
											building[n].type=255;
											building[n].RB=0;
										}
									break;
					case BREAK_UP_BUILDING_LAST:   // gerade angefangen
									min=5000;
									n=0;
									for(i=0;i<MAX_BUILDINGS;i++)
									if(building[i].RB>0)
									{
										if((stats[building[i].type].need==2) && (stats[building[i].type].BT-building[i].RB<min)) // warum need=2? nur bei gebaeuden sinnvoll!
										{
											min=stats[building[i].type].BT-building[i].RB;
											n=i;
										}
									}
									if(min<5000)
										{
											dronemins++;
											mins+=stats[building[n].type].mins*0.75;
											gas+=stats[building[n].type].gas*0.75;
											Supply--;
											force[DRONE]++;
											building[n].type=255;
											building[n].RB=0;
										}
									break;
					default:break;
				}
			}

			
			else
			{
				Build(program[IP]);
				if(ok==0)				
					program[IP]=255;
				
				IP++;
			}
// Reihenfolge mal ueberlegen
			if(dronemins<56)
			{
				mins+=mining[dronemins]; //~~~~~~~double wegmachen
				harvested_mins+=mining[dronemins];
			}
			else 
			{
				mins+=mining[56];
				harvested_mins+=mining[56];
			}
			if(dronegas<5)
			{
				gas+=gasing[dronegas];
				harvested_gas+=gasing[dronegas];
			}
			else
			{
				gas+=gasing[4];
				harvested_gas+=gasing[4];
			}
			ready=1;
			for(i=0;i<BUILDING_TYPES;i++)
				ready&=(goal[i]<=force[i]);

			timer++;
		}

		
	fitness=0;

	if(ready==0)
	{
		timer=MAX_TIME;
		fitness=5000-harvested_mins-harvested_gas;
		//for(i=0;i<BUILDING_TYPES;i++)
	 	//	if(goal[i]>force[i])
		//		fitness+=(goal[i]-force[i])*(goal[i]-force[i]);
			//if(harvested_gas<600)
			//	fitness+=6-(harvested_gas/100);
	}
	//fitness+=timer;
}


void Mutate()
{
	unsigned char X;
	for(j=0;j<MUTATIONS;j++)
	{
		if((rand()%MUTATION_FAKTOR==0))
			program[rand()%MAX_LENGTH]=ChooseInstr();
		if((rand()%MUTATION_FAKTOR==0))
		{
			X=rand()%MAX_LENGTH;
			switch(rand()%4)
			{
				case 0:for(i=X;i>0;i--) program[i]=program[i-1];program[0]=ChooseInstr();break;// Loeschen und von vorne nachruecken
				case 1:for(i=X;i<MAX_LENGTH;i++) program[i]=program[i+1];program[MAX_LENGTH-1]=ChooseInstr();break;			// Loeschen und von hinten vorruecken
				case 2:for(i=0;i<X;i++) program[i]=program[i+1];program[X]=ChooseInstr();break;			// Einfuegen und nach vorne schieben
				case 3:for(i=MAX_LENGTH-1;i>X;i--) program[i]=program[i-1];program[X]=ChooseInstr();break;	// Einfuegen und nach hinten schieben
			}
		}
			
	}
	
}

void Init()
{

	for(i=0;i<BUILDING_TYPES;i++)
	{
		force[i]=0;
		availible[i]=0;
		building[i].RB=0;
		building[i].type=255;
	}
	IP=0;

	for(i=0;i<200;i++)
		larva[i]=0;
	fitness=5000;
	
	mins=50;
	gas=0;
	larvae=3;
	force[HATCHERY]=1;
	availible[HATCHERY]++;
	force[DRONE]=4;
	force[OVERLORD]=1;
	larvacounter=1;
	larva[0]=20;
	Supply=5;
	dronemins=4;
	dronegas=0;
	NewBuildingReady=0;
}

void Restart()
{
	afit=2000;
	if((SRESTART==0)||(run>0))
	{
		for(i=0;i<MAX_LENGTH;i++)
			program[i]=ChooseInstr();
	}
	else if(SRESTART>0)
	for(i=0;i<MAX_LENGTH;i++)
		program[i]=200;

	if(SRESTART==2)
	{
		program[0]=DRONE;
		program[2]=WAIT_FOR_NEXT;
		program[4]=DRONE;
		program[6]=WAIT_FOR_NEXT;
		program[8]=DRONE;
		program[10]=WAIT_FOR_NEXT;
		program[12]=DRONE;
		program[14]=WAIT_FOR_NEXT;
		program[16]=DRONE;
		program[18]=WAIT_FOR_NEXT;
		program[20]=OVERLORD;
		program[22]=WAIT_FOR_NEXT;
		program[24]=EXTRACTOR;
		program[26]=WAIT_FOR_NEXT;
		program[28]=ONE_MINERAL_DRONE_TO_GAS;
		program[30]=ONE_MINERAL_DRONE_TO_GAS;
		program[32]=ONE_MINERAL_DRONE_TO_GAS;
		program[34]=DRONE;
		program[36]=WAIT_FOR_NEXT;
		program[38]=OVERLORD;
		program[40]=WAIT_FOR_NEXT;
		program[42]=DRONE;
		program[44]=WAIT_FOR_NEXT;
		program[46]=DRONE;
		program[48]=WAIT_FOR_NEXT;
		program[50]=SPAWNING_POOL;
		program[52]=WAIT_FOR_NEXT;
		program[54]=LAIR;
		program[56]=WAIT_FOR_NEXT;
		program[58]=SPIRE;
		program[60]=WAIT_FOR_NEXT;
		program[62]=OVERLORD;
		program[64]=WAIT_FOR_NEXT;
		program[66]=MUTALISK;
		program[68]=WAIT_FOR_NEXT;
		program[70]=MUTALISK;
		program[72]=WAIT_FOR_NEXT;
		program[74]=MUTALISK;
		program[76]=WAIT_FOR_NEXT;
		program[78]=DRONE;
		program[80]=WAIT_FOR_NEXT;
		program[82]=DRONE;
		program[84]=WAIT_FOR_NEXT;
	}


}

} player[MAX_PLAYER];


int main(int argc, char* argv[])
{
  unsigned char Sporen[2][MAX_LENGTH];
  unsigned char calc,pos,l;
  unsigned char child[MAX_CHILDREN];
  unsigned char adder;
  
  for(i=0;i<BUILDING_TYPES;i++)
	  goal[i]=0;
  goal[DRONE]=20;
  goal[OVERLORD]=5;
  goal[MUTALISK]=6;
  goal[EXTRACTOR]=1;
  goal[LAIR]=1;
  goal[SPIRE]=1;
  goal[SPAWNING_POOL]=1;
 
  for(i=0;i<RUNNINGS;i++)
  {
	Save[i].fitness=666;
	Save[i].timer=333;
	for(j=0;j<MAX_LENGTH;j++)
		Save[i].program[j]=(unsigned char)254;
  }
  
  adder=0;
  for(i=0;i<ONE_MINERAL_DRONE_TO_GAS;i++)
  {
	adder+=goal[i];
	probability[i]=adder;
  }
  adder+=10;
  probability[ONE_MINERAL_DRONE_TO_GAS]=adder;
  adder+=5;
  probability[ONE_GAS_DRONE_TO_MINERAL]=adder;
  adder+=20;
  probability[WAIT_FOR_NEXT]=adder;
  adder+=10;
  probability[WAIT_FOR_LAST]=adder;
  adder+=3;
  probability[BREAK_UP_BUILDING_LAST]=adder;
  adder+=4;
  probability[BREAK_UP_BUILDING_FIRST]=adder;
  adder+=50;
  probability[BUILDING_TYPES]=adder; // 1 sec. Pause 

  
  
  
  
  generation=0;


	srand(time(NULL));
	 HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	 COORD coord={0,0};
	COORD coord2={25,22};
	SetConsoleCursorPosition(hStdOut,coord2);
	printf("This is Freeware. Brought to you by clawsoftware.de");

	for(l=0;l<MAX_PLAYER;l++)
		player[l].Restart();
	run=0;

	while( (kbhit()==0) && (run<RUNNINGS))
	{
		for(l=0;l<MAX_PLAYER;l++)
		player[l].Init();

		for(l=0;l<MAX_PLAYER;l++)
			player[l].Mutate();
		
		for(l=0;l<MAX_PLAYER;l++)
			player[l].Calculate();

		for(i=0;i<MAX_PLAYER-3;i++)
			for(j=0;j<MAX_PLAYER-i-1;j++)
				if(player[j].fitness>player[j+1].fitness)
				{
					tempw=player[j].fitness;
					player[j].fitness=player[j+1].fitness;
					player[j+1].fitness=tempw;

					tempw=player[j].timer;
					player[j].timer=player[j+1].timer;
					player[j+1].timer=tempw;

					//buildings, mins, gas,... ?

					for(x=0;x<MAX_LENGTH;x++)
					{
						templ=player[j].program[x];
						player[j].program[x]=player[j+1].program[x];
						player[j+1].program[x]=templ;
					}
				}	

		
		if(player[0].fitness>0)
		{
			generation++;
			rfit++;
		}

		SetConsoleCursorPosition(hStdOut,coord);

		calc++;
		if(calc>2)
			calc=1;
		printf("Calculating ... %c\n",calc);
		printf("%i runs remaining . . .  \n",10-run);
		printf("Some Debug Output: \n");
		printf("Fit: %i, Time: %i    Generation: %i               \n",player[0].fitness,player[0].timer,generation);
		printf("Fit: %i, Time: %i    Generation: %i               \n",player[5].fitness,player[5].timer,generation);
		printf("Fit: %i, Time: %i    Generation: %i               \n",player[10].fitness,player[10].timer,generation);
		printf("Fit: %i, Time: %i    Generation: %i               \n",player[50].fitness,player[50].timer,generation);
		printf("Fit: %i, Time: %i    Generation: %i               \n",player[100].fitness,player[100].timer,generation);

		if(player[0].fitness<afit)
		{
			afit=player[0].fitness;
			rfit=0;
		}
				
		
						//sortieren unwichtig wenn folgende Fitness calculation
				/*for(i=0;i<MAX_PLAYER;i++)
					if(rand()%(player[i].fitness+MAX_PLAYER-i+1)==0)
						A=i;
				for(i=0;i<MAX_PLAYER;i++)
					if(rand()%(player[i].fitness+MAX_PLAYER-i+1)==0)
						B=i;
				//Fitness dann noch relativ zur Gesamtfitness setzen!*/

				//oder (wenns sortiert ist...)
					A=MAX_PLAYER;
				for(i=0;(i<MAX_PLAYER)&&(A==MAX_PLAYER);i++)
					if(rand()%(i+2)==0)
						A=i;
				B=MAX_PLAYER;
				for(i=0;(i<MAX_PLAYER)&&(B==MAX_PLAYER);i++)
					if(rand()%(i+2)==0)
						B=i;
				if(A==MAX_PLAYER) A=rand()%MAX_PLAYER;
				if(B==MAX_PLAYER) B=rand()%MAX_PLAYER;
				for(i=0;i<MAX_LENGTH;i++)
				{
					Sporen[0][i]=player[A].program[i];
					Sporen[1][i]=player[B].program[i];
				}

				x=0;
				for(i=0;(i<MAX_PLAYER)&&(x<MAX_CHILDREN);i++)
					if(rand()%(MAX_PLAYER-i+1)==0)
					{
						child[x]=i;
						x++;
					}

				if(x<MAX_CHILDREN-1)
					for(i=x;i<MAX_CHILDREN;i++)
						child[i]=rand()%MAX_PLAYER;
				
				for(l=0;l<MAX_CHILDREN;l++)
				{
					j=0;x=MAX_LENGTH;
					for(pos=0;pos<MAX_LENGTH;pos++)
					{
						x--;
						if(rand()%x==0) //Crossing Over Stellen finden
						{
							x=MAX_LENGTH;
							if(j==0) j=1;
							else
							if(j==1) j=0;
							else j=rand()%2;
							
							if((rand()%20==0)&&(run>0))
							j=2;
							

						}
						if(j==0)
							player[child[l]].program[pos]=Sporen[0][pos];
						else if(j==1)
							player[child[l]].program[pos]=Sporen[1][pos];
						else if(j==2) //fremd dna
							player[child[l]].program[pos]=Save[run-1].program[pos];
					}
					player[child[l]].Init();
				}

	if(rfit>MAX_GENERATIONS)
		{
			rfit=0;
			generation=0;
			Save[run].fitness=player[0].fitness;
			Save[run].timer=player[0].timer;
			for(x=0;x<MAX_LENGTH;x++)
				Save[run].program[x]=player[0].program[x];
			run++;
			for(l=0;l<MAX_PLAYER;l++)
				player[l].Restart();
		}
	
}

//Output
for(i=0;i<run-1;i++)
	for(j=0;j<run-i+1;j++)
		if(Save[j].fitness>Save[j+1].fitness)
		{
			tempw=Save[j].fitness;
			Save[j].fitness=Save[j+1].fitness;
			Save[j+1].fitness=tempw;

			tempw=Save[j].timer;
			Save[j].timer=Save[j+1].timer;
			Save[j+1].timer=tempw;

			for(x=0;x<MAX_LENGTH;x++)
			{
				templ=Save[j].program[x];
				Save[j].program[x]=Save[j+1].program[x];
				Save[j+1].program[x]=templ;
			}
		}			

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P
	printf("Calculating completed.\n");
	printf("Final fitness: %i (%i:%i Time used)\n",Save[0].fitness,Save[0].timer/60,Save[0].timer%60);
	printf("  You can find the Zerg Build Order in the ""zergbo.txt""\n");
	printf(" Brought to you by clawsoftware.de\n");
	printf("  Give it to all your friends :-)");
	printf("... and always remember: never attack a Terran wallin ;-)");
	printf("\n\n\n\n\n\n\n\n");

	ofstream out_file("zergbo.txt");
	out_file<<"Fitness: "<<Save[0].fitness<<"\n";
	out_file<<"Time used: "<<Save[0].timer/60<<":"<<Save[0].timer%60<<"\n";

	for(i=0;i<MAX_LENGTH;i++)	
	{
		if(Save[0].program[i]<BUILDING_TYPES)
			out_file<<(i+0)<<": "<<stats[Save[0].program[i]].name<<"\n";
	}
	
	for(i=0;i<BUILDING_TYPES;i++)
		if(player[0].force[i]>0)
			out_file<<stats[i].name<<" : "<<(player[0].force[i]+0)<<"\n";
	out_file.close();

	x=getch();
	return 0;
}




/*
ChooseInstr
SRESTART=2

 goals einlesen
save[0] ausgeben*/