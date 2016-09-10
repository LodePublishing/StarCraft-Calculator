#include "anarace.h"
#include <stdlib.h>
#include <string.h>

// TODO: reimplement/recheck the speed of the units
/*
void ANARACE::calculate()
{
//ZERG: Larvenproduktion!  CREEP!
//PROTOSS: Bauen: Hin und rueckfahren! PYLON!
	int timeout=pSet->ga.maxTimeOut;
	int time=pSet->ga.maxTime;
	int ready=0;
	int i,j;
	IP=pSet->ga.maxLength-1;
	//mins, gas hier rein...
	while((time)&&(!ready)&&(IP>0))
	{
//TODO: evtl ueberlegen IP zu springen... also erstmal feststellen, warum nicht gebuildet werden kann und dann in einem Ruck resources und btimes hochsetzen...
		int dominant=0;
		int ok=0;
					//evtl versuchen umzuschreiben, dass er mehrere Befehle pro Sekunde machen kann ... TODO
		if(Code[0][IP]>Code[1][IP]) //dominance
		{
			if(!(ok=buildGene(genoToPhaenotype[Code[dominant=0][IP]])))
				ok=buildGene(genoToPhaenotype[Code[dominant=1][IP]]);
		}
		else
		{
			if(!(ok=buildGene(genoToPhaenotype[Code[dominant=1][IP]])))
				ok=buildGene(genoToPhaenotype[Code[dominant=0][IP]]);
		}
                if(success.type>0)
		{
			program[IP].success[dominant].type=success.type;
			program[IP].success[dominant].loc=success.loc;
			program[IP].success[dominant].what=success.what;
		}

		if((ok)||(!timeout))
		{
			if(timeout) 
			{
				program[IP].time=pSet->ga.maxTime-time; //ANA~
		                program[IP].dominant=dominant; //ANA~
		                program[IP].type=Code[dominant][IP];
			}
			else 
			{
				program[IP].time=pSet->ga.maxTime+1;
				program[IP].success[dominant].type=TIMEOUT;
				program[IP].success[dominant].what=0;
				program[IP].success[dominant].loc=0;
			}
			program[IP].needSupply=maxSupply-supply;
			program[IP].haveSupply=maxSupply;
			
			timeout=pSet->ga.maxTimeOut;
			IP--;
		}
	
		Building* build;//=&(building[MAX_BUILDINGS-1]);
//!!!???		for(j=MAX_BUILDINGS;j--;build=&(building[j]))
		for(j=MAX_BUILDINGS;j--;)
		{
			build=&building[j];

			if(build->RB)
			{
				if(!(--(build->RB)))
				{
					const UNIT_STATISTICS* stat=&pStats[build->type];
					switch(stat->facility_type)
					{
						case IS_LOST:
							if(build->facility)
							{
								location[build->location].force[build->facility]--;
								location[0].force[build->facility]--;
								//availible was already taken account when starting the building
							}
							if(stat->facility2)
							{
								location[build->location].force[stat->facility2]--;
								location[0].force[stat->facility2]--;
							}
							break;
						case NEEDED_ONCE:break;
						case NEEDED_UNTIL_COMPLETE:
							if(build->facility)
							{
								location[build->location].availible[build->facility]++;
								location[0].availible[build->facility]++;
							}
							break; // fuer spaeter mal: Wenn in 2 Fabriken produziert wuerde wirds probmelatisch, da
//in Buiding nur eine facility gespeichert wird...
						case NEEDED_ONCE_IS_LOST:
							if(stat->facility2)
							{
								location[build->location].force[stat->facility2]--;
								location[0].force[stat->facility2]--;
							}
							break;
						case NEEDED_UNTIL_COMPLETE_IS_LOST:
							if(build->facility)
							{
								location[build->location].availible[build->facility]++;
								location[0].availible[build->facility]++;
							}
							if(stat->facility2)
							{
								location[build->location].force[stat->facility2]--;
								location[0].force[stat->facility2]--;
							}
							break;
						case NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE:
							{
								if(build->facility)
								{
									location[build->location].availible[build->facility]++;
									location[0].availible[build->facility]++;
								}
								if(stat->facility2) // special rule for upgrades!
								{
									location[build->location].force[stat->facility2]--;
									location[build->location].availible[stat->facility2]++;
									location[0].force[stat->facility2]--;
									location[0].availible[stat->facility2]++;
								};
							}
							break;
						case NEEDED_ALWAYS:break;
						default:break;
					}
					if(stat->supply<0) {supply-=stat->supply;maxSupply-=stat->supply;};
					//~~~~
					location[0].force[build->type]+=build->unitCount;
					location[0].availible[build->type]+=build->unitCount;
					location[build->location].force[build->type]+=build->unitCount;
					location[build->location].availible[build->type]+=build->unitCount;
					
					if(build->type==REFINERY) adjustGasHarvest(build->location);
					if(build->type==COMMAND_CENTER) {adjustMineralHarvest(build->location);adjustGasHarvest(build->location);}
					last[lastcounter].what=build->type;
					last[lastcounter].count=build->unitCount;
					last[lastcounter].location=build->location;

					if((stat->create)&&(!build->onTheRun)) //one additional unit (zerglings, scourge, comsat, etc.)
					{ //here no unitCount! ~~~
						location[build->location].force[stat->create]++;
						location[build->location].availible[stat->create]++;
						location[0].force[stat->create]++;
						location[0].availible[stat->create]++;
						// ~~~~ Ja... geht schon... aber kann ja auch mal was anderes sein...
					}
					//evtl noch location==0 als 'egal wo' einfuehren
					//ANA~

					program[build->IP].built=1;
					program[build->IP].location=build->location;
					lastcounter++;
	//			IP zeugs checken... length is immer 2 :/	
					for(i=MAX_GOALS;i--;)
						if((goal[i].unit>0)&&((goal[i].location==0)||(build->location==goal[i].location))&&(build->type==goal[i].unit)&&((goal[i].time==0)||(time<=goal[i].time)))
							ftime[build->type]=time;
					
					ready=1;
					for(i=MAX_GOALS;i--;)
						
						ready&=( ( ((goal[i].location==0)&&(goal[i].count<=location[0].force[goal[i].unit]))||((goal[i].location>0)&&(goal[i].count<=location[goal[i].location].force[goal[i].unit])) )&&((goal[i].time>=ftime[i])||(goal[i].time==0)));
					// oder: irgendeine location... TODO: Problem: die Einheiten koennen irgendwo sein, also nicht gesammelt an einem Fleck...
				}
			}
		}
		harvestResources();
		time--;
		timeout--;
	}
	 //end while
	length=pSet->ga.maxLength-IP;

//TODO: Alles rausschmeissen, was schon von race berechnet wurde!
	if(ready) 
	{
//		pFitness=time;
		timer=time;
	}
	else timer=pSet->ga.maxTime;
	
	//TODO: Auch voruebergehende Ziele miteinberechnen (Bewegungen!)
	//Also quasi eine zweite Goalreihe rein um scvs/Einheiten zu belohnen die bestimmte Orte besetzen... erstmal nur scvs... also z.B. int tempGoal...
	//mmmh... aber was reinschreiben? baue barracks bei Ort bla => belohne EINMAL ein scv bei ort bla
}

// falschen Standort ueber distances abrechnen! (100-distance oder so... je nach dem wieviele am falschen Ort sind!)


int ANARACE::buildGene(int what)
{
	const UNIT_STATISTICS* stat=&pStats[what];
	int ok=0;

	success.what=0;//ANA~
	success.loc=0;
	success.type=OK;

	if(what<=EXTRACTOR+1)
	{
		if((stat->prerequisite[0]>0)&&(location[0].force[stat->prerequisite[0]]==0))
		{
			success.what=stat->prerequisite[0];
			success.loc=0;
			success.type=PREREQUISITE_FAILED;
		}
		else		
		if((stat->prerequisite[1]>0)&&(location[0].force[stat->prerequisite[1]]==0))
                {
                        success.what=stat->prerequisite[1];
                        success.loc=0;
                        success.type=PREREQUISITE_FAILED;
                }
		else 
		if((stat->prerequisite[2]>0)&&(location[0].force[stat->prerequisite[2]]==0))
                {
                        success.what=stat->prerequisite[2];
                        success.loc=0;
                        success.type=PREREQUISITE_FAILED;
                }
		else
		if //ANA~

                        ( ((stat->facility[0]==0)||(location[0].availible[stat->facility[0]]==0))&&
                          ((stat->facility[1]==0)||(location[0].availible[stat->facility[1]]==0))&&
                          ((stat->facility[2]==0)||(location[0].availible[stat->facility[2]]==0))&&
                          ((stat->facility[0]>0)||(stat->facility[1]>0)||(stat->facility[2]>0))
			)
 
//TODO: availible/force[0] auf 100 setzen... naj ama guggn
		{
			if(stat->facility[0]>0)
				success.what=stat->facility[0];
			else if(stat->facility[1]>0)
				success.what=stat->facility[1];
			else if(stat->facility[2]>0)
				success.what=stat->facility[2];

			success.loc=0;
			success.type=FACILITY_FAILED;
		}
		else
		if((stat->facility2>0)&&(location[0].availible[stat->facility2]==0))
                {
                        success.what=stat->facility2;
                        success.loc=0;
                        success.type=FACILITY_FAILED;
                }
//TODO: evtl success 2 Schritte zurueckverfolgen...
		else
		if(mins<stat->mins+stat->upgrade_cost*location[0].force[what])
		{
			success.what=0;
			success.loc=0;
		        success.type=ENOUGH_MINERALS;
		}
		else
		if(gas<stat->gas+stat->upgrade_cost*location[0].force[what])
		{
			success.what=0;
			success.loc=0;
		        success.type=ENOUGH_GAS;
		}
		else
		if((supply<stat->supply)&&(stat->supply>0))
		{
			success.what=0;
			success.loc=0;
		        success.type=SUPPLY_SATISFIED;
		}
		else 
		{

				//Zuerst: availible pruefen ob am Ort gebaut werden kann
				//Wenn nicht => +/- absteigen bis alle locations durch sind
			int fac=0;
                              int loc=1;
                                if(lastcounter>0)
                                {
                                        lastcounter--;
                                        loc=last[lastcounter].location;
                                }


			if((stat->facility2==0)||(location[loc].availible[stat->facility2]>0))
				for(fac=3;fac--;)
					if( ((stat->facility[fac]>0)&&(location[loc].availible[stat->facility[fac]]>0)) || ((stat->facility[fac]==0)&&(fac==0))) 
					{
						ok=1;
						break;
					}
			if(!ok)
				for(loc=1;loc<MAX_LOCATIONS;loc++)
					if((stat->facility2==0)||(location[loc].availible[stat->facility2]>0))
					{
						for(fac=3;fac--;)
							if( ((stat->facility[fac]>0)&&(location[loc].availible[stat->facility[fac]]>0)) || ((stat->facility[fac]==0)&&(fac==0)))
							{
								ok=1;
								break;
							}
						break;
					}	
//				bewegliche Sachen ueberdenken...
//					evtl zusaetzliche Eigenschaft 'speed' einbauen (muss sowieso noch...)... bei speed>0 ... mmmh... trifft aber auch nur auf scvs zu ... weil bringt ja wenig erst mit der hydra rumzulaufen und dann zum lurker... mmmh... aber waere trotzdem zu ueberlegen...
//					auch noch ueberlegen, wenn z.B. mit scv ohne kommandozentrale woanders gesammelt wird...
//		Phagen ueber Phagen...
				if(ok)
					{
						int nr=0;
						while((nr<MAX_BUILDINGS-1)&&(building[nr].RB))
						{
							nr++;
						//	nr=MAX_BUILDINGS;
						}
						
						building[nr].facility=stat->facility[fac];
						building[nr].location=loc;
						building[nr].unitCount=1; //~~
						building[nr].RB=stat->BT+3200*(stat->facility2==what); //~~ hack :/ TODO
						mins-=stat->mins+stat->upgrade_cost*location[0].force[what];
						gas-=stat->gas+stat->upgrade_cost*location[0].force[what];
						building[nr].type=what;
						if((stat->supply>0)||((pStats[stat->facility[0]].supply<0)&&(stat->facility_type==IS_LOST))) supply-=stat->supply;
							switch(stat->facility_type)
							{
								case IS_LOST:
								if(stat->facility[fac]>0)
								{
									location[loc].availible[stat->facility[fac]]--;
									location[0].availible[stat->facility[fac]]--;
									supply+=pStats[stat->facility[fac]].supply; 
								}
								if(stat->facility2>0)
								{
									location[loc].availible[stat->facility2]--;
									location[0].availible[stat->facility2]--;
									supply+=pStats[stat->facility2].supply;
								}
								break;
							case NEEDED_ONCE:
								break;
							case NEEDED_UNTIL_COMPLETE:
								if(stat->facility[fac]>0)
								{
									location[loc].availible[stat->facility[fac]]--;
									location[0].availible[stat->facility[fac]]--;
								}
								if(stat->facility2>0)
								{
									location[loc].availible[stat->facility2]--;
									location[0].availible[stat->facility2]--; //kommt glaub nicht vor...
								}
								break;
							case NEEDED_ONCE_IS_LOST:
								if(stat->facility2>0)
								{
									location[loc].availible[stat->facility2]--;
									location[0].availible[stat->facility2]--;
									supply+=pStats[stat->facility2].supply; // <- nicht noetig :/
								}
								break;
							case NEEDED_UNTIL_COMPLETE_IS_LOST:
								if(stat->facility2>0)
								{
									location[loc].availible[stat->facility2]--;
									location[0].availible[stat->facility2]--;
									supply+=pStats[stat->facility2].supply; // <- nicht noetig :/
								}
								if(stat->facility[fac]>0)
								{
									location[loc].availible[stat->facility[fac]]--;
									location[0].availible[stat->facility[fac]]--;
								}
								break;
							case NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE:
								if(stat->facility2>0)
								{
									location[loc].availible[stat->facility2]--;						
									location[0].availible[stat->facility2]--; // no supply gain as the item is recovered... well or not? mmmh... ~~~~
								}
								if(stat->facility[fac]>0)
								{
									location[loc].availible[stat->facility[fac]]--;
									location[0].availible[stat->facility[fac]]--;
								}
								break;
							case NEEDED_ALWAYS:
								if(stat->facility[fac]>0)
								{
									location[loc].availible[stat->facility[fac]]--;
									location[0].availible[stat->facility[fac]]--;
									// supply?
								}
								if(stat->facility2>0)
								{
									location[loc].availible[stat->facility2]--;
									location[0].availible[stat->facility2]--;
								}
								break;
							default:break;
						}
	
//						building[nr].on_the_run=0;
						building[nr].IP=IP;
					} //kk!=1?
				}
			}
	else // what > EXTRACTOR+1
	{
		int count=0;
		switch(what)
		{
                       case MOVE_ONE_1_FORWARD:count=1;break;
                       case MOVE_ONE_3_FORWARD:count=3;break;
                       case MOVE_ONE_1_BACKWARD:count=-1;break;
                       default:count=0;break;
		}
               if(count>0)
                {
                        if((lastcounter>0)&&(location[last[lastcounter-1].location].availible[last[lastcounter-1].what]>0)&&(pStats[last[lastcounter-1].what].speed>0))
                                {
					lastcounter--;
                                        int nr=0;
                                        while((nr<MAX_BUILDINGS-1)&&(building[nr].RB))
                                                        nr++;
                                        //TODO: Fehler wenn nicht genug buildings
					if(location[last[lastcounter].location].availible[last[lastcounter].what]>last[lastcounter].count)
                                                building[nr].unitCount=last[lastcounter].count;
                                        else building[nr].unitCount=location[last[lastcounter].location].availible[last[lastcounter].what];
                                        building[nr].facility=0;
                                        building[nr].location=last[lastcounter].location;
                                        building[nr].type=last[lastcounter].what;
                                        building[nr].RB=pMap[last[lastcounter].location].distance[last[lastcounter].location+count]*100/pStats[last[lastcounter].what].speed;
                                        building[nr].onTheRun=1;
					building[nr].IP=IP; // ~ANA
                                                // 2x Unit => send 8/All instead of just one unit there
                                        if((IP>1)&&((Code[0][IP-1]==what)||(Code[1][IP-1]==what)))
                                        {
                    				if(location[last[lastcounter].location].availible[last[lastcounter].what]>=6)
                                                                        building[nr].unitCount=6;
                                                                else building[nr].unitCount=location[last[lastcounter].location].availible[last[lastcounter].what];
                                                                IP--;
                                                                //TODO dominance... und 8 checken... evtl weniger
                                       }
                                                location[last[lastcounter].location].availible[building[nr].type]-=building[nr].unitCount;
                                                location[last[lastcounter].location].force[building[nr].type]-=building[nr].unitCount;
                                                location[0].force[building[nr].type]-=building[nr].unitCount;
                                                location[0].availible[building[nr].type]-=building[nr].unitCount;
						ok=1;
                                }
                }
        }
					
/*      else
      if((gRace==ZERG)&&(what==BREAK_UP_BUILDING)&&(BuildingRunning>0)) // lieber eine variable mit last_gebaeude oder so machen und da die Daten speichern, anstatt Programm oder buildings durchzulaufen...
			{
				int min=5000;
				int n=0;
				for(i=0;i<MAX_BUILDINGS;i++)
					if(building[i].RB>0)
					{
						if((stats[2][building[i].type].type==2) && (stats[2][building[i].type].BT-building[i].RB<min))
		// type == 2 because this makes only sense with buildings
		// Sure... but what about Lurker, Guardien, Sunken, ...  ?
		// mmmh... on the other hand this really makes no sense :}
						{
							min=stats[2][building[i].type].BT-building[i].RB;
							n=i;
						}
					}

					if(min<5000)
					{
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
//						program[IP].built=1;
//						program[building[n].IP].built=1;
					}*/
//TODO: Verwandtschaftsgrad fuer crossing over feststellen!	
/*	if(ok)
		program[IP].built=1; //ANA~
	return ok;
}


// Reset all ongoing data (between two runs)
void ANARACE::resetData() // resets all data to standard starting values
{
	int i;
	for(i=UNIT_TYPE_COUNT;i--;)
		ftime[i]=0;
	for(i=MAX_BUILDINGS;i--;)
	{
	       building[i].RB=0;
	       building[i].type=255;
	       building[i].IP=0;
	       building[i].location=0;
	       building[i].unitCount=0;
	       building[i].onTheRun=0;
	}
       for(i=MAX_LENGTH;i--;)//ANA~
        {
                program[i].built=0;
                program[i].success[0].type=0;
		program[i].success[0].what=0;
		program[i].success[0].loc=0;
                program[i].success[1].type=0;
		program[i].success[1].what=0;
		program[i].success[1].loc=0;
						
		program[i].haveSupply=0;
                program[i].needSupply=0;
                program[i].time=pSet->ga.maxTime+1;
		program[i].type=255;
                program[i].mins=0;
                program[i].gas=0;
                program[i].temp=0;
                program[i].dominant=0;
        }
	harvestedGas=0;
	harvestedMins=0;
	mins=pSet->misc.mins;
	gas=pSet->misc.gas;
	supply=pSet->misc.supply;
	maxSupply=pSet->misc.maxSupply;
	timer=pSet->ga.maxTime;
	for(i=0;i<4;i++)
	{
		last[i].location=1;
		last[i].what=SCV;
		last[i].count=1;
	}
	for(i=4;i<MAX_LOCATIONS;i++)
	{
		last[i].location=0;
		last[i].what=0;
		last[i].count=0;
	}
	lastcounter=4;
}


void ANARACE::init()
{
	pStats=pSet->pStats;
	basicMineralHarvestPerSecond=pSet->misc.pMineralHarvestPerSecond;
	basicGasHarvestPerSecond=pSet->misc.pGasHarvestPerSecond;
	adjustGoals(); //goals und buildable kopieren, goalcount etc.
//#ifdef DEBUGSCC	
	initialized=1;
}


void ANARACE::adjustGoals()
{
	int i;
// TODO: Maybe additional checks of the data sets here...
//Anfangsforce checken
	memcpy(goal,pSet->goalList.goal,sizeof(GOAL)*MAX_GOALS);
        memcpy(isBuildable,pSet->goalList.isBuildable,UNIT_TYPE_COUNT*4);
	maxBuildTypes=0;
	for(i=UNIT_TYPE_COUNT;i--;)
		if(isBuildable[i]==1)
		{
			genoToPhaenotype[maxBuildTypes]=i;
			phaenoToGenotype[i]=maxBuildTypes;
			maxBuildTypes++;
		}
}

void ANARACE::initLocations()
{
	int i;
	memcpy(location,pSet->location,sizeof(LOCATION)*MAX_LOCATIONS);
        for(i=MAX_LOCATIONS;i--;)
        {
                adjustMineralHarvest(i);
                adjustGasHarvest(i);
        }
}*/

ANARACE::ANARACE()
{
/*	run=0;
	unchangedGenerations=0;
	generation=0;
	maxpFitness=0;
	maxsFitness=0;
	maxtFitness=0;
	length=pSet->ga.maxLength;
	pMap=pSet->pMap;
	if(!initialized) init();
	initLocations();
	resetData();*/
}

/*GOAL ANARACE::goal[MAX_GOALS];
int ANARACE::genoToPhaenotype[UNIT_TYPE_COUNT];
int ANARACE::phaenoToGenotype[UNIT_TYPE_COUNT];
int ANARACE::isBuildable[UNIT_TYPE_COUNT];
const UNIT_STATISTICS* ANARACE::pStats;
const DATA* ANARACE::pSet;
int ANARACE::initialized;
int ANARACE::maxBuildTypes;
const int* ANARACE::basicMineralHarvestPerSecond;
const int* ANARACE::basicGasHarvestPerSecond;
const MAP_LOCATION* ANARACE::pMap;
int ANARACE::lastcounter;
LAST ANARACE::last[MAX_LENGTH];*/

