#define MAX_LENGTH 50
#define RUNNINGS 10
#define MAX_PLAYER 128

#define MAX_BUILDINGS 10 // How many buildings can you built simultaneously?
#define BUILDING_TYPES 60

#define MARINE 0
#define GHOST 1
#define VULTURE 2
#define GOLIATH 3
#define SIEGE_TANK 4
#define SCV 5
#define FIREBAT 6
#define MEDIC  7

#define WRAITH 8
#define SCIENCE_VESSEL 9
#define DROPSHIP 10
#define BATTLE_CRUISER 11
#define VALKYRIE 12

#define COMMAND_CENTER 13
#define SUPPLY_DEPOT 14
#define REFINERY 15
#define BARRACKS 16
#define ACADEMY 17
#define FACTORY 18
#define STARPORT 19
#define SCIENCE_FACILITY 20
#define ENGINEERING_BAY 21
#define ARMORY 22
#define MISSILE_TURRET 23
#define BUNKER 24

#define COMSAT_STATION 25
#define NUCLEAR_SILO 26
#define CONTROL_TOWER 27
#define COVERT_OPS 28
#define PHYSICS_LAB 29
#define MACHINE_SHOP 30

#define STIM_PACKS 31
#define LOCKDOWN 32
#define EMP_SHOCKWAVE 33
#define SPIDER_MINES 34
#define TANK_SIEGE_MODE 35
#define IRRADIATE 36
#define YAMATO_GUN 37
#define CLOAKING_FIELD 38
#define PERSONNEL_CLOAKING 39
#define RESTORATION 40
#define OPTICAL_FLARE 41

#define U238_SHELLS 42
#define ION_THRUSTERS 43
#define TITAN_REACTOR 44
#define OCULAR_IMPLANTS 45
#define MOEBIUS_REACTOR 46
#define APOLLO_REACTOR 47
#define COLOSSUS_REACTOR 48
#define CADUCEUS_REACTOR 49
#define CHARON_BOOSTER 50

#define INFANTRY_ARMOR 51
#define INFANTRY_WEAPONS 52
#define VEHICLE_PLATING 53
#define VEHICLE_WEAPONS 54
#define SHIP_PLATING 55
#define SHIP_WEAPONS 56

#define NUCLEAR_WARHEAD 57

#define ONE_MINERAL_SCV_TO_GAS 58
#define ONE_GAS_SCV_TO_MINERAL 59



struct Stats
{
	char name[35];
	unsigned short BT; // Build Time
	unsigned short mins,gas;
	unsigned char supply;
};

struct GOAL
{
	unsigned char what;
	unsigned short time;
};

//Abkuerzungen! ~ 10 Zeichen
const Stats stats[BUILDING_TYPES]=
{
	{"Marine",24,50,0,1},
	{"Ghost",50,25,75,1},
	{"Vulture",30,75,0,2},
	{"Goliath",40,100,50,2},
	{"Siege Tank",50,150,100,2},
	{"SCV",20,50,0,1},
	{"Firebat",24,50,25,1},
	{"Medic",30,50,25,1},
	{"Wraith",60,150,100,2},
	{"Science Vessel",80,100,225,2},
	{"Dropship",50,100,100,2},
	{"Battle Cruiser",133,400,300,6},
	{"Valkyrie",50,250,125,3},

	{"Command Center",120,400,0,0},
	{"Supply Depot",40,100,0,0},
	{"Refinery",40,100,0,0},
	{"Barracks",80,150,0,0},
	{"Academy",80,150,0,0},
	{"Factory",80,200,100,0},
	{"Starport",70,150,100,0},
	{"Science Facility",60,100,150,0},
	{"Engineering Bay",60,125,0,0},
	{"Armory",80,100,50,0},
	{"Missile Turret",30,75,0,0},
	{"Bunker",30,100,0,0},

	{"Comsat Station",40,50,50,0},
	{"Nuclear Silo",40,100,100,0},
	{"Control Tower",80,50,50,0},
	{"Covert Ops",40,50,50,0},
	{"Physics Lab",40,50,50,0},
	{"Machine Shop",40,50,50,0},

	{"Stim Packs",80,100,100,0},
	{"Lockdown",100,200,200,0},
	{"EMP Shockwave",120,200,200,0},
	{"Spider Mines",80,100,100,0},
	{"Siege Mode",80,150,150,0},
	{"Irradiate",80,200,200,0},
	{"Yamato Gun",120,100,100,0},
	{"Cloaking Field",100,150,150,0},
	{"Personnel Cloaking",80,100,100,0},
	{"Restoration",80,100,100,0},
	{"Optical Flare",120,100,100,0},

	{"U-238 Shells",100,150,150,0},
	{"Ion Thrusters",100,100,100,0},
	{"Titan Reactor",166,150,150,0},
	{"Ocular Implants",166,100,100,0},
	{"Moebius Reactor",166,200,200,0},
	{"Apollo Reactor",166,200,200,0},
	{"Colossus Reactor",166,150,150,0},
	{"Caduceus Reactor",166,150,150,0},
	{"Charon Booster",133,100,100,0},

	{"Infantry Armor",266,100,100,0},
	{"Infantry Weapons",266,100,100,0},
	{"Vehicle Plating",266,100,100,0},
	{"Vehicle Weapons",266,100,100,0},
	{"Ship Plating",266,150,150,0},
	{"Ship Weapons",266,100,100,0},

	{"Nuclear Warhead",100,200,200,1},

	{"Bring one Mineral SCV to Gas",0,0,0,0},
	{"Bring one Gas SCV to Mineral",0,0,0,0}
};	

struct Namen
{
	char b[5];
};


const Namen kurz[BUILDING_TYPES]=
{
	{"Mari"},
	{"Ghos"},
	{"Vult"},
	{"Goli"},
	{"Tank"},
	{"SCV "},
	{"FBat"},
	{"Medi"},
	{"Wrai"},
	{"ScVe"},
	{"Drop"},
	{"BatC"},
	{"Valk"},

	{"ComC"},
	{"Depo"},
	{"Refi"},
	{"Barr"},
	{"Acad"},
	{"Fact"},
	{"Star"},
	{"Scie"},
	{"Engi"},
	{"Armo"},
	{"Miss"},
	{"Bunk"},

	{"Coms"},
	{"NuSi"},
	{"CoTo"},
	{"CoOp"},
	{"PhLa"},
	{"MaSh"},

	{"Stim"},
	{"Lock"},
	{"EMPS"},
	{"Mine"},
	{"Sieg"},
	{"Irra"},
	{"Yama"},
	{"Cloa"},
	{"Pers"},
	{"Rest"},
	{"Optc"},

	{"U238"},
	{"IonT"},
	{"Tita"},
	{"Ocul"},
	{"Moeb"},
	{"Apol"},
	{"Colo"},
	{"Cadu"},
	{"Char"},

	{"InAr"},
	{"InWe"},
	{"VeAr"},
	{"VeWe"},
	{"ShAr"},
	{"ShWe"},

	{"NuWa"},

	{">gas"},
	{">min"}

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

	unsigned short mins,gas,IP,min,n;
	unsigned char scvmins,scvgas,scvbuilding,length,BuildingRunning;
	short Supply;

	unsigned char program[MAX_LENGTH];
	unsigned short timep[MAX_LENGTH];
	
	struct Building
	{
		unsigned short RB; // Remaining Buildtime
		unsigned char type; // Type of Building
	} building[MAX_BUILDINGS];

	unsigned char nr,ok;

	unsigned short harvested_gas,harvested_mins;
	unsigned short fitness,timer;



	void Produce(unsigned char who)
	{
		if((who>=INFANTRY_ARMOR)&&(who<=SHIP_WEAPONS))
		{
			building[nr].RB=stats[who].BT+force[who]*32;
			switch(who)
			{
				case INFANTRY_ARMOR:
				case INFANTRY_WEAPONS:
				case VEHICLE_PLATING:
				case VEHICLE_WEAPONS:
				case SHIP_PLATING:mins-=stats[who].mins+force[who]*75;gas-=stats[who].gas+force[who]*75;break;
				case SHIP_WEAPONS:mins-=stats[who].mins+force[who]*50;gas-=stats[who].gas+force[who]*50;break;
				default:break;
			}
		}	
		else
		{
			building[nr].RB=stats[who].BT+((who>=COMMAND_CENTER)&&(who<=BUNKER))*3; // 3 Spielsekunden um zum Bauplatz zu fahren 
			mins-=stats[who].mins;
		    gas-=stats[who].gas;
		}
		building[nr].type=who;
		Supply-=stats[who].supply;

		if((who<=BUNKER)&&(who>=COMMAND_CENTER))
		{
			if(scvmins>0)
				scvmins--;
			else if(scvgas>0)
				scvgas--;
			scvbuilding++;
		}
		ok=1;
	}

	
	
	void Build(unsigned char what)
	{
		unsigned char m;
		
			if((what==ONE_MINERAL_SCV_TO_GAS)&&(force[REFINERY]>0)&&(scvmins>0))
			{
				ok=1;
				scvmins--;
				scvgas++;
			}
			else
			if((what==ONE_GAS_SCV_TO_MINERAL)&&(scvgas>0))
			{
				ok=1;
				scvgas--;
				scvmins++;
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
			( mins>=stats[what].mins+((what>=INFANTRY_ARMOR)&&(what<=SHIP_PLATING))*force[what]*75+(what==SHIP_WEAPONS)*force[what]*50) &&
			( gas>=stats[what].gas+((what>=INFANTRY_ARMOR)&&(what<=SHIP_PLATING))*force[what]*75+(what==SHIP_WEAPONS)*force[what]*50) &&
			(nr<255) && 
			(scvmins+scvgas>=1*((what<=BUNKER)&&(what>=COMMAND_CENTER)))
		  )

		{
			switch(what)
			{
				case MARINE:if((force[BARRACKS]>0)&&(availible[BARRACKS]>0)) 
							{
								Produce(what);
								availible[BARRACKS]--;
							};break;
				case GHOST:if((force[BARRACKS]>0)&&(force[ACADEMY]>0)&&(force[SCIENCE_FACILITY]>0)&&(force[COVERT_OPS]>0)&&(availible[BARRACKS]>0))
							{
								Produce(what);
								availible[BARRACKS]--;
							};break;
				case VULTURE:if((force[FACTORY]>0)&&(availible[FACTORY]>0)) 
							{
								Produce(what);
								availible[FACTORY]--;
							};break;
				case GOLIATH:if((force[FACTORY]>0)&&(force[ARMORY]>0)&&(availible[FACTORY]>0)) 
							{
								Produce(what);
								availible[FACTORY]--;
							};break;
				case SIEGE_TANK:if((force[FACTORY]>0)&&(force[MACHINE_SHOP]>0)&&(availible[FACTORY]>0)&&(availible[MACHINE_SHOP]>0)) 
							{
								Produce(what);
								availible[FACTORY]--;
								availible[MACHINE_SHOP]--;
							};break;
				case SCV:if((force[COMMAND_CENTER]>0)&&(availible[COMMAND_CENTER]>0)) 
							{
								Produce(what);
								availible[COMMAND_CENTER]--;
							};break;
				case FIREBAT:
				case MEDIC:if((force[BARRACKS]>0)&&(force[ACADEMY]>0)&&(availible[BARRACKS]>0)) 
							{
								Produce(what);
								availible[BARRACKS]--;
							};break;
				case WRAITH:if((force[STARPORT]>0)&&(availible[STARPORT]>0)) 
							{
								Produce(what);
								availible[STARPORT]--;
							};break;
				case SCIENCE_VESSEL:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(force[SCIENCE_FACILITY]>0)&&(availible[CONTROL_TOWER]>0)&&(availible[STARPORT]>0))
							{
								Produce(what);
								availible[STARPORT]--;
								availible[CONTROL_TOWER]--;
							};break;
				case DROPSHIP:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(availible[CONTROL_TOWER]>0)&&(availible[STARPORT]>0))
							{
								Produce(what);
								availible[STARPORT]--;
								availible[CONTROL_TOWER]--;
							};break;
				case BATTLE_CRUISER:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(force[SCIENCE_FACILITY]>0)&&(force[PHYSICS_LAB]>0)&&(availible[CONTROL_TOWER]>0)&&(availible[STARPORT]>0))
							{
								Produce(what);
								availible[STARPORT]--;
								availible[CONTROL_TOWER]--;
							};break;
				case VALKYRIE:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(force[ARMORY]>0)&&(availible[CONTROL_TOWER]>0)&&(availible[STARPORT]>0))
							{
								Produce(what);
								availible[STARPORT]--;
								availible[CONTROL_TOWER]--;
							};break;
				case COMMAND_CENTER:
				case SUPPLY_DEPOT:Produce(what);break;
				case REFINERY:if(Vespene_Av>0) { Vespene_Av--;Produce(what);};break;
				case BARRACKS:Produce(what);break;
				case ACADEMY:
				case FACTORY:if(force[BARRACKS]>0) Produce(what);break;
				case STARPORT:if(force[FACTORY]>0) Produce(what);break;
				case SCIENCE_FACILITY:if(force[FACTORY]>0) Produce(what);break;
				case ENGINEERING_BAY:Produce(what);break;
				case ARMORY:if(force[FACTORY]>0) Produce(what);break;
				case MISSILE_TURRET:if(force[ENGINEERING_BAY]>0) Produce(what);break;
				case BUNKER:if(force[BARRACKS]>0) Produce(what);break;

				case COMSAT_STATION:if((force[COMMAND_CENTER]>force[COMSAT_STATION]+force[NUCLEAR_SILO])&&(availible[COMMAND_CENTER]>0)) Produce(what);break;
				case NUCLEAR_SILO:if((force[COMMAND_CENTER]>force[COMSAT_STATION]+force[NUCLEAR_SILO])&&(availible[COMMAND_CENTER]>0)&&(force[SCIENCE_FACILITY]>0)&&(force[COVERT_OPS]>0)) Produce(what);break;
				case CONTROL_TOWER:if((force[STARPORT]>force[CONTROL_TOWER])&&(availible[STARPORT]>0)) Produce(what);break;
				case COVERT_OPS:
				case PHYSICS_LAB:if((force[SCIENCE_FACILITY]>force[COVERT_OPS]+force[PHYSICS_LAB])&&(availible[SCIENCE_FACILITY]>0)) Produce(what);break;
				case MACHINE_SHOP:if((force[FACTORY]>force[MACHINE_SHOP])&&(availible[FACTORY]>0)) Produce(what);break;

				
				
				case CHARON_BOOSTER:
				case SPIDER_MINES:
				case TANK_SIEGE_MODE:
				case ION_THRUSTERS:if(force[MACHINE_SHOP]>0) Produce(what);break; //da stimmt was net :\ ... 

				case TITAN_REACTOR:
				case EMP_SHOCKWAVE:
				case IRRADIATE:if((force[SCIENCE_FACILITY]>0)&&(availible[SCIENCE_FACILITY]>0)) Produce(what);break;
				
				case OCULAR_IMPLANTS:
				case LOCKDOWN:
				case MOEBIUS_REACTOR:
				case PERSONNEL_CLOAKING:if((force[COVERT_OPS]>0)&&(availible[COVERT_OPS]>0)) Produce(what);break;
				
				case CADUCEUS_REACTOR:
				case U238_SHELLS:
				case STIM_PACKS:
				case RESTORATION:
				case OPTICAL_FLARE:if((force[ACADEMY]>0)&&(availible[ACADEMY]>0)) Produce(what);break;

				case COLOSSUS_REACTOR:
				case YAMATO_GUN:if(force[PHYSICS_LAB]>0) Produce(what);break;

				case APOLLO_REACTOR:
				case CLOAKING_FIELD:if(force[CONTROL_TOWER]>0) Produce(what);break;

				case INFANTRY_ARMOR:
				case INFANTRY_WEAPONS:if((force[ENGINEERING_BAY]>0)&&(availible[ENGINEERING_BAY]>0)) 
									   {
										   if((force[what]==0)||( (force[what]>0)&&(force[SCIENCE_FACILITY]>0)))
											   Produce(what);
									   };break;

				case VEHICLE_PLATING:
				case VEHICLE_WEAPONS:
				case SHIP_PLATING:
				case SHIP_WEAPONS:if((force[ARMORY]>0)&&(availible[ARMORY]>0)) 
								  {
										   if((force[what]==0)||( (force[what]>0)&&(force[SCIENCE_FACILITY]>0)))
											   Produce(what);
								  };break;
				case NUCLEAR_WARHEAD:if(force[NUCLEAR_SILO]>0) Produce(what);
									 
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

			if(scvmins<56)
			{
				mins+=mining[scvmins]; //~~~~~~~double wegmachen
				harvested_mins+=mining[scvmins];
			}
			else 
			{
				mins+=mining[56];
				harvested_mins+=mining[56];
			}
			if(scvgas<5)
			{
				gas+=gasing[scvgas];
				harvested_gas+=gasing[scvgas];
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
						if((building[j].type>=COMMAND_CENTER)&&(building[j].type<=BUNKER)) 
						{
							scvmins++;
							scvbuilding--;
						}

						switch(building[j].type)
						{
							case SCV:scvmins++;availible[COMMAND_CENTER]++;break;
							case SUPPLY_DEPOT:Supply+=8;break;
							case COMMAND_CENTER:Supply+=10;break;
							case REFINERY:break;
							case MARINE:
							case FIREBAT:
							case MEDIC:
							case GHOST:availible[BARRACKS]++;break;
							
							case SIEGE_TANK:availible[MACHINE_SHOP]++;
							case VULTURE:
							case GOLIATH:availible[FACTORY]++;break;

							case SCIENCE_VESSEL:
							case BATTLE_CRUISER:
							case DROPSHIP:
							case VALKYRIE:availible[CONTROL_TOWER]++;
							case WRAITH:availible[STARPORT]++;break;

			

				case INFANTRY_ARMOR:
				case INFANTRY_WEAPONS:availible[ENGINEERING_BAY]++;break;

				case VEHICLE_PLATING:
				case VEHICLE_WEAPONS:
				case SHIP_PLATING:
				case SHIP_WEAPONS:availible[ARMORY]++;break;


					//UPGRADES SIND FALSCH, AVAILIBLE CHECKEN!
							default:break;
						}
						ready=1;
						for(i=0;i<BUILDING_TYPES;i++)
							ready&=((goal[i].what<=force[i])&&((goal[i].time>timer)||(goal[i].time==0)));
					}
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
		}
			

	// Ziele unterschiedlich bewerten!
			// sqrt nochmal ueberlegen mmmh :| programm muss halt schritt fuer schritt belohnt werden ^^ vielleicht je nach techstufe, also z.B. pool: 1, lair: 2, spire: 3~~~~

		if(Goal_Harvested_Gas>harvested_gas)
			fitness+=(harvested_gas*100)/Goal_Harvested_Gas;
		else fitness+=100;

		if(Goal_Harvested_Mins>harvested_mins)
			fitness+=(harvested_mins*100)/Goal_Harvested_Mins;
		else fitness+=100;

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

	fitness=0;
	mins=50;
	gas=0;
	force[COMMAND_CENTER]=1;
	availible[COMMAND_CENTER]=1;
	force[SCV]=4;
	Supply=6;
	scvmins=4;
	scvgas=0;
	scvbuilding=0;
	IP=0;
}

	void Restart()
	{
		for(i=0;i<MAX_LENGTH;i++)
			program[i]=rand()%Max_Build_Types;
		timer=Max_Time;
		IP=0;
		length=MAX_LENGTH;
		afit=0;
	}
};
