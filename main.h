//jedem Gebaeude eine Position zuweisen (Entfernung zum Gegner)


#ifndef MAIN_H
#define MAIN_H
#define MAX_LENGTH 100
#define RUNNINGS 5
#define MAX_PLAYER 100
#define LARVA_MAX 500
#define MAX_BUILDINGS 12 // How many buildings can you built simultaneously?

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
unsigned char Vespene_Av,Max_Build_Types,Max_Vespene;
unsigned short Max_Time,Max_Generations,Mut_Rate,Mutations;
unsigned short afit;
unsigned short generation;
unsigned char num,Attack;
unsigned short x,y,i,j,A,B;
GOAL goal[60];
double Goal_Harvested_Gas,Goal_Harvested_Mins;
unsigned short Time_to_Enemy;

struct Stats
{
	char name[35];
	unsigned short BT;
	unsigned short mins,gas;
	unsigned char supply;
	unsigned short type; // 0: nothing, 1: unit, 2: building (primarily for zerg!), 3: Research, 4: Upgrade (schild, waffen etc. bis 3)
	unsigned char tech[10];
	//Zerg:  0: extractor,lair,Hden,evoC,queenN,spire,hive,ultraC,defilerM,greaterspire
};


const Stats stats[3][60]=
{
	{
	{"Marine",24,50,0,1,1, 0,0,0,0,0,0,0,0,0,0},
	{"Ghost",50,25,75,1,1, 1,0,1,0,0,0,1,1,0,1},
	{"Vulture",30,75,0,2,1, 1,0,0,0,0,0,0,0,0,0},
	{"Goliath",40,100,50,2,1, 1,0,0,0,0,1,0,0,0,0},
	{"Siege Tank",50,150,100,2,1, 1,1,0,0,0,0,0,0,0,0},
	{"SCV",20,50,0,1,1, 0,0,0,0,0,0,0,0,0,0},
	{"Firebat",24,50,25,1,1, 0,0,0,0,0,0,0,0,0,1},
	{"Medic",30,50,25,1,1, 0,0,0,0,0,0,0,0,0,1},
	{"Wraith",60,150,100,2,1, 1,0,1,0,0,0,0,0,0,0},
	{"Science Vessel",80,100,225,2,1, 1,0,1,1,0,0,1,0,0,0},
	{"Dropship",50,100,100,2,1, 1,0,1,1,0,0,0,0,0,0},
	{"Battle Cruiser",133,400,300,6,1, 1,0,1,1,0,0,1,0,1,0},
	{"Valkyrie",50,250,125,3,1, 1,0,1,1,0,1,0,0,0,0},
	{"Command Center",120,400,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Supply Depot",40,100,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Refinery",40,100,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Barracks",80,150,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Academy",80,150,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Factory",80,200,100,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Starport",70,150,100,0,2, 1,0,0,0,0,0,0,0,0,0},
	{"Science Facility",60,100,150,0,2, 1,0,1,0,0,0,0,0,0,0},
	{"Engineering Bay",60,125,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Armory",80,100,50,0,2, 1,0,0,0,0,0,0,0,0,0},
	{"Missile Turret",30,75,0,0,2, 0,0,0,0,1,0,0,0,0,0},
	{"Bunker",30,100,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Comsat Station",40,50,50,0,0, 0,0,0,0,0,0,0,0,0,1},
	{"Nuclear Silo",40,100,100,0,0, 1,0,1,0,0,0,1,1,0,0},
	{"Control Tower",80,50,50,0,0, 1,0,1,0,0,0,0,0,0,0},
	{"Covert Ops",40,50,50,0,0, 1,0,1,0,0,0,1,0,0,0},
	{"Physics Lab",40,50,50,0,0, 1,0,1,0,0,0,1,0,0,0},
	{"Machine Shop",40,50,50,0,0, 1,0,0,0,0,0,0,0,0,0},
	{"Stim Packs",80,100,100,0,3, 0,0,0,0,0,0,0,0,0,1},
	{"Lockdown",100,200,200,0,3, 1,0,1,0,0,0,1,1,0,0},
	{"EMP Shockwave",120,200,200,0,3, 1,0,1,0,0,0,1,0,0,0},
	{"Spider Mines",80,100,100,0,3, 1,1,0,0,0,0,0,0,0,0},
	{"Siege Mode",80,150,150,0,3, 1,1,0,0,0,0,0,0,0,0},
	{"Irradiate",80,200,200,0,3, 1,0,1,0,0,0,1,0,0,0},
	{"Yamato Gun",120,100,100,0,3, 1,0,1,0,0,0,1,0,1,0},
	{"Cloaking Field",100,150,150,0,3, 1,0,1,1,0,0,0,0,0,0},
	{"Personnel Cloaking",80,100,100,0,3, 1,0,1,0,0,0,1,1,0,0},
	{"Restoration",80,100,100,0,3, 0,0,0,0,0,0,0,0,0,1},
	{"Optical Flare",120,100,100,0,3, 0,0,0,0,0,0,0,0,0,1},
	{"U-238 Shells",100,150,150,0,3, 0,0,0,0,0,0,0,0,0,1},
	{"Ion Thrusters",100,100,100,0,3, 1,1,0,0,0,0,0,0,0,0},
	{"Titan Reactor",166,150,150,0,3, 1,0,1,0,0,0,1,0,0,0},
	{"Ocular Implants",166,100,100,0,3, 1,0,1,0,0,0,1,1,0,0},
	{"Moebius Reactor",166,200,200,0,3, 1,0,1,0,0,0,1,1,0,0},
	{"Apollo Reactor",166,200,200,0,3, 1,0,1,1,0,0,0,0,0,0},
	{"Colossus Reactor",166,150,150,0,3, 1,0,1,0,0,0,1,0,1,0},
	{"Caduceus Reactor",166,150,150,0,3, 0,0,0,0,0,0,0,0,0,1},
	{"Charon Booster",133,100,100,0,3, 1,1,0,0,0,0,0,0,0,0},
	{"Infantry Armor",266,100,100,0,4, 0,0,0,0,1,0,0,0,0,0},
	{"Infantry Weapons",266,100,100,0,4, 0,0,0,0,1,0,0,0,0,0},
	{"Vehicle Plating",266,100,100,0,4, 0,0,0,0,0,1,0,0,0,0},
	{"Vehicle Weapons",266,100,100,0,4, 0,0,0,0,0,1,0,0,0,0},
	{"Ship Plating",266,150,150,0,4, 0,0,0,0,0,1,0,0,0,0},
	{"Ship Weapons",266,100,100,0,4, 0,0,0,0,0,1,0,0,0,0},
	{"Nuclear Warhead",100,200,200,8,0, 1,0,1,0,0,0,1,1,0,0},
	{"Mineral SCV to Gas",0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Gas SCV to Mineral",0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0}
	},

	{
	{"Dark Templar",50,125,100,2 ,1 ,1,1,1,0,0,0,0,0,0,0},
	{"Dark Archon",20,0,0,0,1 ,1,1,1,0,0,0,0,0,0,0},
	{"Probe",20,50,0,1,1 ,0,0,0,0,0,0,0,0,0,0},
	{"Zealot",40,100,0,2,1 ,0,0,0,0,0,0,0,0,0,0},
	{"Dragoon",50,125,50,2,1 ,1,0,0,0,0,0,0,0,0,0},
	{"High Templar",50,50,150,2,1 ,1,1,1,0,0,0,0,0,0,0},
	{"Archon",20,0,0,0,1 ,1,1,1,0,0,0,0,0,0,0},
	{"Reaver",70,200,100,4,1 ,1,0,0,0,1,0,1,0,0,0},
	{"Corsair",40,150,100,2,1 ,1,0,0,1,0,0,0,0,0,0},
	{"Shuttle",60,200,0,2,1 ,1,0,0,0,1,0,0,0,0,0},
	{"Scout",80,275,125,3,1 ,1,0,0,1,0,0,0,0,0,0},
	{"Arbiter",160,100,350,4,1 ,1,1,1,1,0,0,0,0,1,0},
	{"Carrier",140,350,250,6,1 ,1,0,0,1,0,0,0,0,0,1},
	{"Observer",40,25,75,1,1 ,1,0,0,0,1,1,0,0,0,0},
	{"Nexus",120,400,0,0,2 ,0,0,0,0,0,0,0,0,0,0},
	{"Robotics Facility",80,200,200,0,2 ,1,0,0,0,0,0,0,0,0,0},
	{"Pylon",30,100,0,0,2 ,0,0,0,0,0,0,0,0,0,0},
	{"Assimilator",40,100,0,0,2 ,0,0,0,0,0,0,0,0,0,0},
	{"Observatory",30,50,100,0,2 ,1,0,0,0,1,0,0,0,0,0},
	{"Gateway",60,150,0,0,2 ,0,0,0,0,0,0,0,0,0,0},
	{"Photon Cannon",50,150,0,0,2 ,0,0,0,0,0,0,0,1,0,0},
	{"Cybernetics Core",60,200,0,0,2 ,0,0,0,0,0,0,0,0,0,0},
	{"Citadel Of Adun",60,150,100,0,2 ,1,0,0,0,0,0,0,0,0,0},
	{"Templar Archives",60,150,200,0,2 ,1,1,0,0,0,0,0,0,0,0},
	{"Forge",40,150,0,0,2 ,0,0,0,0,0,0,0,0,0,0},
	{"Stargate",70,150,150,0,2 ,1,0,0,0,0,0,0,0,0,0},
	{"Fleet Beacon",60,300,200,0,2 ,1,0,0,1,0,0,0,0,0,0},
	{"Arbiter Tribunal",60,200,150,0,2 ,1,1,1,1,0,0,0,0,0,0},
	{"Robotics Support Bay",30,150,100,0,2 ,1,0,0,0,1,0,0,0,0,0},
	{"Shield Battery",30,100,0,0,2 ,0,0,0,0,0,0,0,0,0,0},
	{"Psionic Storm",120,200,200,0,3 ,1,1,1,0,0,0,0,0,0,0},
	{"Hallucination",80,150,150,0,3 ,1,1,1,0,0,0,0,0,0,0},
	{"Recall",120,150,150,0,3 ,1,1,1,1,0,0,0,0,0,0},
	{"Stasis Field",100,150,150,0,3 ,1,1,1,1,0,0,0,0,0,0},
	{"Disruption Web",80,200,200,0,3 ,1,0,0,1,0,0,0,0,0,1},
	{"Mind Control",120,200,200,0,3 ,1,1,1,0,0,0,0,0,0,0},
	{"Maelstrom",100,100,100,0,3 ,1,1,1,0,0,0,0,0,0,0},
	{"Singularity Charge",166,150,150,0,3 ,0,0,0,0,0,0,0,0,0,0},//??
	{"Leg Enhancements",133,150,150,0,3 ,1,1,0,0,0,0,0,0,0,0},
	{"Scarab Damage",166,200,200,0,3 ,1,0,0,0,1,0,1,0,0,0},
	{"Reaver Capacity",166,200,200,0,3 ,1,0,0,0,1,0,1,0,0,0},
	{"Gravitic Drive",166,200,200,0,3 ,1,0,0,0,1,0,1,0,0,0},
	{"Sensor Array",133,150,150,0,3 ,1,0,0,0,1,1,0,0,0,0},
	{"Gravitic Boosters",133,150,150,0,3 ,1,0,0,0,1,1,0,0,0,0},
	{"Khaydarin Amulet",166,150,150,0,3 ,1,1,1,0,0,0,0,0,0,0},
	{"Apial Sensors",166,100,100,0,3 ,1,0,0,1,0,0,0,0,0,1},
	{"Gravitic Thrusters",166,200,200,0,3 ,1,0,0,1,0,0,0,0,0,1},
	{"Carrier Capacity",100,100,100,0,3 ,1,0,0,1,0,0,0,0,0,1},
	{"Khaydarin Core",166,150,150,0,3 ,1,1,1,1,0,0,0,0,1,0},
	{"Argus Jewel",166,100,100,0,3 ,1,0,0,1,0,0,0,0,0,1},
	{"Argus Talisman",166,150,150,0,3 ,1,1,1,0,0,0,0,0,0,0},
	{"Armor",266,100,100,0,4 ,0,0,0,0,0,0,0,1,0,0},
	{"Plating",266,150,150,0,4 ,1,0,0,0,0,0,0,0,0,0},
	{"Ground Weapons",266,100,100,0,4 ,0,0,0,0,0,0,0,1,0,0},
	{"Air Weapons",266,100,100,0,4 ,1,0,0,0,0,0,0,0,0,0},
	{"Plasma Shields",266,200,200,0,4 ,0,0,0,0,0,0,0,1,0,0},
	{"Mineral Probe To Gas",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"Gas Probe To Mineral",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0}
	},

	//Zerg:  0: extractor,lair,Hden,evoC,queenN,spire,hive,ultraC,defilerM,greaterspire

	{
	{"Zergling",28,50,0,1,1, 0,0,0,0,0,0,0,0,0,0},
	{"Hydralisk",28,75,25,1,1, 1,0,1,0,0,0,0,0,0,0},
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
	{"Lair",100,150,100,0,0, 1,0,0,0,0,0,0,0,0,0},
	{"Hive",120,200,150,0,0, 1,1,0,0,1,0,1,0,0,0},
	{"Nydus Canal",40,150,0,0,2, 1,1,0,0,1,0,1,0,0,0},
	{"Hydralisk den",40,100,50,0,2, 1,0,0,0,0,0,0,0,0,0},
	{"Defiler mound",60,100,100,0,2, 1,1,0,0,1,0,1,0,0,0},
	{"Greater Spire",120,100,150,0,0, 1,1,0,0,1,1,1,0,0,0},
	{"Queen's Nest",60,150,100,0,2, 1,1,0,0,0,0,0,0,0,0},
	{"Evolution Chamber",40,75,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Ultralisk Cavern",80,150,200,0,2, 1,1,0,0,1,0,0,0,0,0},
	{"Spire",120,200,150,0,2, 1,1,0,0,0,0,0,0,0,0},
	{"Spawning Pool",80,200,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Creep Colony",20,75,0,0,2, 0,0,0,0,0,0,0,0,0,0},
	{"Spore Colony",20,50,0,0,0, 0,0,0,1,0,0,0,0,0,0},
	{"Sunken Colony",20,50,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Extractor",40,50,0,0,2, 0,0,0,0,0,0,0,0,0,0},//27

	{"Ventral Sacs",160,200,200,0,3, 1,1,0,0,0,0,0,0,0,0},
	{"Antennae",133,150,150,0,3, 1,1,0,0,0,0,0,0,0,0},
	{"Pneumatized Carapace",133,150,150,0,3, 1,1,0,0,0,0,0,0,0,0},
	{"Metabolic Boost",100,100,100,0,3, 1,0,0,0,0,0,0,0,0,0},
	{"Adrenal Glands",100,200,200,0,3, 1,1,0,0,1,0,1,0,0,0},
	{"Muscular Augments",100,150,150,0,3, 1,0,1,0,0,0,0,0,0,0},
	{"Grooved Spines",100,150,150,0,3, 1,0,1,0,0,0,0,0,0,0},
	{"Gamete Meiosis",166,150,150,0,3, 1,1,0,0,1,0,0,0,0,0},
	{"Metasynaptic node",166,150,150,0,3, 1,1,0,0,1,0,1,0,1,0},
	{"Chitinous Plating",133,150,150,0,3, 1,1,0,0,1,0,1,1,0,0},
	{"Anabolic Synthesis",133,200,200,0,3, 1,1,0,0,1,0,1,1,0,0},

	{"Burrowing",80,100,100,0,3, 1,0,0,0,0,0,0,0,0,0},
	{"Spawn Broodling",80,100,100,0,3, 1,1,0,0,1,0,0,0,0,0},
	{"Plague",100,200,200,0,3, 1,1,0,0,1,0,1,0,1,0},
	{"Consume",100,100,100,0,3, 1,1,0,0,1,0,1,0,1,0},
	{"Ensnare",80,100,100,0,3, 1,1,0,0,1,0,0,0,0,0},
	{"Lurker Aspect",120,200,200,0,3, 1,1,1,0,0,0,0,0,0,0},

	{"Carapace",266,150,150,0,4, 1,0,0,1,0,0,0,0,0,0},//45
	{"Flyer Carapace",266,150,150,0,4, 1,1,0,0,0,1,0,0,0,0},
	{"Melee Attacks",266,100,100,0,4, 1,0,0,1,0,0,0,0,0,0},
	{"Missile Attacks",266,100,100,0,4, 1,0,0,1,0,0,0,0,0,0},
	{"Flyer Attacks",266,100,100,0,4, 1,1,0,0,0,1,0,0,0,0},
	{"Mineral Drone to Gas",0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Gas Drone to Mineral",0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"Break up Building",0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0},
	{"NULL",0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0}
	}
};	

class RACE
{
public:
	unsigned char force[60];
	unsigned char availible[60];

	double mins,gas;
	unsigned short larvae,IP,min,n;
	unsigned short peonmins,peongas, peonbuilding, length,BuildingRunning;
	short Supply;

	unsigned char av_starport,av_factory;
	//hacked: man kann in nem kompletten Starport sowohl erforschen, als auch valkyries baun etc.

	struct Program
	{
		unsigned char order,location,supply;
		unsigned short time,mins,gas;
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
	unsigned short fitness,timer;

	virtual void Set_Goals() {};
	virtual inline void Produce() {};
	virtual void Build() {};
	virtual void Calculate() {};
	virtual void Mutate() {};
	virtual void Init() {};

	void Restart()
	{
		for(i=0;i<MAX_LENGTH;i++)
		{
			program[i].order=rand()%Max_Build_Types;//evtl ganzes Programm hier rein...
			program[i].time=20000;
//			program[i].loc=
		}
		timer=Max_Time;
		IP=0;
		length=MAX_LENGTH;
		av_starport=0;
		av_factory=0;
		afit=0;
	}
};

unsigned char building_types;

#endif