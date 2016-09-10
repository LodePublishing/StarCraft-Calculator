#include "zerg.h"
#include "settings.h"
#include <stdio.h>

#define BUILDING_TYPES_ZERG 53

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

#define ONE_MINERAL_DRONE_TO_GAS 50
#define ONE_GAS_DRONE_TO_MINERAL 51

#define BREAK_UP_BUILDING 52

	void Player_Zerg::Set_Goals()
	{
		unsigned char i,j;
		long Need_Gas;
		building_types=BUILDING_TYPES_ZERG;
		for(j=0;j<5;j++)
		for(i=0;i<BUILDING_TYPES_ZERG;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;
				switch(i)
				{
					case HYDRALISK_DEN:
					case LAIR:
					case METABOLIC_BOOST:
					case ZERGLING:
						if(goal[SPAWNING_POOL].what==0) goal[SPAWNING_POOL].what=1;break;
					case CHITINOUS_PLATING:
					case ANABOLIC_SYNTHESIS:
					case ULTRALISK:
						if(goal[ULTRALISK_CAVERN].what==0) goal[ULTRALISK_CAVERN].what=1;break;
					case MUSCULAR_AUGMENTS:
					case GROOVED_SPINES:
					case HYDRALISK:
						if(goal[HYDRALISK_DEN].what==0) goal[HYDRALISK_DEN].what=1;break;
					case METASYNAPTIC_NODE:
					case PLAGUE:
					case CONSUME:
					case DEFILER:
						if(goal[DEFILER_MOUND].what==0) goal[DEFILER_MOUND].what=1;break;
					case LURKER:
						Ziel[HYDRALISK]=1;
						if(goal[LURKER_ASPECT].what==0) goal[LURKER_ASPECT].what=1;break;
					
					case FLYER_CARAPACE:
					case FLYER_ATTACKS:
						if((goal[i].what==3)&&(goal[HIVE].what==0)) goal[HIVE].what=1;
					case SCOURGE:
					case MUTALISK:
						Ziel[SPIRE]=1;
						Ziel[LAIR]=1;
						if((goal[GREATER_SPIRE].what==0)&&(goal[DEVOURER].what==0)&&(goal[GUARDIEN].what==0))
						{
							goal[SPIRE].what=1;
						};break;
					case DEVOURER:	
					case GUARDIEN:
						{
							if(goal[GREATER_SPIRE].what==0) goal[GREATER_SPIRE].what=1;
							Ziel[MUTALISK]=1;
						};
							break;
					case GAMETE_MEIOSIS:
					case SPAWN_BROODLING:
					case ENSNARE:
					case QUEEN:
						if(goal[QUEENS_NEST].what==0) goal[QUEENS_NEST].what=1;break;
					case LURKER_ASPECT:
						Ziel[LAIR]=1;
						if(goal[HYDRALISK_DEN].what==0) goal[HYDRALISK_DEN].what=1;break;
					
					case HIVE:
						Ziel[LAIR]=1;
						if(goal[QUEENS_NEST].what==0) goal[QUEENS_NEST].what=1;break;						
					case GREATER_SPIRE:
						if(goal[SPIRE].what==0) goal[SPIRE].what=1;
					case ADRENAL_GLANDS:
					case ULTRALISK_CAVERN:
					case DEFILER_MOUND:
					case NYDUS_CANAL:
						if(goal[HIVE].what==0) goal[HIVE].what=1;break;
					case SPIRE:
					case VENTRAL_SACKS:
					case ANTENNAE:
					case PNEUMATIZED_CARAPACE:		
					case QUEENS_NEST:
						Ziel[LAIR]=1;
						break;
					case SPORE_COLONY:
						if(goal[EVOLUTION_CHAMBER].what==0) goal[EVOLUTION_CHAMBER].what=1;Ziel[CREEP_COLONY]=1;break;
					case SUNKEN_COLONY:
						if(goal[SPAWNING_POOL].what==0) goal[SPAWNING_POOL].what=1;Ziel[CREEP_COLONY]=1;break;
							
					case CARAPACE:
					case MELEE_ATTACKS:
					case MISSILE_ATTACKS:
						goal[EVOLUTION_CHAMBER].what=1;
						if((goal[i].what==3)&&(goal[HIVE].what==0)) goal[HIVE].what=1;
						else if(goal[i].what==2) Ziel[LAIR]=1;break;
				}
			}
		if(Ziel[LAIR]>0)
		{
			goal[SPAWNING_POOL].what=1;
			Ziel[SPAWNING_POOL]=1;
			if((Ziel[HIVE]==0)&&(goal[LAIR].what==0))
				goal[LAIR].what=1;
		}

//TODO: Check whether Lair/Hive always works		
		if((Ziel[SPIRE]>0)&&(Ziel[GREATER_SPIRE]==0))
			goal[SPIRE].what=1;

		Ziel[OVERLORD]=1;
		Ziel[DRONE]=1;
		Ziel[HATCHERY]=1;
		Ziel[BREAK_UP_BUILDING]=1;

		Need_Gas=0;

		for(i=0;i<BUILDING_TYPES_ZERG;i++)
			Need_Gas+=(goal[i].what*stats[2][i].gas);
		if(Need_Gas>0)
		{
			if(goal[EXTRACTOR].what==0) goal[EXTRACTOR].what=1;
			Ziel[EXTRACTOR]=1;
			Ziel[ONE_MINERAL_DRONE_TO_GAS]=1;
			Ziel[ONE_GAS_DRONE_TO_MINERAL]=1;				 	}

		Max_Build_Types=0;
		
		Ziel[EXTRACTOR]=1;
		Ziel[CREEP_COLONY]=1;
		
		for(i=0;i<BUILDING_TYPES_ZERG;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
		for(i=50;i<60;i++)
			goal[i].what=0; //just to be sure :)
	}


	void Player_Zerg::Build(unsigned short what)
	{
		unsigned char m,i;
		suc=0;
		
			if(what==ONE_MINERAL_DRONE_TO_GAS)
			{
				if(force[EXTRACTOR]>0)
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
			if(what==ONE_GAS_DRONE_TO_MINERAL)
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
			if((what==BREAK_UP_BUILDING)&&(BuildingRunning>0))
			{
				min=5000;
				n=0;
				for(i=0;i<MAX_BUILDINGS;i++)
					if(building[i].RB>0)
					{
						if((stats[2][building[i].type].type==2) && (stats[2][building[i].type].BT-building[i].RB<min))
		// type == 2 because this makes only sense with buildings			
						{
							min=stats[2][building[i].type].BT-building[i].RB;
							n=i;
						}
					}

					if(min<5000)
					{
						ok=1;
						peonmins++;
						mins+=stats[2][building[n].type].mins*0.75;
						gas+=stats[2][building[n].type].gas*0.75;
						Supply--;
						force[DRONE]++;
						if(building[n].type==EXTRACTOR)
						{
							Vespene_Extractors--;
							Vespene_Av++;
						}
						building[n].type=255;
						building[n].RB=0;
						program[IP].built=1;
					} 
			}
			//TODO: Think about inserting suc= here... 
			else
			{
		
		nr=255;
		for(m=0;m<MAX_BUILDINGS;m++)
			if(building[m].RB==0)
			{
				nr=m;
				m=MAX_BUILDINGS;			
			}
		if((Supply<stats[2][what].supply) && (stats[2][what].supply>0))
			suc=4;
		else if(mins<stats[2][what].mins+(stats[2][what].type==4)*force[what]*stats[2][what].tmp) suc=2;
		else if( gas<stats[2][what].gas+(stats[2][what].type==4)*force[what]*stats[2][what].tmp) suc=3;
		else if (peonmins+peongas<1*(stats[2][what].type==2)) suc=6;
		else if (larvae<1*(stats[2][what].type==1)) suc=5;
		else if	(
			 (stats[2][what].type>=3)&&
			 ((stats[2][what].type<4)||(force[what]>=3)||(availible[what]!=1))&&
			 ((stats[2][what].type!=3)||(force[what]!=0)||(availible[what]!=1))
			) suc=7;
		else if(nr<255)
		{
			switch(what)
			{
				case ZERGLING:
					if(force[SPAWNING_POOL]>0) 
						Produce(what);
					break;
				case HYDRALISK:
					if(force[HYDRALISK_DEN]>0) 
						Produce(what);
					break;
				case ULTRALISK:
					if(force[ULTRALISK_CAVERN]>0) 
						Produce(what);
					break;
				case DRONE:
					Produce(what);
					break;
				case DEFILER:
					if(force[DEFILER_MOUND]>0) 
						Produce(what);
					break;
				case LURKER:
					if((force[LURKER_ASPECT]>0)&&(force[HYDRALISK]>0))
					{
						force[HYDRALISK]--;
						Produce(what);
					};break;
				case OVERLORD:
					Produce(what);
					break;
				case MUTALISK:
					if(force[SPIRE]+force[GREATER_SPIRE]>0) 
						Produce(what);
					break;
				case GUARDIEN:
					if((force[GREATER_SPIRE]>0)&&(force[MUTALISK]>0))
					{
						force[MUTALISK]--;
						Produce(what);
					};break;
				case QUEEN:
					if(force[QUEENS_NEST]>0) 
						Produce(what);
					break;
				case SCOURGE:
					if(force[SPIRE]+force[GREATER_SPIRE]>0) 
						Produce(what);
					break;
				case HATCHERY:
					Produce(what);
					break;
				case LAIR:
					if((force[HATCHERY]>0)&&(force[SPAWNING_POOL]>0)&&(availible[HATCHERY]>0)) 
					{
						availible[HATCHERY]--;	  
						Produce(what);
					};break;
				case HIVE:
					if((force[LAIR]>0)&&(force[QUEENS_NEST]>0)&&(availible[LAIR]>0))
					{
						availible[LAIR]--;
						Produce(what);
					};break;
				case NYDUS_CANAL:
					if(force[HIVE]>0) 
						Produce(what);
					break;
				case HYDRALISK_DEN:
					if(force[SPAWNING_POOL]>0) 
						Produce(what);
					break;
				case DEFILER_MOUND:
					if(force[HIVE]>0) 
						Produce(what);
					break;
				case GREATER_SPIRE:
					if((force[SPIRE]>0)&&(availible[SPIRE]>0)&&(force[HIVE]>0)) 
					{
						availible[SPIRE]--;
						Produce(what);
					};break;
				case QUEENS_NEST:
					if(force[LAIR]>0) 
						Produce(what);
					break;
				case EVOLUTION_CHAMBER:
					Produce(what);
					break;
				case ULTRALISK_CAVERN:
					if(force[HIVE]>0) 
						Produce(what);
					break;
				case SPIRE:
					if(force[LAIR]>0) 
				   		Produce(what);
					break;
				case SPAWNING_POOL:
					Produce(what);
					break;
				case CREEP_COLONY:
					Produce(what);
					break;
				case SPORE_COLONY:
					if((force[EVOLUTION_CHAMBER]>0)&&(force[CREEP_COLONY]>0))
					{
						force[CREEP_COLONY]--;
						Produce(what);
					};break;
				case SUNKEN_COLONY:
					if((force[SPAWNING_POOL]>0)&&(force[CREEP_COLONY]>0))
					{
						force[CREEP_COLONY]--;
						Produce(what);
					};break;
				case EXTRACTOR:
					if(Vespene_Av>0) 
					{ 
						Vespene_Av--;
						Produce(what);
						Vespene_Extractors++;
					};break;
//TODO: Check whether this always works... maybe problems with multiple Extractors				
				case VENTRAL_SACKS:
				case ANTENNAE:
				case PNEUMATIZED_CARAPACE:
					if((force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
					{
						if(availible[LAIR]>0) 
							availible[LAIR]--;
						else availible[HIVE]--;
						availible[what]=0;
						Produce(what);
					};break;
				case METABOLIC_BOOST:
					if((force[SPAWNING_POOL]>0)&&(availible[SPAWNING_POOL]>0))
					{
						availible[SPAWNING_POOL]--;
						availible[what]=0;
						Produce(what);
					};break;
				case ADRENAL_GLANDS:
					if((force[HIVE]>0)&&(force[SPAWNING_POOL]>0)&&(availible[SPAWNING_POOL]>0))
					{
						availible[SPAWNING_POOL]--;
						availible[what]=0;
						Produce(what);
					};break;
				case MUSCULAR_AUGMENTS:
				case GROOVED_SPINES:
					if((force[HYDRALISK_DEN]>0)&&(availible[HYDRALISK_DEN]>0))
					{
						availible[HYDRALISK_DEN]--;
						availible[what]=0;
						Produce(what);
					};break;
				case CHITINOUS_PLATING:
					if((force[ULTRALISK_CAVERN]>0)&&(availible[ULTRALISK_CAVERN]>0)) 
					{
						availible[ULTRALISK_CAVERN]--;
						availible[what]=0;
						Produce(what);
				  	};break;
				case ANABOLIC_SYNTHESIS:
					if((force[ULTRALISK_CAVERN]>0)&&(availible[ULTRALISK_CAVERN]>0)) 
					{
						availible[ULTRALISK_CAVERN]--;
						availible[what]=0;
						Produce(what);
					};break;
				case BURROWING:
					if((force[HATCHERY]+force[LAIR]+force[HIVE]>0)&&(availible[HATCHERY]+availible[LAIR]+availible[HIVE]>0)) 
					{
						if(availible[HATCHERY]>0)
							availible[HATCHERY]--;
						else if(availible[LAIR]>0)
							availible[LAIR]--;
						else availible[HIVE]--;
							Produce(what);
						availible[what]=0;
					 };break;
				case ENSNARE:
				case GAMETE_MEIOSIS:
				case SPAWN_BROODLING:
					if((force[QUEENS_NEST]>0)&&(availible[QUEENS_NEST]>0))
					{
						availible[QUEENS_NEST]--;
						Produce(what);
						availible[what]=0;
					};break;
				case METASYNAPTIC_NODE:
				case PLAGUE:
				case CONSUME:
					if((force[DEFILER_MOUND]>0)&&(availible[DEFILER_MOUND]>0))
					{
						availible[DEFILER_MOUND]--;
						Produce(what);
						availible[what]=0;
					};break;
				case LURKER_ASPECT:
					if((force[HYDRALISK_DEN]>0)&&(force[LAIR]>0)&&(availible[HYDRALISK_DEN]>0))
					{
						availible[HYDRALISK_DEN]--;
						Produce(what);
						availible[what]=0;
					};break;
				case CARAPACE:
				case MELEE_ATTACKS:
				case MISSILE_ATTACKS:
					if((force[EVOLUTION_CHAMBER]>0)&&(availible[EVOLUTION_CHAMBER]>0)&&(force[HATCHERY+force[what]]>0))
			      		{
						availible[EVOLUTION_CHAMBER]--;
						Produce(what);
						availible[what]=0;
					};break;
				case FLYER_CARAPACE:
				case FLYER_ATTACKS:
					if((force[SPIRE]>0)&&(availible[SPIRE]>0)&&(force[HATCHERY+force[what]]>0))
					{
						if(availible[SPIRE]>0)
							availible[SPIRE]--;
						else availible[GREATER_SPIRE]--;
						Produce(what);
						availible[what]=0;
					};break;
				default:break;
			}	
			if(ok==1)
			{
				if(stats[2][what].type==1)
					larvae--;
				else
				if(stats[2][what].type==2)
				{
					building[nr].RB+=3;
					force[DRONE]--;
					Supply++;
					if(peonmins>0)
						peonmins--;
					else if(peongas>0)
						peongas--;
				}
			}
					 
		}
	}
			if((suc==0)&&(ok==0))
				suc=1;
	}

	
	void Player_Zerg::Calculate()
	{
		unsigned char tt,i,j,tSupply,tMax_Supply;
		ready=0;
		timer=0;
		harvested_gas=0;
		harvested_mins=0;
		Vespene_Av=setup.Vespene_Geysirs;
		Vespene_Extractors=0;		
		tt=0;

		while((timer<setup.Max_Time) && (ready==0) && (IP<MAX_LENGTH))
		{			
			tSupply=Supply;tMax_Supply=Max_Supply;
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
						if((setup.Time_to_Enemy>0)&&(building[j].type<HATCHERY)&&(building[j].on_the_run==0)&&(building[j].type!=OVERLORD)&&(building[j].type!=DRONE)&&(building[j].type!=LURKER))
						{
							building[j].on_the_run=1;
							if(building[j].type==ZERGLING)
							{
								if(force[METABOLIC_BOOST]>0)

// TODO : Acceleration during the run, say you got 6 zerglings and research metabolic boost just when they are underway
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.5);
								else
									building[j].RB+=setup.Time_to_Enemy;
							}
							else if(building[j].type==HYDRALISK)
							{
								if(force[MUSCULAR_AUGMENTS]>0)
									building[j].RB+=setup.Time_to_Enemy;
								else
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
							}
							else if(building[j].type==ULTRALISK)
							{
								if(force[ANABOLIC_SYNTHESIS]>0)
									building[j].RB+=setup.Time_to_Enemy;
								else
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
							}
							else if((building[j].type==MUTALISK)||(building[j].type==SCOURGE)||(building[j].type==QUEEN))
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
							else if(building[j].type==DEVOURER)
								building[j].RB+=setup.Time_to_Enemy;
							else if((building[j].type==GUARDIEN)||(building[j].type==DEFILER))
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
						}
						switch(building[j].type)
						{
							case DRONE:peonmins++;break;
							case OVERLORD:Supply+=8;Max_Supply+=8;break;
							case HATCHERY:larvacounter++;larvae++;larva[larvacounter]=21;Supply++;Max_Supply++;break;
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

							case CHITINOUS_PLATING:
							case ANABOLIC_SYNTHESIS:availible[ULTRALISK_CAVERN]++;break;

							case BURROWING:
							   if(availible[HATCHERY]<force[HATCHERY])
								   availible[HATCHERY]++;
							   else if(availible[LAIR]<force[LAIR])
								   availible[LAIR]++;
							   else availible[HIVE]++;
							   break;
							
							case METASYNAPTIC_NODE:
							case PLAGUE:
							case CONSUME:availible[DEFILER_MOUND]++;break;

							case ENSNARE:
							case SPAWN_BROODLING:
							case GAMETE_MEIOSIS:availible[QUEENS_NEST]++;break;

							case MUSCULAR_AUGMENTS:
							case GROOVED_SPINES:
							case LURKER_ASPECT:availible[HYDRALISK_DEN]++;break;
							
							case CARAPACE:
							case MELEE_ATTACKS:
							case MISSILE_ATTACKS:availible[EVOLUTION_CHAMBER]++;availible[building[j].type]=1;break;

							case FLYER_CARAPACE:
							case FLYER_ATTACKS:
								if(availible[SPIRE]<force[SPIRE])
									availible[SPIRE]++;
								else availible[GREATER_SPIRE]++;
								availible[building[j].type]=1;
								break;
							default:break;
						}
						if(building[j].RB==0)
							CheckReady(j);
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

			tt++;
			ok=0;
			Build(Build_Av[program[IP].order]); 
		// suc and ok is modified by 'Build'
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


		timer++;
	}

	length=IP;
	CalculateFitness();
}

void Player_Zerg::InitRaceSpecific()
{
	unsigned short i;
	for(i=0;i<LARVA_MAX;i++)
		larva[i]=20; // 20 seconds until a new larva comes out of the hatchery
	larvae=3;
	force[HATCHERY]=1;
	availible[HATCHERY]=1;
	force[DRONE]=4;
	force[OVERLORD]=1;
	larvacounter=1;
	Supply=5;
	Max_Supply=9;
}

Player_Zerg::Player_Zerg()
{
}

Player_Zerg::~Player_Zerg()
{
}
