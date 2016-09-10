//jedem Gebaeude eine Position zuweisen (Entfernung zum Gegner)


#ifndef MAIN_H
#define MAIN_H
#define MAX_LENGTH 100
#define RUNNINGS 5
#define MAX_PLAYER 100
#define LARVA_MAX 200
#define MAX_BUILDINGS 12 // How many buildings can you built simultaneously?
#define MAX_GOALS 60
#define DATA_SET_SIZE 14

using namespace std;


struct Namen
{
	char b[6];
};

const Namen kurz[3][60]=
{
	{
	{"Marin"},{"Ghost"},{"Vultu"},{"Golia"},{"STank"},{"SCV  "},{"FiBat"},{"Medic"},{"Wrait"},
	{"SciVe"},{"Drops"},{"BCrui"},{"Valky"},{"CommC"},{"Depot"},{"Refin"},{"Barra"},{"Acade"},
	{"Facto"},{"StarP"},{"SciLa"},{"Engin"},{"Armor"},{"MisTu"},{"Bunke"},{"ComSa"},{"NucSi"},
	{"ConTo"},{"CovOp"},{"PhyLa"},{"MasSh"},{"StimP"},{"LockD"},{"EMPSw"},{"SMine"},{"SiegM"},
	{"Irrad"},{"YamaG"},{"Cloak"},{"PersC"},{"Resto"},{"OptcF"},{"U238S"},{"IonTh"},{"TitaR"},
	{"OculI"},{"MoebR"},{"ApolR"},{"ColoR"},{"CaduR"},{"CharB"},{"InfAr"},{"InfWe"},{"VehAr"},
	{"VehWe"},{"ShpAr"},{"ShpWe"},{"NucWa"},{">>Gas"},{">>Min"}
	},


	{
	{"DarkT"},{"DarkA"},{"Probe"},{"Zealo"},{"Drago"},{"HighT"},{"Archo"},{"Reave"},{"Corsa"},
	{"Shutt"},{"Scout"},{"Arbit"},{"Carri"},{"Obser"},{"Nexus"},{"RobFa"},{"Pylon"},{"Assim"},
	{"ObsTy"},{"GateW"},{"Photo"},{"Cyber"},{"Citad"},{"TempA"},{"Forge"},{"StarG"},{"Fleet"},
	{"ArbTr"},{"RobBy"},{"Shiel"},{"PsiSt"},{"Hallu"},{"Recal"},{"Stasi"},{"Disru"},{"MindC"},
	{"Maels"},{"Singu"},{"LegEn"},{"ScrbD"},{"ReavC"},{"GraDr"},{"Senso"},{"GraBo"},{"KhaAm"},
	{"ApiaS"},{"GraTh"},{"CarCa"},{"KhaCo"},{"ArgJe"},{"ArgTa"},{"Armor"},{"Plati"},{"Groun"},
	{"AirWe"},{"PShie"},{">>Gas"},{">>Min"},{"NULL!"},{"NULL!"}
	},
		
	{
	{"ZLing"},{"Hydra"},{"Ultra"},{"Drone"},{"Defil"},{"Lurkr"},{"Overl"},{"Mutal"},{"Guard"},
	{"Queen"},{"Scour"},{"Devou"},{"Hatch"},{"Lair "},{"Hive "},{"Nydus"},{"HyDen"},{"DeMou"},
	{"GSpir"},{"QNest"},{"EvoCh"},{"UCave"},{"Spire"},{"SPool"},{"Creep"},{"Spore"},{"Sunkn"},
	{"Extra"},{"VSacs"},{"Anten"},{"Pneum"},{"Boost"},{"Adren"},{"Muscu"},{"Groov"},{"Gamet"},
	{"MNode"},{"Chiti"},{"Anabo"},{"Burro"},{"Spawn"},{"Plagu"},{"Consu"},{"Ensna"},{"LAspc"},
	{"Carap"},{"FCarp"},{"Melee"},{"Missl"},{"FAtta"},{">>Gas"},{">>Min"},{"Cancl"},{"NULL!"},
	{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"}
	}
};	


struct GOAL
{
	unsigned short time,what;
};

unsigned short Ziel[60],Build_Av[60],Build_Bv[60]; 
unsigned char Vespene_Av,Max_Build_Types,race;
unsigned short total_goals,building_types;
unsigned char num;
GOAL goal[MAX_GOALS];
double Goal_Harvested_Gas,Goal_Harvested_Mins;

struct Stats
{
	char name[35];
	unsigned short BT;
	unsigned short mins,gas;
	unsigned char supply;
	unsigned short type; // 0: nothing, 1: unit, 2: building (primarily for zerg!), 3: Research, 4: Upgrade (schild, waffen etc. bis 3)
	double speed;
	unsigned char tech[10];
};


const Stats stats[3][60]=
{
/*
 * Tech Terra
 *
 * 0 Factory
 * 1 Machine Shop
 * 2 StarPort
 * 3 Control Tower
 * 4 Engineering Bay
 * 5 Armory
 * 6 Science Facility
 * 7 Covert Ops
 * 8 Physics Lab
 * 9 Academy
 * */

	{
	{"Marine",		 24, 50,  0,1,1,1.00, 0,0,0,0,0,0,0,0,0,0},
	{"Ghost",		 50, 25, 75,1,1,1.00, 1,0,1,0,0,0,1,1,0,1},
	{"Vulture",		 30, 75,  0,2,1,1.00, 1,0,0,0,0,0,0,0,0,0},
	{"Goliath",		 40,100, 50,2,1,1.00, 1,0,0,0,0,1,0,0,0,0},
	{"Siege Tank",		 50,150,100,2,1,1.00, 1,1,0,0,0,0,0,0,0,0},
	{"SCV",			 20, 50,  0,1,1,0.00, 0,0,0,0,0,0,0,0,0,0}, // 0.0 Time to Enemy da es im Lager bleibt!
	{"Firebat",		 24, 50, 25,1,1,1.00, 0,0,0,0,0,0,0,0,0,1},
	{"Medic",		 30, 50, 25,1,1,1.00, 0,0,0,0,0,0,0,0,0,1},
	{"Wraith",		 60,150,100,2,1,0.60, 1,0,1,0,0,0,0,0,0,0},
	{"Science Vessel",	 80,100,225,2,1,0.70, 1,0,1,1,0,0,1,0,0,0},
	{"Dropship",		 50,100,100,2,1,0.70, 1,0,1,1,0,0,0,0,0,0},
	{"Battle Cruiser",	133,400,300,6,1,1.25, 1,0,1,1,0,0,1,0,1,0},
	{"Valkyrie",		 50,250,125,3,1,0.80, 1,0,1,1,0,1,0,0,0,0},

	{"Command Center",	120,400,  0,2,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Supply Depot",	 40,100,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Refinery",		 40,100,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Barracks",		 80,150,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Academy",		 80,150,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Factory",		 80,200,100,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Starport",		 70,150,100,0,2,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Science Facility",	 60,100,150,0,2,0.00, 1,0,1,0,0,0,0,0,0,0},
	{"Engineering Bay",	 60,125,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Armory",		 80,100, 50,0,2,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Missile Turret",	 30, 75,  0,0,2,0.00, 0,0,0,0,1,0,0,0,0,0},
	{"Bunker",		 30,100,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Comsat Station",	 40, 50, 50,0,0,0.00, 0,0,0,0,0,0,0,0,0,1},
	{"Nuclear Silo",	 40,100,100,0,0,0.00, 1,0,1,0,0,0,1,1,0,0},
	{"Control Tower",	 80, 50, 50,0,0,0.00, 1,0,1,0,0,0,0,0,0,0},
	{"Covert Ops",		 40, 50, 50,0,0,0.00, 1,0,1,0,0,0,1,0,0,0},
	{"Physics Lab",		 40, 50, 50,0,0,0.00, 1,0,1,0,0,0,1,0,0,0},
	{"Machine Shop",	 40, 50, 50,0,0,0.00, 1,0,0,0,0,0,0,0,0,0},

	{"Stim Packs",		 80,100,100,0,3,0.00, 0,0,0,0,0,0,0,0,0,1},
	{"Lockdown",		100,200,200,0,3,0.00, 1,0,1,0,0,0,1,1,0,0},
	{"EMP Shockwave",	120,200,200,0,3,0.00, 1,0,1,0,0,0,1,0,0,0},
	{"Spider Mines",	 80,100,100,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Siege Mode",		 80,150,150,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Irradiate",	 	 80,200,200,0,3,0.00, 1,0,1,0,0,0,1,0,0,0},
	{"Yamato Gun",		120,100,100,0,3,0.00, 1,0,1,0,0,0,1,0,1,0},
	{"Cloaking Field",	100,150,150,0,3,0.00, 1,0,1,1,0,0,0,0,0,0},
	{"Personnel Cloaking",	 80,100,100,0,3,0.00, 1,0,1,0,0,0,1,1,0,0},
	{"Restoration",	 	 80,100,100,0,3,0.00, 0,0,0,0,0,0,0,0,0,1},
	{"Optical Flare",	120,100,100,0,3,0.00, 0,0,0,0,0,0,0,0,0,1},
	{"U-238 Shells",	100,150,150,0,3,0.00, 0,0,0,0,0,0,0,0,0,1},
	{"Ion Thrusters",	100,100,100,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Titan Reactor",	166,150,150,0,3,0.00, 1,0,1,0,0,0,1,0,0,0},
	{"Ocular Implants",	166,100,100,0,3,0.00, 1,0,1,0,0,0,1,1,0,0},
	{"Moebius Reactor",	166,200,200,0,3,0.00, 1,0,1,0,0,0,1,1,0,0},
	{"Apollo Reactor",	166,200,200,0,3,0.00, 1,0,1,1,0,0,0,0,0,0},
	{"Colossus Reactor",	166,150,150,0,3,0.00, 1,0,1,0,0,0,1,0,1,0},
	{"Caduceus Reactor",	166,150,150,0,3,0.00, 0,0,0,0,0,0,0,0,0,1},
	{"Charon Booster",	133,100,100,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},

	{"Infantry Armor",	266,100,100,0,4,0.00, 0,0,0,0,1,0,0,0,0,0},
	{"Infantry Weapons",	266,100,100,0,4,0.00, 0,0,0,0,1,0,0,0,0,0},
	{"Vehicle Plating",	266,100,100,0,4,0.00, 0,0,0,0,0,1,0,0,0,0},
	{"Vehicle Weapons",	266,100,100,0,4,0.00, 0,0,0,0,0,1,0,0,0,0},
	{"Ship Plating",	266,150,150,0,4,0.00, 0,0,0,0,0,1,0,0,0,0},
	{"Ship Weapons",        266,100,100,0,4,0.00, 0,0,0,0,0,1,0,0,0,0},
	{"Nuclear Warhead",     100,200,200,8,0,0.00, 1,0,1,0,0,0,1,1,0,0},

	{"Mineral SCV to Gas",    0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Gas SCV to Mineral",    0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0}
	},
/* Tech Protoss:
 * 
 * 0 Cybernetics Core
 * 1 Citadel of Adun
 * 2 Templar Archives
 * 3 Stargate
 * 4 Robotics Facility
 * 5 Observatory
 * 6 Robotics Support Bay
 * 7 Forge
 * 8 Arbiter Tribunal
 * 9 Fleet Beacon
 * */
	
	{
	{"Dark Templar",	 50,125,100,2,1,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Dark Archon",		 20,  0,  0,0,1,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Probe",		 20, 50,  0,1,1,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Zealot",		 40,100,  0,2,1,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Dragoon",		 50,125, 50,2,1,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"High Templar",	 50, 50,150,2,1,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Archon",		 20,  0,  0,0,1,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Reaver",		 70,200,100,4,1,0.00, 1,0,0,0,1,0,1,0,0,0},
	{"Corsair",		 40,150,100,2,1,0.00, 1,0,0,1,0,0,0,0,0,0},
	{"Shuttle",		 60,200,  0,2,1,0.00, 1,0,0,0,1,0,0,0,0,0},
	{"Scout",		 80,275,125,3,1,0.00, 1,0,0,1,0,0,0,0,0,0},
	{"Arbiter",		160,100,350,4,1,0.00, 1,1,1,1,0,0,0,0,1,0},
	{"Carrier",		140,350,250,6,1,0.00, 1,0,0,1,0,0,0,0,0,1},
	{"Observer",		 40, 25, 75,1,1,0.00, 1,0,0,0,1,1,0,0,0,0},
	{"Nexus",		120,400,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Robotics Facility",	 80,200,200,0,2,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Pylon",		 30,100,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Assimilator",		 40,100,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Observatory",		 30, 50,100,0,2,0.00, 1,0,0,0,1,0,0,0,0,0},
	{"Gateway",		 60,150,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Photon Cannon",	 50,150,  0,0,2,0.00, 0,0,0,0,0,0,0,1,0,0},
	{"Cybernetics Core",	 60,200,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Citadel Of Adun",	 60,150,100,0,2,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Templar Archives",	 60,150,200,0,2,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Forge",		 40,150,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Stargate",		 70,150,150,0,2,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Fleet Beacon",	 60,300,200,0,2,0.00, 1,0,0,1,0,0,0,0,0,0},
	{"Arbiter Tribunal",	 60,200,150,0,2,0.00, 1,1,1,1,0,0,0,0,0,0},
	{"Robotics Support Bay", 30,150,100,0,2,0.00, 1,0,0,0,1,0,0,0,0,0},
	{"Shield Battery",	 30,100,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Psionic Storm",	120,200,200,0,3,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Hallucination",	 80,150,150,0,3,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Recall",		120,150,150,0,3,0.00, 1,1,1,1,0,0,0,0,0,0},
	{"Stasis Field",	100,150,150,0,3,0.00, 1,1,1,1,0,0,0,0,0,0},
	{"Disruption Web",	 80,200,200,0,3,0.00, 1,0,0,1,0,0,0,0,0,1},
	{"Mind Control",	120,200,200,0,3,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Maelstrom",		100,100,100,0,3,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Singularity Charge",	166,150,150,0,3,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Leg Enhancements",	133,150,150,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Scarab Damage",	166,200,200,0,3,0.00, 1,0,0,0,1,0,1,0,0,0},
	{"Reaver Capacity",	166,200,200,0,3,0.00, 1,0,0,0,1,0,1,0,0,0},
	{"Gravitic Drive",	166,200,200,0,3,0.00, 1,0,0,0,1,0,1,0,0,0},
	{"Sensor Array",	133,150,150,0,3,0.00, 1,0,0,0,1,1,0,0,0,0},
	{"Gravitic Boosters",	133,150,150,0,3,0.00, 1,0,0,0,1,1,0,0,0,0},
	{"Khaydarin Amulet",	166,150,150,0,3,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Apial Sensors",	166,100,100,0,3,0.00, 1,0,0,1,0,0,0,0,0,1},
	{"Gravitic Thrusters",	166,200,200,0,3,0.00, 1,0,0,1,0,0,0,0,0,1},
	{"Carrier Capacity",	100,100,100,0,3,0.00, 1,0,0,1,0,0,0,0,0,1},
	{"Khaydarin Core",	166,150,150,0,3,0.00, 1,1,1,1,0,0,0,0,1,0},
	{"Argus Jewel",		166,100,100,0,3,0.00, 1,0,0,1,0,0,0,0,0,1},
	{"Argus Talisman",	166,150,150,0,3,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Armor",		266,100,100,0,4,0.00, 0,0,0,0,0,0,0,1,0,0},
	{"Plating",		266,150,150,0,4,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Ground Weapons",	266,100,100,0,4,0.00, 0,0,0,0,0,0,0,1,0,0},
	{"Air Weapons",		266,100,100,0,4,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Plasma Shields",	266,200,200,0,4,0.00, 0,0,0,0,0,0,0,1,0,0},
	{"Mineral Probe To Gas",  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Gas Probe To Mineral",  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0}
	},
/*
 * Tech Zerg
 *
 * 0 Extractor // evtl noch raus
 * 1 Lair
 * 2 Hydra Den
 * 3 Evolution Chamber
 * 4 Queen's Nest
 * 5 Spire
 * 6 Hive
 * 7 Ultralisk Chamber
 * 8 Defiler Mound
 * 9 Greater Spire
 * 
 * */
	{
	{"Zergling",		 28, 50,  0,1,1,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Hydralisk",		 28, 75, 25,1,1,0.00, 1,0,1,0,0,0,0,0,0,0},
	{"Ultralisk",		 60,200,200,6,1,0.00, 1,1,0,0,1,0,1,1,0,0},
	{"Drone",		 23, 50,  0,1,1,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Defiler",		 50, 50,150,2,1,0.00, 1,1,0,0,1,0,1,0,1,0},
	{"Lurker",		 40, 50,100,2,0,0.00, 1,1,1,0,0,0,0,0,0,0},
	{"Overlord",		 40,100,  0,0,1,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Mutalisk",		 40,100,100,2,1,0.00, 1,1,0,0,0,1,0,0,0,0},
	{"Guardien",		 40, 50,100,2,0,0.00, 1,1,0,0,1,1,1,0,0,1},
	{"Queen",		 50,100,100,2,1,0.00, 1,1,0,0,1,0,0,0,0,0},
	{"Scourge",		 30, 25, 75,1,1,0.00, 1,1,0,0,0,1,0,0,0,0},
	{"Devourer",		 40,100, 50,2,0,0.00, 1,1,0,0,1,1,1,0,0,1},

	{"Hatchery",		120,300,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Lair",		100,150,100,0,0,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Hive",		120,200,150,0,0,0.00, 1,1,0,0,1,0,1,0,0,0},
	{"Nydus Canal",		 40,150,  0,0,2,0.00, 1,1,0,0,1,0,1,0,0,0},
	{"Hydralisk den",	 40,100, 50,0,2,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Defiler mound",	 60,100,100,0,2,0.00, 1,1,0,0,1,0,1,0,0,0},
	{"Greater Spire",	120,100,150,0,0,0.00, 1,1,0,0,1,1,1,0,0,0},
	{"Queen's Nest",	 60,150,100,0,2,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Evolution Chamber",	 40, 75,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Ultralisk Cavern",	 80,150,200,0,2,0.00, 1,1,0,0,1,0,0,0,0,0},
	{"Spire",		120,200,150,0,2,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Spawning Pool",	 80,200,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Creep Colony",	 20, 75,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Spore Colony",	 20, 50,  0,0,0,0.00, 0,0,0,1,0,0,0,0,0,0},
	{"Sunken Colony",	 20, 50,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Extractor",		 40, 50,  0,0,2,0.00, 0,0,0,0,0,0,0,0,0,0},//27
 
	{"Ventral Sacs",	160,200,200,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Antennae",		133,150,150,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Pneumatized Carapace",133,150,150,0,3,0.00, 1,1,0,0,0,0,0,0,0,0},
	{"Metabolic Boost",	100,100,100,0,3,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Adrenal Glands",	100,200,200,0,3,0.00, 1,1,0,0,1,0,1,0,0,0},
	{"Muscular Augments",	100,150,150,0,3,0.00, 1,0,1,0,0,0,0,0,0,0},
	{"Grooved Spines",	100,150,150,0,3,0.00, 1,0,1,0,0,0,0,0,0,0},
	{"Gamete Meiosis",	166,150,150,0,3,0.00, 1,1,0,0,1,0,0,0,0,0},
	{"Metasynaptic node",	166,150,150,0,3,0.00, 1,1,0,0,1,0,1,0,1,0},
	{"Chitinous Plating",	133,150,150,0,3,0.00, 1,1,0,0,1,0,1,1,0,0},
	{"Anabolic Synthesis",	133,200,200,0,3,0.00, 1,1,0,0,1,0,1,1,0,0},

	{"Burrowing",		 80,100,100,0,3,0.00, 1,0,0,0,0,0,0,0,0,0},
	{"Spawn Broodling",	 80,100,100,0,3,0.00, 1,1,0,0,1,0,0,0,0,0},
	{"Plague",		100,200,200,0,3,0.00, 1,1,0,0,1,0,1,0,1,0},
	{"Consume",		100,100,100,0,3,0.00, 1,1,0,0,1,0,1,0,1,0},
	{"Ensnare",		 80,100,100,0,3,0.00, 1,1,0,0,1,0,0,0,0,0},
	{"Lurker Aspect",	120,200,200,0,3,0.00, 1,1,1,0,0,0,0,0,0,0},

	{"Carapace",		266,150,150,0,4,0.00, 1,0,0,1,0,0,0,0,0,0},//45
	{"Flyer Carapace",	266,150,150,0,4,0.00, 1,1,0,0,0,1,0,0,0,0},
	{"Melee Attacks",	266,100,100,0,4,0.00, 1,0,0,1,0,0,0,0,0,0},
	{"Missile Attacks",	266,100,100,0,4,0.00, 1,0,0,1,0,0,0,0,0,0},
	{"Flyer Attacks",	266,100,100,0,4,0.00, 1,1,0,0,0,1,0,0,0,0},
	{"Mineral Drone to Gas",  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Gas Drone to Mineral",  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"Break up Building",	  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},

	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",		  0,  0,  0,0,0,0.00, 0,0,0,0,0,0,0,0,0,0}
	}
};

unsigned long power(signed char t)
{
	if(t>0)
		return (power(t-1)*10);
	else return (1);
}
	

class Settings
{
	public:
	//Output Switches 0/1
	unsigned short numbers,colors,Detailed_Output;
	//Map Data
	unsigned short Time_to_Enemy,Mineral_Mod,Time_to_Wallin,Scout_Time;
	unsigned short Mineral_Blocks,Vespene_Geysirs,Verbose;
	//Internal Options
	unsigned short Max_Time,Max_Generations,Mutations,Mutation_Rate;

	unsigned short s;
	
	unsigned char d;
	signed char t;
	
	char * buffer;

	unsigned short data[2*MAX_GOALS];
	unsigned long size;

	unsigned char Init(char I[11])
	{
		printf("Checking input file [settings.txt]...\n");
	FILE * pFileS;
        pFileS = fopen ("settings.txt","rb");
	// Auf Error checken! Evtl nciht da!
	printf("File opened... reading...\n");
	
	fseek (pFileS, 0, SEEK_END);
	size = ftell (pFileS);
	buffer = new char [size];
	fseek (pFileS, 0, SEEK_SET);
	fread(buffer,1,size,pFileS);
	fclose(pFileS);
	printf("File closed, data saved.\n");
	s=0;d=0;

	while(s<size)
	{
		if((buffer[s]>=48)&&(buffer[s]<58)&&(d<DATA_SET_SIZE))
		{
			t=0;
			s++;
			while((buffer[s]>=48)&&(buffer[s]<58)&&(s<size))
			{
				t++;s++;
			}
			if(t>3)
			{
				printf("FATAL ERROR: Do not use numbers bigger than 9999 in the settings.txt file!\n");
				printf("Freeing Buffer, Exiting...\n");
				free(buffer);
				return(1);
			}
			while(t>=0)
			{
				data[d]+=(buffer[s-t-1]-48)*power(t);
				t--;
			}
			d++;
		}
		s++;
	}
	free(buffer);
	printf("Buffer freed and saved...\n");
	printf("Checking data:\n");
	
	if(d<DATA_SET_SIZE)
	{
		printf("Not enough Data sets found (%i out of expected %i).\n",d,DATA_SET_SIZE);
		printf("Please report this to ClawSoftware and/or get an original copy of the 'settings.txt'\n");
		printf("Using defaults...\n");
		numbers=1;
		colors=1;
		Detailed_Output=1;
		Time_to_Enemy=50;
		Vespene_Geysirs=1;
		Mineral_Mod=100;
		Mineral_Blocks=8;
		Time_to_Wallin=0;
		Scout_Time=160;
		Max_Time=45;
		Max_Generations=150;
		Mutations=50;
		Mutation_Rate=50;
		Verbose=1;
	}
	else
	{
		numbers=data[0];
		colors=data[1];
		Detailed_Output=data[2];
		Time_to_Enemy=data[3];
		Vespene_Geysirs=data[4];
		Mineral_Mod=data[5];
		Mineral_Blocks=data[6];
		Time_to_Wallin=data[7];
		Scout_Time=data[8];
		Max_Time=data[9];
		Max_Generations=data[10];
		Mutations=data[11];
		Mutation_Rate=data[12];
		Verbose=data[13];
	}

	if((numbers!=0)&&(numbers!=1))
	{
		printf("ERROR: 'Numbers' not correctly initialized [%i].\n",numbers);
		printf("Please use 0 (no numbers) or 1 (numbers in front of the orders)!\n");
		printf("Falling back to default: Numbers = 1\n");
		numbers=1;
	}

        if((colors!=0)&&(colors!=1))
        {
               printf("ERROR: 'Colors' not correctly initialized [%i].\n",colors);
	       printf("Please use 0 (white/black) or 1 (colors to stress changes in the BO)!\n");
	       printf("Falling back to default: Colors = 1\n");
	       colors=1;
	}
	
	if((Detailed_Output!=0)&&(Detailed_Output!=1))
	 {
	       printf("ERROR: 'Detailed_Output' not correctly initialized [%i].\n",Detailed_Output);
	       printf("Please use 0 (more readable) or 1 (timestamp in front of each order)!\n");
	       printf("Falling back to default: Detailed_Output = 0\n");
	       Detailed_Output=0;
	 }
	if(Time_to_Enemy>300)
	{
		printf("WARNING: 'Time to Enemy' is larger than 5 minutes! [%i]\n",Time_to_Enemy);
		printf("This is not recommended. Try to change the 'settings.txt'\n");	      	
	}
	if(Vespene_Geysirs==0)
	{
		printf("WARNING: 'Vespene Geysirs' is set to 0.\n");
		printf("This is not recommended. No gas can be gathered!\n");
		printf("Try to change the 'settings.txt'\n");
	}
	if(Mineral_Mod<10)
	{
		printf("WARNING: 'Mineral Gathering modificator' is set below 10.\n");
		printf("This is not recommended. Almost no minerals can be gathered!\n");
		printf("Try to change the settings.txt'\n");
	}
	if(Mineral_Blocks==0)
	{
		printf("ERROR: 'Mineral Blocks' is set to zero.\n");
		printf("Are you crazy or what? ;-)\n");
		printf("Falling back to default: Mineral Blocks = 8\n");
	       Mineral_Blocks=8;	
	}
	if(Max_Time<5)
	{
		printf("ERROR: 'Max Time' is set too low. [%i]\n",Max_Time);
		printf("Please use at least 10 minutes.\n");
		printf("Falling back to default: Max Time = 45\n");
		Max_Time=45;
	}
	else
	if(Max_Time<10)
	{
		printf("WARNING: 'Max Time' is set very low. [%i]\n",Max_Time);
		printf("The program will probably not work very well.\n");
		printf("Try to change the 'settings.txt'\n");
	}
	if(Scout_Time/60 >Max_Time)
	{
		printf("ERROR: 'Scout Time' is set too high. [%i]\n",Scout_Time);
		printf("Please keep it below 'Max Time'.\n");
		printf("Falling back to default: Scout Time = 160\n");
		Scout_Time=160;
	}
	if(Max_Generations<10)
	{
		printf("ERROR: 'Max Generations' is set too low. [%i]\n",Max_Generations);
		printf("The program is useless with this setting.\n");
		printf("Falling back to default: Max Generations = 150");
		Max_Generations=150;
	}
	else if(Max_Generations<50)
	{
		printf("WARNING: 'Max Generations' is set very low. [%i]\n",Max_Generations);
		printf("It is not very likely that the program will find an optimal solution.\n");
	       printf("Try to change the 'settings.txt'.\n");
	}	       
	
	if(Mutations==0)
	{
		printf("WARNING: 'Mutations' is set to zero.\n");
		printf("This is only useful if you want to test an own build order and determine its speed\n");
		printf("Optimization is set OFF!\n");
	} else
	if(Mutations<10)
	{
		printf("WARNING: 'Mutations' is set very low.\n");
		printf("The program will probably not be able to determine the optimal solution!\n");
		printf("Try to change the 'settings.txt'.\n");
	}

	if(Mutation_Rate<5)
	{
		printf("ERROR: 'Mutation Rate' is set too low. [%i]\n",Mutation_Rate);
		printf("Please use at least 5! Remember: 1/Mutation Rate = Probability of a Mutation\n");
	       printf("Falling back to default: Mutation Rate = 50");
       		Mutation_Rate=50;	       
	}
	if((Verbose!=0)&&(Verbose!=1))
	{
		printf("ERROR: 'Numbers' not correctly initialized [%i].\n",numbers);
                printf("Please use 0 (no numbers) or 1 (numbers in front of the orders)!\n");
		printf("Falling back to default: Verbose = 1\n");
	        Verbose=1;
								
	}

	printf("Reformatting Data Minutes -> Seconds\n");
	Max_Time*=60;

	printf("'settings.txt' succesfully checked!\n");
	printf("Moving on to %s...\n",I);

	for(s=0;s<MAX_GOALS;s++)
	{
		goal[s].what=0;
		goal[s].time=0;
		Ziel[s]=0;
		data[2*s]=0;
		data[2*s+1]=0;
	}

	printf("Checking input file [%s]...\n",I);
	
        pFileS = fopen (I,"rb");
	// Auf Error checken! Evtl nciht da!
	printf("File opened... reading...\n");
	
	fseek (pFileS, 0, SEEK_END);
	size = ftell (pFileS);
	buffer = new char [size];
	fseek (pFileS, 0, SEEK_SET);
	fread(buffer,1,size,pFileS);
	fclose(pFileS);
	printf("File closed, data saved [%i Bytes].\n",size);
	s=0;d=0;
	while(s<size)
	{
		if((buffer[s]>=48)&&(buffer[s]<58))
		{
			t=0;
			s++;
			while((buffer[s]>=48)&&(buffer[s]<58)&&(s<size))
			{
				t++;s++;
			}
			if(t>3)
			{
				printf("FATAL ERROR: Do not use numbers bigger than 9999 in the %s file!\n",I);
                                printf("Freeing Buffer, Exiting...\n");
			        free(buffer);
				 return(1);
			}
			while(t>=0)
			{
				data[d]+=(buffer[s-t-1]-48)*power(t);
				t--;
			}
			d++;
		}
		s++;
	}
	free(buffer);
	printf("Buffer freed and saved...\n");
	printf("Analyzing data and setting goals...\n");
// Noch eine Ueberpruefung auf die Anzahl der gefundenen Datensaetze machen!
	// 	
	unsigned long count_goals;
	count_goals=0;

	for(s=0;s<60;s++)
	{
		if((stats[race][s].type==3)&&(data[s*2]>1))
		{
			printf("ERROR: Research projects cannot be build more than a single time.\n");
			printf("Section %s in %s: Using 1 instead of %i...\n",stats[race][s].name,I,data[s*2]);
			data[s*2]=1;
		}
		if((data[s*2+1]>0)&&(data[s*2+1]*60+stats[race][s].BT >= Max_Time))
		{
			printf("ERROR: Build Time nearly exceeds Max Time!\n");
			printf("Try to increase Max Time [%i] in 'settings.txt' or reduce the goal time [%i] in %s!\n",Max_Time/60,data[s*2+1],I);
			printf("Disabling goal time for %s...\n",stats[race][s].name);
			data[s*2+1]=0;
		}
		goal[s].what=data[s*2];
		goal[s].time=data[s*2+1];
		count_goals+=goal[s].what;
	}
	
	printf("Reformatting Data Minutes -> Seconds\n");
	for(s=0;s<60;s++)
		goal[s].time*=60;
	
	printf("All goals [%i] succesfully initialized!\n\n",count_goals);
	
	return(0);
	};
} setup;



class RACE
{
public:
	unsigned force[60];
	unsigned short ftime[60]; //when the goal is reached...
	unsigned char availible[60];
	double mins,gas;
	unsigned short larvae,IP,min,n;
	unsigned short peonmins,peongas, peonbuilding, length,BuildingRunning;
	short Supply,Max_Supply;

	unsigned char av_starport,av_factory;
	//hacked: man kann sonst in nem kompletten Starport sowohl erforschen, als auch valkyries baun etc.

	unsigned char ready;
	struct Program
	{
		unsigned char order,location,need_Supply,have_Supply,success;
		unsigned short time,mins,gas,temp;		
	} program[MAX_LENGTH];
	struct Building
	{
		unsigned short RB; // Remaining Buildtime
		unsigned short type; // Type of Building
		unsigned char on_the_run; //unit that is running towards the enemy
		unsigned char location;
		// Main, Front, Enemy Front, Enemy Main, Drop(?), Expansion(?)
	} building[MAX_BUILDINGS];

	unsigned char nr,ok;

	unsigned char larva[LARVA_MAX]; // larvacounter for producing larvas
	unsigned char larvacounter;

	double harvested_gas,harvested_mins;
	unsigned short pFitness,sFitness,timer,gasready,minsready;

	virtual void Set_Goals() {};
	virtual inline void Produce() {};
	virtual void Build() {};
	virtual void Calculate() {};
	virtual void InitRaceSpecific() {};

	const double mining[57],const double gasing[5];

	void CalculateFitness()
	{
		unsigned char i;
		unsigned short verschwendung;
		unsigned char bonus[MAX_GOALS]; // ob schon Bonus fuer halbfertige Einheit vergeben wurde
		pFitness=0;
		sFitness=0;
		sFitness=(unsigned short)(harvested_mins+harvested_gas);
		//Problem: Verschwendung... viele Science Labors etc
		 if(ready==0)
	         {
	                 timer=setup.Max_Time;
	         //Bei Zeit: Zwischenziele rein, z.B. Lair, Hive, etc. ??
		// HAEE??? WARUM HIER MAX_BUILD_TYPES!?
			 for(i=0;i<building_types;i++)
                                if(goal[i].what>0)
	        	             {
	                              if(goal[i].what>force[i])
				      {
				      //nicht alle erledigt & ueber der Zeit
					      if(goal[i].time>0)
					      	pFitness+=(100*goal[i].time*force[i])/(goal[i].what*setup.Max_Time);
					      else pFitness+=(100*force[i])/goal[i].what;
				      }
				      else
				      {
					if((goal[i].time>0)&&(ftime[i]>goal[i].time))
						pFitness+=(goal[i].time*100/ftime[i]);
					else	pFitness+=100;
			//		if(goal[i].what<force[i])
			//			sFitness-=(force[i]-goal[i].what)*(stats[race][i].mins+stats[race][i].gas);
				      }
				     }
// Obacht vor sehr kleinen goal[i].times vielleicht nochmal in der scc.cpp checken
				      
				      
		//if(Goal_Harvested_Gas>harvested_gas)
                  //      fitness+=(unsigned short)(harvested_gas*100/Goal_Harvested_Gas);
             //   else
	//	{
	//		fitness+=100;
	//		fitness+=gasready;
	//	};
	
     	//	if(Goal_Harvested_Mins>harvested_mins)
          //              fitness+=(unsigned short)(harvested_mins*100/Goal_Harvested_Mins);
            //    else 
	//	{
	//		fitness+=100;
	//		fitness+=minsready;
	//	};
//Problem hier: wenn Programm viele nichtfertige Gebaeude kurz vor Ende hat wirds nicht abgefangen...
		for(i=0;i<MAX_GOALS;i++)
			bonus[i]=goal[i].what-force[i];
		for(i=0;i<MAX_BUILDINGS;i++)
                        if((building[i].RB>0)&&(goal[building[i].type].what>force[building[i].type])&&(bonus[building[i].type]>0))
			{
	                          pFitness+=((building[i].RB*100)/(goal[building[i].type].what*stats[race][building[i].type].BT));
				  bonus[building[i].type]--;
			}
	       }
	        else
		 {
		            pFitness=setup.Max_Time-timer;//~~~~~~~~~Zeit staerker ins gewicht fallen lassen!
		            
			    // pFitness+=400;//mins, gas
		            // Warum hier Max_Build_Types!? 
			    for(i=0;i<building_types;i++)
	                      if(goal[i].what>0)
		                   pFitness+=100;
		   }
		
	}
	
	void Mutate()
{
	unsigned char ttt,ta,tb,i,x,y;
//loeschen, einfuegen, veraendern
	for(i=0;i<setup.Mutations;i++)
	{
	if(rand()%setup.Mutation_Rate==0)
	{
		x=rand()%MAX_LENGTH;
		for(y=x;y<MAX_LENGTH-1;y++)
			program[y].order=program[y+1].order;
	}
	
	if(rand()%setup.Mutation_Rate==0)
	{
		x=rand()%MAX_LENGTH;
		for(y=MAX_LENGTH-1;y>x;y--)
			program[y].order=program[y-1].order;
		program[x].order=rand()%Max_Build_Types;
	}

	if(rand()%setup.Mutation_Rate==0)
	{
		x=rand()%MAX_LENGTH;
		program[x].order=rand()%Max_Build_Types;
	}
	if(rand()%setup.Mutation_Rate==0)
	{
		ta=rand()%MAX_LENGTH;
		tb=rand()%MAX_LENGTH;
		ttt=program[ta].order;
		program[ta].order=program[tb].order;
		program[tb].order=ttt;
	}
	if(rand()%(setup.Mutation_Rate/2)==0)
	{
		ta=rand()%MAX_LENGTH;
		tb=rand()%MAX_LENGTH;
		if(ta>tb)
		{
		ttt=program[ta].order;
		for(i=ta;i<tb;i++)
			program[i].order=program[i+1].order;
		program[tb].order=ttt;
		}
	}
	}
}

void Init()
{
	unsigned char i;
	for(i=0;i<building_types;i++)
        {
               force[i]=0;
	       ftime[i]=0;
               if(stats[race][i].type<3)
	               availible[i]=0;
	       else
	               availible[i]=1;
	}
	for(i=0;i<MAX_BUILDINGS;i++)
	{
	       building[i].RB=0;
	       building[i].type=255;
	}
        pFitness=0;
	sFitness=0;
        mins=50;
        gas=0;
	peonmins=4;
	peongas=0;
	IP=0;
	InitRaceSpecific();
}
	
	
	void Restart()
	{
		unsigned char i;
		/*unsigned char randliste[100],xxx,xy,i;
		xxx=0;xy=0;
		for(i=0;i<building_types;i++)
		{
			xy=0;
			while(Ziel[i]-xy>0)
			{
				randliste[xxx]=Build_Av[i];
				xxx++;xy++;
			}
		}*/
		for(i=0;i<MAX_LENGTH;i++)
		{
			program[i].order=rand()%Max_Build_Types;
			//evtl ganzes Programm hier rein...
			//Liste erstellen 
			program[i].time=20000;
			program[i].temp=0;
//			program[i].loc=
		}
		timer=setup.Max_Time;
		IP=0;
		length=MAX_LENGTH;
		av_starport=0;
		av_factory=0;
	}
};







#endif


