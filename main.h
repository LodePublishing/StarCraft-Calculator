#define MAX_LENGTH 50
#define RUNNINGS 10
#define MAX_PLAYER 128

#define MAX_BUILDINGS 10 // How many buildings can you built simultaneously?
#define BUILDING_TYPES 58

#define DARK_TEMPLAR 0
#define DARK_ARCHON 1
#define PROBE 2
#define ZEALOT 3
#define DRAGOON 4
#define HIGH_TEMPLAR 5
#define ARCHON 6
#define REAVER 7
//scarab? ^^ ne... nur auf raeuber draufschlagen
#define CORSAIR 8
#define SHUTTLE 9
#define SCOUT 10
#define ARBITER 11
#define CARRIER 12
//interceptor? ^^ ne... nur auf Carrier draufschlagen mmmh... naja, mal guggn
#define OBSERVER 13

#define NEXUS 14
#define ROBOTICS_FACILITY 15
#define PYLON 16
#define ASSIMILATOR 17
#define OBSERVATORY 18
#define GATEWAY 19
#define PHOTON_CANNON 20
#define CYBERNETICS_CORE 21
#define CITADEL_OF_ADUN 22
#define TEMPLAR_ARCHIVES 23
#define FORGE 24
#define STARGATE 25
#define FLEET_BEACON 26
#define ARBITER_TRIBUNAL 27
#define ROBOTICS_SUPPORT_BAY 28
#define SHIELD_BATTERY 29


#define PSIONIC_STORM 30
#define HALLUCINATION 31
#define RECALL 32
#define STASIS_FIELD 33
#define DISRUPTION_WEB 34
#define MIND_CONTROL 35
#define MAELSTROM 36

#define SINGULARITY_CHARGE 37
#define LEG_ENHANCEMENTS 38
#define SCARAB_DAMAGE 39
#define REAVER_CAPACITY 40
#define GRAVITIC_DRIVE 41
#define SENSOR_ARRAY 42
#define GRAVITIC_BOOSTERS 43
#define KHAYDARIN_AMULET 44
#define APIAL_SENSORS 45
#define GRAVITIC_THRUSTERS 46
#define CARRIER_CAPACITY 47
#define KHAYDARIN_CORE 48
#define ARGUS_JEWEL 49
#define ARGUS_TALISMAN 50

#define ARMOR 51
#define PLATING 52
#define GROUND_WEAPONS 53
#define AIR_WEAPONS 54
#define PLASMA_SHIELDS 55

#define ONE_MINERAL_PROBE_TO_GAS 56
#define ONE_GAS_PROBE_TO_MINERAL 57

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
	{"Dark Templar",50,125,100,2},
	{"Dark Archon",20,0,0,0},
	{"Probe",20,50,0,1},
	{"Zealot",40,100,0,2},
	{"Dragoon",50,125,50,2},
	{"High Templar",50,50,150,2},
	{"Archon",20,0,0,0},
	{"Reaver",70,200,100,4},
	{"Corsair",40,150,100,2},
	{"Shuttle",60,200,0,2},
	{"Scout",80,275,125,3},
	{"Arbiter",160,100,350,4},
	{"Carrier",140,350,250,6},
	{"Observer",40,25,75,1},
	{"Nexus",120,400,0,0},
	{"Robotics Facility",80,200,200,0},
	{"Pylon",30,100,0,0},
	{"Assimilator",40,100,0,0},
	{"Observatory",30,50,100,0},
	{"Gateway",60,150,0,0},
	{"Photon Cannon",50,150,0,0},
	{"Cybernetics Core",60,200,0,0},
	{"Citadel Of Adun",60,150,100,0},
	{"Templar Archives",60,150,200,0},
	{"Forge",40,150,0,0},
	{"Stargate",70,150,150,0},
	{"Fleet Beacon",60,300,200,0},
	{"Arbiter Tribunal",60,200,150,0},
	{"Robotics Support Bay",30,150,100,0},
	{"Shield Battery",30,100,0,0},
	{"Psionic Storm",120,200,200,0},
	{"Hallucination",80,150,150,0},
	{"Recall",120,150,150,0},
	{"Stasis Field",100,150,150,0},
	{"Disruption Web",80,200,200,0},
	{"Mind Control",120,200,200,0},
	{"Maelstrom",100,100,100,0},
	{"Singularity Charge",166,150,150,0},
	{"Leg Enhancements",133,150,150,0},
	{"Scarab Damage",166,200,200,0},
	{"Reaver Capacity",166,200,200,0},
	{"Gravitic Drive",166,200,200,0},
	{"Sensor Array",133,150,150,0},
	{"Gravitic Boosters",133,150,150,0},
	{"Khaydarin Amulet",166,150,150,0},
	{"Apial Sensors",166,100,100,0},
	{"Gravitic Thrusters",166,200,200,0},
	{"Carrier Capacity",100,100,100,0},
	{"Khaydarin Core",166,150,150,0},
	{"Argus Jewel",166,100,100,0},
	{"Argus Talisman",166,150,150,0},
	{"Armor",266,100,100,0},
	{"Plating",266,150,150,0},
	{"Ground Weapons",266,100,100,0},
	{"Air Weapons",266,100,100,0},
	{"Plasma Shields",266,200,200,0},
	{"One Mineral Probe To Gas",0,0,0,0},
	{"One Gas Probe To Mineral",0,0,0,0}
};	

struct Namen
{
	char b[5];
};


const Namen kurz[BUILDING_TYPES]=
{
	{"Dark"},
	{"Dark"},
	{"Prob"},
	{"Zeal"},
	{"Drag"},
	{"High"},
	{"Arch"},
	{"Reav"},
	{"Cors"},
	{"Shut"},
	{"Scou"},
	{"Arbi"},
	{"Carr"},
	{"Obse"},
	{"Nexu"},
	{"Robo"},
	{"Pylo"},
	{"Assi"},
	{"Obse"},
	{"Gate"},
	{"Phot"},
	{"Cybe"},
	{"Cita"},
	{"Temp"},
	{"Forg"},
	{"Star"},
	{"Flee"},
	{"Arbi"},
	{"Robo"},
	{"Shie"},
	{"Psio"},
	{"Hall"},
	{"Reca"},
	{"Stas"},
	{"Disr"},
	{"Mind"},
	{"Mael"},
	{"Sing"},
	{"Leg_"},
	{"Scar"},
	{"Reav"},
	{"Grav"},
	{"Sens"},
	{"Grav"},
	{"Khay"},
	{"Apia"},
	{"Grav"},
	{"Carr"},
	{"Khay"},
	{"Argu"},
	{"Argu"},
	{"Armo"},
	{"Plat"},
	{"Grou"},
	{"AirW"},
	{"Plas"},
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
	unsigned char probemins,probegas,length,BuildingRunning;
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
		if((who>=ARMOR)&&(who<=PLASMA_SHIELDS))
		{
			building[nr].RB=stats[who].BT+force[who]*32;
			switch(who)
			{
				case PLATING:
				case ARMOR:
				case AIR_WEAPONS:mins-=stats[who].mins+force[who]*75;gas-=stats[who].gas+force[who]*75;break;
				case GROUND_WEAPONS:mins-=stats[who].mins+force[who]*50;gas-=stats[who].gas+force[who]*50;break;
				case PLASMA_SHIELDS:mins-=stats[who].mins+force[who]*100;gas-=stats[who].gas+force[who]*100;break;
				default:break;
			}
		}	
		else
		{
			building[nr].RB=stats[who].BT+((who>=NEXUS)&&(who<=SHIELD_BATTERY))*5; // 3 Spielsekunden um zum Bauplatz zu fahren 
//			if(who==ZERGLING)
//			{
//				if(force[METABOLIC_BOOST]==1)
//					building[nr].RB+=30;
//				if(force[METABOLIC_BOOST]==1)
//					building[nr].RB+=50;
//			}
			mins-=stats[who].mins;
		    gas-=stats[who].gas;
		}
		building[nr].type=who;
		Supply-=stats[who].supply;

		if((who<=SHIELD_BATTERY)&&(who>=NEXUS))
		{
			if(probemins>0)
				probemins--;
			else if(probegas>0)
				probegas--;
		}
		ok=1;
	}

	
	
	void Build(unsigned char what)
	{
		unsigned char m;

		if((what>=NEXUS)&&(what<=SHIELD_BATTERY)&&(what!=PYLON)&&(force[PYLON]==0))
			return;
	
			if((what==ONE_MINERAL_PROBE_TO_GAS)&&(force[ASSIMILATOR]>0)&&(probemins>0))
			{
				ok=1;
				probemins--;
				probegas++;
			}
			else
			if((what==ONE_GAS_PROBE_TO_MINERAL)&&(probegas>0))
			{
				ok=1;
				probegas--;
				probemins++;
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
			( mins>=stats[what].mins+((what==ARMOR)||(what==PLATING)||(what==AIR_WEAPONS))*force[what]*75+(what==GROUND_WEAPONS)*force[what]*50)+(what==PLASMA_SHIELDS)*force[what]*100 &&
			(  gas>=stats[what].gas +((what==ARMOR)||(what==PLATING)||(what==AIR_WEAPONS))*force[what]*75+(what==GROUND_WEAPONS)*force[what]*50)+(what==PLASMA_SHIELDS)*force[what]*100 &&
			(nr<255) && 
			(probemins+probegas>=1*((what<=SHIELD_BATTERY)&&(what>=NEXUS)))
		  )

		{
			switch(what)
			{
				case DARK_TEMPLAR:
				case HIGH_TEMPLAR:if((force[GATEWAY]>0)&&(availible[GATEWAY]>0)&&(force[TEMPLAR_ARCHIVES]>0)) 
							{
								Produce(what);
								availible[GATEWAY]--;
							};break;
				case DRAGOON:if((force[GATEWAY]>0)&&(force[CYBERNETICS_CORE]>0)&&(availible[GATEWAY]>0))
							{
								Produce(what);
								availible[GATEWAY]--;
							};break;
				case ZEALOT:if((force[GATEWAY]>0)&&(availible[GATEWAY]>0)) 
							{
								Produce(what);
								availible[GATEWAY]--;
							};break;
				case REAVER:if((force[ROBOTICS_SUPPORT_BAY]>0)&&(force[ROBOTICS_FACILITY]>0)&&(availible[ROBOTICS_FACILITY]>0)) 
							{
								Produce(what);
								availible[ROBOTICS_FACILITY]--;
							};break;
				case SHUTTLE:if((force[ROBOTICS_FACILITY]>0)&&(availible[ROBOTICS_FACILITY]>0)) 
							{
								Produce(what);
								availible[ROBOTICS_FACILITY]--;
							};break;
				case PROBE:if((force[NEXUS]>0)&&(availible[NEXUS]>0)) 
							{
								Produce(what);
								availible[NEXUS]--;
							};break;
				case OBSERVER:
							if((force[ROBOTICS_FACILITY]>0)&&(force[OBSERVATORY]>0)&&(availible[ROBOTICS_FACILITY]>0)) 
							{
								Produce(what);
								availible[ROBOTICS_FACILITY]--;
							};break;
				case SCOUT:
				case CORSAIR:if((force[STARGATE]>0)&&(availible[STARGATE]>0)) 
							{
								Produce(what);
								availible[STARGATE]--;
							};break;
				case ARBITER:if((force[STARGATE]>0)&&(availible[STARGATE]>0)&&(force[TEMPLAR_ARCHIVES]>0)&&(force[ARBITER_TRIBUNAL]>0)) 
							{
								Produce(what);
								availible[STARGATE]--;
							};break;
				case CARRIER:if((force[STARGATE]>0)&&(availible[STARGATE]>0)&&(force[FLEET_BEACON]>0)) 
							{
								Produce(what);
								availible[STARGATE]--;
							};break;
				case ARCHON:if(force[HIGH_TEMPLAR]>1)
							{
								Produce(what);
								force[HIGH_TEMPLAR]-=2;
							};break;
				case DARK_ARCHON:if(force[DARK_TEMPLAR]>1)
							{
								Produce(what);
								force[DARK_TEMPLAR]-=2;
							};break;
				case FORGE:
				case NEXUS:
				case PYLON:Produce(what);break;
				case ASSIMILATOR:if(Vespene_Av>0) { Vespene_Av--;Produce(what);};break;
				case GATEWAY:Produce(what);break;
				case CYBERNETICS_CORE:
				case SHIELD_BATTERY:if(force[GATEWAY]>0) Produce(what);break;
				case ROBOTICS_FACILITY:
				case CITADEL_OF_ADUN:
				case STARGATE:if(force[CYBERNETICS_CORE]>0) Produce(what);break;
				case PHOTON_CANNON:if(force[FORGE]>0) Produce(what);break;
				
				case TEMPLAR_ARCHIVES:if(force[CITADEL_OF_ADUN]>0) Produce(what);break;

				case OBSERVATORY:
				case ROBOTICS_SUPPORT_BAY:if(force[ROBOTICS_FACILITY]>0) Produce(what);break;
				
				case ARBITER_TRIBUNAL:if((force[STARGATE]>0)&&(force[TEMPLAR_ARCHIVES]>0))
										  Produce(what);break;
				case FLEET_BEACON:if(force[STARGATE]>0)
									 Produce(what);break;
				
				case ARGUS_TALISMAN:
				case KHAYDARIN_AMULET:
				case PSIONIC_STORM:
				case HALLUCINATION:
				case MIND_CONTROL:
				case MAELSTROM:if((force[TEMPLAR_ARCHIVES]>0)&&(availible[TEMPLAR_ARCHIVES]>0))
							   {
								   Produce(what);
								   availible[TEMPLAR_ARCHIVES]--;
							   };break;


				case KHAYDARIN_CORE:
				case RECALL:
				case STASIS_FIELD:if((force[ARBITER_TRIBUNAL]>0)&&(availible[ARBITER_TRIBUNAL]>0))
							   {
								   Produce(what);
								   availible[ARBITER_TRIBUNAL]--;
							   };break;

				case ARGUS_JEWEL:
				case APIAL_SENSORS:
				case GRAVITIC_THRUSTERS:				
				case DISRUPTION_WEB:
				case CARRIER_CAPACITY:if((force[FLEET_BEACON]>0)&&(availible[FLEET_BEACON]>0))
							   {
								   Produce(what);
								   availible[FLEET_BEACON]--;
							   };break;

				case LEG_ENHANCEMENTS:if((force[CITADEL_OF_ADUN]>0)&&(availible[CITADEL_OF_ADUN]>0))
							   {
								   Produce(what);
								   availible[CITADEL_OF_ADUN]--;
							   };break;

				

				case GRAVITIC_DRIVE:
				case SCARAB_DAMAGE:
				case REAVER_CAPACITY:if((force[ROBOTICS_SUPPORT_BAY]>0)&&(availible[ROBOTICS_SUPPORT_BAY]>0))
									 {
										 Produce(what);
										 availible[ROBOTICS_SUPPORT_BAY]--;
									 };break;




				case SENSOR_ARRAY:
				case GRAVITIC_BOOSTERS:if((force[OBSERVATORY]>0)&&(availible[OBSERVATORY]>0))
									 {
										 Produce(what);
										 availible[OBSERVATORY]--;
									 };break;



				case SINGULARITY_CHARGE:
				case PLATING:
				case AIR_WEAPONS:if((force[CYBERNETICS_CORE]>0)&&(availible[CYBERNETICS_CORE]>0)&&((force[what]==0)||(force[FLEET_BEACON]>0))) 
								 {
									 Produce(what);
									 availible[CYBERNETICS_CORE]--;
								 };break;

				case ARMOR:
				case GROUND_WEAPONS:
				case PLASMA_SHIELDS:if((force[FORGE]>0)&&(availible[FORGE]>0)) 
									{
										Produce(what);
										availible[FORGE]--;										
									};break;								 
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

			if(probemins<56)
			{
				mins+=mining[probemins]; //~~~~~~~double wegmachen
				harvested_mins+=mining[probemins];
			}
			else 
			{
				mins+=mining[56];
				harvested_mins+=mining[56];
			}
			if(probegas<5)
			{
				gas+=gasing[probegas];
				harvested_gas+=gasing[probegas];
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
							case PROBE:probemins++;availible[NEXUS]++;break;
							case PYLON:Supply+=7;break;
							case NEXUS:Supply+=10;break;
							case ASSIMILATOR:break;
							case ZEALOT:
							case DRAGOON:
							case DARK_TEMPLAR:
							case HIGH_TEMPLAR:availible[GATEWAY]++;break;
							
							case REAVER:
							case SHUTTLE:
							case OBSERVER:availible[ROBOTICS_FACILITY]++;break;

							case SCOUT:
							case CORSAIR:
							case ARBITER:
							case CARRIER:availible[STARGATE]++;

				
							case PLASMA_SHIELDS:
							case ARMOR:
							case GROUND_WEAPONS:availible[FORGE]++;break;

							case PLATING:
							case AIR_WEAPONS:
							case SINGULARITY_CHARGE:availible[CYBERNETICS_CORE]++;break;

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
	force[NEXUS]=1;
	availible[NEXUS]=1;
	force[PROBE]=4;
	Supply=5;
	probemins=4;
	probegas=0;
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
