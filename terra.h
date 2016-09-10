#include "main.h"

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

/*
Tech

Factory
Machine Shop
StarPort
Control Tower
Engineering Bay
Armory
Science Facility
Covert Ops
Physics Lab
Academy
*/


const double gasing_t[5]=
{
	0,
	0.89,
	1.76,
	2.30,
	2.45
};

const double mining_t[57]=
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


class Player_Terra: public RACE
{
public:
	void Set_Goals()
	{
		unsigned char i;
		//total_goals=0;
		building_types=BUILDING_TYPES_TERRA;
		for(i=0;i<BUILDING_TYPES_TERRA;i++)
			if(goal[i].what>0)
			{
			//	total_goals++;
				Ziel[i]=1;
				if(stats[0][i].tech[0]==1) Ziel[FACTORY]=1;
				if(stats[0][i].tech[1]==1) Ziel[MACHINE_SHOP]=1;
				if(stats[0][i].tech[2]==1) Ziel[STARPORT]=1;
				if(stats[0][i].tech[3]==1) Ziel[CONTROL_TOWER]=1;
				if(stats[0][i].tech[4]==1) Ziel[ENGINEERING_BAY]=1;
				if(stats[0][i].tech[5]==1) Ziel[ARMORY]=1;
				if(stats[0][i].tech[6]==1) Ziel[SCIENCE_FACILITY]=1;
				if(stats[0][i].tech[7]==1) Ziel[COVERT_OPS]=1;
				if(stats[0][i].tech[8]==1) Ziel[PHYSICS_LAB]=1;
				if(stats[0][i].tech[9]==1) Ziel[ACADEMY]=1;
			}

		Ziel[SCV]=1;
		Ziel[COMMAND_CENTER]=1;

		if((goal[INFANTRY_WEAPONS].what>1)||(goal[INFANTRY_ARMOR].what>1)||(goal[VEHICLE_WEAPONS].what>1)||(goal[VEHICLE_PLATING].what>1)||(goal[SHIP_WEAPONS].what>1)||(goal[SHIP_PLATING].what>1)||(goal[NUCLEAR_WARHEAD].what>0)||(goal[GHOST].what>0))
		{
			Ziel[BARRACKS]=1;
			Ziel[FACTORY]=1;
			Ziel[STARPORT]=1;
			Ziel[SCIENCE_FACILITY]=1;
		}
		if(goal[NUCLEAR_WARHEAD].what>0)
		{
			Ziel[COVERT_OPS]=1;
			Ziel[NUCLEAR_SILO]=1;
		}
		if(goal[GHOST].what>0)
		{
			Ziel[COVERT_OPS]=1;
			Ziel[ACADEMY]=1;
		}
		for(i=0;i<BUILDING_TYPES_TERRA;i++)
			   if(Ziel[i]>goal[i].what)
		        	  goal[i].what=Ziel[i];
		

		if((goal[MARINE].what>0)||(goal[FACTORY].what>0)||(goal[ACADEMY].what>0)||(goal[BUNKER].what>0))
			Ziel[BARRACKS]=1;
		// Noch rein: goals -> ziele -> ziele !!!!!!!!!!!!!!!
		// ok ;)
		for(i=0;i<BUILDING_TYPES_TERRA;i++)
			if(Ziel[i]>goal[i].what)
				goal[i].what=Ziel[i];

		//Ziel[BARRACKS]=1;
		Ziel[SUPPLY_DEPOT]=1;

		for(i=0;i<BUILDING_TYPES_TERRA;i++)
			Goal_Harvested_Gas+=(goal[i].what*stats[0][i].gas);

		if(Goal_Harvested_Gas>0)
		{
			Ziel[REFINERY]=1;
			if(goal[REFINERY].what==0) goal[REFINERY].what=1;
			Ziel[ONE_MINERAL_SCV_TO_GAS]=1;
			Ziel[ONE_GAS_SCV_TO_MINERAL]=1;
		}

		for(i=0;i<BUILDING_TYPES_TERRA;i++)
			Goal_Harvested_Mins+=(goal[i].what*stats[0][i].mins);
		Goal_Harvested_Mins*=1.1;

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_TERRA;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}

	}



	inline void Produce(unsigned short who)
	{
		if((who>=INFANTRY_ARMOR)&&(who<=SHIP_WEAPONS))
		{
			//On The Run??
			building[nr].RB=stats[0][who].BT+force[who]*32;
			switch(who)
			{
				case INFANTRY_ARMOR:
				case INFANTRY_WEAPONS:
				case VEHICLE_PLATING:
				case VEHICLE_WEAPONS:
				case SHIP_PLATING:mins-=stats[0][who].mins+force[who]*75;gas-=stats[0][who].gas+force[who]*75;break;
				case SHIP_WEAPONS:mins-=stats[0][who].mins+force[who]*50;gas-=stats[0][who].gas+force[who]*50;break;
				default:break;
			}
		}	
		else
		{
			building[nr].RB=stats[0][who].BT+(stats[0][who].type==2)*3; // 3 Spielsekunden um zum Bauplatz zu fahren 
			mins-=stats[0][who].mins;
		    gas-=stats[0][who].gas;
		}
		building[nr].type=who;
		Supply-=stats[0][who].supply;

		if(stats[0][who].type==2)
		{
			if(peonmins>0)
				peonmins--;
			else if(peongas>0)
				peongas--;
			peonbuilding++;
		}
		ok=1;
		building[nr].on_the_run=0;
	}

	
	
	void Build(unsigned short what)
	{
		unsigned char m;

			if((what==ONE_MINERAL_SCV_TO_GAS)&&(force[REFINERY]>0)&&(peonmins>0))
			{
				ok=1;
				peonmins--;
				peongas++;
			}
			else
			if((what==ONE_GAS_SCV_TO_MINERAL)&&(peongas>0))
			{
				ok=1;
				peongas--;
				peonmins++;
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
// hier liegt irgendwo der Fehler mit den Upgrades...
		if( ((Supply>=stats[0][what].supply) || (stats[0][what].supply==0)) &&
			( mins>=stats[0][what].mins+((what>=INFANTRY_ARMOR)&&(what<=SHIP_PLATING))*force[what]*75+(what==SHIP_WEAPONS)*force[what]*50) &&
			( gas>=stats[0][what].gas+((what>=INFANTRY_ARMOR)&&(what<=SHIP_PLATING))*force[what]*75+(what==SHIP_WEAPONS)*force[what]*50) &&
			(nr<255) && 
			(peonmins+peongas>=1*(stats[0][what].type==2))
		//Pruefe ob nicht schon erforscht bzw. mehr als 2x upgegradet is	
			&&
			(
			 (stats[0][what].type<3)||
			 ((stats[0][what].type==4)&&(force[what]<3)&&(availible[what]==1))||
			 ((stats[0][what].type==3)&&(force[what]==0)&&(availible[what]==1))
			)

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
				case VULTURE:if((force[FACTORY]>0)&&((availible[FACTORY]>0)||(av_factory>0))) 
							{
								Produce(what);
								if(availible[FACTORY]>0)
									availible[FACTORY]--;
								else av_factory--;
							};break;
				case GOLIATH:if((force[FACTORY]>0)&&(force[ARMORY]>0)&&((availible[FACTORY]>0)||(av_factory>0))) 
							{
								Produce(what);
								if(availible[FACTORY]>0)
									availible[FACTORY]--;
								else av_factory--;
							};break;
				case SIEGE_TANK:if((force[FACTORY]>0)&&(force[MACHINE_SHOP]>0)&&(av_factory>0)) 
							{
								Produce(what);
								av_factory--;
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
				case WRAITH:if((force[STARPORT]>0)&&((availible[STARPORT]>0)||(av_starport>0))) 
							{
								Produce(what);
								if(availible[STARPORT]>0)
									availible[STARPORT]--;
								else av_starport--;
							};break;
				case SCIENCE_VESSEL:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(force[SCIENCE_FACILITY]>0)&&(av_starport>0))
							{
								Produce(what);
								av_starport--;
							};break;
				case DROPSHIP:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(av_starport>0))
							{
								Produce(what);
								av_starport--;
							};break;
				case BATTLE_CRUISER:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(force[SCIENCE_FACILITY]>0)&&(force[PHYSICS_LAB]>0)&&(av_starport>0))
							{
								Produce(what);
								av_starport--;
							};break;
				case VALKYRIE:if((force[STARPORT]>0)&&(force[CONTROL_TOWER]>0)&&(force[ARMORY]>0)&&(av_starport>0))
							{
								Produce(what);
								av_starport--;
							};break;
				case COMMAND_CENTER:
				case SUPPLY_DEPOT:Produce(what);break;
				case REFINERY:if(Vespene_Av>0) { Vespene_Av--;Produce(what);};break;
				case BARRACKS:Produce(what);break;
				case ACADEMY:
				case FACTORY:if(force[BARRACKS]>0) Produce(what);break;
				case STARPORT:if(force[FACTORY]>0) Produce(what);break;
				case SCIENCE_FACILITY:if(force[STARPORT]>0) Produce(what);break;
				case ENGINEERING_BAY:Produce(what);break;
				case ARMORY:if(force[FACTORY]>0) Produce(what);break;
				case MISSILE_TURRET:if(force[ENGINEERING_BAY]>0) Produce(what);break;
				case BUNKER:if(force[BARRACKS]>0) Produce(what);break;

				case COMSAT_STATION:if((force[COMMAND_CENTER]>force[COMSAT_STATION]+force[NUCLEAR_SILO])&&(availible[COMMAND_CENTER]>0)&&(force[ACADEMY]>0)) 
									{
										Produce(what);
										availible[COMMAND_CENTER]--;
									};break;
				case NUCLEAR_SILO:if((force[COMMAND_CENTER]>force[COMSAT_STATION]+force[NUCLEAR_SILO])&&(availible[COMMAND_CENTER]>0)&&(force[SCIENCE_FACILITY]>0)&&(force[COVERT_OPS]>0))
								  {
									  Produce(what);
									  availible[COMMAND_CENTER]--;
								  };break;
				case CONTROL_TOWER:if((force[STARPORT]>force[CONTROL_TOWER])&&(availible[STARPORT]>0)) 
								   {
									   Produce(what);
									   availible[STARPORT]--;
								   };break;
				case COVERT_OPS:
				case PHYSICS_LAB:if((force[SCIENCE_FACILITY]>force[COVERT_OPS]+force[PHYSICS_LAB])&&(availible[SCIENCE_FACILITY]>0)) 
								 {
									 Produce(what);
									 availible[SCIENCE_FACILITY]--;
								 };break;

				case MACHINE_SHOP:if((force[FACTORY]>force[MACHINE_SHOP])&&(availible[FACTORY]>0)) 
								  {
									  Produce(what);
									  availible[FACTORY]--;
								  };break;

				
				
				case CHARON_BOOSTER:
				case SPIDER_MINES:
				case TANK_SIEGE_MODE:
				case ION_THRUSTERS:if((force[MACHINE_SHOP]>0)&&(availible[MACHINE_SHOP]>0))
								   {
									   Produce(what);
									   availible[what]=0;
									   availible[MACHINE_SHOP]--;
								   };break;

				case TITAN_REACTOR:
				case EMP_SHOCKWAVE:
				case IRRADIATE:if((force[SCIENCE_FACILITY]>0)&&(availible[SCIENCE_FACILITY]>0)) 
							   {
								   Produce(what);
								   availible[what]=0;
								   availible[SCIENCE_FACILITY]--;
							   };break;
				
				case OCULAR_IMPLANTS:
				case LOCKDOWN:
				case MOEBIUS_REACTOR:
				case PERSONNEL_CLOAKING:if((force[COVERT_OPS]>0)&&(availible[COVERT_OPS]>0)) 
										{
											Produce(what);
											availible[what]=0;
											availible[COVERT_OPS]--;
										};break;
				
				case CADUCEUS_REACTOR:
				case U238_SHELLS:
				case STIM_PACKS:
				case RESTORATION:
				case OPTICAL_FLARE:if((force[ACADEMY]>0)&&(availible[ACADEMY]>0)) 
								   {
									   Produce(what);
									   availible[what]=0;
									   availible[ACADEMY]--;
								   };break;

				case COLOSSUS_REACTOR:
				case YAMATO_GUN:if((force[PHYSICS_LAB]>0)&&(availible[PHYSICS_LAB]>0))
								{
									Produce(what);
									availible[what]=0;
									availible[PHYSICS_LAB]--;
								};break;

				case APOLLO_REACTOR:
				case CLOAKING_FIELD:if((force[CONTROL_TOWER]>0)&&(availible[CONTROL_TOWER]>0))
									{
										Produce(what);
										availible[what]=0;
										availible[CONTROL_TOWER]--;
									};break;

				case INFANTRY_ARMOR:
				case INFANTRY_WEAPONS:
						    if((force[ENGINEERING_BAY]>0)&&(availible[ENGINEERING_BAY]>0)/*&&( (force[what]==0)||(force[SCIENCE_FACILITY]>0)) */) 
									   {
											Produce(what);
											availible[what]=0;
											availible[ENGINEERING_BAY]--;
									   };break;

				case VEHICLE_PLATING:
				case VEHICLE_WEAPONS:
				case SHIP_PLATING:
				case SHIP_WEAPONS:if((force[ARMORY]>0)&&(availible[ARMORY]>0)&&((force[what]==0)|| ((force[what]>0)&&(force[SCIENCE_FACILITY]>0)))) 
								  {
									   Produce(what);
									   availible[what]=0;
									   availible[ARMORY]--;
								  };break;
				case NUCLEAR_WARHEAD:if((force[NUCLEAR_SILO]>0)&&(availible[NUCLEAR_SILO]>0))
									 {
										 Produce(what);
										 availible[NUCLEAR_SILO]--;
									 }
									 
				default:break;
			}	
		}
	}
	}

	
	void Calculate()
	{
		unsigned char tt,i,j,tSupply;
		ready=0;
		timer=0;
		harvested_gas=0;
		harvested_mins=0;
		
	//	gasready=0;
	//	minsready=0;
		Vespene_Av=setup.Vespene_Geysirs;		
		tt=0;

		while((timer<setup.Max_Time) && (ready==0) && (IP<MAX_LENGTH))
		{			
			
			tSupply=Supply;// fuer Log
			BuildingRunning=0;
			ok=0;

			if(peonmins<56)
			{
				mins+=mining_t[peonmins]*0.9;
				harvested_mins+=mining_t[peonmins]*0.9;
			}
			else 
			{
				mins+=(mining_t[56]*0.9);
				harvested_mins+=(mining_t[56]*0.9);
			}
			if(peongas<5)
			{
				gas+=gasing_t[peongas];
				harvested_gas+=gasing_t[peongas];
			}
			else
			{
				gas+=gasing_t[4];
				harvested_gas+=gasing_t[4];
			}


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
							force[building[j].type]++;
							if((force[building[j].type]>=goal[building[j].type].what)&&(ftime[building[j].type]==0))
								ftime[building[j].type]=timer;
							
							
							if(stats[0][building[j].type].type<3)
								availible[building[j].type]++;
							else
								availible[building[j].type]=1;
							if(stats[0][building[j].type].type==2) 
							{
								peonmins++;
								peonbuilding--;
							}
							
							ready=1;
							for(i=0;i<BUILDING_TYPES_TERRA;i++)
								ready&=((goal[i].what<=force[i])&&((goal[i].time==0)||(goal[i].time>=ftime[i])));
//							if((harvested_mins >= Goal_Harvested_Mins)&&(minsready==0)) minsready=(timer*100)/Max_Time;
//							if((harvested_gas >= Goal_Harvested_Gas)&&(gasready==0)) gasready=(timer*100)/Max_Time;
						}
					}
				}
			}

			Build(Build_Av[program[IP].order]);
			tt++;
			if((ok==1)||(tt>267))
			{
				if(tt<=267) program[IP].time=timer;
				else program[IP].time=20000;
				program[IP].need_Supply=Max_Supply-tSupply;
				// Warum nicht Supply statt tSupply? sonst 5/9 bei ersten drone z.B.
				program[IP].have_Supply=Max_Supply;
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


void InitRaceSpecific()
{
	av_starport=0;
	av_factory=0;
	force[COMMAND_CENTER]=1;
	availible[COMMAND_CENTER]=1;
	force[SCV]=4;
	Supply=6;
	Max_Supply=10;
	peonbuilding=0;
}

};
