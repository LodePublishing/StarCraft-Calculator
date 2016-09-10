#include "race.h"
#include "settings.h"
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// TODO: reimplement/recheck the speed of the units

void RACE::adjustMineralHarvest(int loc)
{
	if(loc==0)
	{
		for(int j=45;j--;)
			mineralHarvestPerSecond[0][j]=0;
	}
	else
	if(location[loc].force[MINERALS]>0)//TODO Check auf Hauptgebaeude machen! Fernsammeln!
	{
		for(int i=0;i<45;i++)
		if(i*8<45*location[loc].force[MINERALS])
		{
			int k=0;
			for(int j=0;j<45;j++)
				if(i*8<=j*location[loc].force[MINERALS]) { k=j;j=45;}
			mineralHarvestPerSecond[loc][i]=basicMineralHarvestPerSecond[k]*location[loc].force[MINERALS]/8;
		}
		else mineralHarvestPerSecond[loc][i]=basicMineralHarvestPerSecond[44]*location[loc].force[MINERALS]/8;
	}
}

void RACE::adjustGasHarvest(int loc)
{
//TODO: Gas ermoeglichen... updaten wenn Refinery gebaut wird etc.
	if(loc==0)
	{
		for(int j=5;j--;)
			gasHarvestPerSecond[0][j]=0;
	}
	else
	if(location[loc].force[REFINERY]>0)//TODO Check auf Hauptgebaeude machen! Fernsammeln!
	{
        	for(int i=0;i<5;i++)
                	gasHarvestPerSecond[loc][i]=basicGasHarvestPerSecond[i];
/*


		for(int i=5;i--;)
		if(i*8<45*location[loc].force[REFINERY])
				{
			int k=0;
					for(int j=0;j<5;j++)
						if(i*8<=j*location[loc].force[REFINERY]) { k=j;j=45;}
			gasHarvestPerSecond[loc][i]=basicGasHarvestPerSecond[k]*location[loc].force[REFINERY]/8;
		}
		else gasHarvestPerSecond[loc][i]=basicGasHarvestPerSecond[44]*location[loc].force[REFINERY]/8;*/
	}
}

void RACE::calculate()
{
//ZERG: Larvenproduktion!  CREEP!
//PROTOSS: Bauen: Hin und rueckfahren! PYLON!
	int timeout=pSet->ga.maxTimeOut;
	int time=pSet->ga.maxTime;
	int ready=0;
	IP=pSet->ga.maxLength-1;
//mins, gas hier rein...
	while((time)&&(!ready)&&(IP))
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
		if((ok)||(!timeout))
		{
			timeout=pSet->ga.maxTimeOut;
			IP--;
		}
	
		Building* build;//=&(building[MAX_BUILDINGS-1]);
//!!!???		for(int j=MAX_BUILDINGS;j--;build=&(building[j]))
		for(int j=MAX_BUILDINGS;j--;)
		{
			build=&building[j];
			if(build->RB)
			{
				if(!(--(build->RB)))
				{
					const UNIT_STATISTICS* stat=&pStats[build->type];
#ifdef SCCDEBUG
					printf("%s built [%i].\n",stat->name,build->location);
#endif		
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
					if(stat->create>0) //one additional unit (zerglings, scourge, comsat, etc.)
					{ //here no unitCount! ~~~
						location[build->location].force[stat->create]++;
						location[build->location].availible[stat->create]++;
						location[0].force[stat->create]++;
						location[0].availible[stat->create]++;
						// ~~~~ Ja... geht schon... aber kann ja auch mal was anderes sein...
					}
					//evtl noch location==0 als 'egal wo' einfuehren
					for(int i=MAX_GOALS;i--;)
						if((goal[i].unit>0)&&((goal[i].location==0)||(build->location==goal[i].location))&&(build->type==goal[i].unit)&&((goal[i].time==0)||(time<=goal[i].time)))
							ftime[build->type]=time;
					
					ready=1;
					for(int i=MAX_GOALS;i--;)
						
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
	if(ready) pFitness=time;
	calculateFitness(ready);
	
	//TODO: Auch voruebergehende Ziele miteinberechnen (Bewegungen!)
	//Also quasi eine zweite Goalreihe rein um scvs/Einheiten zu belohnen die bestimmte Orte besetzen... erstmal nur scvs... also z.B. int tempGoal...
	//mmmh... aber was reinschreiben? baue barracks bei Ort bla => belohne EINMAL ein scv bei ort bla
}

// falschen Standort ueber distances abrechnen! (100-distance oder so... je nach dem wieviele am falschen Ort sind!)


void RACE::calculateFitness(int ready)
{
	int bonus[MAX_LOCATIONS][UNIT_TYPE_COUNT]; // temporary data to check whether a bonus is already given (only applies if force > goal)
	sFitness=(harvested_mins+harvested_gas); //TODO: evtl gas und mins (wie urspruenglich eigentlich) in Verhaeltnis setyen wieviel es jeweils Geysire/Mineralien gibt...
//TODO: Nicht alle Einheiten am Ort? => Ort egal sein lassen aber zur Zeit hinzuzaehlen
	// Nicht alle Einheiten ueberhaupt gebaut UND nicht alle am Ort => nur viertel Bonus fuer Einheiten die nicht am Ort sind

	if(!ready)
	{
		pFitness=0;
		 for(int i=MAX_GOALS;i--;)
		 	if(goal[i].count>0)
			{
				if( ((goal[i].location==0)&&(goal[i].count>location[0].force[goal[i].unit])) || ( (goal[i].location>0)&&(goal[i].count>location[goal[i].location].force[goal[i].unit])) )
				{
					//total points: (Am Ort befindliche Einheiten + (Summe aller Locations(100-distance)/100)) / Goalcount
					//TODO: Absteigen und markieren der benutzten wbfs! Also zuerst die eigentliche location abchecken, dann nach links und rechts die naehesten hinzuziehen
					//evtl direkt von den locations die wbfs erstmal abziehen und am Schluss nochmal alle goals durchlaufen und den Rest verteilen!
					int sumup=0;
					int bon=0;
					if(goal[i].location==0)
						sumup=location[0].force[goal[i].unit]*100;
					else
					{
						sumup=location[goal[i].location].force[goal[i].unit];
						bon=goal[i].count-location[goal[i].location].force[goal[i].unit];
						for(int j=1;(j<MAX_LOCATIONS)&&(bon>0);j++)
							if(j!=goal[i].location)
							{
								if(bon>location[j].force[goal[i].unit])
								{
									sumup+=location[j].force[goal[i].unit]*(100-pSet->map[j].distance[goal[i].location]);
									bon-=location[j].force[goal[i].unit];
								}
								else 
								{
									sumup+=bon*(100-pSet->map[j].distance[goal[i].location]);
									bon=0;
								}
							}
					}
					//TODO: Hier gibts Probleme wenn mehrere goals gleicher Units an unterschiedlichen Orten existieren...
					// evtl funktionsglobales bonus System wie bei den '@' in scc.cpp einfuegen
					// bissl komplex da mans ja den einzelnen goals verteilen muss...
					if(goal[i].time>0)
					{
						if(ftime[i]>0)
							pFitness+=(goal[i].time*sumup)/(goal[i].count*ftime[i]);
						else
							pFitness+=(goal[i].time*sumup)/(goal[i].count*pSet->ga.maxTime);
					}
					else
						pFitness+=sumup/goal[i].count;
				}
				else if( ((goal[i].location==0)&&(goal[i].count<=location[0].force[goal[i].unit])) || ( (goal[i].location>0)&&(goal[i].count<=location[goal[i].location].force[goal[i].unit])) )
						//force >= goal
				{
					if((goal[i].time>0)&&(ftime[i]>goal[i].time))
						pFitness+=(goal[i].time*100/ftime[i]);
					else pFitness+=100;
//				if(goal[i].count<location[goal[i].location].force[goal[i].unit])
//					sFitness-=(location[goal[i].location].force[goal[i].unit])*(gpStats[i].mins+gpStats[i].gas);
				}
			}
// TODO: Check for very small 'goal.time' values, probably in scc.cpp!!	

//Bonus: Sind noch Plaetze offen?
		 
/*		for(int i=MAX_LOCATIONS;i--;)
		       for(int j=UNIT_TYPE_COUNT;j--;)
			       bonus[i][j]=0;
	
		for(int i=MAX_GOALS;i--;)
			if(location[goal[i].location].force[goal[i].unit]<goal[i].count)
				bonus[goal[i].location][goal[i].unit]+=goal[i].count-location[goal[i].location].force[goal[i].unit];
		for(int i=MAX_BUILDINGS;i--;)
			if((building[i].RB>0)&&(bonus[building[i].type][building[i].location]>0))
			{
			//erstmal ohne Zeit...
				pFitness+=((building[i].RB*100)/((location[building[i].location].force[building[i].type]+bonus[building[i].type][building[i].location])*pStats[building[i].type].BT));
				/*
				
				if((goal[building[i].type].time>0)&&(location[building[i].location].force[building[i].type]==0))
					pFitness+=(building[i].RB*100*goal[building[i].type].time*location[0].force[i])/(goal[building[i].type].count*gpStats[building[i].type].BT*pSet->Max_Time);
				else 				   		
					pFitness+=((building[i].RB*100)/(goal[building[i].type].count*gpStats[building[i].type].BT));*/
//				bonus[building[i].location][building[i].type]--;
//			}
	}
	else   // all goals fulfilled, fitness <- timer 
	{
		for(int i=MAX_GOALS;i--;)
			if(goal[i].count>0)
				pFitness+=100;
	}
}



int RACE::buildGene(int what)
{
	const UNIT_STATISTICS* stat=&pStats[what];
	int ok=0;
	if(what<=EXTRACTOR+1)
	{
//TODO: Array und testen wo der comp am meisten haengenbleibt und abbricht... moeglichst dann nach oben bringen!
//	printf("Building %s [%i].\n",stat->name,window);
		if(
			((stat->prerequisite[0]==0)||(location[0].force[stat->prerequisite[0]]>0))&&
			((stat->prerequisite[1]==0)||(location[0].force[stat->prerequisite[1]]>0))&&
			((stat->prerequisite[2]==0)||(location[0].force[stat->prerequisite[2]]>0))
			&&
			( ((stat->facility[0]>0)&&(location[0].availible[stat->facility[0]]>0))||
			  ((stat->facility[1]>0)&&(location[0].availible[stat->facility[1]]>0))||
			  ((stat->facility[2]>0)&&(location[0].availible[stat->facility[2]]>0))||
			  ((stat->facility[0]==0)&&(stat->facility[1]==0)&&(stat->facility[2]==0))
			)
			&&
			(mins>=stat->mins+stat->upgrade_cost*location[0].force[what])&&
			(gas>=stat->gas+stat->upgrade_cost*location[0].force[what])
			&&
			
			((supply>=stat->supply)||(stat->supply<=0))&&
			((stat->facility2==0)||(location[0].availible[stat->facility2]>0)))
			{
				//Zuerst: availible pruefen ob am Ort gebaut werden kann
				//Wenn nicht => +/- absteigen bis alle locations durch sind
		
				int fac=0;
				int loc=window;
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
							//nr=MAX_BUILDINGS;
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
					//	building[nr].IP=IP;
					} //kk!=1?
				}
			}
	else // what > EXTRACTOR+1
	{
		switch(what)
		{
			case WINDOW_MOVE_ADD_3:
			{
				ok=1;
				prev=window;
				if(window<MAX_LOCATIONS-3) window+=3;
				else window=window+4-MAX_LOCATIONS;
			};break;
			case WINDOW_MOVE_ADD_1:
				{
					ok=1;
					prev=window;
					if(window<MAX_LOCATIONS-1) window++;
					else window=1;					
				};break;				
			case WINDOW_MOVE_SUB_1:
				{
					ok=1;
					prev=window;
					if(window>1) window--;
					else window=MAX_LOCATIONS-1;					
				};break;
			case WINDOW_MOVE_PREV:
				if(window!=prev)
				{
					ok=1;
					int temp=window;window=prev;prev=temp;					
				};break;
			case MOVE_FROM_HERE:
				if(start!=window)
				{
					ok=1;
					start=window;					
				};break;
			case MOVE_TO_HERE:if((start!=window)&&(IP>0))
						  //move ALL units (type specified in IP-1) at that location!
				{
					IP--;
					int what=0;
					int dominant=0;
					if((Code[0][IP]>Code[1][IP])&&(pStats[genoToPhaenotype[Code[0][IP]]].speed>0)&&(location[start].availible[genoToPhaenotype[Code[0][IP]]]>0))
					{
						what=genoToPhaenotype[Code[dominant=0][IP]];
						ok=1;
					}
					else if((pStats[genoToPhaenotype[Code[1][IP]]].speed>0)&&(location[start].availible[genoToPhaenotype[Code[1][IP]]]>0))
					{
						what=genoToPhaenotype[Code[dominant=1][IP]];
						ok=1;
					}
					else if(location[start].availible[SCV]>0) 
					{
						what=SCV;
						ok=1;
					}
//	 TODO else  ?? alle durchsuchen bis ein scv gefunden wurde? mmmh...
						
					if(ok)
					{
						int nr=0;
						while((nr<MAX_BUILDINGS-1)&&(building[nr].RB))
						{
							nr++;
						//	nr=MAX_BUILDINGS;
						}
						//TODO: Fehler wenn nicht genug buildings
						building[nr].facility=0;
						building[nr].location=window;
					       	building[nr].type=what;
						building[nr].RB=map[start].distance[window]*100/pStats[what].speed;
//						building[nr].IP=IP;
						// 2x Unit => send 12/All instead of just one unit there
						if((IP>0)&&((Code[0][IP-1]==Code[dominant][IP])||(Code[1][IP-1]==Code[dominant][IP])))
							{
								if(location[start].availible[what]>12)
									building[nr].unitCount=12;
								else building[nr].unitCount=location[start].availible[what];
								IP--;
								//TODO dominance... und 12 checken... evtl weniger
							}
						else 
							building[nr].unitCount=1;
						location[start].availible[building[nr].type]-=building[nr].unitCount;
						location[start].force[building[nr].type]-=building[nr].unitCount;
						location[0].force[building[nr].type]-=building[nr].unitCount;
						location[0].availible[building[nr].type]-=building[nr].unitCount;
					}
				};break;//move the units!
			default:break;
		}

/*      else
      if((gRace==ZERG)&&(what==BREAK_UP_BUILDING)&&(BuildingRunning>0)) // lieber eine variable mit last_gebaeude oder so machen und da die Daten speichern, anstatt Programm oder buildings durchzulaufen...
			{
				int min=5000;
				int n=0;
				for(int i=0;i<MAX_BUILDINGS;i++)
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
	}
	return ok;
}


void RACE::harvestResources()
{
//	int t=(rand()%10)-5;
	for(int i=1;i<MAX_LOCATIONS;i++)//~~
	{
		if((location[i].force[MINERALS]>0)&&(location[i].force[COMMAND_CENTER]>0))			
				//TODO: Fernsammeln einbauen! also z.B. gas von entfernter Exe ohne Hauptgebaeude...
				//TODO!! Protoss/Zerg Hauptgebaeude!
		{
			int s=location[i].availible[SCV];
			if(s>0)
			{
				if(s<56) //~~
				{
					mins+=mineralHarvestPerSecond[i][s];
				       	//~~~ neu berechnen / Tabelle anlegen! sind ja nicht bei jeder Exe gleichviel Mineralien...
					harvested_mins+=mineralHarvestPerSecond[i][s]; //~~~
				}
				else
				{
					mins+=mineralHarvestPerSecond[i][56];
					harvested_mins+=mineralHarvestPerSecond[i][56];
				}
			}
		}
		if(location[i].force[EXTRACTOR]>0) //mehrere extractoren noch ermoeglichen!!!
			//evtl auch einfach die location updaten sobald ein extraktor gebaut wird......
		{
			int s=location[i].availible[GAS_SCV];
			if(s>0)
			{
				if(s<4)
				{
					gas+=gasHarvestPerSecond[i][s];
					harvested_gas+=gasHarvestPerSecond[i][s];
				}
				else
				{
					gas+=gasHarvestPerSecond[i][4];;
					harvested_gas+=gasHarvestPerSecond[i][4];
				}
			}
		}
	}
}

void RACE::mutateGeneCode()
{
	if(length==0) return;
	if(rand()%100==0)
	{
       		if(mutationRate>100)
			mutationRate-=rand()%100;
		else mutationRate+=rand()%100;
	}
	for(int x=MAX_LENGTH;x--;) //length
		if(rand()%mutationRate==0)
		{
			switch(rand()%6)
			{
				//TODO: wenn generateBuildOrder==1 dann bleibts stehen!
				case 0://delete one variabel entry and move - Mehrere Schmieden/Kasernen etc. zulassen!
					if((!pSet->ga.generateBuildOrder)||((isVariable[phaenoToGenotype[Code[0][x]]]==1)&&(isVariable[phaenoToGenotype[Code[1][x]]]==1)))
					for(int y=x;y<MAX_LENGTH-1;y++)
					{
						Code[0][y]=Code[0][y+1];
						Code[1][y]=Code[1][y+1];
					};
					break;
				case 1://add one variabel entry
					for(int y=MAX_LENGTH-1;y>x;y--)
					{
						Code[0][y]=Code[0][y-1];
						Code[1][y]=Code[1][y-1];
					}
					{
					int y=rand()%maxBuildTypes;
					if(pSet->ga.generateBuildOrder)
						while(isVariable[y]==0) y=rand()%maxBuildTypes;
					Code[0][x]=y;
					y=rand()%maxBuildTypes;
					if(pSet->ga.generateBuildOrder)
						while(isVariable[y]==0) y=rand()%maxBuildTypes;
					Code[1][x]=y;
					};break;
				case 2://change one entry
					{
						int k=rand()%2;
						if(isVariable[phaenoToGenotype[Code[k][x]]]==1)
						{
							int y=rand()%maxBuildTypes;//Optimieren
							if(pSet->ga.generateBuildOrder)
								while(isVariable[y]==0) y=rand()%maxBuildTypes;
							Code[k][x]=y;
						};
					};break;
				case 3://exchange two entries
					{
						int y=rand()%MAX_LENGTH; //TODO: Aendern in bevorzugtes Ziel => Naehe
						if(abs(x-y)>(MAX_LENGTH/2)) y=rand()%MAX_LENGTH;
						if(x!=y)
						{
							int k=rand()%2;
							int ta=Code[k][x];
							Code[k][x]=Code[k][y];
							Code[k][y]=ta;
						}
					};break;
				case 4://exchange two entries
					{
						int y=rand()%MAX_LENGTH; //TODO: Aendern in bevorzugtes Ziel => Naehe
						if(abs(x-y)>(MAX_LENGTH/2)) y=rand()%MAX_LENGTH;
						if(x!=y)
						{
							int ta=Code[0][x];
							Code[0][x]=Code[0][y];
							Code[0][y]=ta;
							ta=Code[1][x];
							Code[1][x]=Code[1][y];
							Code[1][y]=ta;
						}
					};break;
				case 5://move a block of orders  [a..b..ta..tb..c..d] -> [a..ta..tb..b..c..d]
					//~~~
					if(length>2)
					{
						int ttt;
						int ta=rand()%(length-2)+1; //>0    <length-2
						int tb=rand()%(length-1)+2; //>1   <length-1 
						while(ta==tb) tb=rand()%(length-1)+2;
						if(ta>tb) {ttt=tb;tb=ta;ta=ttt;}; //~~
						int y=rand()%length; //move it here
						while((y<=tb)&&(y>=ta)) y=rand()%length;
						int tmp[MAX_LENGTH];
						if(y>tb)
						{
							for(int i=0;i<y-tb;i++) tmp[i]=Code[0][i+tb];
							for(int i=ta;i<tb;i++) Code[0][i+y-tb]=Code[0][i];
							for(int i=0;i<y-tb;i++) Code[0][ta+i]=tmp[i];
							for(int i=0;i<y-tb;i++) tmp[i]=Code[1][i+tb];
							for(int i=ta;i<tb;i++) Code[1][i+y-tb]=Code[1][i];
							for(int i=0;i<y-tb;i++) Code[1][ta+i]=tmp[i];
						}
						else
						if(y<ta)
						{
							for(int i=0;i<ta-y;i++) tmp[i]=Code[0][i+y];
							for(int i=ta;i<tb;i++) Code[0][y+i-ta]=Code[0][i];
							for(int i=0;i<ta-y;i++) Code[0][tb-y]=tmp[i];
							for(int i=0;i<ta-y;i++) tmp[i]=Code[1][i+y];
							for(int i=ta;i<tb;i++) Code[1][y+i-ta]=Code[1][i];
							for(int i=0;i<ta-y;i++) Code[1][tb-y]=tmp[i];
						}
					};break;
			}
		}
}


// Reset all ongoing data (between two runs)
void RACE::resetData() // resets all data to standard starting values
{
	for(int i=UNIT_TYPE_COUNT;i--;)
		ftime[i]=0;
	for(int i=MAX_BUILDINGS;i--;)
	{
	       building[i].RB=0;
	       building[i].type=255;
//	       building[i].IP=0;
	       building[i].location=0;
	       building[i].unitCount=0;
	}
	pFitness=0;
	sFitness=0;
	harvested_gas=0;
	harvested_mins=0;
	start=1;window=1;prev=1; //location 0 is for globalForce, so take location 1 for starting point instead
	mins=pSet->misc.mins;
	gas=pSet->misc.gas;
	supply=pSet->misc.supply;
	maxSupply=pSet->misc.maxSupply;
}


void RACE::init()
{
	pStats=pSet->pStats;
	basicMineralHarvestPerSecond=pSet->misc.pMineralHarvestPerSecond;
	basicGasHarvestPerSecond=pSet->misc.pGasHarvestPerSecond;
	adjustGoals(); //goals und buildable kopieren, goalcount etc.
//#ifdef DEBUGSCC	
	generateBasicBuildOrder();
	initialized=1;
}


void RACE::adjustGoals()
{
// TODO: Maybe additional checks of the data sets here...
//Anfangsforce checken
	memcpy(goal,pSet->goalList.goal,sizeof(GOAL)*MAX_GOALS);
	for(int i=MAX_GOALS;i--;)
		if(goal[i].count>0)
			printf("Added %s [%i] to goal list.\n",pStats[goal[i].unit].name,goal[i].location);
	maxBuildTypes=0;
	for(int i=UNIT_TYPE_COUNT;i--;)
		if(isBuildable[i]==1)
		{
//#ifdef DEBUGSCC
			printf("%s is buildable.\n",pStats[i].name);
//#endif
			genoToPhaenotype[maxBuildTypes]=i;
			phaenoToGenotype[i]=maxBuildTypes;
			maxBuildTypes++;
		}
}


void RACE::generateBasicBuildOrder()
{
	//problem wieder mit keep/castle
	//pre[GOALS]
//	int build_max,sup;
//	build_max=0;
	for(int i=MAX_LENGTH;i--;)
	{
		basicBuildOrder[0][i]=0;
		basicBuildOrder[1][i]=0;
	}
	basicLength=0;
/*	while((supply<maxSupply)&&(basicLength<20))
	{
		if(supply<maxSupply)
		{
			basicBuildOrder[0][basicLength]=phaenoToGenotype[SCV];
			supply++;
		} else
		{
			basicBuildOrder[0][basicLength]=phaenoToGenotype[SUPPLY_DEPOT];
		}
		basicLength++;
	}*/
	
/*	
//~~~ allgemeines supply, arbeiter, gas/min, Main, ref, ... einfuehren... is teilweise schon, aber v.a. bei hatch etc. noch machen!
	
//TODO: Arbeiter, Raffinerie und Supplysachen deklarieren und hier allgemein durchlaufen lassen
	switch(gRace)
	{
		case TERRA:
			basicBuildOrder[0][0]=phaenoToGenotype[SCV];
			basicBuildOrder[0][1]=phaenoToGenotype[SCV];
			basicBuildOrder[0][2]=phaenoToGenotype[SCV];
			basicBuildOrder[0][3]=phaenoToGenotype[SCV];
			basicBuildOrder[0][4]=phaenoToGenotype[SCV];
			basicBuildOrder[0][5]=phaenoToGenotype[SCV];
			basicBuildOrder[0][6]=phaenoToGenotype[SUPPLY_DEPOT];
			if(isBuildable[REFINERY]==1)
			{
				basicBuildOrder[0][7]=phaenoToGenotype[REFINERY];
				basicBuildOrder[0][8]=phaenoToGenotype[GAS_SCV];
				basicBuildOrder[0][9]=phaenoToGenotype[GAS_SCV];
				basicBuildOrder[0][10]=phaenoToGenotype[GAS_SCV];
			};
			basicLength=10;sup=8;
			break;
		case PROTOSS:
			basicBuildOrder[0][0]=phaenoToGenotype[PROBE];
			basicBuildOrder[0][1]=phaenoToGenotype[PROBE];
			basicBuildOrder[0][2]=phaenoToGenotype[PROBE];
			basicBuildOrder[0][3]=phaenoToGenotype[PROBE];
			basicBuildOrder[0][4]=phaenoToGenotype[PROBE];
			basicBuildOrder[0][5]=phaenoToGenotype[PYLON];
			if(isBuildable[ASSIMILATOR]==1)
			{
				basicBuildOrder[0][6]=phaenoToGenotype[ASSIMILATOR];
				basicBuildOrder[0][7]=phaenoToGenotype[GAS_PROBE];
				basicBuildOrder[0][8]=phaenoToGenotype[GAS_PROBE];
				basicBuildOrder[0][9]=phaenoToGenotype[GAS_PROBE];
			};
			basicLength=9;sup=8;
			break;
		case ZERG:
			basicBuildOrder[0][0]=phaenoToGenotype[DRONE];
			basicBuildOrder[0][1]=phaenoToGenotype[DRONE];
			basicBuildOrder[0][2]=phaenoToGenotype[DRONE];
			basicBuildOrder[0][3]=phaenoToGenotype[DRONE];
			basicBuildOrder[0][4]=phaenoToGenotype[DRONE];
			basicBuildOrder[0][5]=phaenoToGenotype[OVERLORD];

			if(isBuildable[EXTRACTOR]==1)
			{
				basicBuildOrder[0][6]=phaenoToGenotype[EXTRACTOR];
				basicBuildOrder[0][7]=phaenoToGenotype[GAS_DRONE];
				basicBuildOrder[0][8]=phaenoToGenotype[GAS_DRONE];
				basicBuildOrder[0][9]=phaenoToGenotype[GAS_DRONE];
			};
			basicLength=9;sup=8;
			break;
	}
	//bis hier: 08/15 Start

//	for(int j=0;j<MAX_GOALS;j++)
//		if(force[j]>0) pre[j]=force[j]; else pre[j]=0;	
//TODO: Problem bei KEEPs
	if(settings.generateBuildOrder==1)
	{
	for(k=0;k<MAX_LENGTH;k++)
	{
		j=0;
		while((j<build_max)&&(i<MAX_LENGTH-20))
		{
			if(((pre[j]<goal[j].count)&&(goal[j].count>0))||((isBuildable[j]>0)&&(force[j]==0)&&(pre[j]<isBuildable[j])))
			{
				if((gpStats[j].facility>0)&&(pre[gpStats[j].facility]==0))
					j=gpStats[j].facility;
				else if((gpStats[j].prerequisite[0]>0)&&(pre[gpStats[j].prerequisite[0]]==0))
					j=gpStats[j].prerequisite[0];
				else if((gpStats[j].prerequisite[1]>0)&&(pre[gpStats[j].prerequisite[1]]==0))
					j=gpStats[j].prerequisite[1];
				else if((gpStats[j].prerequisite[2]>0)&&(pre[gpStats[j].prerequisite[2]]==0))
					j=gpStats[j].prerequisite[2];
				else if((gpStats[j].type==UPGRADE)&&(gpStats[j].special>0)&&(pre[TIER3]==0))
					j=TIER3;
				else if((gpStats[j].special>0)&&(pre[TIER2]==0))
					j=TIER2;
				else if((gpStats[j].special>0)&&(pre[TIER3]==0))
					j=TIER3;
				else
				{
					//building!
					if(gpStats[j].type==BUILDING)//&&(gRace=ZERG))
					{
						i++;
						basicBuildOrder[i][0]=phaenoToGenotype[DRONE];
					} else
					
					if((gpStats[j].type==UNIT)&&(gpStats[j].supply>sup))
					{
						i++;
						switch(gRace)
						{
							case TERRA:basicBuildOrder[i][0]=phaenoToGenotype[SUPPLY_DEPOT];pre[SUPPLY_DEPOT]++;sup+=8;break;
							case PROTOSS:basicBuildOrder[i][0]=phaenoToGenotype[PYLON];pre[PYLON]++;sup+=8;break;
							case ZERG:basicBuildOrder[i][0]=phaenoToGenotype[OVERLORD];pre[OVERLORD]++;sup+=8;break;
							default:break;
						};
					};
					i++;
					if((gpStats[j].type==UNIT)&&(gpStats[j].supply>0)) sup-=pStats[j].supply;
					basicBuildOrder[i][0]=phaenoToGenotype[j];
					pre[j]++;
					j++;
				}
			} else j++;
		}
	}
	}*/
//	basicLength++;
	memcpy(basicBuildOrder[1],basicBuildOrder[0],MAX_LENGTH*4);
}


//Reinitialize programs with random orders
void RACE::resetGeneCode()
{
	mutationRate=500+rand()%1000;
	if((pSet->ga.generateBuildOrder)&&(basicLength>0))
	{
		memcpy(Code[0],basicBuildOrder[0],MAX_LENGTH*4);
		memcpy(Code[1],basicBuildOrder[1],MAX_LENGTH*4);
	}
	else
	for(int i=MAX_LENGTH;i--;)
	{
		Code[0][i]=rand()%maxBuildTypes;
		Code[1][i]=rand()%maxBuildTypes;
	}
}

void RACE::crossOver(RACE* parent2, RACE* child1, RACE* child2)
{
	int counter,num;
	counter=MAX_LENGTH;
	RACE* c;

	for(int i=0;i<MAX_LENGTH;i++)
	{
		if(rand()%counter<4)
		{
			num=MAX_LENGTH-counter;
			memcpy(&child1->Code[0][i-num],&Code[0][i-num],num*2);
			memcpy(&child1->Code[1][i-num],&parent2->Code[1][i-num],num*2);
			memcpy(&child2->Code[1][i-num],&Code[1][i-num],num*2);
			memcpy(&child2->Code[0][i-num],&parent2->Code[0][i-num],num*2);
			counter=MAX_LENGTH; //~~ TODO
			c=child1;
			child1=child2;
			child2=c;
		}
		counter--;
	}
	num=MAX_LENGTH-counter;
	memcpy(&child1->Code[0][counter],&Code[0][counter],num*2);
	memcpy(&child1->Code[1][counter],&parent2->Code[1][counter],num*2);
	memcpy(&child2->Code[1][counter],&Code[1][counter],num*2);
	memcpy(&child2->Code[0][counter],&parent2->Code[0][counter],num*2);
	
	child1->mutationRate=(2*mutationRate+parent2->mutationRate)/3;
	child2->mutationRate=(2*parent2->mutationRate+mutationRate)/3;
}


void RACE::initLocations()
{
	memcpy(location,pSet->location,sizeof(LOCATION)*MAX_LOCATIONS);
        for(int i=MAX_LOCATIONS;i--;)
        {
                adjustMineralHarvest(i);
                adjustGasHarvest(i);
        }
}

RACE::RACE()
{
	length=pSet->ga.maxLength;
	map=pSet->map;
	memcpy(isBuildable,pSet->goalList.isBuildable,UNIT_TYPE_COUNT); 
	memcpy(isVariable,pSet->goalList.isVariable,UNIT_TYPE_COUNT);
	if(!initialized) init();
	initLocations();
	resetData();
	resetGeneCode();
}

