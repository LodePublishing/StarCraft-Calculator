#include "main.h"

#define BUILDING_TYPES_PROTOSS 58

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

/*tech: 
0 Cybernetics Core
1 Citadel of Adun
2 Templar Archives
3 Stargate
4 Robotics Facility
5 Observatory
6 Robotics Support Bay
7 Forge
8 Arbiter Tribunal
9 Fleet Beacon
*/		



const double gasing_p[5]=
{
	0,
	0.89,
	1.76,
	2.30,
	2.45
};

const double mining_p[57]=
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



class Player_Protoss: public RACE
{
public:
	void Set_Goals()
	{
		unsigned char i,j;
		building_types=BUILDING_TYPES_PROTOSS;
		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;
				if(stats[1][i].tech[0]==1) Ziel[CYBERNETICS_CORE]=1;
				if(stats[1][i].tech[1]==1) Ziel[CITADEL_OF_ADUN]=1;
				if(stats[1][i].tech[2]==1) Ziel[TEMPLAR_ARCHIVES]=1;
				if(stats[1][i].tech[3]==1) Ziel[STARGATE]=1;
				if(stats[1][i].tech[4]==1) Ziel[ROBOTICS_FACILITY]=1;
				if(stats[1][i].tech[5]==1) Ziel[OBSERVATORY]=1;
				if(stats[1][i].tech[6]==1) Ziel[ROBOTICS_SUPPORT_BAY]=1;
				if(stats[1][i].tech[7]==1) Ziel[FORGE]=1;
				if(stats[1][i].tech[8]==1) Ziel[ARBITER_TRIBUNAL]=1;
				if(stats[1][i].tech[9]==1) Ziel[FLEET_BEACON]=1;
			}

		Ziel[PROBE]=1;
		Ziel[NEXUS]=1;
		Ziel[GATEWAY]=1; // noch in Tech rein! 

		if((goal[ARMOR].what>1)||(goal[GROUND_WEAPONS].what>1))
		{
			Ziel[GATEWAY]=1;
			Ziel[CYBERNETICS_CORE]=1;
			Ziel[CITADEL_OF_ADUN]=1;
			Ziel[TEMPLAR_ARCHIVES]=1;
		}	
		if((goal[PLATING].what>1)||(goal[AIR_WEAPONS].what>1))
		{
			Ziel[GATEWAY]=1;
			Ziel[CYBERNETICS_CORE]=1;
			Ziel[STARGATE]=1;
			Ziel[FLEET_BEACON]=1;
		}

/*		if((wallin==3)||(wallin==4))
		{
			Ziel[FORGE]=1;
			Ziel[PHOTON_CANNON]=1;
			goal[PHOTON_CANNON]+=2;
		}

		if((wallin==3)||(wallin==2))
		{
			if(goal[GATEWAY]==0) goal[GATEWAY]=1;
			if(goal[ZEALOT]<3) goal[ZEALOT]=3;
		}*/



		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
			if(Ziel[i]>goal[i].what)
				goal[i].what=Ziel[i];
		
		Ziel[PYLON]=1;
		Ziel[GATEWAY]=1;



		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
			Goal_Harvested_Gas+=(goal[i].what*stats[1][i].gas);

		if(Goal_Harvested_Gas>0)
		{
			Ziel[ASSIMILATOR]=1;
			if(goal[ASSIMILATOR].what==0) goal[ASSIMILATOR].what=1;
			Ziel[ONE_MINERAL_PROBE_TO_GAS]=1;
			Ziel[ONE_GAS_PROBE_TO_MINERAL]=1;
		}

		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
			Goal_Harvested_Mins+=(goal[i].what*stats[1][i].mins);
		Goal_Harvested_Mins*=1.1;

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
	}

	void Produce(unsigned short who)
	{
		if((who>=ARMOR)&&(who<=PLASMA_SHIELDS))
		{
			building[nr].on_the_run=0;
			building[nr].RB=stats[1][who].BT+force[who]*32;
			switch(who)
			{
				case PLATING:
				case ARMOR:
				case AIR_WEAPONS:mins-=stats[1][who].mins+force[who]*75;gas-=stats[1][who].gas+force[who]*75;break;
				case GROUND_WEAPONS:mins-=stats[1][who].mins+force[who]*50;gas-=stats[1][who].gas+force[who]*50;break;
				case PLASMA_SHIELDS:mins-=stats[1][who].mins+force[who]*100;gas-=stats[1][who].gas+force[who]*100;break;
				default:break;
			}
		}	
		else
		{
			building[nr].RB=stats[1][who].BT+(stats[1][who].type==2)*3; // 3 Spielsekunden um zum Bauplatz zu fahren 

			mins-=stats[1][who].mins;
		    gas-=stats[1][who].gas;
			building[nr].on_the_run=0;
		}
		building[nr].type=who;
		Supply-=stats[1][who].supply;

		ok=1;
		building[nr].on_the_run=0;
	}

	
	
	void Build(unsigned short what)
	{
	   unsigned char m;

		if((stats[1][what].type==2)&&(what!=PYLON)&&(force[PYLON]==0)&&(what!=ASSIMILATOR)&&(what!=NEXUS))
			return;
	
			if((what==ONE_MINERAL_PROBE_TO_GAS)&&(force[ASSIMILATOR]>0)&&(peonmins>0))
			{
				ok=1;
				peonmins--;
				peongas++;
			}
			else
			if((what==ONE_GAS_PROBE_TO_MINERAL)&&(peongas>0))
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

		if( ((Supply>=stats[1][what].supply) || (stats[1][what].supply==0)) &&
			( mins>=stats[1][what].mins+((what==ARMOR)||(what==PLATING)||(what==AIR_WEAPONS))*force[what]*75+(what==GROUND_WEAPONS)*force[what]*50+(what==PLASMA_SHIELDS)*force[what]*100) &&
			(  gas>=stats[1][what].gas +((what==ARMOR)||(what==PLATING)||(what==AIR_WEAPONS))*force[what]*75+(what==GROUND_WEAPONS)*force[what]*50+(what==PLASMA_SHIELDS)*force[what]*100) &&
			(nr<255) && 
			(peonmins+peongas>=1*(stats[1][what].type==2))
			&&
			(
			 (stats[1][what].type<3)||
			 ((stats[1][what].type==4)&&(force[what]<3)&&(availible[what]==1))||
			 ((stats[1][what].type==3)&&(force[what]==0)&&(availible[what]==1))
			)

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
								   availible[what]=0;
								   availible[TEMPLAR_ARCHIVES]--;
							   };break;


				case KHAYDARIN_CORE:
				case RECALL:
				case STASIS_FIELD:if((force[ARBITER_TRIBUNAL]>0)&&(availible[ARBITER_TRIBUNAL]>0))
							   {
								   Produce(what);
								   availible[what]=0;
								   availible[ARBITER_TRIBUNAL]--;
							   };break;

				case ARGUS_JEWEL:
				case APIAL_SENSORS:
				case GRAVITIC_THRUSTERS:				
				case DISRUPTION_WEB:
				case CARRIER_CAPACITY:if((force[FLEET_BEACON]>0)&&(availible[FLEET_BEACON]>0))
							   {
								   Produce(what);
								   availible[what]=0;
								   availible[FLEET_BEACON]--;
							   };break;

				case LEG_ENHANCEMENTS:if((force[CITADEL_OF_ADUN]>0)&&(availible[CITADEL_OF_ADUN]>0))
							   {
								   Produce(what);
								   availible[what]=0;
								   availible[CITADEL_OF_ADUN]--;
							   };break;

				

				case GRAVITIC_DRIVE:
				case SCARAB_DAMAGE:
				case REAVER_CAPACITY:if((force[ROBOTICS_SUPPORT_BAY]>0)&&(availible[ROBOTICS_SUPPORT_BAY]>0))
									 {
										 Produce(what);
										 availible[what]=0;
										 availible[ROBOTICS_SUPPORT_BAY]--;
									 };break;




				case SENSOR_ARRAY:
				case GRAVITIC_BOOSTERS:if((force[OBSERVATORY]>0)&&(availible[OBSERVATORY]>0))
									 {
										 Produce(what);
										 availible[what]=0;
										 availible[OBSERVATORY]--;
									 };break;

				case SINGULARITY_CHARGE:
				case PLATING:
				case AIR_WEAPONS:if((force[CYBERNETICS_CORE]>0)&&(availible[CYBERNETICS_CORE]>0)&&((force[what]==0)||(force[FLEET_BEACON]>0))) 
								 {
									 Produce(what);
									 availible[what]=0;
									 availible[CYBERNETICS_CORE]--;
								 };break;

				case ARMOR:
				case GROUND_WEAPONS:
				case PLASMA_SHIELDS:if((force[FORGE]>0)&&(availible[FORGE]>0)&&(availible[what]>0)) 
									{
										Produce(what);
										availible[what]=0;
										availible[FORGE]--;										
									};break;								 
				default:break;
			}	
		}
	}
	}

	
	void Calculate()
	{
		unsigned short tt,i,j;
		ready=0;
		timer=0;
		harvested_gas=0;
		harvested_mins=0;
		//gasready=0;
		//minsready=0;
		Vespene_Av=setup.Vespene_Geysirs;		
		tt=0;
		

		while((timer<setup.Max_Time) && (ready==0) && (IP<MAX_LENGTH))
		{			
	/*		if((Scout_Time<9999)&&(scout==0)&&(timer>Scout_Time))
			{
				scout=1;
				if(peonmins>0)
					peonmins--;
				else peongas--;
				Scout_Time=timer;
			}*/
			
			BuildingRunning=0;
			ok=0;

			if(peonmins<56)
			{
				mins+=mining_p[peonmins]; //~~~~~~~double wegmachen
				harvested_mins+=mining_p[peonmins];
			}
			else 
			{
				mins+=mining_p[56];
				harvested_mins+=mining_p[56];
			}
			if(peongas<5)
			{
				gas+=gasing_p[peongas];
				harvested_gas+=gasing_p[peongas];
			}
			else
			{
				gas+=gasing_p[4];
				harvested_gas+=gasing_p[4];
			}


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
									building[j].RB+=(unsigned short)((/*Main_Production*Time_to_Front+*/setup.Time_to_Enemy)*0.75);
								else
									building[j].RB+=(/*Main_Production*Time_to_Front+*/setup.Time_to_Enemy);
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
								building[j].RB+=(/*Main_Production*Time_to_Front+*/setup.Time_to_Enemy);
								break;
							case CARRIER:
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
								break;
							case HIGH_TEMPLAR:
								building[j].RB+=(unsigned short)(/*Main_Production*Time_to_Front+*/setup.Time_to_Enemy*1.25);
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
							case PYLON:Supply+=8;break;
							case NEXUS:Supply+=9;break;
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
						{
							force[building[j].type]++;
							if((force[building[j].type]>=goal[force[building[j].type]].what)&&(ftime[building[j].type]==0))
								ftime[building[j].type]=timer;
							if(stats[1][building[j].type].type<3)
								availible[building[j].type]++;
							else
								availible[building[j].type]=1;
							ready=1;
							for(i=0;i<BUILDING_TYPES_PROTOSS;i++)
								ready&=((goal[i].what<=force[i])&&((goal[i].time>=ftime[i])||(goal[i].time==0)));
						//	if((harvested_mins >= Goal_Harvested_Mins)&&(minsready==0)) minsready=(timer*100)/Max_Time;
						//	if((harvested_gas >= Goal_Harvested_Gas)&&(gasready==0)) gasready=(timer*100)/Max_Time;
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
				program[IP].temp=availible[GATEWAY];
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


void InitRaceSpecific()
{
	force[NEXUS]=1;
	availible[NEXUS]=1;
	force[PROBE]=4;
	Supply=5;
}

};
