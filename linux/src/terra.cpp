#include "terra.h"
#include "settings.h"

#define BUILDING_TYPES_TERRA 60

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

	void Player_Terra::Set_Goals()
	{
		unsigned char i,j;
		long Need_Gas;
		building_types=BUILDING_TYPES_TERRA;
		for(j=0;j<6;j++) // Nuclear Warhead needs 6 steps :)
		for(i=0;i<BUILDING_TYPES_TERRA;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;
				switch(i)
				{
					case BUNKER:
					case MARINE:
					case ACADEMY:
					case FACTORY:
						if(goal[BARRACKS].what==0) goal[BARRACKS].what=1;break;
					
					case ARMORY:
					case MACHINE_SHOP:
					case STARPORT:
					case VULTURE:
						if(goal[FACTORY].what==0) goal[FACTORY].what=1;break;
					case GOLIATH:
						if(goal[ARMORY].what==0) goal[ARMORY].what=1;break;
					case ION_THRUSTERS:
					case TANK_SIEGE_MODE:
					case CHARON_BOOSTER:
					case SPIDER_MINES:
					case SIEGE_TANK:
						if(goal[MACHINE_SHOP].what==0) goal[MACHINE_SHOP].what=1;break;
						
					case GHOST:
						if(goal[COVERT_OPS].what==0) goal[COVERT_OPS].what=1;	
					case COMSAT_STATION:
					case MEDIC:
					case FIREBAT:
					case STIM_PACKS:
					case RESTORATION:
					case OPTICAL_FLARE:
					case U238_SHELLS:
					case CADUCEUS_REACTOR:
						if(goal[ACADEMY].what==0) goal[ACADEMY].what=1;break;
					case MOEBIUS_REACTOR:
					case PERSONNEL_CLOAKING:
					case LOCKDOWN:
					case NUCLEAR_SILO:
					case OCULAR_IMPLANTS:
						if(goal[COVERT_OPS].what==0) goal[COVERT_OPS].what=1;break;
					case CLOAKING_FIELD:
					case APOLLO_REACTOR:
					case SCIENCE_VESSEL:if((i==SCIENCE_VESSEL)&&(goal[SCIENCE_FACILITY].what==0)) goal[SCIENCE_FACILITY].what=1;
					case DROPSHIP:	
					case BATTLE_CRUISER:if((i==BATTLE_CRUISER)&&(goal[PHYSICS_LAB].what==0)) goal[PHYSICS_LAB].what=1;
					case VALKYRIE:if((i==VALKYRIE)&&(goal[ARMORY].what==0)) goal[ARMORY].what=1;
						if(goal[CONTROL_TOWER].what==0) goal[CONTROL_TOWER].what=1;break;
					case SCIENCE_FACILITY:
					case CONTROL_TOWER:
					case WRAITH:
						if(goal[STARPORT].what==0) goal[STARPORT].what=1;break;
					case IRRADIATE:
					case EMP_SHOCKWAVE:
					case TITAN_REACTOR:
					case PHYSICS_LAB:
					case COVERT_OPS:
						if(goal[SCIENCE_FACILITY].what==0) goal[SCIENCE_FACILITY].what=1;break;
					case YAMATO_GUN:
					case COLOSSUS_REACTOR:
						if(goal[PHYSICS_LAB].what==0) goal[PHYSICS_LAB].what=1;break;
					case INFANTRY_ARMOR:
					case INFANTRY_WEAPONS:if((goal[i].what>1)&&(goal[SCIENCE_FACILITY].what==0)) goal[SCIENCE_FACILITY].what=1;
					case MISSILE_TURRET:
						if(goal[ENGINEERING_BAY].what==0) goal[ENGINEERING_BAY].what=1;break;
					case VEHICLE_PLATING:
					case VEHICLE_WEAPONS:
					case SHIP_PLATING:
					case SHIP_WEAPONS:
						if((goal[i].what>1)&&(goal[SCIENCE_FACILITY].what==0)) goal[SCIENCE_FACILITY].what=1;
						if(goal[ARMORY].what==0) goal[ARMORY].what=1;break;
					case NUCLEAR_WARHEAD:
						if(goal[NUCLEAR_SILO].what<goal[NUCLEAR_WARHEAD].what) goal[NUCLEAR_SILO].what=goal[NUCLEAR_WARHEAD].what;
						break;					
				}
			}

		Ziel[SCV]=1;
		Ziel[COMMAND_CENTER]=1;
		Ziel[SUPPLY_DEPOT]=1;

		Need_Gas=0;

		for(i=0;i<BUILDING_TYPES_TERRA;i++)
			Need_Gas+=(goal[i].what*stats[0][i].gas);

		if(Need_Gas>0)
		{
			Ziel[REFINERY]=1;
			if(goal[REFINERY].what==0) goal[REFINERY].what=1;
			Ziel[ONE_MINERAL_SCV_TO_GAS]=1;
			Ziel[ONE_GAS_SCV_TO_MINERAL]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_TERRA;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
		goal[ONE_MINERAL_SCV_TO_GAS].what=0; // Just to be sure :)
		goal[ONE_GAS_SCV_TO_MINERAL].what=0;		
	}
	
// Test whether the item can be build (minerals, gas, supply, buildings, ...)
	void Player_Terra::Build(unsigned char what)
	{
		unsigned char m;
		suc=0;
			if(what==ONE_MINERAL_SCV_TO_GAS)
			{
				if(force[REFINERY]>0)
				{
					if(peonmins>0)
					{
						ok=1;
						peonmins--;
						peongas++;
						program[IP].built=1;
					} else suc=6;
				};	
			}
			else
			if(what==ONE_GAS_SCV_TO_MINERAL)
			{
				if(peongas>0)
				{
					ok=1;
					peongas--;
					peonmins++;
					program[IP].built=1;
				} else suc=6;
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
		
			if( (Supply<stats[0][what].supply) && (stats[0][what].supply>0)) suc=4;
			else 
			if ( mins<stats[0][what].mins+(stats[race][what].type==4)*force[what]*stats[race][what].tmp) suc=2;
			else
			if ( gas<stats[0][what].gas+(stats[race][what].type==4)*force[what]*stats[race][what].tmp) suc=3;
			else if	(peonmins+peongas<1*(stats[0][what].type==2)) suc=6;
			else //Check whether this is already researched/upgraded
				
			if(
			 (stats[0][what].type>=3)&&
			 ((stats[0][what].type!=4)||(force[what]>=3)||(availible[what]!=1))&&
			 ((stats[0][what].type!=3)||(force[what]!=0)||(availible[what]!=1))
			) suc=7; 
			else if(nr<255)
		{
			switch(what) 
	// TODO: Maybe optimize the order of checks to improve speed
			{
				case MARINE:
					if(availible[BARRACKS]>0) 
					{
						Produce(what);
						availible[BARRACKS]--;
					};break;
				case GHOST:
					if((force[ACADEMY]>0)&&(force[COVERT_OPS]>0)&&(availible[BARRACKS]>0))
					{
						Produce(what);
						availible[BARRACKS]--;
					};break;
				case VULTURE:
					if((availible[FACTORY]>0)||(av_factory>0)) 
					{
						Produce(what);
						if(availible[FACTORY]>0)
							availible[FACTORY]--;
						else av_factory--;
					};break;
				case GOLIATH:
					if((force[ARMORY]>0)&&((availible[FACTORY]>0)||(av_factory>0))) 
					{
						Produce(what);
						if(availible[FACTORY]>0)
							availible[FACTORY]--;
						else av_factory--;
					};break;
				case SIEGE_TANK:
					if(av_factory>0) 
					{
						Produce(what);
						av_factory--;
					};break;
				case SCV:
					if(availible[COMMAND_CENTER]>0)
					{
						Produce(what);
						availible[COMMAND_CENTER]--;
					};break;
				case FIREBAT:
				case MEDIC:
					if((force[BARRACKS]>0)&&(force[ACADEMY]>0)&&(availible[BARRACKS]>0)) 
					{
						Produce(what);
						availible[BARRACKS]--;
					};break;
				case WRAITH:
					if((availible[STARPORT]>0)||(av_starport>0)) 
					{
						Produce(what);
						if(availible[STARPORT]>0) 								availible[STARPORT]--;
						else av_starport--;
					};break;
				case SCIENCE_VESSEL:
					if((force[SCIENCE_FACILITY]>0)&&(av_starport>0))
					{
						Produce(what);
						av_starport--;
					};break;
				case DROPSHIP:
					if(av_starport>0)
					{
						Produce(what);
						av_starport--;
					};break;
				case BATTLE_CRUISER:
					if((force[PHYSICS_LAB]>0)&&(av_starport>0))
					{
						Produce(what);
						av_starport--;
					};break;
				case VALKYRIE:
					if((force[ARMORY]>0)&&(av_starport>0))
					{
						Produce(what);
						av_starport--;
					};break;
				case COMMAND_CENTER:
				case SUPPLY_DEPOT:
					      Produce(what);
					      break;
				case REFINERY:
					if(Vespene_Av>0) 
					{ 
						Vespene_Av--;
						Vespene_Extractors++;
						Produce(what);
					};break;
				case BARRACKS:
					Produce(what);break;
				case ACADEMY:
				case FACTORY:
					if(force[BARRACKS]>0) Produce(what);
					break;
				case STARPORT:
					if(force[FACTORY]>0) Produce(what);
					break;
				case SCIENCE_FACILITY:
					if(force[STARPORT]>0) Produce(what);
					break;
				case ENGINEERING_BAY:
					Produce(what);
					break;
				case ARMORY:
					if(force[FACTORY]>0) Produce(what);
					break;
				case MISSILE_TURRET:
					if(force[ENGINEERING_BAY]>0) Produce(what);
					break;
				case BUNKER:
					if(force[BARRACKS]>0) Produce(what);
					break;
				case COMSAT_STATION:
					if((force[COMMAND_CENTER]>force[COMSAT_STATION]+force[NUCLEAR_SILO])&&(availible[COMMAND_CENTER]>0)&&(force[ACADEMY]>0)) 
					{
						Produce(what);
						availible[COMMAND_CENTER]--;
					};break;
				case NUCLEAR_SILO:
					if((force[COMMAND_CENTER]>force[COMSAT_STATION]+force[NUCLEAR_SILO])&&(availible[COMMAND_CENTER]>0)&&(force[COVERT_OPS]>0))
					{
						Produce(what);
						availible[COMMAND_CENTER]--;
					};break;
				case CONTROL_TOWER:
					if((force[STARPORT]>force[CONTROL_TOWER])&&(availible[STARPORT]>0)) 
					{
						Produce(what);
						availible[STARPORT]--;
					};break;
				case COVERT_OPS:
				case PHYSICS_LAB:
					if((force[SCIENCE_FACILITY]>force[COVERT_OPS]+force[PHYSICS_LAB])&&(availible[SCIENCE_FACILITY]>0)) 
					{
						Produce(what);
						availible[SCIENCE_FACILITY]--;
					};break;

				case MACHINE_SHOP:
					if((force[FACTORY]>force[MACHINE_SHOP])&&(availible[FACTORY]>0)) 
					{
						Produce(what);
			 			availible[FACTORY]--;
					};break;

				
				
				case CHARON_BOOSTER:
				case SPIDER_MINES:
				case TANK_SIEGE_MODE:
				case ION_THRUSTERS:
					if(availible[MACHINE_SHOP]>0)
					{
						Produce(what);
						availible[MACHINE_SHOP]--;
					};break;

				case TITAN_REACTOR:
				case EMP_SHOCKWAVE:
				case IRRADIATE:
					if(availible[SCIENCE_FACILITY]>0) 
					{
						Produce(what);
						availible[SCIENCE_FACILITY]--;
					};break;
				
				case OCULAR_IMPLANTS:
				case LOCKDOWN:
				case MOEBIUS_REACTOR:
				case PERSONNEL_CLOAKING:
					if(availible[COVERT_OPS]>0) 
					{
						Produce(what);
						availible[COVERT_OPS]--;
					};break;
				
				case CADUCEUS_REACTOR:
				case U238_SHELLS:
				case STIM_PACKS:
				case RESTORATION:
				case OPTICAL_FLARE:
					
					if(availible[ACADEMY]>0) 
					{
						Produce(what);
						availible[ACADEMY]--;
					 };break;

				case COLOSSUS_REACTOR:
				case YAMATO_GUN:
					if(availible[PHYSICS_LAB]>0)
					{
						Produce(what);
						availible[PHYSICS_LAB]--;
					};break;

				case APOLLO_REACTOR:
				case CLOAKING_FIELD:
						if(availible[CONTROL_TOWER]>0)
					{
						Produce(what);
						availible[CONTROL_TOWER]--;
					};break;
				case INFANTRY_ARMOR:
				case INFANTRY_WEAPONS:
						    if((availible[ENGINEERING_BAY]>0)&&((force[what]==0)||(force[SCIENCE_FACILITY]>0))) 
									   {
											Produce(what);
	availible[ENGINEERING_BAY]--;
									   };break;

				case VEHICLE_PLATING:
				case VEHICLE_WEAPONS:
				case SHIP_PLATING:
				case SHIP_WEAPONS:
					if((availible[ARMORY]>0)&&((force[what]==0)|| ((force[what]>0)&&(force[SCIENCE_FACILITY]>0)))) 
					{
					   Produce(what);
					   availible[ARMORY]--;
					  };break;
				case NUCLEAR_WARHEAD:
					if(availible[NUCLEAR_SILO]>0)
					{
						Produce(what);
						availible[NUCLEAR_SILO]--;
					};break;
				default:break;
			}
		if((ok==1)&&(stats[race][what].type==2))				        {
			building[nr].RB+=3; //3 in game seconds to reach the building site
			if(peonmins>0)
				peonmins--;
			else if(peongas>0)
				peongas--;
			peonbuilding++;
	         }
		}
	}
			if((suc==0)&&(ok==0))
				suc=1;
	}

// Do one run, go through one build order and record the results	
	void Player_Terra::Calculate()
	{
		unsigned char tt,j,tSupply,tMax_Supply;
		ready=0;
		timer=0;
		harvested_gas=0;
		harvested_mins=0;
		
		Vespene_Av=setup.Vespene_Geysirs;		
		Vespene_Extractors=0;
		tt=0;

		while((timer<setup.Max_Time) && (ready==0) && (IP<MAX_LENGTH))
		{
			tSupply=Supply;// for the log file
			tMax_Supply=Max_Supply;
			BuildingRunning=0;

			Harvest_Resources();
			
			for(j=0;j<MAX_BUILDINGS;j++)
			{
				if(building[j].RB>0)
				{
					BuildingRunning=1;
					building[j].RB--;
					if(building[j].RB==0)
					{
						if((setup.Time_to_Enemy>0)&&(building[j].type<COMMAND_CENTER)&&(building[j].on_the_run==0)&&(building[j].type!=SCV)&&(building[j].type!=DROPSHIP))
						{
							building[j].on_the_run=1;
							if(building[j].type==VULTURE)
							{
								if(force[ION_THRUSTERS]>0)
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
								else
									building[j].RB+=setup.Time_to_Enemy;
							}
							else if((building[j].type==MARINE)||(building[j].type==FIREBAT))
							{
								if((force[STIM_PACKS]>0)&&(force[MARINE]<4*force[MEDIC]))
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
								else
									building[j].RB+=setup.Time_to_Enemy;
							}
							else if(building[j].type==WRAITH)
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
							else if((building[j].type<SIEGE_TANK)||(building[j].type==MEDIC)||(building[j].type==SCV)||(building[j].type==GOLIATH)||(building[j].type==GHOST)||(building[j].type==VALKYRIE)||(building[j].type==SCIENCE_VESSEL))
								building[j].RB+=setup.Time_to_Enemy;
							else if(building[j].type==BATTLE_CRUISER)
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
						}
						switch(building[j].type)
						{
							case SCV:peonmins++;availible[COMMAND_CENTER]++;break;
							case SUPPLY_DEPOT:Supply+=8;Max_Supply+=8;break;
							case COMMAND_CENTER:Supply+=10;Max_Supply+=8;break;
							case REFINERY:break;
							case MARINE:
							case FIREBAT:
							case MEDIC:
							case GHOST:availible[BARRACKS]++;break;
							case CONTROL_TOWER:av_starport++;break;
							case MACHINE_SHOP:av_factory++;break;
							case SIEGE_TANK:av_factory++;break;
							case VULTURE:
							case GOLIATH:if(availible[FACTORY]<force[FACTORY]-force[MACHINE_SHOP]) availible[FACTORY]++;
								else av_factory++;break;
							case SCIENCE_VESSEL:
							case BATTLE_CRUISER:
							case DROPSHIP:
							case VALKYRIE:av_starport++;break;
							case WRAITH:if(availible[STARPORT]<force[STARPORT]-force[CONTROL_TOWER]) availible[STARPORT]++;
								else av_starport++;break;
	
							case STIM_PACKS:
							case U238_SHELLS:
							case RESTORATION:
							case OPTICAL_FLARE:
							case CADUCEUS_REACTOR:availible[ACADEMY]++;break;


							case LOCKDOWN:
							case PERSONNEL_CLOAKING:
							case MOEBIUS_REACTOR:
							case OCULAR_IMPLANTS:availible[COVERT_OPS]++;break;

							case EMP_SHOCKWAVE:
							case IRRADIATE:
							case TITAN_REACTOR:availible[SCIENCE_FACILITY]++;break;

							case SPIDER_MINES:
							case TANK_SIEGE_MODE:
							case ION_THRUSTERS:
							case CHARON_BOOSTER:availible[MACHINE_SHOP]++;break;

							case YAMATO_GUN:
							case COLOSSUS_REACTOR:availible[PHYSICS_LAB]++;break;

							case CLOAKING_FIELD:
							case APOLLO_REACTOR:availible[CONTROL_TOWER]++;break;

							case INFANTRY_ARMOR:
							case INFANTRY_WEAPONS:availible[ENGINEERING_BAY]++;availible[building[j].type]=1;break;
							case COMSAT_STATION:
							case NUCLEAR_SILO:availible[COMMAND_CENTER]++;break;
							case COVERT_OPS:
							case PHYSICS_LAB:availible[SCIENCE_FACILITY]++;break;
							case VEHICLE_PLATING:
							case VEHICLE_WEAPONS:
							case SHIP_PLATING:
							case SHIP_WEAPONS:availible[ARMORY]++;availible[building[j].type]=1;break;
							default:break;
						}
						if(building[j].RB==0)
						{
							CheckReady(j);
							if(stats[0][building[j].type].type==2) 
							{
								peonmins++;
								peonbuilding--;
							}
						}
					}
				}
			}
			
			tt++;
			ok=0;
			Build(Build_Av[program[IP].order]);
			if(suc>0) program[IP].success=suc;
			if((ok==1)||(tt>267))
			{
				if(tt<=267) program[IP].time=timer;
				else 
				{
					program[IP].success=8;
					program[IP].time=20000;
				}
				program[IP].need_Supply=tMax_Supply-tSupply;
				program[IP].have_Supply=tMax_Supply;
				tt=0;
				IP++;
			}
		//Scoutpeon
		if((setup.Scout_Time>0)&&(timer==setup.Scout_Time)&&((peonmins>0)||(peongas>0)))
		{
			if(peonmins>0)
				peonmins--;
			else peongas--;			
		}
		
		timer++;
	}

	length=IP;
	CalculateFitness();
}


void Player_Terra::InitRaceSpecific()
{
	av_starport=0;
	av_factory=0;
	force[COMMAND_CENTER]=1;
	availible[COMMAND_CENTER]=1;
	force[SCV]=4;
// Supply -> how much supply is left
	Supply=6;
	Max_Supply=10;
	peonbuilding=0;
}

Player_Terra::Player_Terra()
{
}

Player_Terra::~Player_Terra()
{
}

void Player_Terra::readjust_goals()
{
	//nothing to readjust here as Terra has no morphing units
}
