#include "main.h"

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



const double gasing_z[5]=
{
	0,
	0.89,
	1.76,
	2.30,
	2.45
};

const double mining_z[57]=
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





class Player_Zerg: public RACE
{
public:

	void Set_Goals()
	{
		unsigned char i;
		building_types=BUILDING_TYPES_ZERG;
		for(i=0;i<BUILDING_TYPES_ZERG;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;
				if(stats[2][i].tech[0]==1) Ziel[EXTRACTOR]=1;
				if(stats[2][i].tech[1]==1) Ziel[LAIR]=1;
				if(stats[2][i].tech[2]==1) Ziel[HYDRALISK_DEN]=1;
				if(stats[2][i].tech[3]==1) Ziel[EVOLUTION_CHAMBER]=1;
				if(stats[2][i].tech[4]==1) Ziel[QUEENS_NEST]=1;
				if(stats[2][i].tech[5]==1) Ziel[SPIRE]=1;
				if(stats[2][i].tech[6]==1) Ziel[HIVE]=1;
				if(stats[2][i].tech[7]==1) Ziel[ULTRALISK_CAVERN]=1;
				if(stats[2][i].tech[8]==1) Ziel[DEFILER_MOUND]=1;
				if(stats[2][i].tech[9]==1) Ziel[GREATER_SPIRE]=1;
			}

		Ziel[OVERLORD]=1;
		Ziel[DRONE]=1;
		if((goal[CARAPACE].what>0)||(goal[MELEE_ATTACKS].what>0)||(goal[MISSILE_ATTACKS].what>0))
			Ziel[EVOLUTION_CHAMBER]=1;

		if((goal[CARAPACE].what>1)||(goal[FLYER_CARAPACE].what>1)||(goal[MELEE_ATTACKS].what>1)||(goal[MISSILE_ATTACKS].what>1)||(goal[FLYER_ATTACKS].what>1))
		{
			Ziel[SPAWNING_POOL]=1;
			Ziel[LAIR]=1;
			if((goal[CARAPACE].what>2)||(goal[FLYER_CARAPACE].what>2)||(goal[MELEE_ATTACKS].what>2)||(goal[MISSILE_ATTACKS].what>2)||(goal[FLYER_ATTACKS].what>2))
			{
				Ziel[QUEENS_NEST]=1;
				Ziel[HIVE]=1;
			}
		}	
		if((goal[FLYER_CARAPACE].what>0)||(goal[FLYER_ATTACKS].what>0))
		{
			Ziel[LAIR]=1;
			Ziel[SPAWNING_POOL]=1;
			Ziel[SPIRE]=1;
		}

		if(Ziel[LAIR]>0)
			Ziel[SPAWNING_POOL]=1;
		
		for(i=0;i<BUILDING_TYPES_ZERG;i++)
			if((Ziel[i]>goal[i].what)&&(i!=HATCHERY)&&(i!=LAIR))//~~~~~~
				goal[i].what=Ziel[i];
		Ziel[HATCHERY]=1;
		if((Ziel[LAIR]>goal[LAIR].what)&&(Ziel[HIVE]<Ziel[LAIR]))
			goal[LAIR].what=Ziel[LAIR]-Ziel[HIVE];

		if(goal[LURKER].what>0)
		{
			Ziel[HYDRALISK]=1;
			Ziel[LURKER_ASPECT]=1;
			goal[LURKER_ASPECT].what=1;
		}
		
		Ziel[SPAWNING_POOL]=1;//vielleicht noch bei tech rein...
		Ziel[EXTRACTOR]=1;
//		Ziel[METABOLIC_BOOST]=1;
//		if(goal[EXTRACTOR].what==0) goal[EXTRACTOR].what=1;
		Ziel[ONE_MINERAL_DRONE_TO_GAS]=1;
		Ziel[ONE_GAS_DRONE_TO_MINERAL]=1;

		if((goal[SPORE_COLONY].what>0)||(goal[SUNKEN_COLONY].what>0)) Ziel[CREEP_COLONY]=1;
		
		Ziel[BREAK_UP_BUILDING]=1;

		for(i=0;i<BUILDING_TYPES_ZERG;i++)
			Goal_Harvested_Gas+=(goal[i].what*stats[2][i].gas);

		for(i=0;i<BUILDING_TYPES_ZERG;i++)
			Goal_Harvested_Mins+=(goal[i].what*stats[2][i].mins)+(stats[2][goal[i].what].type==2)*50;
		Goal_Harvested_Mins*=1.1;

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_ZERG;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}


	}



	void Produce(unsigned short who)
	{
		if((who>=CARAPACE)&&(who<=FLYER_ATTACKS))
		{
			building[nr].RB=stats[2][who].BT+force[who]*32;
			switch(who)
			{
				case CARAPACE:
				case FLYER_CARAPACE:
				case FLYER_ATTACKS:mins-=stats[2][who].mins+force[who]*75;gas-=stats[2][who].gas+force[who]*75;break;

				case MELEE_ATTACKS:
				case MISSILE_ATTACKS:mins-=stats[2][who].mins+force[who]*75;gas-=stats[2][who].gas+force[who]*75;break;
				default:break;
			}
		}	
		else
		{
			building[nr].RB=stats[2][who].BT+(stats[2][who].type==2)*3; // 3 Spielsekunden um zum Bauplatz zu fahren 

			mins-=stats[2][who].mins;
		    gas-=stats[2][who].gas;
		}
		building[nr].type=who;
		Supply-=stats[2][who].supply;
		if(stats[2][who].type==1)
			larvae--;
		else
	    if(stats[2][who].type==2)
		{
			force[DRONE]--;
			Supply++;
			if(peonmins>0)
				peonmins--;
			else if(peongas>0)
				peongas--;
		}
		ok=1;
		building[nr].on_the_run=0;
	}

	
	
	void Build(unsigned short what)
	{
		unsigned char m,i,j;
		
			if((what==ONE_MINERAL_DRONE_TO_GAS)&&(force[EXTRACTOR]>0)&&(peonmins>0))
			{
				ok=1;
				peonmins--;
				peongas++;
			}
			else
			if((what==ONE_GAS_DRONE_TO_MINERAL)&&(peongas>0))
			{
				ok=1;
				peongas--;
				peonmins++;
			}
			else
			if((what==BREAK_UP_BUILDING)&&(BuildingRunning>0))
			{
				min=5000;
				n=0;
				for(i=0;i<MAX_BUILDINGS;i++)
					if(building[i].RB>0)
					{
						if((stats[2][building[i].type].type==2) && (stats[2][building[i].type].BT-building[i].RB<min)) // warum need=2? nur bei gebaeuden sinnvoll!
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
							Vespene_Av++;
						building[n].type=255;
						building[n].RB=0;
					}
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

		if( ((Supply>=stats[2][what].supply) || (stats[2][what].supply==0)) &&
			( mins>=stats[2][what].mins+((what==CARAPACE)||(what==FLYER_CARAPACE)||(what==FLYER_ATTACKS))*force[what]*75+((what==MELEE_ATTACKS)||(what==MISSILE_ATTACKS))*force[what]*50 ) &&
			( gas>=stats[2][what].gas+((what==CARAPACE)||(what==FLYER_CARAPACE)||(what==FLYER_ATTACKS))*force[what]*75+((what==MELEE_ATTACKS)||(what==MISSILE_ATTACKS))*force[what]*50 ) &&
			(nr<255) && 
			(peonmins+peongas>=1*(stats[2][what].type==2)) &&
			(larvae>=1*(stats[2][what].type==1))
			&&
			(
			 (stats[2][what].type<3)||
			 ((stats[2][what].type==4)&&(force[what]<3)&&(availible[what]==1))||
			 ((stats[2][what].type==3)&&(force[what]==0)&&(availible[what]==1))
			)
		  )

		{
			switch(what)
			{
				case ZERGLING:if(force[SPAWNING_POOL]>0) Produce(what);break;
				case HYDRALISK:if(force[HYDRALISK_DEN]>0) Produce(what);break;
				case ULTRALISK:if(force[ULTRALISK_CAVERN]>0) Produce(what);break;
				case DRONE:Produce(what);break;
				case DEFILER:if(force[DEFILER_MOUND]>0) Produce(what);break;
				case LURKER:if((force[LURKER_ASPECT]>0)&&(force[HYDRALISK]>0))
							{
								force[HYDRALISK]--;
								Produce(what);
							};break;
				case OVERLORD:Produce(what);break;
				case MUTALISK:if(force[SPIRE]+force[GREATER_SPIRE]>0) Produce(what);break;
				case GUARDIEN:if((force[GREATER_SPIRE]>0)&&(force[MUTALISK]>0))
							  {
								  force[MUTALISK]--;
								  Produce(what);
							  };break;
				case QUEEN:if(force[QUEENS_NEST]>0) Produce(what);break;
				case SCOURGE:if(force[SPIRE]+force[GREATER_SPIRE]>0) Produce(what);break;
				case HATCHERY:Produce(what);break;
				case LAIR:if((force[HATCHERY]>0)&&(force[SPAWNING_POOL]>0)&&(availible[HATCHERY]>0)) 
						  {
							  availible[HATCHERY]--;	  
							  Produce(what);
						  }
							  break;
				case HIVE:if((force[LAIR]>0)&&(force[QUEENS_NEST]>0)&&(availible[LAIR]>0))
						  {
							  availible[LAIR]--;
							  Produce(what);
						  }
						  break;
				case NYDUS_CANAL:if(force[HIVE]>0) Produce(what);break;
				case HYDRALISK_DEN:if(force[SPAWNING_POOL]>0) Produce(what);break;
				case DEFILER_MOUND:if(force[HIVE]>0) Produce(what);break;
				case GREATER_SPIRE:if((force[SPIRE]>0)&&(availible[SPIRE]>0)&&(force[HIVE]>0)) 
								   {
									   availible[SPIRE]--;
									   Produce(what);
								   };break;
				case QUEENS_NEST:if(force[LAIR]>0) Produce(what);break;
				case EVOLUTION_CHAMBER:Produce(what);break;
				case ULTRALISK_CAVERN:if(force[HIVE]>0) Produce(what);break;
				case SPIRE:if(force[LAIR]>0) Produce(what);break;
				case SPAWNING_POOL:Produce(what);break;
				case CREEP_COLONY:Produce(what);break;
				case SPORE_COLONY:if((force[EVOLUTION_CHAMBER]>0)&&(force[CREEP_COLONY]>0))
								  {
									  force[CREEP_COLONY]--;
									  Produce(what);
								  };break;
				case SUNKEN_COLONY:if((force[SPAWNING_POOL]>0)&&(force[CREEP_COLONY]>0))
								   {
									   force[CREEP_COLONY]--;
									   Produce(what);
								   };break;
				case EXTRACTOR:if(Vespene_Av>0) { Vespene_Av--;Produce(what);}break;//Fehler: wenn 2 extractoren gleichzeitig gebaut werden, gehts hier net richtig!
				case VENTRAL_SACKS:
				case ANTENNAE:
				case PNEUMATIZED_CARAPACE:if((force[LAIR]+force[HIVE]>0)&&(availible[LAIR]+availible[HIVE]>0))
											{
												if(availible[LAIR]>0) availible[LAIR]--;
												else availible[HIVE]--;
												availible[what]=0;
												Produce(what);
											};break;
				case METABOLIC_BOOST:if((force[SPAWNING_POOL]>0)&&(availible[SPAWNING_POOL]>0))
									 {
										 availible[SPAWNING_POOL]--;
										 availible[what]=0;
										 Produce(what);
									 }
									break;
				case ADRENAL_GLANDS:if((force[HIVE]>0)&&(force[SPAWNING_POOL]>0)&&(availible[SPAWNING_POOL]>0))
									{
										availible[SPAWNING_POOL]--;
										availible[what]=0;
										Produce(what);
									}
									break;
			case MUSCULAR_AUGMENTS:
			case GROOVED_SPINES:if((force[HYDRALISK_DEN]>0)&&(availible[HYDRALISK_DEN]>0))
									 {
										availible[HYDRALISK_DEN]--;
										availible[what]=0;
										Produce(what);
									 };break;
			case CHITINOUS_PLATING:if((force[ULTRALISK_CAVERN]>0)&&(availible[ULTRALISK_CAVERN]>0)) 
								   {
									   availible[ULTRALISK_CAVERN]--;
									   availible[what]=0;
									   Produce(what);
								   }
									break;
			case ANABOLIC_SYNTHESIS:if((force[ULTRALISK_CAVERN]>0)&&(availible[ULTRALISK_CAVERN]>0)) 
								   {
									   availible[ULTRALISK_CAVERN]--;
									   availible[what]=0;
									   Produce(what);
								   }
								break;
			case BURROWING:if((force[HATCHERY]+force[LAIR]+force[HIVE]>0)&&(availible[HATCHERY]+availible[LAIR]+availible[HIVE]>0)) 
						   {
							   if(availible[HATCHERY]>0)
								   availible[HATCHERY]--;
							   else if(availible[LAIR]>0)
								   availible[LAIR]--;
							   else availible[HIVE]--;
							   Produce(what);
							   availible[what]=0;
						   }
							   break;
			case ENSNARE:
			case GAMETE_MEIOSIS:
			case SPAWN_BROODLING:if((force[QUEENS_NEST]>0)&&(availible[QUEENS_NEST]>0))
								 {
									 availible[QUEENS_NEST]--;
									 Produce(what);
									 availible[what]=0;
								 }
									 break;
			case METASYNAPTIC_NODE:
			case PLAGUE:
			case CONSUME:if((force[DEFILER_MOUND]>0)&&(availible[DEFILER_MOUND]>0))
						 {
								availible[DEFILER_MOUND]--;
								Produce(what);
								availible[what]=0;
							}
							 break;


			case LURKER_ASPECT:if((force[HYDRALISK_DEN]>0)&&(force[LAIR]>0)&&(availible[HYDRALISK_DEN]>0))
							   {
								   availible[HYDRALISK_DEN]--;
								   Produce(what);
								   availible[what]=0;
							   }
								   break;
			case CARAPACE:
			case MELEE_ATTACKS:
			case MISSILE_ATTACKS:if((force[EVOLUTION_CHAMBER]>0)&&(availible[EVOLUTION_CHAMBER]>0)&&(force[HATCHERY+force[what]]>0))
									 {
										availible[EVOLUTION_CHAMBER]--;
										Produce(what);
										availible[what]=0;
									  }
									 break;
			case FLYER_CARAPACE:
			case FLYER_ATTACKS:if((force[SPIRE]>0)&&(availible[SPIRE]>0)&&(force[HATCHERY+force[what]]>0))
						 {
							  if(availible[SPIRE]>0)
								  availible[SPIRE]--;
							  else availible[GREATER_SPIRE]--;
							  Produce(what);
							  availible[what]=0;
						  }
					   break;
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
			tSupply=Supply;
			BuildingRunning=0;
			ok=0;

			if(peonmins<56)
			{
				mins+=mining_z[peonmins]; //~~~~~~~double wegmachen
				harvested_mins+=mining_z[peonmins];
			}
			else 
			{
				mins+=mining_z[56];
				harvested_mins+=mining_z[56];
			}
			if(peongas<5)
			{
				gas+=gasing_z[peongas];
				harvested_gas+=gasing_z[peongas];
			}
			else
			{
				gas+=gasing_z[4];
				harvested_gas+=gasing_z[4];
			}


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


									//noch rein, dass es waehrend dem Lauf beschleunigen kann!
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
						{
							force[building[j].type]++;
							if((force[building[j].type]>=goal[force[building[j].type]].what)&&(ftime[building[j].type]==0))                                                              ftime[building[j].type]=timer;
							if(stats[2][building[j].type].type<3)
								availible[building[j].type]++;
							else
								availible[building[j].type]=1;
							ready=1;
							for(i=0;i<BUILDING_TYPES_ZERG;i++)
								ready&=((goal[i].what<=force[i])&&((goal[i].time==0)||(goal[i].time>ftime[i])));
						}
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

			Build(Build_Av[program[IP].order]);
			tt++;
			if((ok==1)||(tt>267))
			{
				if(tt<=267) program[IP].time=timer;
				else program[IP].time=20000;
				program[IP].need_Supply=Max_Supply-tSupply;
				program[IP].have_Supply=Max_Supply;
				tt=0;
				IP++;
			}


		timer++;
	}

	length=IP;
	CalculateFitness();
/*	if(ready==0)
	{
		timer=Max_Time;
		//Bei Zeit: Zwischenziele rein, z.B. Lair, Hive, etc. ??
		
		for(i=0;i<BUILDING_TYPES_ZERG;i++)		
		if(goal[i].what>0)
		{
			if(goal[i].what>force[i])
					fitness+=((force[i]*100)/goal[i].what);
				else fitness+=100;
			switch(i)
			{
				case LURKER:if(goal[HYDRALISK].what<force[HYDRALISK])
							{
								if(goal[LURKER].what>force[HYDRALISK]-goal[HYDRALISK].what)
									fitness+=(((force[HYDRALISK]-goal[HYDRALISK].what)*50)/goal[LURKER].what);
								else fitness+=50;
							};break;
				case SPORE_COLONY:
				case SUNKEN_COLONY:if(goal[CREEP_COLONY].what<force[CREEP_COLONY])
							{
								if(goal[i].what>force[CREEP_COLONY]-goal[CREEP_COLONY].what)
									fitness+=(((force[CREEP_COLONY]-goal[CREEP_COLONY].what)*25)/goal[i].what);
								else fitness+=25;
							};break;

				case GUARDIEN:
				case DEVOURER:if(goal[MUTALISK].what<force[MUTALISK])
							{
								if(goal[i].what>force[MUTALISK]-goal[MUTALISK].what)
									fitness+=(((force[MUTALISK]-goal[MUTALISK].what)*25)/goal[i].what);
								else fitness+=25;
							};break;
				default:break;
			}
		}
*/		
}

void InitRaceSpecific()
{
	unsigned short i;
	for(i=0;i<LARVA_MAX;i++)
		larva[i]=20; // 20 Sekunden bis neue Larve aus Hatch rauskommt
	larvae=3;
	force[HATCHERY]=1;
	availible[HATCHERY]=1;
	force[DRONE]=4;
	force[OVERLORD]=1;
	larvacounter=1;
	Supply=5;
	Max_Supply=9;
}

};
