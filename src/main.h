#ifndef MAIN_H
#define MAIN_H

#define MAX_LENGTH 96
#define RUNNINGS 5
#define MAX_PLAYER 100
#define LARVA_MAX 200
#define MAX_BUILDINGS 12 // How many buildings can you built simultaneously?
#define MAX_GOALS 60


#define TERRA 0
#define PROTOSS 1
#define ZERG 2

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


#define DARK_TEMPLAR 0
#define DARK_ARCHON 1
#define PROBE 2
#define ZEALOT 3
#define DRAGOON 4
#define HIGH_TEMPLAR 5
#define ARCHON 6
#define REAVER 7
#define CORSAIR 8
#define SHUTTLE 9
#define SCOUT 10
#define ARBITER 11
#define CARRIER 12
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

#define ONE_MINERAL_PROBE_TO_GAS 58
#define ONE_GAS_PROBE_TO_MINERAL 59



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
#define PLAGUE 41
#define CONSUME 42
#define ENSNARE 43
#define LURKER_ASPECT 44

#define CARAPACE 45
#define FLYER_CARAPACE 46
#define MELEE_ATTACKS 47
#define MISSILE_ATTACKS 48
#define FLYER_ATTACKS 49

#define ONE_MINERAL_DRONE_TO_GAS 58
#define ONE_GAS_DRONE_TO_MINERAL 59

#define BREAK_UP_BUILDING 50




struct GOAL
{
	unsigned short time,what;
};

//some global variables

extern unsigned char buildable[MAX_GOALS],Build_Av[MAX_GOALS],Build_Bv[MAX_GOALS]; 
extern unsigned char Vespene_Av,Max_Build_Types,race,Variabel[MAX_GOALS];
extern unsigned short total_goals;
extern unsigned char num,Vespene_Extractors,colors,need_Gas;
extern GOAL goal[MAX_GOALS];
extern int mining[45],gasing[5];
extern unsigned char Basic[MAX_LENGTH][2],Basic_Length;

const int gasing_z[5]=
{
0,
112,
203,
320,
352
};

const int mining_z[45]=
{
0,
83,165,244,314,385,450,520,583,
645,701,765,819,853,879,911,938,
995,1041,1070,1092,1121,1143,1200,1253, // [Claw,4/4/03] changed 1149 -> 12
1266,1276,1283,1288,1292,1294,1296,1297,
1298,1298,1299,1299,1299,1299,1300,1300,
1300,1300,1300,1300
};

const int gasing_p[5]=
{
0,
117,
219,
336,
352	
};

const int mining_p[45]=
{
0,
80,159,244,314,384,447,520,584,
651,706,767,817,847,872,902,927,
1000,1050,1085,1111,1144,1173,1223,1263,
1272,1282,1287,1291,1293,1295,1297,1298,
1299,1299,1299,1299,1299,1300,1300,1300,
1300,1300,1300,1300
};

const int gasing_t[5]=
{
0,
123,
235,
352,
352
};

const int mining_t[45]={
0,
72,143,219,295,369,442,506,570, //1-8
626,682,725,767,807,847,878,909, //9-16
943,977,1012,1046,1073,1101,1142,1183, //17-24
1203,1223,1233,1243,1251,1259,1266,1274, //25-32
1277,1279,1281,1282,1283,1283,1284,1284, //33-40
1284,1284,1285,1285 //41-44
};

//TODO: Wenn eine Drone fertig is, dann muss sie erstmal hinfahren und sammeln kann also nicht sofort 15 Sekunden lang mitmachen => Bauzeit um 15 sec erhoehen

#define NAME_LENGTH 21
#define NOTHING 0
#define UNIT 1
#define BUILDING 2
#define RESEARCH 3
#define UPGRADE 4

struct Stats
{
	char name[NAME_LENGTH];
	unsigned short BT;
	int mins,gas;
	unsigned char supply;
	unsigned short type; // 0: nothing, 1: unit, 2: building (primarily for zerg!), 3: Research, 4: Upgrade
	int tmp; //fuer Upgrades erstmal nur.. 50, 75, 100

	unsigned char special;
	unsigned char prerequisite[3];
	unsigned char facility;
};

const Stats stats[3][MAX_GOALS]=
{
	{
	{"              Marine", 24, 5000,    0,1,1,    0,0, {0 ,0, 0}, BARRACKS},
	{"               Ghost", 50, 2500, 7500,1,1,    0,0, {ACADEMY ,COVERT_OPS, 0}, BARRACKS},
	{"             Vulture", 30, 7500,    0,2,1,    0,0, {FACTORY ,0, 0}, FACTORY},
	{"             Goliath", 40,10000, 5000,2,1,    0,0, {ARMORY, 0, 0}, FACTORY},
	{"          Siege Tank", 50,15000,10000,2,1,    0,0, {MACHINE_SHOP ,0, 0}, FACTORY},
	{"                 SCV", 20, 5000,    0,1,1,    0,0, {0 ,0, 0}, COMMAND_CENTER}, // 0.0 Time to Enemy da es im Lager bleibt!
	{"             Firebat", 24, 5000, 2500,1,1,    0,0, {ACADEMY ,0, 0}, BARRACKS},
	{"               Medic", 30, 5000, 2500,1,1,    0,0, {ACADEMY ,0, 0}, BARRACKS},
	{"              Wraith", 60,15000,10000,2,1,    0,0, {STARPORT ,0, 0}, STARPORT},
	{"      Science Vessel", 80,10000,22500,2,1,    0,0, {CONTROL_TOWER ,SCIENCE_FACILITY, 0}, STARPORT},
	{"            Dropship", 50,10000,10000,2,1,    0,0, {CONTROL_TOWER ,0, 0}, STARPORT},
	{"      Battle Cruiser",133,40000,30000,6,1,    0,0, {CONTROL_TOWER ,PHYSICS_LAB, 0}, STARPORT},
	{"            Valkyrie", 50,25000,12500,3,1,    0,0, {CONTROL_TOWER ,ARMORY, 0}, STARPORT},
	{"      Command Center",120,40000,    0,2,0,    0,0, {0 ,0, 0}, 0},
	{"        Supply Depot", 40,10000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"            Refinery", 40,10000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"            Barracks", 80,15000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"             Academy", 80,15000,    0,0,2,    0,0, {BARRACKS ,0, 0}, 0},
	{"             Factory", 80,20000,10000,0,2,    0,0, {BARRACKS ,0, 0}, 0},
	{"            Starport", 70,15000,10000,0,2,    0,0, {FACTORY ,0, 0}, 0},
	{"    Science Facility", 60,10000,15000,0,2,    0,0, {STARPORT ,0, 0}, 0},
	{"     Engineering Bay", 60,12500,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"              Armory", 80,10000, 5000,0,2,    0,0, {FACTORY ,0, 0}, 0},
	{"      Missile Turret", 30, 7500,    0,0,2,    0,0, {ENGINEERING_BAY ,0, 0}, 0},
	{"              Bunker", 30,10000,    0,0,2,    0,0, {BARRACKS ,0, 0}, 0},
	{"      Comsat Station", 40, 5000, 5000,0,0,    0,0, {ACADEMY ,0, 0}, COMMAND_CENTER},
	{"        Nuclear Silo", 40,10000,10000,0,0,    0,0, {COVERT_OPS ,0, 0}, COMMAND_CENTER},
	{"       Control Tower", 80, 5000, 5000,0,0,    0,0, {0 ,0, 0}, STARPORT},
	{"          Covert Ops", 40, 5000, 5000,0,0,    0,0, {0 ,0, 0}, SCIENCE_FACILITY},
	{"         Physics Lab", 40, 5000, 5000,0,0,    0,0, {0 ,0, 0}, SCIENCE_FACILITY},
	{"        Machine Shop", 40, 5000, 5000,0,0,    0,0, {0 ,0, 0}, FACTORY},
	{"          Stim Packs", 80,10000,10000,0,3,    0,0, {0 ,0, 0}, ACADEMY},
	{"            Lockdown",100,20000,20000,0,3,    0,0, {0 ,0, 0}, COVERT_OPS},
	{"       EMP Shockwave",120,20000,20000,0,3,    0,0, {0 ,0, 0}, SCIENCE_FACILITY},
	{"        Spider Mines", 80,10000,10000,0,3,    0,0, {0 ,0, 0}, MACHINE_SHOP},
	{"          Siege Mode", 80,15000,15000,0,3,    0,0, {0 ,0, 0}, MACHINE_SHOP},
	{"           Irradiate", 80,20000,20000,0,3,    0,0, {0 ,0, 0}, SCIENCE_FACILITY},
	{"          Yamato Gun",120,10000,10000,0,3,    0,0, {0 ,0, 0}, PHYSICS_LAB},
	{"      Cloaking Field",100,15000,15000,0,3,    0,0, {0 ,0, 0}, CONTROL_TOWER},
	{"  Personnel Cloaking", 80,10000,10000,0,3,    0,0, {0 ,0, 0}, COVERT_OPS},
	{"         Restoration", 80,10000,10000,0,3,    0,0, {0 ,0, 0}, ACADEMY},
	{"       Optical Flare",120,10000,10000,0,3,    0,0, {0 ,0, 0}, ACADEMY},
	{"        U-238 Shells",100,15000,15000,0,3,    0,0, {0 ,0, 0}, ACADEMY},
	{"       Ion Thrusters",100,10000,10000,0,3,    0,0, {0 ,0, 0}, MACHINE_SHOP},
	{"       Titan Reactor",166,15000,15000,0,3,    0,0, {0 ,0, 0}, SCIENCE_FACILITY},
	{"     Ocular Implants",166,10000,10000,0,3,    0,0, {0 ,0, 0}, COVERT_OPS},
	{"     Moebius Reactor",166,20000,20000,0,3,    0,0, {0 ,0, 0}, COVERT_OPS},
	{"      Apollo Reactor",166,20000,20000,0,3,    0,0, {0 ,0, 0}, CONTROL_TOWER},
	{"    Colossus Reactor",166,15000,15000,0,3,    0,0, {0 ,0, 0}, PHYSICS_LAB},
	{"    Caduceus Reactor",166,15000,15000,0,3,    0,0, {0 ,0, 0}, ACADEMY},
	{"      Charon Booster",133,10000,10000,0,3,    0,0, {0 ,0, 0}, MACHINE_SHOP},
	{"      Infantry Armor",266,10000,10000,0,4, 7500,0, {0 ,0, 0}, ENGINEERING_BAY},
	{"    Infantry Weapons",266,10000,10000,0,4, 7500,0, {0 ,0, 0}, ENGINEERING_BAY},
	{"     Vehicle Plating",266,10000,10000,0,4, 7500,0, {0 ,0, 0}, ARMORY},
	{"     Vehicle Weapons",266,10000,10000,0,4, 7500,0, {0 ,0, 0}, ARMORY},
	{"        Ship Plating",266,15000,15000,0,4, 7500,0, {0 ,0, 0}, ARMORY},
	{"        Ship Weapons",266,10000,10000,0,4, 5000,0, {0 ,0, 0}, ARMORY},
	{"     Nuclear Warhead",100,20000,20000,8,0,    0,0, {0 ,0, 0}, NUCLEAR_SILO},
	{"  Mineral SCV to Gas",  0,	0,	  0,0,0,    0,0, {0 ,0, 0}, 0},
	{"  Gas SCV to Mineral",  0,	0,	  0,0,0,    0,0, {0 ,0, 0}, 0}
},
	
	{
	{"        Dark Templar", 50,12500,10000,2,1,    0,0, {TEMPLAR_ARCHIVES ,0, 0}, GATEWAY},
	{"         Dark Archon", 20,    0,    0,0,1,    0,0, {0 ,0, 0}, 0},//~~
	{"               Probe", 20, 5000,    0,1,1,    0,0, {0 ,0, 0}, NEXUS},
	{"              Zealot", 40,10000,    0,2,1,    0,0, {0 ,0, 0}, GATEWAY},
	{"             Dragoon", 50,12500, 5000,2,1,    0,0, {CYBERNETICS_CORE ,0, 0}, GATEWAY},
	{"        High Templar", 50, 5000,15000,2,1,    0,0, {TEMPLAR_ARCHIVES ,0, 0}, GATEWAY},
	{"              Archon", 20,    0,    0,0,1,    0,0, {0 ,0, 0}, 0},//~~
	{"              Reaver", 70,20000,10000,4,1,    0,0, {ROBOTICS_SUPPORT_BAY ,0, 0}, ROBOTICS_FACILITY}, 
	{"             Corsair", 40,15000,10000,2,1,    0,0, {0 ,0, 0}, STARGATE},
	{"             Shuttle", 60,20000,    0,2,1,    0,0, {0 ,0, 0}, ROBOTICS_FACILITY},
	{"               Scout", 80,27500,12500,3,1,    0,0, {0 ,0, 0}, STARGATE},
	{"             Arbiter",160,10000,35000,4,1,    0,0, {ARBITER_TRIBUNAL ,0, 0}, STARGATE},
	{"             Carrier",140,35000,25000,6,1,    0,0, {FLEET_BEACON ,0, 0}, STARGATE},
	{"            Observer", 40, 2500, 7500,1,1,    0,0, {OBSERVATORY ,0, 0}, ROBOTICS_FACILITY},
	{"               Nexus",120,40000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"   Robotics Facility", 80,20000,20000,0,2,    0,0, {CYBERNETICS_CORE ,0, 0}, 0},
	{"               Pylon", 30,10000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"         Assimilator", 40,10000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"         Observatory", 30, 5000,10000,0,2,    0,0, {ROBOTICS_FACILITY ,0, 0}, 0},
	{"             Gateway", 60,15000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"       Photon Cannon", 50,15000,    0,0,2,    0,0, {FORGE ,0, 0}, 0},
	{"    Cybernetics Core", 60,20000,    0,0,2,    0,0, {GATEWAY ,0, 0}, 0},
	{"     Citadel Of Adun", 60,15000,10000,0,2,    0,0, {CYBERNETICS_CORE ,0, 0}, 0},
	{"    Templar Archives", 60,15000,20000,0,2,    0,0, {CITADEL_OF_ADUN ,0, 0}, 0},
	{"               Forge", 40,15000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"            Stargate", 70,15000,15000,0,2,    0,0, {CYBERNETICS_CORE ,0, 0}, 0},
	{"        Fleet Beacon", 60,30000,20000,0,2,    0,0, {STARGATE ,0, 0}, 0},
	{"    Arbiter Tribunal", 60,20000,15000,0,2,    0,0, {TEMPLAR_ARCHIVES ,STARGATE, 0}, 0},
	{"Robotics Support Bay", 30,15000,10000,0,2,    0,0, {ROBOTICS_FACILITY ,0, 0}, 0},
	{"      Shield Battery", 30,10000,    0,0,2,    0,0, {GATEWAY ,0, 0}, 0},
	{"       Psionic Storm",120,20000,20000,0,3,    0,0, {0 ,0, 0}, TEMPLAR_ARCHIVES},
	{"       Hallucination", 80,15000,15000,0,3,    0,0, {0 ,0, 0}, TEMPLAR_ARCHIVES},
	{"              Recall",120,15000,15000,0,3,    0,0, {0 ,0, 0}, ARBITER_TRIBUNAL},
	{"        Stasis Field",100,15000,15000,0,3,    0,0, {0 ,0, 0}, ARBITER_TRIBUNAL},
	{"      Disruption Web", 80,20000,20000,0,3,    0,0, {0 ,0, 0}, FLEET_BEACON},
	{"        Mind Control",120,20000,20000,0,3,    0,0, {0 ,0, 0}, TEMPLAR_ARCHIVES},
	{"           Maelstrom",100,10000,10000,0,3,    0,0, {0 ,0, 0}, TEMPLAR_ARCHIVES},
	{"  Singularity Charge",166,15000,15000,0,3,    0,0, {0 ,0, 0}, CYBERNETICS_CORE},
	{"    Leg Enhancements",133,15000,15000,0,3,    0,0, {0 ,0, 0}, CITADEL_OF_ADUN},
	{"       Scarab Damage",166,20000,20000,0,3,    0,0, {0 ,0, 0}, ROBOTICS_SUPPORT_BAY},
	{"     Reaver Capacity",166,20000,20000,0,3,    0,0, {0 ,0, 0}, ROBOTICS_SUPPORT_BAY},
	{"      Gravitic Drive",166,20000,20000,0,3,    0,0, {0 ,0, 0}, ROBOTICS_SUPPORT_BAY},
	{"        Sensor Array",133,15000,15000,0,3,    0,0, {0 ,0, 0}, OBSERVATORY},
	{"   Gravitic Boosters",133,15000,15000,0,3,    0,0, {0 ,0, 0}, OBSERVATORY},
	{"    Khaydarin Amulet",166,15000,15000,0,3,    0,0, {0 ,0, 0}, TEMPLAR_ARCHIVES},
	{"       Apial Sensors",166,10000,10000,0,3,    0,0, {0 ,0, 0}, FLEET_BEACON},
	{"  Gravitic Thrusters",166,20000,20000,0,3,    0,0, {0 ,0, 0}, FLEET_BEACON},
	{"    Carrier Capacity",100,10000,10000,0,3,    0,0, {0 ,0, 0}, FLEET_BEACON},
	{"      Khaydarin Core",166,15000,15000,0,3,    0,0, {0 ,0, 0}, ARBITER_TRIBUNAL},
	{"         Argus Jewel",166,10000,10000,0,3,    0,0, {0 ,0, 0}, FLEET_BEACON},
	{"      Argus Talisman",166,15000,15000,0,3,    0,0, {0 ,0, 0}, TEMPLAR_ARCHIVES},
	{"               Armor",266,10000,10000,0,4, 7500,0, {0 ,0, 0}, FORGE},
	{"             Plating",266,15000,15000,0,4, 7500,0, {0 ,0, 0}, CYBERNETICS_CORE},
	{"      Ground Weapons",266,10000,10000,0,4, 5000,0, {0 ,0, 0}, FORGE},
	{"         Air Weapons",266,10000,10000,0,4, 7500,0, {0 ,0, 0}, CYBERNETICS_CORE},
	{"      Plasma Shields",266,20000,20000,0,4,10000,0, {0 ,0, 0}, FORGE},
	{"Mineral Probe To Gas",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"Gas Probe To Mineral",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0}
	},
	
	{
	{"            Zergling", 28, 5000,    0,1,1,    0,0, {SPAWNING_POOL ,0, 0}, 0},
	{"           Hydralisk", 28, 7500, 2500,1,1,    0,0, {HYDRALISK_DEN ,0, 0}, 0},
	{"           Ultralisk", 60,20000,20000,6,1,    0,0, {ULTRALISK_CAVERN ,0, 0}, 0},
	{"               Drone", 23, 5000,    0,1,1,    0,0, {0 ,0, 0}, 0},
	{"             Defiler", 50, 5000,15000,2,1,    0,0, {DEFILER_MOUND ,0, 0}, 0},
	{"              Lurker", 40, 5000,10000,2,0,    0,0, {HYDRALISK_DEN ,0, 0}, 0},
	{"            Overlord", 40,10000,    0,0,1,    0,0, {0 ,0, 0}, 0},
	{"            Mutalisk", 40,10000,10000,2,1,    0,0, {SPIRE ,0, 0}, 0},
	{"            Guardien", 40, 5000,10000,0,0,    0,0, {GREATER_SPIRE ,0, 0}, 0},
	{"               Queen", 50,10000,10000,2,1,    0,0, {QUEENS_NEST ,0, 0}, 0},
	{"             Scourge", 30, 2500, 7500,1,1,    0,0, {SPIRE ,0, 0}, 0},
	{"            Devourer", 40,10000, 5000,0,0,    0,0, {GREATER_SPIRE ,0, 0}, 0}, //~~
	{"            Hatchery",120,30000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"                Lair",100,15000,10000,0,0,    0,0, {SPAWNING_POOL ,0, 0}, HATCHERY}, //~~
	{"                Hive",120,20000,15000,0,0,    0,0, {QUEENS_NEST ,0, 0}, LAIR},
	{"         Nydus Canal", 40,15000,    0,0,2,    0,0, {HIVE ,0, 0}, 0},
	{"       Hydralisk den", 40,10000, 5000,0,2,    0,0, {SPAWNING_POOL ,0, 0}, 0},
	{"       Defiler mound", 60,10000,10000,0,2,    0,0, {HIVE ,0, 0}, 0},
	{"       Greater Spire",120,10000,15000,0,0,    0,0, {HIVE ,0, 0}, SPIRE}, //~~
	{"        Queen's Nest", 60,15000,10000,0,2,    0,0, {LAIR ,0, 0}, 0},
	{"   Evolution Chamber", 40, 7500,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"    Ultralisk Cavern", 80,15000,20000,0,2,    0,0, {HIVE ,0, 0}, 0},
	{"               Spire",120,20000,15000,0,2,    0,0, {LAIR ,0, 0}, 0},
	{"       Spawning Pool", 80,20000,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"        Creep Colony", 20, 7500,    0,0,2,    0,0, {0 ,0, 0}, 0},
	{"        Spore Colony", 20, 5000,    0,0,0,    0,0, {0 ,0, 0}, CREEP_COLONY},
	{"       Sunken Colony", 20, 5000,    0,0,0,    0,0, {0 ,0, 0}, CREEP_COLONY},
	{"           Extractor", 40, 5000,    0,0,2,    0,0, {0 ,0, 0}, 0},//27
	{"        Ventral Sacs",160,20000,20000,0,3,    0,0, {0 ,0, 0}, 0}, //~~
	{"            Antennae",133,15000,15000,0,3,    0,0, {0 ,0, 0}, 0},
	{"Pneumatized Carapace",133,15000,15000,0,3,    0,0, {0 ,0, 0}, 0},
	{"     Metabolic Boost",100,10000,10000,0,3,    0,0, {0 ,0, 0}, SPAWNING_POOL},
	{"      Adrenal Glands",100,20000,20000,0,3,    0,0, {0 ,0, 0}, SPAWNING_POOL},
	{"   Muscular Augments",100,15000,15000,0,3,    0,0, {0 ,0, 0}, HYDRALISK_DEN},
	{"      Grooved Spines",100,15000,15000,0,3,    0,0, {0 ,0, 0}, HYDRALISK_DEN},
	{"      Gamete Meiosis",166,15000,15000,0,3,    0,0, {0 ,0, 0}, QUEENS_NEST},
	{"   Metasynaptic node",166,15000,15000,0,3,    0,0, {0 ,0, 0}, 0},
	{"   Chitinous Plating",133,15000,15000,0,3,    0,0, {0 ,0, 0}, ULTRALISK_CAVERN},
	{"  Anabolic Synthesis",133,20000,20000,0,3,    0,0, {0 ,0, 0}, ULTRALISK_CAVERN},
	{"           Burrowing", 80,10000,10000,0,3,    0,0, {0 ,0, 0}, 0}, //~~
	{"     Spawn Broodling", 80,10000,10000,0,3,    0,0, {0 ,0, 0}, QUEENS_NEST},
	{"              Plague",100,20000,20000,0,3,    0,0, {0 ,0, 0}, DEFILER_MOUND},
	{"             Consume",100,10000,10000,0,3,    0,0, {0 ,0, 0}, DEFILER_MOUND},
	{"             Ensnare", 80,10000,10000,0,3,    0,0, {0 ,0, 0}, QUEENS_NEST},
	{"       Lurker Aspect",120,20000,20000,0,3,    0,0, {0 ,0, 0}, HYDRALISK_DEN}, //~~
	{"            Carapace",266,15000,15000,0,4, 7500,0, {0 ,0, 0}, EVOLUTION_CHAMBER},
	{"      Flyer Carapace",266,15000,15000,0,4, 7500,0, {0 ,0, 0}, SPIRE},//~~
	{"       Melee Attacks",266,10000,10000,0,4, 5000,0, {0 ,0, 0}, EVOLUTION_CHAMBER},
	{"     Missile Attacks",266,10000,10000,0,4, 5000,0, {0 ,0, 0}, EVOLUTION_CHAMBER},
	{"       Flyer Attacks",266,10000,10000,0,4, 7500,0, {0 ,0, 0}, SPIRE},//~~
	{"Mineral Drone to Gas",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"Gas Drone to Mineral",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"   Break up Building",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0},
	{"                NULL",  0,    0,    0,0,0,    0,0, {0 ,0, 0}, 0}
	} 
};








#endif


