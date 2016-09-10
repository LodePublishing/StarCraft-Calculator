#define MAX_LENGTH 50
#define RUNNINGS 10
#define MAX_PLAYER 128

#define MAX_BUILDINGS 10 // How many buildings can you built simultaneously?
#define BUILDING_TYPES 55  // warum 64 und nicht 51??

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

#define BREAK_UP_BUILDING 54
#define LARVA_MAX 400

struct Stats
{
	char name[35];
	unsigned short BT; // Build Time
	unsigned short mins,gas;
	unsigned char supply;
	unsigned char need; // 0: nothing, 1: larvae, 2: drone
	unsigned char extractor,lair,den,evo,queens,spire,hive,ultra,defiler,greaterspire;
			// pool, den, evo, hatch, lair, hive, defiler, spire, greater spire, 
};

struct GOAL
{
	unsigned char what;
	unsigned short time;
};

//Abkuerzungen! ~ 10 Zeichen
const Stats stats[BUILDING_TYPES]=
{
	{"Zergling",28,50,0,1,1, 0,0,0,0,0,0,0,0,0,0},
	{"Hydralisk",28,75,0,1,1, 1,0,1,0,0,0,0,0,0,0},
	{"Ultralisk",60,200,200,6,1, 1,1,0,0,1,0,1,1,0,0},
	{"Drone",23,50,0,1,1, 0,0,0,0,0,0,0,0,0,0},
	{"Defiler",50,50,150,2,1, 1,1,0,0,1,0,1,0,1,0},
	{"Lurker",40,50,100,2,0, 1,1,1,0,0,0,0,0,0,0},
	{"Overlord",40,100,0,0,1, 0,0,0,0,0,0,0,0,0,0},
	{"Mutalisk",40,100,100,2,1, 1,1,0,0,0,1,0,0,0,0},
	{"Guardien",40,50,100,2,0, 1,1,0,0,1,1,1,0,0,1},
	{"Queen",50,100,100,2,1, 1,1,0,0,1,0,0,0,0,0},
	{"Scourge",30,25,75,1,1, 1,1,0,0,0,1,0,0,0,0},
	{"Devourer",40,100,50,2,0, 1,1,0,0,1,1,1,0,0,1},

	{"Hatchery",120,300,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Lair",100,150,100,0,0, 1,1,0,0,0,0,0,0,0,0},
	{"Hive",120,200,150,0,0, 1,1,0,0,1,0,1,0,0,0},
	{"Nydus Canal",40,150,0,0,2, 1,1,0,0,1,0,1,0,0,0},
	{"Hydralisk den",40,100,50,0,2, 1,0,1,0,0,0,0,0,0,0},
	{"Defiler mound",60,100,100,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Greater Spire",120,100,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Queen's Nest",60,150,100,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Evolution Chamber",40,75,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Ultralisk Cavern",80,150,200,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Spire",120,200,150,0,2, 1,1,0,0,0,0,0,0,0,0},
	{"Spawning Pool",80,200,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Creep Colony",20,75,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Spore Colony",20,50,0,0,0, 0,0,0,1,0,0,0,0,0,0},
	{"Sunken Colony",20,50,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Extractor",40,50,0,0,2, 0,0,0,0,0,0,0,0,0,0},

	{"Ventral Sacs",160,200,200,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Antennae",133,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Pneumatized Carapace",133,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Metabolic Boost",100,100,100,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Adrenal Glands",100,200,200,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Muscular Augments",100,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Grooved Spines",100,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Gamete Meiosis",166,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Metasynaptic node",166,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Chitinous Plating",133,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Anabolic Synthesis",133,200,200,0,0, 0,0,0,0,0,0,0,0,0,0},

	{"Burrowing",80,100,100,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Spawn Broodling",80,100,100,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Dark Swarm",80,100,100,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Plague",100,200,200,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Consume",100,100,100,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Ensnare",80,100,100,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Parasite",80,100,100,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Lurker Aspect",120,200,200,0,0, 0,0,0,0,0,0,0,0,0,0},

	{"Carapace",266,150,150,0,0, 0,0,0,1,0,0,0,0,0,0},
	{"Flyer Carapace",266,150,150,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Melee Attacks",266,100,100,0,0, 0,0,0,1,0,0,0,0,0,0},
	{"Missile Attacks",266,100,100,0, 0,0,0,1,0,0,0,0,0,0},
	{"Flyer Attacks",266,100,100,0, 0,0,0,0,0,0,0,0,0,0},
	{"Bring one Mineral Drone to Gas",330,200,200,0, 0,0,0,0,0,0,0,0,0,0},
	{"Bring one Gas Drone to Mineral",266,100,100,0, 0,0,0,0,0,0,0,0,0,0},
	{"Break up Building",0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
};	

struct Namen
{
	char b[6];
};


const Namen kurz[BUILDING_TYPES]=
{
	{"ZLing"},
	{"Hydra"},
	{"Ultra"},
	{"Drone"},
	{"Defil"},
	{"Lurkr"},
	{"Overl"},
	{"Mutal"},
	{"Guard"},
	{"Queen"},
	{"Scour"},
	{"Devou"},
	{"Hatch"},
	{"Lair "},
	{"Hive "},
	{"Nydus"},
	{"HyDen"},
	{"DeMou"},
	{"GSpir"},
	{"QNest"},
	{"EvoCh"},
	{"UCave"},
	{"Spire"},
	{"SPool"},
	{"Creep"},
	{"Spore"},
	{"Sunkn"},
	{"Extra"},
	{"VSacs"},
	{"Anten"},
	{"Pneum"},
	{"Boost"},
	{"Adren"},
	{"Muscu"},
	{"Groov"},
	{"Gamet"},
	{"MNode"},
	{"Chiti"},
	{"Anabo"},
	{"Burro"},
	{"Spawn"},
	{"Swarm"},
	{"Plagu"},
	{"Consu"},
	{"Ensna"},
	{"Paras"},
	{"LAspc"},
	{"Carap"},
	{"FCarp"},
	{"Melee"},
	{"Missl"},
	{"FAtta"},
	{"->Gas"},
	{"->Min"},
	{"Cancl"}
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



unsigned char Ziel[BUILDING_TYPES],Build_Av[BUILDING_TYPES],Build_Bv[BUILDING_TYPES]; 
unsigned char Vespene_Av,Max_Build_Types;
unsigned long Fitness_All;
unsigned short Fitness_Average;
unsigned short Max_Time,Max_Generations,Mut_Rate,Mutations,Max_Vespene;
unsigned short afit;
unsigned short generation;
unsigned char num;
unsigned short x,y,i,j,A,B;
GOAL goal[BUILDING_TYPES];
unsigned short Goal_Harvested_Gas,Goal_Harvested_Mins; 



class Player
{
public:
	unsigned char force[BUILDING_TYPES];
	unsigned char availible[BUILDING_TYPES];

	unsigned short mins,gas,larvae,IP,min,n;
	unsigned char dronemins,dronegas,length,BuildingRunning;
	short Supply;

	unsigned char program[MAX_LENGTH];
	unsigned short timep[MAX_LENGTH];
	
	struct Building
	{
		unsigned short RB; // Remaining Buildtime
		unsigned char type; // Type of Building
	} building[MAX_BUILDINGS];

	unsigned char nr,ok;
	unsigned char larva[LARVA_MAX]; // larvacounter for producing larvas
	unsigned char larvacounter;

	unsigned short harvested_gas,harvested_mins;
	unsigned short fitness,timer;



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
			if(who==ZERGLING)
			{
				if(force[METABOLIC_BOOST]==1)
					building[nr].RB+=30;
				if(force[METABOLIC_BOOST]==1)
					building[nr].RB+=50;
			}
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
		
			if((what==ONE_MINERAL_DRONE_TO_GAS)&&(force[EXTRACTOR]>0)&&(dronemins>0))
			{
				ok=1;
				dronemins--;
				dronegas++;
			}
			else
			if((what==ONE_GAS_DRONE_TO_MINERAL)&&(dronegas>0))
			{
				ok=1;
				dronegas--;
				dronemins++;
			}
			else
			if((what==BREAK_UP_BUILDING)&&(BuildingRunning>0))
			{
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
						ok=1;
						dronemins++;
						mins+=stats[building[n].type].mins*0.75;
						gas+=stats[building[n].type].gas*0.75;
						Supply--;
						force[DRONE]++;
						if(building[n].type==EXTRACTOR)
							Vespene_Av++;
						building[n].type=255;
						building[n].RB=0;
					}
			}
			else
			{
		
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
				case LAIR:if((force[HATCHERY]>0)&&(force[SPAWNING_POOL]>0)&&(availible[HATCHERY]>0)) 
						  {
							  availible[HATCHERY]--;	  
							  Produce(what);
						  }
							  break;
				case HIVE:if((force[LAIR]>0)&&(force[QUEENS_NEST]>0)&&(availible[LAIR]>0))
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
				case EXTRACTOR:if(Vespene_Av>0) { Vespene_Av--;Produce(what);}break;//Fehler: wenn 2 extractoren gleichzeitig gebaut werden, gehts hier net richtig!
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
			case MUSCULAR_AUGMENTS:
			case GROOVED_SPINES:if((force[what]==0)&&(force[HYDRALISK_DEN]>0)&&(availible[HYDRALISK_DEN]>0))
									 {
										availible[HYDRALISK_DEN]--;
										Produce(what);
									 };break;
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

				default:break;
			}	
		}
	}
	}

	
	void Calculate()
	{
		unsigned char ready,tt;
		ready=0;
		timer=0;
		harvested_gas=0;
		harvested_mins=0;
		Vespene_Av=Max_Vespene;		
		tt=0;

		while((timer<Max_Time) && (ready==0) && (IP<MAX_LENGTH))
		{			
			BuildingRunning=0;
			ok=0;

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


			for(j=0;j<MAX_BUILDINGS;j++)
			{
				if(building[j].RB>0)
				{
					BuildingRunning=1;
					building[j].RB--;
					if(building[j].RB==0)
					{
						force[building[j].type]++;
						availible[building[j].type]++;

						switch(building[j].type)
						{
							case DRONE:dronemins++;break;
							case OVERLORD:Supply+=8;break;
							case HATCHERY:larvacounter++;larvae++;larva[larvacounter]=21;Supply++;break;
							case EXTRACTOR:break;		
							case LAIR:force[HATCHERY]--;availible[LAIR]++;break;
							case HIVE:force[LAIR]--;availible[HIVE]++;break;
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
							case MUSCULAR_AUGMENTS:
							case GROOVED_SPINES:availible[HYDRALISK_DEN]++;break;
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
						ready=1;
						for(i=0;i<BUILDING_TYPES;i++)
							ready&=((goal[i].what<=force[i])&&((goal[i].time>timer)||(goal[i].time==0)));
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
					}
				}

			Build(Build_Av[program[IP]]);
			tt++;
			if((ok==1)||(tt>100))
			{
				if(tt<=100) timep[IP]=timer;
				else timep[IP]=0;
				tt=0;
				IP++;
			}


		timer++;
	}

	fitness=0;

	length=IP;

	if(ready==0)
	{
		timer=Max_Time;
		//Bei Zeit: Zwischenziele rein, z.B. Lair, Hive, etc. ??
		
		for(i=0;i<BUILDING_TYPES;i++)		
		if(goal[i].what>0)
		{
			if(goal[i].what>force[i])
					fitness+=((force[i]*100)/goal[i].what);
					else fitness+=100;
			switch(i)
			{
				case LURKER:if(goal[HYDRALISK].what<force[HYDRALISK])
							{
								if(goal[LURKER].what>force[HYDRALISK]-goal[HYDRALISK].what)
									fitness+=(((force[HYDRALISK]-goal[HYDRALISK].what)*50)/goal[LURKER].what);
								else fitness+=50;
							};break;
				case SPORE_COLONY:
				case SUNKEN_COLONY:if(goal[CREEP_COLONY].what<force[CREEP_COLONY])
							{
								if(goal[i].what>force[CREEP_COLONY]-goal[CREEP_COLONY].what)
									fitness+=(((force[CREEP_COLONY]-goal[CREEP_COLONY].what)*25)/goal[i].what);
								else fitness+=25;
							};break;

				case GUARDIEN:
				case DEVOURER:if(goal[MUTALISK].what<force[MUTALISK])
							{
								if(goal[i].what>force[MUTALISK]-goal[MUTALISK].what)
									fitness+=(((force[MUTALISK]-goal[MUTALISK].what)*25)/goal[i].what);
								else fitness+=25;
							};break;
				default:break;
			}
		}
			

	// Ziele unterschiedlich bewerten!
			// sqrt nochmal ueberlegen mmmh :| programm muss halt schritt fuer schritt belohnt werden ^^ vielleicht je nach techstufe, also z.B. pool: 1, lair: 2, spire: 3~~~~

		if(Goal_Harvested_Gas>harvested_gas)
			fitness+=(harvested_gas*100)/Goal_Harvested_Gas;
		else fitness+=100;

		if(Goal_Harvested_Mins>harvested_mins)
			fitness+=(harvested_mins*100)/Goal_Harvested_Mins;
		else fitness+=100;
		//!!!!!!!!!!!!!!!!!

	}
	else
	{
		fitness=Max_Time-timer;//~~~~~~~~~Zeit staerker ins gewicht fallen lassen!
		fitness+=200;//mins, gas
		for(i=0;i<BUILDING_TYPES;i++)
	 		if(goal[i].what>0)
				fitness+=100;
	}
}


void Mutate()
{
	unsigned char ttt,ta,tb;
//loeschen, einfuegen, veraendern
	for(i=0;i<Mutations;i++)
	{
	if(rand()%Mutations==0)
	{
		x=rand()%MAX_LENGTH;
		for(y=x;y<MAX_LENGTH-1;y++)
			program[y]=program[y+1];
	}
	
	if(rand()%Mut_Rate==0)
	{
		x=rand()%MAX_LENGTH;
		for(y=MAX_LENGTH-1;y>x;y--)
			program[y]=program[y-1];
		program[x]=rand()%Max_Build_Types;
	}

	if(rand()%Mut_Rate==0)
	{
		x=rand()%MAX_LENGTH;
		program[x]=rand()%Max_Build_Types;
	}
	if(rand()%Mut_Rate==0)
	{
		ta=rand()%MAX_LENGTH;
		tb=rand()%MAX_LENGTH;
		ttt=program[ta];
		program[ta]=program[tb];
		program[tb]=ttt;
	}
	if(rand()%(Mut_Rate/2)==0)
	{
		ta=rand()%MAX_LENGTH;
		tb=rand()%MAX_LENGTH;
		if(ta>tb)
		{
		ttt=program[ta];
		for(i=ta;i<tb;i++)
			program[i]=program[i+1];
		program[tb]=ttt;
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
	}
	for(i=0;i<MAX_BUILDINGS;i++)
	{
		building[i].RB=0;
		building[i].type=255;
	}

	for(i=0;i<LARVA_MAX;i++)
		larva[i]=20;

	fitness=0;

	mins=50;
	gas=0;
	larvae=3;
	force[HATCHERY]=1;
	availible[HATCHERY]=1;
	force[DRONE]=4;
	force[OVERLORD]=1;
	larvacounter=1;
	Supply=5;
	dronemins=4;
	dronegas=0;
	IP=0;
}


	void Restart()
	{
		for(i=0;i<MAX_LENGTH;i++)
			program[i]=rand()%Max_Build_Types;
		timer=Max_Time;
		IP=0;
		fitness=0;
		length=MAX_LENGTH;
		afit=0;
	}
};
