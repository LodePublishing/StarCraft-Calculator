//sloooooooooooooow
//mal checken was da so lang braucht

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>
#include <malloc.h>

//#define MAX_NODES 100

#define HIDDEN 64

#define INPUTS 23
#define OUTPUTS 5

#define MAX_ORDERS 200

//#define MAX_NODE_DEPTH 3

#define RUNNINGS 10

#define MAX_PARENTS 2

#define MAX_PLAYER 128
#define MAX_BUILDINGS 10 // How many buildings can you built simultaneously?
#define BUILDING_TYPES 64  // warum 64 und nicht 51??

#define MAX_TIME 300

#define MAX_GENERATIONS 50
#define MAX_VESPENE 1

//#define MUTATION_FACTOR MAX_NODES*MAX_NODES*2
#define MUTATIONS HIDDEN*INPUTS/2


#define MAX_CHILDREN 12

#define CROSS_OVER_EVENT 200

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

#define BREAK_UP_BUILDING_LAST 54
#define BREAK_UP_BUILDING_FIRST 55

#define LARVA_MAX 400

struct Stats
{
	char name[35];
	unsigned short BT; // Build Time
	unsigned short mins,gas;
	unsigned char supply;
	unsigned char need; // 0: nothing, 1: larvae, 2: drone
};
//Abkuerzungen! ~ 10 Zeichen
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
	{"Spawning Pool",80,200,0,0,2},
	{"Creep Colony",20,75,0,0,2},
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



struct HIDDEN_NODES
{
		short Input;
		signed short CON[OUTPUTS];
};

struct INPUT_NODES
{
		unsigned char Input;
		signed short CON[HIDDEN];
};

struct OUTPUT_NODES
{
		short Input;
};

unsigned short generation;
unsigned char num;

unsigned short x,i,j,A,B;

unsigned char goal[BUILDING_TYPES];

unsigned char Goal_Harvested_Gas,Goal_Harvested_Mins; // in 50er schritten



class Player
{
public:
	unsigned char force[BUILDING_TYPES];
	unsigned char availible[BUILDING_TYPES];

	unsigned short mins,gas,larvae,order_num;
	unsigned char dronemins,dronegas,New_Event;
	short Supply;

	struct Programm
	{
		unsigned char order;
		unsigned short time;
	} programm[MAX_ORDERS];
	
	struct Building
	{
		unsigned short RB; // Remaining Buildtime
		unsigned char type; // Type of Building
	} building[MAX_BUILDINGS];

	unsigned char nr,ok;
	unsigned char larva[LARVA_MAX]; // larvacounter for producing larvas
	unsigned char NewBuildingReady,LastBuildingReady,larvacounter;

	INPUT_NODES INode[INPUTS];
	OUTPUT_NODES ONode[OUTPUTS];
	HIDDEN_NODES HNode[HIDDEN];

	unsigned short harvested_gas,harvested_mins;
	unsigned short fitness,timer;


	unsigned char RunNeuralNetwork()
	{
//		inputs... Situation, Buildings, To build etc., jede Menge :\
//		Gas,Mins, Dronesmins,Dronesgas, Anzahl der Gebaeude, ...

		//erstmal weniger input
		// evtl techtree speichern und nur fuer die bo notwendige Gebaeude zulassen . . .

		unsigned short m,g;
		m=mins/50;
		g=gas/50;
	
		if(m<750)
		{
			INode[0].Input=(m%2>0);
			INode[1].Input=(m%4>1);
			INode[2].Input=(m%8>3);
			INode[3].Input=(m%16>7);
		}
		else
		{
			INode[0].Input=1;INode[1].Input=1;INode[2].Input=1;INode[3].Input=1;
		}
		
		if(g<750)
		{
			INode[4].Input=(g%2>0);
			INode[5].Input=(g%4>1);
			INode[6].Input=(g%8>3);
			INode[7].Input=(g%16>7);
		}
		else
		{
			INode[4].Input=1;INode[5].Input=1;INode[6].Input=1;INode[7].Input=1;
		}
		
		if(Supply<16)
		{
			INode[8].Input=(Supply%2>0);
			INode[9].Input=(Supply%4>1);
			INode[10].Input=(Supply%8>3);
			INode[11].Input=(Supply%16>7);
		}
		else
		{
			INode[8].Input=1;INode[9].Input=1;INode[10].Input=1;INode[11].Input=1;
		}
		
		if(dronemins<32)
		{
			INode[12].Input=(dronemins%2>0);
			INode[13].Input=(dronemins%4>1);
			INode[14].Input=(dronemins%8>3);
			INode[15].Input=(dronemins%16>7);
			INode[16].Input=(dronemins%32>15);
		}	
		else
		{
			INode[12].Input=1;INode[13].Input=1;INode[14].Input=1;INode[15].Input=1;INode[16].Input=1;
		}
		
	
		if(dronegas<8)
		{
			INode[17].Input=(dronegas%2>0);
			INode[18].Input=(dronegas%4>1);
			INode[19].Input=(dronegas%8>3);
		}
		else
		{
			INode[17].Input=1;INode[18].Input=1;INode[19].Input=1;
		}
		
		if(larvae<8)
		{
			INode[20].Input=((larvae%2)>0);
			INode[21].Input=((larvae%4)>1);
			INode[22].Input=((larvae%8)>3);
		}
		else
		{
			INode[20].Input=1;INode[21].Input=1;INode[22].Input=1;
		}



		for(j=0;j<HIDDEN;j++)
			HNode[j].Input=0;
		for(j=0;j<OUTPUTS;j++)
			ONode[j].Input=0;
		
		for(i=0;i<INPUTS;i++)
			for(j=0;j<HIDDEN;j++)
				HNode[j].Input+=(INode[i].Input>0)*(INode[i].CON[j]);
		
		for(i=0;i<HIDDEN;i++)
			for(j=0;j<OUTPUTS;j++)
					ONode[j].Input+=(HNode[i].Input>0)*(HNode[i].CON[j]);

	//		return(y);
			//return((ONode[0].Input>0)+(ONode[1].Input>0)*2+(ONode[2].Input>0)*4);

			return((ONode[0].Input>0)*32+(ONode[1].Input>0)*16+(ONode[2].Input>0)*8+(ONode[3].Input>0)*4+(ONode[4].Input>0)*2+(ONode[5].Input>0));//1..128
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
		unsigned char m;
		nr=255;
		for(m=0;m<MAX_BUILDINGS;m++)
			if(building[m].RB==0)
			{
				nr=m;
				m=MAX_BUILDINGS;			
			}

		if( ((Supply>=stats[what].supply) || (stats[what].supply==0)) &&
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
							};break;
				case OVERLORD:Produce(what);break;
				case MUTALISK:if(force[SPIRE]+force[GREATER_SPIRE]>0) Produce(what);break;
				case GUARDIEN:if((force[GREATER_SPIRE]>0)&&(force[MUTALISK]>0))
							  {
								  force[MUTALISK]--;
								  Produce(what);
							  };break;
				case QUEEN:if(force[QUEENS_NEST]>0) Produce(what);break;
				case SCOURGE:if(force[SPIRE]+force[GREATER_SPIRE]>0) Produce(what);break;
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
				case NYDUS_CANAL:if(force[HIVE]>0) Produce(what);break;
				case HYDRALISK_DEN:if(force[SPAWNING_POOL]>0) Produce(what);break;
				case DEFILER_MOUND:if(force[HIVE]>0) Produce(what);break;
				case GREATER_SPIRE:if((force[SPIRE]>0)&&(availible[SPIRE]>0)&&(force[HIVE]>0)) 
								   {
									   availible[SPIRE]--;
									   Produce(what);
								   };break;
				case QUEENS_NEST:if(force[LAIR]>0) Produce(what);break;
				case EVOLUTION_CHAMBER:Produce(what);break;
				case ULTRALISK_CAVERN:if(force[HIVE]>0) Produce(what);break;
				case SPIRE:if(force[LAIR]>0) Produce(what);break;
				case SPAWNING_POOL:Produce(what);break;
				case CREEP_COLONY:Produce(what);break;
				case SPORE_COLONY:if((force[EVOLUTION_CHAMBER]>0)&&(force[CREEP_COLONY]>0))
								  {
									  force[CREEP_COLONY]--;
									  Produce(what);
								  };break;
				case SUNKEN_COLONY:if((force[SPAWNING_POOL]>0)&&(force[CREEP_COLONY]>0))
								   {
									   force[CREEP_COLONY]--;
									   Produce(what);
								   };break;
				case EXTRACTOR:if(force[EXTRACTOR]<MAX_VESPENE) Produce(what);break;
				case VENTRAL_SACKS:if((force[VENTRAL_SACKS]==0)&&(force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
								   {
									   if(availible[LAIR]>0) availible[LAIR]--;
									   else availible[HIVE]--;
									   Produce(what);
								   };break;
				case ANTENNAE:if((force[ANTENNAE]==0)&&(force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
							   {
								   if(availible[LAIR]>0) availible[LAIR]--;
								   else availible[HIVE]--;
								   Produce(what);
								};break;
				case PNEUMATIZED_CARAPACE:if((force[PNEUMATIZED_CARAPACE]==0)&&(force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
											{
												if(availible[LAIR]>0) availible[LAIR]--;
												else availible[HIVE]--;
												Produce(what);
											};break;
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
				case BREAK_UP_BUILDING_LAST:break;
				case BREAK_UP_BUILDING_FIRST:break;
				default:break;
			}	
		}
	}

	
	void Calculate()
	{
		unsigned char ready,BuildingRunning,program;
		unsigned short min,n,oldmins,oldgas;
		ready=0;
		timer=0;
		harvested_gas=0;
		harvested_mins=0;
		New_Event=1; // nur fuer erste Aktvierung!
		
		while((timer<MAX_TIME) && (ready==0))
		{			
			NewBuildingReady=0;
			BuildingRunning=0;
			ok=0;


			oldmins=mins/50;oldgas=gas/50;

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

			if( (oldmins<(mins/50)) || (oldgas<(gas/50)) )
				New_Event=1;

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
						New_Event=1;
						for(i=0;i<MAX_BUILDINGS;i++)
							LastBuildingReady&=(building[i].RB==0);
						force[building[j].type]++;
						availible[building[j].type]++;

						switch(building[j].type)
						{
							case DRONE:dronemins++;break;
							case OVERLORD:Supply+=8;break;
							case HATCHERY:larvacounter++;larvae++;larva[larvacounter]=21;Supply++;break;
							case EXTRACTOR:
									   if(dronemins>0)
										  {
											  dronemins--;
											  dronegas++;
										  };
								   if(dronemins>0)
										  {
											  dronemins--;
											  dronegas++;
										  };break;
		
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
				if(larvae<(force[HATCHERY]+force[LAIR]+force[HIVE])*3)
				{
					larva[i]--;
					if(larva[i]==0)
					{
						larvae++;
						larva[i]=20;
						New_Event=1;
					}
				}

//			Wann isses ueberhaupt notwendig neuralnetwork aufzurufen?
//			Gebaeude fertig
//			50 Mineralien/Gas gesammelt 
//			Neue Larve

			if(New_Event==1)
			{
				program=RunNeuralNetwork();
//				printf("%i.",program);

				if((program>ONE_GAS_DRONE_TO_MINERAL)&&(program<=BREAK_UP_BUILDING_LAST)&&(BuildingRunning==1))
				{
					ok=1;
					switch(program)
					{
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
				Build(program);

			if(ok==1)
			{
				programm[order_num].time=timer;
				programm[order_num].order=program;
				order_num++;
			} else programm[order_num].order=255;

			ready=1;
			for(i=0;i<BUILDING_TYPES;i++)
				ready&=(goal[i]<=force[i]);
			}
			
			timer++;
			New_Event=0;
		}

		







	fitness=4000;

	if(ready==0)
	{
		timer=MAX_TIME;
		for(i=0;i<BUILDING_TYPES;i++)
	 		if(goal[i]>force[i])
				fitness-=force[i];//*(goal[i]-force[i]);

	// Ziele unterschiedlich bewerten!
			// sqrt nochmal ueberlegen mmmh :| programm muss halt schritt fuer schritt belohnt werden ^^ vielleicht je nach techstufe, also z.B. pool: 1, lair: 2, spire: 3~~~~

//		if(Goal_Harvested_Gas>harvested_gas/50)
//			fitness+=Goal_Harvested_Gas-harvested_gas/50;

//		if(Goal_Harvested_Mins>harvested_mins/50)
//			fitness+=Goal_Harvested_Mins-harvested_mins/50;
	}
	fitness+=timer/2;
}


void Mutate()
{
	for(j=0;j<MUTATIONS;j++)
	{
		INode[rand()%INPUTS].CON[rand()%HIDDEN]++;
		INode[rand()%INPUTS].CON[rand()%HIDDEN]--;

		HNode[rand()%HIDDEN].CON[rand()%OUTPUTS]++;
		HNode[rand()%HIDDEN].CON[rand()%OUTPUTS]--;
	}
}

void Init()
{
	for(i=0;i<BUILDING_TYPES;i++)
	{
		force[i]=0;
		availible[i]=0;
	}
	for(i=0;i<MAX_BUILDINGS;i++)
	{
		building[i].RB=0;
		building[i].type=255;
	}

	for(i=0;i<LARVA_MAX;i++)
		larva[i]=20;

	fitness=5000;
	order_num=0;
	
	mins=50;
	gas=0;
	larvae=3;
	force[HATCHERY]=1;
	availible[HATCHERY]++;
	force[DRONE]=4;
	force[OVERLORD]=1;
	larvacounter=1;
	Supply=5;
	dronemins=4;
	dronegas=0;
	NewBuildingReady=0;

	for(i=0;i<INPUTS;i++)
		INode[i].Input=0;
	for(i=0;i<HIDDEN;i++)
		HNode[i].Input=0;
	for(i=0;i<OUTPUTS;i++)
		ONode[i].Input=0;
}


void Restart()
{
	for(i=0;i<INPUTS;i++)
	{
		INode[i].Input=0;
		for(j=0;j<HIDDEN;j++)
			INode[i].CON[j]=rand()%21-10;
	}

	for(i=0;i<HIDDEN;i++)
	{
		HNode[i].Input=0;
		for(j=0;j<OUTPUTS;j++)
			HNode[i].CON[j]=rand()%21-10;
	}

	for(i=0;i<OUTPUTS;i++)
		ONode[i].Input=0;

	afit=5000;
	for(i=0;i<MAX_ORDERS;i++)
	{
		programm[i].order=255;
		programm[i].time=0;
	}
}
};


Player *player[MAX_PLAYER];
Player *tempp;
Player *Save[RUNNINGS];

int main(int argc, char* argv[])
{
	unsigned char calc,l;
	unsigned short q,k;

	for(i=0;i<BUILDING_TYPES;i++)
		goal[i]=0;
//	goal[DRONE]=9;
//	goal[OVERLORD]=2;
//	goal[HATCHERY]=1;
//	goal[MUTALISK]=6;
//	goal[METABOLIC_BOOST]=1;
//	goal[EXTRACTOR]=1;
//	goal[LAIR]=1;
//	goal[SPIRE]=1;
	goal[SPAWNING_POOL]=1;
	goal[ZERGLING]=6;

	for(i=0;i<BUILDING_TYPES;i++)
	{
		Goal_Harvested_Gas+=goal[i]*stats[i].gas;
		Goal_Harvested_Mins+=goal[i]*stats[i].mins;
	}



//	Input noch rein (vom Output her die Datei, damit man von einem evtl alten Programm ein neues Problem angehen kann)
//Ausserdem: Goal Input datei, also insgesamt 2 Dateien...

	COORD c11={3,8},c12={3,9},c13={3,10},c14={3,11},c15={3,12},c21={12,8},c22={12,9},c23={12,10},c24={12,11},c25={12,12},c31={22,8},c32={22,9},c33={22,10},c34={22,11},c35={22,12};

	calc=0;

	generation=0;
	srand(time(NULL));
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord={0,0};
	COORD coord2={25,22};
	SetConsoleCursorPosition(hStdOut,coord2);
	printf("This is Freeware. Brought to you by clawsoftware.de");

	for(l=0;l<MAX_PLAYER;l++)
	{
		player[l]=(Player*)malloc(sizeof(Player));
		player[l]->Restart();
	}
	run=0;

	for(l=0;l<RUNNINGS;l++)
	{
		Save[l]=(Player*)malloc(sizeof(Player));
		Save[l]->Restart();
		for(q=0;q<MAX_ORDERS;q++)
		{
			Save[l]->programm[q].order=255;
			Save[l]->programm[q].time=0;
		}
	}

	SetConsoleCursorPosition(hStdOut,coord);
		
	printf("Calculating [");
	for(l=0;l<MAX_PLAYER/2;l++)
		printf("%c",calc);
	printf("]\n");


	while( (kbhit()==0) && (run<RUNNINGS))
	{
		for(l=0;l<MAX_PLAYER;l++)
			player[l]->Init();

		for(l=0;l<MAX_PLAYER;l++)
			player[l]->Mutate();
	
		SetConsoleCursorPosition(hStdOut,coord);
		
		calc++;
		if(calc>2)
			calc=1;
		
		printf("Calculating [");
	
		for(l=0;l<MAX_PLAYER;l++)
		{
			player[l]->Calculate();
			if(l%2==0) printf("%c",calc);
		}

		printf("]\n");

		for(i=0;i<MAX_PLAYER-3;i++)
			for(j=0;j<MAX_PLAYER-i-1;j++)
				if(player[j]->fitness>player[j+1]->fitness)
				{
					tempp=player[j];
					player[j]=player[j+1];
					player[j+1]=tempp;
				}	

		
		generation++;
		rfit++;
		printf("\n");
		printf("%i runs remaining (this run %i generations remaining)      \n",RUNNINGS-run,MAX_GENERATIONS-rfit);
		printf("\n");
		printf("Overview Generation %i :   (best fitness: %i)          \n",generation,afit);
		printf("\n");

		printf("[fitness]  [time]  [position]\n");
		printf("----------------------------------------\n");


	SetConsoleCursorPosition(hStdOut,c11);printf("%i",player[0]->fitness);
	SetConsoleCursorPosition(hStdOut,c12);printf("%i",player[MAX_PLAYER/16]->fitness);
	SetConsoleCursorPosition(hStdOut,c13);printf("%i",player[MAX_PLAYER/8]->fitness);
	SetConsoleCursorPosition(hStdOut,c14);printf("%i",player[MAX_PLAYER/4]->fitness);
	SetConsoleCursorPosition(hStdOut,c15);printf("%i",player[MAX_PLAYER/2]->fitness);

	SetConsoleCursorPosition(hStdOut,c21);printf("%i:%i",player[0]->timer/60,player[0]->timer%60);
	SetConsoleCursorPosition(hStdOut,c22);printf("%i:%i",player[MAX_PLAYER/16]->timer/60,player[MAX_PLAYER/16]->timer%60);
	SetConsoleCursorPosition(hStdOut,c23);printf("%i:%i",player[MAX_PLAYER/8]->timer/60,player[MAX_PLAYER/8]->timer%60);
	SetConsoleCursorPosition(hStdOut,c24);printf("%i:%i",player[MAX_PLAYER/4]->timer/60,player[MAX_PLAYER/4]->timer%60);
	SetConsoleCursorPosition(hStdOut,c25);printf("%i:%i",player[MAX_PLAYER/2]->timer/60,player[MAX_PLAYER/2]->timer%60);

	SetConsoleCursorPosition(hStdOut,c31);printf("#1");
	SetConsoleCursorPosition(hStdOut,c32);printf("#%i",MAX_PLAYER/16);
	SetConsoleCursorPosition(hStdOut,c33);printf("#%i",MAX_PLAYER/8);
	SetConsoleCursorPosition(hStdOut,c34);printf("#%i",MAX_PLAYER/4);
	SetConsoleCursorPosition(hStdOut,c35);printf("#%i",MAX_PLAYER/2);

	printf("\n");
	printf("Build Order of the best individual:");

		if(player[0]->fitness<afit)
		{
			afit=player[0]->fitness;
			rfit=0;
		}

		x=0;
		printf("\n");

		for(i=0;i<MAX_ORDERS;i++)	
		{
			if(player[0]->programm[i].order<BUILDING_TYPES)
			{
				x++;
				printf("[%2i:%2i] (%c) ",player[0]->programm[i].time/60,player[0]->programm[i].time%60,stats[player[0]->programm[i].order].name[0]);
				if(x%3==0) printf("\n");
			}
		}
		printf(" . . . \n");
		printf("Drones: %i",player[0]->force[DRONE]);
		//printf("Harvested Mins: %i, Harvested Gas: %i              \n",player[0]->harvested_mins,player[0]->harvested_gas);
		printf("                                         ");

// besser machen, mehr von relativer Fitness abhaengen lassen -> schnellere Evolution (mei... lokale Minima, was solls)
		for(x=0;x<MAX_PARENTS;x++)				
		{
		
						//sortieren unwichtig wenn folgende Fitness calculation
				/*for(i=0;i<MAX_PLAYER;i++)
					if(rand()%(player[i]->fitness+MAX_PLAYER-i+1)==0)
						A=i;
				for(i=0;i<MAX_PLAYER;i++)
					if(rand()%(player[i]->fitness+MAX_PLAYER-i+1)==0)
						B=i;
				//Fitness dann noch relativ zur Gesamtfitness setzen!*/
	//Nach fitness sortieren, 0-100, 0:~~~~
				//oder (wenns sortiert ist...)
					A=MAX_PLAYER;
				for(i=0;(i<MAX_PLAYER-MAX_CHILDREN)&&(A==MAX_PLAYER);i++)
					if(rand()%(i+3)==0)
						A=i;
				B=MAX_PLAYER;
				for(i=0;(i<MAX_PLAYER)&&(B==MAX_PLAYER);i++)
					if(rand()%(i+3)==0)
						B=i;
				if(A==MAX_PLAYER) A=rand()%(MAX_PLAYER-MAX_CHILDREN);
				if(B==MAX_PLAYER) B=rand()%(MAX_PLAYER-MAX_CHILDREN);

				for(l=0;l<MAX_CHILDREN;l++)
				{
					k=CROSS_OVER_EVENT; //~~~~~~
					tempp=player[A];

				for(i=0;i<INPUTS;i++)
					for(j=0;j<HIDDEN;j++)
					{
						k--;
						player[MAX_PLAYER-1-l-x*MAX_CHILDREN]->INode[i].CON[j]=tempp->INode[i].CON[j];
						if(rand()%k==0)
							{
								k=CROSS_OVER_EVENT;
								if(tempp==player[A])
									tempp=player[B];
								else tempp=player[A];
							}
					}

				for(i=0;i<HIDDEN;i++)
					for(j=0;j<OUTPUTS;j++)
					{
						k--;
						player[MAX_PLAYER-1-l-x*MAX_CHILDREN]->HNode[i].CON[j]=tempp->HNode[i].CON[j];
						if(rand()%k==0)
							{
								k=CROSS_OVER_EVENT;
								if(tempp==player[A])
									tempp=player[B];
								else tempp=player[A];
							}
					}

			}
}


	    if(rfit>=MAX_GENERATIONS)
		{
			rfit=0;
			generation=0;
			calc=0;

			for(i=0;i<INPUTS;i++)
				for(j=0;j<HIDDEN;j++)
					Save[run]->INode[i].CON[j]=player[0]->INode[i].CON[j];
			for(i=0;i<HIDDEN;i++)
				for(j=0;j<OUTPUTS;j++)
					Save[run]->HNode[i].CON[j]=player[0]->HNode[i].CON[j];

			Save[run]->fitness=player[0]->fitness;
			Save[run]->timer=player[0]->timer;
			Save[run]->harvested_mins=player[0]->harvested_mins;
			Save[run]->harvested_gas=player[0]->harvested_gas;

			for(i=0;i<MAX_ORDERS;i++)
			{
				Save[run]->programm[i].order=player[0]->programm[i].order;
				Save[run]->programm[i].time=player[0]->programm[i].time;
			}

			for(i=0;i<BUILDING_TYPES;i++)
				Save[run]->force[i]=player[0]->force[i];

			run++;

			for(l=0;l<MAX_PLAYER;l++)
				player[l]->Restart();
		}

	} // end while...

//Output

if(run==0)
{
	for(i=0;i<INPUTS;i++)
		for(j=0;j<HIDDEN;j++)
			Save[run]->INode[i].CON[j]=player[0]->INode[i].CON[j];
	for(i=0;i<HIDDEN;i++)
		for(j=0;j<OUTPUTS;j++)
			Save[run]->HNode[i].CON[j]=player[0]->HNode[i].CON[j];	
	Save[run]->fitness=player[0]->fitness;
	Save[run]->timer=player[0]->timer;
	Save[run]->harvested_mins=player[0]->harvested_mins;
	Save[run]->harvested_gas=player[0]->harvested_gas;

	for(i=0;i<MAX_TIME;i++)
	{
		Save[run]->programm[i].order=player[0]->programm[i].order;
		Save[run]->programm[i].time=player[0]->programm[i].time;
	}

	for(i=0;i<BUILDING_TYPES;i++)
		Save[run]->force[i]=player[0]->force[i];
}
else

for(i=0;i<run-3;i++)
	for(j=0;j<run-i-1;j++)
		if(Save[j]->fitness>Save[j+1]->fitness)//!!!!! access violation
		{
			tempp=Save[j];
			Save[j]=Save[j+1];
			Save[j+1]=tempp;
		}

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//new page :P
	printf("Calculating completed.\n");
	printf("Final fitness: %i (%i:%i Time used)\n",Save[0]->fitness,Save[0]->timer/60,Save[0]->timer%60);
	printf("  You can find the Zerg Build Order in the ""zergbo.txt""\n");
	printf(" Brought to you by clawsoftware.de\n");
	printf("  Give it to all your friends :-)");
	printf("\n\n\n\n\n\n\n\n");

	ofstream out_file("zergbo2.txt");
	out_file<<"Fitness: "<<Save[0]->fitness<<"\n";
	out_file<<"Time used: "<<Save[0]->timer/60<<":"<<Save[0]->timer%60<<"\n";


	for(i=0;i<MAX_ORDERS;i++)	
	{
		if(Save[0]->programm[i].order<BUILDING_TYPES)
			out_file<<(Save[0]->programm[i].time+0)<<". second: "<<stats[Save[0]->programm[i].order].name<<"\n";
	}
	
	for(i=0;i<BUILDING_TYPES;i++)
		if(Save[0]->force[i]>0)
			out_file<<stats[i].name<<" : "<<(Save[0]->force[i]+0)<<"\n";

	out_file<<"Harvested Minerals: "<<(Save[0]->harvested_mins+0)<<"\n";
	out_file<<"Harvested Gas: "<<(Save[0]->harvested_gas+0)<<"\n";

	out_file.close();

	for(i=0;i<MAX_PLAYER;i++)
		free(player[i]);
	for(i=0;i<RUNNINGS;i++)
		free(Save[i]);

	tempp=NULL;
	
	x=getch();
	return 0;
}




/*
ChooseInstr
SRESTART=2

 goals einlesen

  save[0] ausgeben*/