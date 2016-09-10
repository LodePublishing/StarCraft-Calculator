#include "protoss.h"
#include "settings.h"

#define BUILDING_TYPES_PROTOSS 58

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

#define ONE_MINERAL_PROBE_TO_GAS 56
#define ONE_GAS_PROBE_TO_MINERAL 57



	void Player_Protoss::Set_Goals()
	{
		unsigned char i,j;
		long Need_Gas;
		
		building_types=BUILDING_TYPES_PROTOSS;
		for(j=0;j<5;j++)
		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;
				switch(i)
				{
					case PHOTON_CANNON:
					case ARMOR:
					case GROUND_WEAPONS:
					case PLASMA_SHIELDS:if(goal[FORGE].what==0) goal[FORGE].what=1; if((i==PLASMA_SHIELDS)||(goal[i].what<=1)||(i==PHOTON_CANNON)) break;
					case DARK_ARCHON:if(i==DARK_ARCHON) Ziel[DARK_TEMPLAR]=1;
					case ARCHON:if(i==ARCHON) Ziel[HIGH_TEMPLAR]=1;
					case ARBITER_TRIBUNAL:if((i==ARBITER_TRIBUNAL)&&(goal[STARGATE].what==0)) goal[STARGATE].what=1;
					case DARK_TEMPLAR:
					case HIGH_TEMPLAR:
					case PSIONIC_STORM:
					case HALLUCINATION:
					case MIND_CONTROL:
					case MAELSTROM:
					case ARGUS_TALISMAN:
					case KHAYDARIN_AMULET:
						if(goal[TEMPLAR_ARCHIVES].what==0) goal[TEMPLAR_ARCHIVES].what=1;break;
					case CYBERNETICS_CORE:
					case SHIELD_BATTERY:
					case ZEALOT:
						if(goal[GATEWAY].what==0) goal[GATEWAY].what=1;break;
					case OBSERVATORY:
					case REAVER:
					case SCARAB_DAMAGE:
					case REAVER_CAPACITY:
					case GRAVITIC_DRIVE:
						if(goal[ROBOTICS_SUPPORT_BAY].what==0) goal[ROBOTICS_SUPPORT_BAY].what=1;break;
					case PLATING:
					case AIR_WEAPONS:
						if((goal[i].what>1)&&(goal[FLEET_BEACON].what==0)) goal[FLEET_BEACON].what=1;
					case ROBOTICS_FACILITY:
					case CITADEL_OF_ADUN:
					case STARGATE:
					case DRAGOON:
					case SINGULARITY_CHARGE:
						if(goal[CYBERNETICS_CORE].what==0) goal[CYBERNETICS_CORE].what=1;break;
					case ROBOTICS_SUPPORT_BAY:
					case SHUTTLE:
						if(goal[ROBOTICS_FACILITY].what==0) goal[ROBOTICS_FACILITY].what=1;break;

					case FLEET_BEACON:
					case SCOUT:
					case CORSAIR:
						if(goal[STARGATE].what==0) goal[STARGATE].what=1;break;
					case KHAYDARIN_CORE:
					case STASIS_FIELD:
					case RECALL:
					case ARBITER:
						if(goal[ARBITER_TRIBUNAL].what==0) goal[ARBITER_TRIBUNAL].what=1;break;
					case APIAL_SENSORS:
					case GRAVITIC_THRUSTERS:
					case CARRIER_CAPACITY:
					case ARGUS_JEWEL:
					case DISRUPTION_WEB:
					case CARRIER:
						if(goal[FLEET_BEACON].what==0) goal[FLEET_BEACON].what=1;break;
					case OBSERVER:
					case GRAVITIC_BOOSTERS:
					case SENSOR_ARRAY:
						if(goal[OBSERVATORY].what==0) goal[OBSERVATORY].what=1;break;
					case TEMPLAR_ARCHIVES:
					case LEG_ENHANCEMENTS:
						if(goal[CITADEL_OF_ADUN].what==0) goal[CITADEL_OF_ADUN].what=1;break;
				};
			}
					

		Ziel[PROBE]=1;
		Ziel[NEXUS]=1;
		Ziel[PYLON]=1;

		Need_Gas=0;

		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
			Need_Gas+=(goal[i].what*stats[1][i].gas);

		if(Need_Gas>0)
		{
			Ziel[ASSIMILATOR]=1;
			goal[ASSIMILATOR].what=1;
			Ziel[ONE_MINERAL_PROBE_TO_GAS]=1;
			Ziel[ONE_GAS_PROBE_TO_MINERAL]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
		for(i=56;i<60;i++)
			goal[i].what=0; // Just to be sure that these unfulfillable goals are not set
	}

	void Player_Protoss::Build(unsigned short what)
	{
	   unsigned char m;
	   suc=0;

		if((stats[1][what].type==2)&&(what!=PYLON)&&(force[PYLON]==0)&&(what!=ASSIMILATOR)&&(what!=NEXUS))
			return;
	
			if(what==ONE_MINERAL_PROBE_TO_GAS)
			{
				if(force[ASSIMILATOR]>0)
				{
					if(peonmins>0)
					{
						ok=1;
						peonmins--;
						peongas++;
						program[IP].built=1;
					} else suc=6;
				}
			}
			else
			if(what==ONE_GAS_PROBE_TO_MINERAL)
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
		if((Supply<stats[1][what].supply) && (stats[1][what].supply>0))
			suc=4;
		else if( mins<stats[1][what].mins+(stats[race][what].type==4)*force[what]*stats[race][what].tmp) suc=2;
		else if(  gas<stats[1][what].gas +(stats[race][what].type==4)*force[what]*stats[race][what].tmp) suc=3;
		else if(peonmins+peongas<1*(stats[1][what].type==2))
			suc=6;
		else if(
			 (stats[1][what].type>=3)&&
			 ((stats[1][what].type<4)||(force[what]>=3)||(availible[what]!=1))&&
			 ((stats[1][what].type!=3)||(force[what]!=0)||(availible[what]!=1))
			) suc=7;
		else if(nr<255)
		{		
			switch(what)
			{
				case DARK_TEMPLAR:
				case HIGH_TEMPLAR:
					if((force[GATEWAY]>0)&&(availible[GATEWAY]>0)&&(force[TEMPLAR_ARCHIVES]>0)) 
					{
						Produce(what);
						availible[GATEWAY]--;
					};break;
				case DRAGOON:
					if((force[GATEWAY]>0)&&(force[CYBERNETICS_CORE]>0)&&(availible[GATEWAY]>0))
					{
						Produce(what);
						availible[GATEWAY]--;
					};break;
				case ZEALOT:
					if((force[GATEWAY]>0)&&(availible[GATEWAY]>0)) 
					{
						Produce(what);
						availible[GATEWAY]--;
					};break;
				case REAVER:
					if((force[ROBOTICS_SUPPORT_BAY]>0)&&(force[ROBOTICS_FACILITY]>0)&&(availible[ROBOTICS_FACILITY]>0)) 
					{
						Produce(what);
						availible[ROBOTICS_FACILITY]--;
					};break;
				case SHUTTLE:
					if((force[ROBOTICS_FACILITY]>0)&&(availible[ROBOTICS_FACILITY]>0)) 
					{
						Produce(what);
						availible[ROBOTICS_FACILITY]--;
					};break;
				case PROBE:
					if((force[NEXUS]>0)&&(availible[NEXUS]>0)) 
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
				case CORSAIR:
					if((force[STARGATE]>0)&&(availible[STARGATE]>0)) 
					{
						Produce(what);
						availible[STARGATE]--;
					};break;
				case ARBITER:
					if((force[STARGATE]>0)&&(availible[STARGATE]>0)&&(force[TEMPLAR_ARCHIVES]>0)&&(force[ARBITER_TRIBUNAL]>0)) 
					{
						Produce(what);
						availible[STARGATE]--;
					};break;
				case CARRIER:
					if((force[STARGATE]>0)&&(availible[STARGATE]>0)&&(force[FLEET_BEACON]>0)) 
					{
						Produce(what);
						availible[STARGATE]--;
					};break;
				case ARCHON:
					if(force[HIGH_TEMPLAR]>1)
					{
						Produce(what);
						force[HIGH_TEMPLAR]-=2;
					};break;
				case DARK_ARCHON:
					if(force[DARK_TEMPLAR]>1)
					{
						Produce(what);
						force[DARK_TEMPLAR]-=2;
					};break;
				case FORGE:
				case NEXUS:
				case PYLON:
					Produce(what);
					break;
				case ASSIMILATOR:
					if(Vespene_Av>0) 
					{
					       Vespene_Av--;
					       Vespene_Extractors++;
					       Produce(what);
					};break;
				case GATEWAY:
					Produce(what);
					break;
				case CYBERNETICS_CORE:
				case SHIELD_BATTERY:
					if(force[GATEWAY]>0) 
						Produce(what);
					break;
				case ROBOTICS_FACILITY:
				case CITADEL_OF_ADUN:
				case STARGATE:
					if(force[CYBERNETICS_CORE]>0) 
						Produce(what);
					break;
				case PHOTON_CANNON:
					if(force[FORGE]>0) 
						Produce(what);
					break;
				case TEMPLAR_ARCHIVES:
					if(force[CITADEL_OF_ADUN]>0) 
						Produce(what);
					break;
				case OBSERVATORY:
				case ROBOTICS_SUPPORT_BAY:
					if(force[ROBOTICS_FACILITY]>0) 
						Produce(what);
					break;
				case ARBITER_TRIBUNAL:
					if((force[STARGATE]>0)&&(force[TEMPLAR_ARCHIVES]>0))
						Produce(what);
					break;
				case FLEET_BEACON:
					if(force[STARGATE]>0)
						Produce(what);
					break;
				
				case ARGUS_TALISMAN:
				case KHAYDARIN_AMULET:
				case PSIONIC_STORM:
				case HALLUCINATION:
				case MIND_CONTROL:
				case MAELSTROM:
					if((force[TEMPLAR_ARCHIVES]>0)&&(availible[TEMPLAR_ARCHIVES]>0))
					{
						Produce(what);
						availible[what]=0;
						availible[TEMPLAR_ARCHIVES]--;
					};break;
				case KHAYDARIN_CORE:
				case RECALL:
				case STASIS_FIELD:
					if((force[ARBITER_TRIBUNAL]>0)&&(availible[ARBITER_TRIBUNAL]>0))
					{
						Produce(what);
						availible[what]=0;
						availible[ARBITER_TRIBUNAL]--;
					};break;
				case ARGUS_JEWEL:
				case APIAL_SENSORS:
				case GRAVITIC_THRUSTERS:							case DISRUPTION_WEB:
				case CARRIER_CAPACITY:
					if((force[FLEET_BEACON]>0)&&(availible[FLEET_BEACON]>0))
					{
						Produce(what);
						availible[what]=0;
						availible[FLEET_BEACON]--;
					};break;
				case LEG_ENHANCEMENTS:
					if((force[CITADEL_OF_ADUN]>0)&&(availible[CITADEL_OF_ADUN]>0))
					{
						Produce(what);
						availible[what]=0;
						availible[CITADEL_OF_ADUN]--;
					};break;
				case GRAVITIC_DRIVE:
				case SCARAB_DAMAGE:
				case REAVER_CAPACITY:
					if((force[ROBOTICS_SUPPORT_BAY]>0)&&(availible[ROBOTICS_SUPPORT_BAY]>0))
					{
						Produce(what);
						availible[what]=0;
						availible[ROBOTICS_SUPPORT_BAY]--;
					};break;
				case SENSOR_ARRAY:
				case GRAVITIC_BOOSTERS:
					if((force[OBSERVATORY]>0)&&(availible[OBSERVATORY]>0))
					{
						Produce(what);
						availible[what]=0;
						availible[OBSERVATORY]--;
					 };break;
				case SINGULARITY_CHARGE:
				case PLATING:
				case AIR_WEAPONS:
					if((force[CYBERNETICS_CORE]>0)&&(availible[CYBERNETICS_CORE]>0)&&((force[what]==0)||(force[FLEET_BEACON]>0))) 
					{
						Produce(what);
						availible[what]=0;
						availible[CYBERNETICS_CORE]--;
					};break;
				case ARMOR:
				case GROUND_WEAPONS:
				case PLASMA_SHIELDS:
					if((force[FORGE]>0)&&(availible[FORGE]>0)&&(availible[what]>0)) 
					{
						Produce(what);
						availible[what]=0;
						availible[FORGE]--;
					};break;
				default:break;
			}	
			if((ok==1)&&(stats[race][what].type==2))
				building[nr].RB+=5;
	// probe needs 5 seconds to reach the building site and to return
		}
	}
			if((suc==0)&&(ok==0))
				suc=1;
	}

	
	void Player_Protoss::Calculate()
	{
		unsigned short tt,j,tSupply,tMax_Supply;
		ready=0;
		timer=0;
		harvested_gas=0;
		harvested_mins=0;
		Vespene_Av=setup.Vespene_Geysirs;		
		Vespene_Extractors=0;
		tt=0;

		while((timer<setup.Max_Time) && (ready==0) && (IP<MAX_LENGTH))
		{
			tSupply=Supply;			
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
						
						if((setup.Time_to_Enemy>0)&&(building[j].type<NEXUS)&&(building[j].on_the_run==0)&&(building[j].type!=PROBE)&&(building[j].type!=SHUTTLE)&&(building[j].type!=DARK_ARCHON)&&(building[j].type!=ARCHON))
						{
							building[j].on_the_run=1;
							switch(building[j].type)
							{
							case ZEALOT:
								if(force[LEG_ENHANCEMENTS]>0)
									building[j].RB+=(unsigned short)((setup.Time_to_Enemy)*0.75);
								else
									building[j].RB+=(setup.Time_to_Enemy);
								break;
							
							case SCOUT:
								if(force[GRAVITIC_THRUSTERS]>0)
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
								else
									building[j].RB+=setup.Time_to_Enemy;
								break;
							case CORSAIR:
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
								break;
							case ARCHON:
							case DARK_ARCHON:
							case DARK_TEMPLAR:
								building[j].RB+=(setup.Time_to_Enemy);
								break;
							case CARRIER:
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
								break;
							case HIGH_TEMPLAR:
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
									break;
							case OBSERVER:
								if(force[GRAVITIC_BOOSTERS]>0)
									building[j].RB+=setup.Time_to_Enemy;
								else
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
								break;
							case REAVER:
								if(force[SHUTTLE]>0)
								{
									if(force[GRAVITIC_DRIVE]>0)
										building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.5);
									else
										building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
								}
								else
								building[j].RB+=setup.Time_to_Enemy*3;
								break;
						}
					}

						switch(building[j].type)
						{
							case PROBE:peonmins++;availible[NEXUS]++;break;
							case PYLON:Supply+=8;Max_Supply+=8;break;
							case NEXUS:Supply+=9;Max_Supply+=9;break;
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
							case CARRIER:availible[STARGATE]++;break;
							case ARGUS_TALISMAN:
							case KHAYDARIN_AMULET:
							case PSIONIC_STORM:
							case HALLUCINATION:
							case MIND_CONTROL:
							case MAELSTROM:availible[TEMPLAR_ARCHIVES]++;break;
			
							case KHAYDARIN_CORE:
							case RECALL:
							case STASIS_FIELD:availible[ARBITER_TRIBUNAL]++;break;
			
							case ARGUS_JEWEL:
							case APIAL_SENSORS:
							case GRAVITIC_THRUSTERS:				
							case DISRUPTION_WEB:
							case CARRIER_CAPACITY:availible[FLEET_BEACON]++;break;
			
							case LEG_ENHANCEMENTS:availible[CITADEL_OF_ADUN]++;break;
			
							case GRAVITIC_DRIVE:
							case SCARAB_DAMAGE:
							case REAVER_CAPACITY:availible[ROBOTICS_SUPPORT_BAY]++;break;
			
							case SENSOR_ARRAY:
							case GRAVITIC_BOOSTERS:availible[OBSERVATORY]++;break;
			
							case PLASMA_SHIELDS:
							case ARMOR:
							case GROUND_WEAPONS:availible[FORGE]++;availible[building[j].type]=1;break;	

							case PLATING:
							case AIR_WEAPONS:availible[CYBERNETICS_CORE]++;availible[building[j].type]=1;break;
							case SINGULARITY_CHARGE:availible[CYBERNETICS_CORE]++;break;
							default:break;
						}
					if(building[j].RB==0)
						CheckReady(j);
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
					program[IP].time=20000;
					program[IP].success=8;
				}
				program[IP].need_Supply=tMax_Supply-tSupply;
				program[IP].have_Supply=tMax_Supply;
				tt=0;
				IP++;
			}

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


void Player_Protoss::InitRaceSpecific()
{
	force[NEXUS]=1;
	availible[NEXUS]=1;
	force[PROBE]=4;
	Supply=5;
	Max_Supply=9;
}

Player_Protoss::Player_Protoss()
{
}

Player_Protoss::~Player_Protoss()
{
}
