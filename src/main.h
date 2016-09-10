#ifndef MAIN_H
#define MAIN_H

#define MAX_LENGTH 96
#define RUNNINGS 5
#define MAX_PLAYER 100
#define LARVA_MAX 200
#define MAX_BUILDINGS 12 // How many buildings can you built simultaneously?
#define MAX_GOALS 60
#define DATA_SET_SIZE 15

struct GOAL
{
	unsigned short time,what;
};

//some global variables

extern unsigned char Ziel[60],Build_Av[60],Build_Bv[60]; 
extern unsigned char Vespene_Av,Max_Build_Types,race,building_types;
extern unsigned short total_goals;
extern unsigned char num,Vespene_Extractors;
extern GOAL goal[MAX_GOALS];
extern double mining[45],gasing[5];

const double gasing_z[5]=
{
0,
1.12,
2.03,
3.2,
3.52
};

const double mining_z[45]=
{
0,
0.83,1.65,2.44,3.14,3.85,4.5,5.2,5.83,
6.45,7.01,7.65,8.19,8.53,8.79,9.11,9.38,
9.95,10.41,10.7,10.92,11.21,11.43,12,12.53, // [Claw,4/4/03] changed 11.49 -> 12
12.66,12.76,12.83,12.88,12.92,12.94,12.96,12.97,
12.98,12.98,12.99,12.99,12.99,12.99,13,13,
13,13,13,13
};

const double gasing_p[5]=
{
0,
1.17,
2.19,
3.36,
3.52	
};

const double mining_p[45]=
{
0,
0.8,1.59,2.44,3.14,3.84,4.47,5.2,5.84,
6.51,7.06,7.67,8.17,8.47,8.72,9.02,9.27,
10,10.5,10.85,11.11,11.44,11.73,12.23,12.63,
12.72,12.82,12.87,12.91,12.93,12.95,12.97,12.98,
12.99,12.99,12.99,12.99,12.99,13,13,13,
13,13,13,13
};

const double gasing_t[5]=
{
0,
1.23,
2.35,
3.52,
3.52
};

const double mining_t[45]={
0,
0.72,1.43,2.19,2.95,3.69,4.42,5.06,5.7, //1-8
6.26,6.82,7.25,7.67,8.07,8.47,8.78,9.09, //9-16
9.43,9.77,10.12,10.46,10.73,11.01,11.42,11.83, //17-24
12.03,12.23,12.33,12.43,12.51,12.59,12.66,12.74, //25-32
12.77,12.79,12.81,12.82,12.83,12.83,12.84,12.84, //33-40
12.84,12.84,12.85,12.85 //41-44
};



struct Stats
{
	char name[21];
	unsigned short BT;
	unsigned short mins,gas;
	unsigned char supply;
	unsigned short type; // 0: nothing, 1: unit, 2: building (primarily for zerg!), 3: Research, 4: Upgrade
	unsigned char tmp; //fuer Upgrades erstmal nur... 50, 75, 100
};

const Stats stats[3][60]=
{
	{
	{"              Marine", 24, 50,  0,1,1},
	{"               Ghost", 50, 25, 75,1,1},
	{"             Vulture", 30, 75,  0,2,1},
	{"             Goliath", 40,100, 50,2,1},
	{"          Siege Tank", 50,150,100,2,1},
	{"                 SCV", 20, 50,  0,1,1}, // 0.0 Time to Enemy da es im Lager bleibt!
	{"             Firebat", 24, 50, 25,1,1},
	{"               Medic", 30, 50, 25,1,1},
	{"              Wraith", 60,150,100,2,1},
	{"      Science Vessel", 80,100,225,2,1},
	{"            Dropship", 50,100,100,2,1},
	{"      Battle Cruiser",133,400,300,6,1},
	{"            Valkyrie", 50,250,125,3,1},
	{"      Command Center",120,400,  0,2,0},
	{"        Supply Depot", 40,100,  0,0,2},
	{"            Refinery", 40,100,  0,0,2},
	{"            Barracks", 80,150,  0,0,2},
	{"             Academy", 80,150,  0,0,2},
	{"             Factory", 80,200,100,0,2},
	{"            Starport", 70,150,100,0,2},
	{"    Science Facility", 60,100,150,0,2},
	{"     Engineering Bay", 60,125,  0,0,2},
	{"              Armory", 80,100, 50,0,2},
	{"      Missile Turret", 30, 75,  0,0,2},
	{"              Bunker", 30,100,  0,0,2},
	{"      Comsat Station", 40, 50, 50,0,0},
	{"        Nuclear Silo", 40,100,100,0,0},
	{"       Control Tower", 80, 50, 50,0,0},
	{"          Covert Ops", 40, 50, 50,0,0},
	{"         Physics Lab", 40, 50, 50,0,0},
	{"        Machine Shop", 40, 50, 50,0,0},
	{"          Stim Packs", 80,100,100,0,3},
	{"            Lockdown",100,200,200,0,3},
	{"       EMP Shockwave",120,200,200,0,3},
	{"        Spider Mines", 80,100,100,0,3},
	{"          Siege Mode", 80,150,150,0,3},
	{"           Irradiate", 80,200,200,0,3},
	{"          Yamato Gun",120,100,100,0,3},
	{"      Cloaking Field",100,150,150,0,3},
	{"  Personnel Cloaking", 80,100,100,0,3},
	{"         Restoration", 80,100,100,0,3},
	{"       Optical Flare",120,100,100,0,3},
	{"        U-238 Shells",100,150,150,0,3},
	{"       Ion Thrusters",100,100,100,0,3},
	{"       Titan Reactor",166,150,150,0,3},
	{"     Ocular Implants",166,100,100,0,3},
	{"     Moebius Reactor",166,200,200,0,3},
	{"      Apollo Reactor",166,200,200,0,3},
	{"    Colossus Reactor",166,150,150,0,3},
	{"    Caduceus Reactor",166,150,150,0,3},
	{"      Charon Booster",133,100,100,0,3},

	{"      Infantry Armor",266,100,100,0,4,75},
	{"    Infantry Weapons",266,100,100,0,4,75},
	{"     Vehicle Plating",266,100,100,0,4,75},
	{"     Vehicle Weapons",266,100,100,0,4,75},
	{"        Ship Plating",266,150,150,0,4,75},
	{"        Ship Weapons",266,100,100,0,4,50},
	{"     Nuclear Warhead",100,200,200,8,0},

	{"  Mineral SCV to Gas",  0,  0,  0,0,0},
	{"  Gas SCV to Mineral",  0,  0,  0,0,0}
},
	
	{
	{"        Dark Templar", 50,125,100,2,1},
	{"         Dark Archon", 20,  0,  0,0,1},
	{"               Probe", 20, 50,  0,1,1},
	{"              Zealot", 40,100,  0,2,1},
	{"             Dragoon", 50,125, 50,2,1},
	{"        High Templar", 50, 50,150,2,1},
	{"              Archon", 20,  0,  0,0,1},
	{"              Reaver", 70,200,100,4,1},
	{"             Corsair", 40,150,100,2,1},
	{"             Shuttle", 60,200,  0,2,1},
	{"               Scout", 80,275,125,3,1},
	{"             Arbiter",160,100,350,4,1},
	{"             Carrier",140,350,250,6,1},
	{"            Observer", 40, 25, 75,1,1},
	{"               Nexus",120,400,  0,0,2},
	{"   Robotics Facility", 80,200,200,0,2},
	{"               Pylon", 30,100,  0,0,2},
	{"         Assimilator", 40,100,  0,0,2},
	{"         Observatory", 30, 50,100,0,2},
	{"             Gateway", 60,150,  0,0,2},
	{"       Photon Cannon", 50,150,  0,0,2},
	{"    Cybernetics Core", 60,200,  0,0,2},
	{"     Citadel Of Adun", 60,150,100,0,2},
	{"    Templar Archives", 60,150,200,0,2},
	{"               Forge", 40,150,  0,0,2},
	{"            Stargate", 70,150,150,0,2},
	{"        Fleet Beacon", 60,300,200,0,2},
	{"    Arbiter Tribunal", 60,200,150,0,2},
	{"Robotics Support Bay", 30,150,100,0,2},
	{"      Shield Battery", 30,100,  0,0,2},
	{"       Psionic Storm",120,200,200,0,3},
	{"       Hallucination", 80,150,150,0,3},
	{"              Recall",120,150,150,0,3},
	{"        Stasis Field",100,150,150,0,3},
	{"      Disruption Web", 80,200,200,0,3},
	{"        Mind Control",120,200,200,0,3},
	{"           Maelstrom",100,100,100,0,3},
	{"  Singularity Charge",166,150,150,0,3},
	{"    Leg Enhancements",133,150,150,0,3},
	{"       Scarab Damage",166,200,200,0,3},
	{"     Reaver Capacity",166,200,200,0,3},
	{"      Gravitic Drive",166,200,200,0,3},
	{"        Sensor Array",133,150,150,0,3},
	{"   Gravitic Boosters",133,150,150,0,3},
	{"    Khaydarin Amulet",166,150,150,0,3},
	{"       Apial Sensors",166,100,100,0,3},
	{"  Gravitic Thrusters",166,200,200,0,3},
	{"    Carrier Capacity",100,100,100,0,3},
	{"      Khaydarin Core",166,150,150,0,3},
	{"         Argus Jewel",166,100,100,0,3},
	{"      Argus Talisman",166,150,150,0,3},
	{"               Armor",266,100,100,0,4,75},
	{"             Plating",266,150,150,0,4,75},
	{"      Ground Weapons",266,100,100,0,4,50},
	{"         Air Weapons",266,100,100,0,4,75},
	{"      Plasma Shields",266,200,200,0,4,100},
	{"Mineral Probe To Gas",  0,  0,  0,0,0},
	{"Gas Probe To Mineral",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0}
	},
	
	{
	{"            Zergling", 28, 50,  0,1,1},
	{"           Hydralisk", 28, 75, 25,1,1},
	{"           Ultralisk", 60,200,200,6,1},
	{"               Drone", 23, 50,  0,1,1},
	{"             Defiler", 50, 50,150,2,1},
	{"              Lurker", 40, 50,100,2,0},
	{"            Overlord", 40,100,  0,0,1},
	{"            Mutalisk", 40,100,100,2,1},
	{"            Guardien", 40, 50,100,0,0},
	{"               Queen", 50,100,100,2,1},
	{"             Scourge", 30, 25, 75,1,1},
	{"            Devourer", 40,100, 50,0,0},

	{"            Hatchery",120,300,  0,0,2},
	{"                Lair",100,150,100,0,0},
	{"                Hive",120,200,150,0,0},
	{"         Nydus Canal", 40,150,  0,0,2},
	{"       Hydralisk den", 40,100, 50,0,2},
	{"       Defiler mound", 60,100,100,0,2},
	{"       Greater Spire",120,100,150,0,0},
	{"        Queen's Nest", 60,150,100,0,2},
	{"   Evolution Chamber", 40, 75,  0,0,2},
	{"    Ultralisk Cavern", 80,150,200,0,2},
	{"               Spire",120,200,150,0,2},
	{"       Spawning Pool", 80,200,  0,0,2},
	{"        Creep Colony", 20, 75,  0,0,2},
	{"        Spore Colony", 20, 50,  0,0,0},
	{"       Sunken Colony", 20, 50,  0,0,0},
	{"           Extractor", 40, 50,  0,0,2},//27
 
	{"        Ventral Sacs",160,200,200,0,3},
	{"            Antennae",133,150,150,0,3},
	{"Pneumatized Carapace",133,150,150,0,3},
	{"     Metabolic Boost",100,100,100,0,3},
	{"      Adrenal Glands",100,200,200,0,3},
	{"   Muscular Augments",100,150,150,0,3},
	{"      Grooved Spines",100,150,150,0,3},
	{"      Gamete Meiosis",166,150,150,0,3},
	{"   Metasynaptic node",166,150,150,0,3},
	{"   Chitinous Plating",133,150,150,0,3},
	{"  Anabolic Synthesis",133,200,200,0,3},

	{"           Burrowing", 80,100,100,0,3},
	{"     Spawn Broodling", 80,100,100,0,3},
	{"              Plague",100,200,200,0,3},
	{"             Consume",100,100,100,0,3},
	{"             Ensnare", 80,100,100,0,3},
	{"       Lurker Aspect",120,200,200,0,3},

	{"            Carapace",266,150,150,0,4,75},
	{"      Flyer Carapace",266,150,150,0,4,75},
	{"       Melee Attacks",266,100,100,0,4,50},
	{"     Missile Attacks",266,100,100,0,4,50},
	{"       Flyer Attacks",266,100,100,0,4,75},
	{"Mineral Drone to Gas",  0,  0,  0,0,0},
	{"Gas Drone to Mineral",  0,  0,  0,0,0},
	{"   Break up Building",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0},

	{"                NULL",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0},
	{"                NULL",  0,  0,  0,0,0}
	}
};








#endif


