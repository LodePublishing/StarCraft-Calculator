#include "race.h"
#include <stdlib.h>
#include <string.h>
// TODO: reimplement/recheck the speed of the units



/*void RACE::calculate()
{
//ZERG: Larvenproduktion!  CREEP!
//PROTOSS: Bauen: Hin und rueckfahren! PYLON!
	int timeout=pSet->ga.maxTimeOut;
	int time=pSet->ga.maxTime;
	int ready=0;
	int i,j;
	tFitness=300;
//	const SETTINGS* pSet2=pSet;
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
		if((ok)||(!timeout))
		{
			if(!timeout)
				tFitness-=2;
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
						last[lastcounter].count++;
						// ~~~~ Ja... geht schon... aber kann ja auch mal was anderes sein...
					}
					//evtl noch location==0 als 'egal wo' einfuehren
					lastcounter++;
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
	tFitness-=length;
	if(ready) pFitness=time;
	calculateFitness(ready);
	
	//TODO: Auch voruebergehende Ziele miteinberechnen (Bewegungen!)
	//Also quasi eine zweite Goalreihe rein um scvs/Einheiten zu belohnen die bestimmte Orte besetzen... erstmal nur scvs... also z.B. int tempGoal...
	//mmmh... aber was reinschreiben? baue barracks bei Ort bla => belohne EINMAL ein scv bei ort bla
}

// falschen Standort ueber distances abrechnen! (100-distance oder so... je nach dem wieviele am falschen Ort sind!)


void RACE::calculateFitness(int ready)
{
	int i;
//	int bonus[MAX_LOCATIONS][UNIT_TYPE_COUNT]; // temporary data to check whether a bonus is already given (only applies if force > goal)
	sFitness=(harvestedMins+harvestedGas); //TODO: evtl gas und mins (wie urspruenglich eigentlich) in Verhaeltnis setyen wieviel es jeweils Geysire/Mineralien gibt...
//TODO: Nicht alle Einheiten am Ort? => Ort egal sein lassen aber zur Zeit hinzuzaehlen
	// Nicht alle Einheiten ueberhaupt gebaut UND nicht alle am Ort => nur viertel Bonus fuer Einheiten die nicht am Ort sind

	if(!ready)
	{
		pFitness=0;
		 for(i=MAX_GOALS;i--;)
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
						bon=goal[i].count;
						int j=1;
						while((j<MAX_LOCATIONS)&&(bon>location[locationList[goal[i].location][j]].force[goal[i].unit]))
						{
							sumup+=location[locationList[goal[i].location][j]].force[goal[i].unit]*(100-pMap[j].distance[goal[i].location]);
							bon-=location[locationList[goal[i].location][j]].force[goal[i].unit];
							j++;
						}
						//rest
						if(j<MAX_LOCATIONS)
							sumup+=bon*(100-pMap[locationList[goal[i].location][j]].distance[goal[i].location]);
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
		 
/*		for(i=MAX_LOCATIONS;i--;)
		       for(j=UNIT_TYPE_COUNT;j--;)
			       bonus[i][j]=0;
	
		for(i=MAX_GOALS;i--;)
			if(location[goal[i].location].force[goal[i].unit]<goal[i].count)
				bonus[goal[i].location][goal[i].unit]+=goal[i].count-location[goal[i].location].force[goal[i].unit];
		for(i=MAX_BUILDINGS;i--;)
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
/*	}
	else   // all goals fulfilled, fitness <- timer 
	{
		for(i=MAX_GOALS;i--;)
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
				{
					int j=1;
                                        while(j<MAX_LOCATIONS)
					{
						if((stat->facility2==0)||(location[locationList[loc][j]].availible[stat->facility2]>0))
						{
							for(fac=3;fac--;)
								if( ((stat->facility[fac]>0)&&(location[locationList[loc][j]].availible[stat->facility[fac]]>0)) || ((stat->facility[fac]==0)&&(fac==0)))
								{
									loc=locationList[loc][j];
									ok=1;
									break;
								}
							break;
						}
						j++;
					}
				}
//TODO: Wenn verschiedene facilities moeglich sind, dann das letzte nehmen						
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
						building[nr].onTheRun=0;
						building[nr].facility=stat->facility[fac];
						building[nr].location=loc;
						building[nr].unitCount=1; //~~
						building[nr].RB=stat->BT+3200*(stat->facility2==what); //~~ hack :/ TODO
						if((mins*5/4<stat->mins+stat->upgrade_cost*location[0].force[what])||
						   (gas*5/4<stat->gas+stat->upgrade_cost*location[0].force[what]))
							tFitness--;
						if(lastwhat==0) lastwhat=what;
						if(what!=lastwhat)//~~
						{
							tFitness--;
							lastwhat=what;
						}
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
									supply+=pStats[stat->facility2].supply; // <- nicht noetig :/ eigentlich schon... bei gas scv z.B. :/
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
//						building[nr].IP=IP;
						// 2x Unit => send 8/All instead of just one unit there
						if((IP>1)&&((Code[0][IP-1]==what)||(Code[1][IP-1]==what)))
							{
								if(location[last[lastcounter].location].availible[last[lastcounter].what]>=6)
									building[nr].unitCount=6;
								else building[nr].unitCount=location[last[lastcounter].location].availible[last[lastcounter].what];
								IP--;
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
/*	return ok;
}

void RACE::mutateGeneCode()
{
	int x,y,i;
	if(length==0) return;
	if(rand()%100==0)
	{
       		if(mutationRate>50)
			mutationRate-=rand()%50;
		else mutationRate+=rand()%50;
	}
	for(x=MAX_LENGTH;x--;) //length
		if(rand()%mutationRate==0)
		{
			switch(rand()%6)
			{
				//TODO: wenn generateBuildOrder==1 dann bleibts stehen!
				case 0://delete one variabel entry and move - Mehrere Schmieden/Kasernen etc. zulassen!
					if((!pSet->ga.generateBuildOrder)||((isVariable[Code[0][x]]==1)&&(isVariable[Code[1][x]]==1)))
						//TODO: ueberlegen, ob Code evtl struct sein sollte... mmmh
					for(y=x;y<MAX_LENGTH-1;y++)
					{
						Code[0][y]=Code[0][y+1];
						Code[1][y]=Code[1][y+1];
					};
					break;
				case 1://add one variabel entry
					for(y=MAX_LENGTH-1;y>x;y--)
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
						if(isVariable[Code[k][x]]==1)
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
							for(i=0;i<y-tb;i++) tmp[i]=Code[0][i+tb];
							for(i=ta;i<tb;i++) Code[0][i+y-tb]=Code[0][i];
							for(i=0;i<y-tb;i++) Code[0][ta+i]=tmp[i];
							for(i=0;i<y-tb;i++) tmp[i]=Code[1][i+tb];
							for(i=ta;i<tb;i++) Code[1][i+y-tb]=Code[1][i];
							for(i=0;i<y-tb;i++) Code[1][ta+i]=tmp[i];
						}
						else
						if(y<ta)
						{
							for(i=0;i<ta-y;i++) tmp[i]=Code[0][i+y];
							for(i=ta;i<tb;i++) Code[0][y+i-ta]=Code[0][i];
							for(i=0;i<ta-y;i++) Code[0][tb-y]=tmp[i];
							for(i=0;i<ta-y;i++) tmp[i]=Code[1][i+y];
							for(i=ta;i<tb;i++) Code[1][y+i-ta]=Code[1][i];
							for(i=0;i<ta-y;i++) Code[1][tb-y]=tmp[i];
						}
					};break;
			}
		}
}


// Reset all ongoing data (between two runs)
void RACE::resetData() // resets all data to standard starting values
{
	int i;
	for(i=UNIT_TYPE_COUNT;i--;)
		ftime[i]=0;
	for(i=MAX_BUILDINGS;i--;)
	{
	       building[i].RB=0;
	       building[i].type=255;
	       building[i].location=0;
	       building[i].unitCount=0;
	       building[i].onTheRun=0;
	}
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
	
	pFitness=0;
	harvestedGas=0;
	harvestedMins=0;
	//location 0 is for globalForce, so take location 1 for starting point instead
	mins=pSet->misc.mins;
	gas=pSet->misc.gas;
	supply=pSet->misc.supply;
	maxSupply=pSet->misc.maxSupply;
}


void RACE::init()
{
	int i,j,counter,k;
	pStats=pSet->pStats;
	
	basicMineralHarvestPerSecond=pSet->misc.pMineralHarvestPerSecond;
	basicGasHarvestPerSecond=pSet->misc.pGasHarvestPerSecond;
	adjustGoals(); //goals und buildable kopieren, goalcount etc.
//#ifdef DEBUGSCC	
	generateBasicBuildOrder();
	initialized=1;
    for(i=1;i<MAX_LOCATIONS;i++)
        {
		for(counter=1;counter<MAX_LOCATIONS;counter++)
		{
			int min=200;
	                for(j=1;j<MAX_LOCATIONS;j++)
                	        if(pMap[i].distance[j]<min)
                        	{
					int ok=1;
        	                        for(k=1;k<counter;k++)
                	                        if(locationList[i][k]==j) ok=0;
					if(ok)
					{
		                                min=pMap[i].distance[j];
        		                        locationList[i][counter]=j;
                		        }
                        	}
		}
        }
}


void RACE::adjustGoals()
{
	int i;
// TODO: Maybe additional checks of the data sets here...
//Anfangsforce checken
	memcpy(goal,pSet->goalList.goal,sizeof(GOAL)*MAX_GOALS); //*4?
	maxBuildTypes=0;

        memcpy(isBuildable,pSet->goalList.isBuildable,UNIT_TYPE_COUNT*4);
	
	for(i=UNIT_TYPE_COUNT;i--;)
		if(isBuildable[i]==1)
		{
			genoToPhaenotype[maxBuildTypes]=i;
			phaenoToGenotype[i]=maxBuildTypes;
			isVariable[maxBuildTypes]=pSet->goalList.isVariable[i];
			maxBuildTypes++;
		}
}


void RACE::generateBasicBuildOrder()
{
	int i;
	//problem wieder mit keep/castle
	//pre[GOALS]
//	int build_max,sup;
//	build_max=0;
	for(i=MAX_LENGTH;i--;)
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

//	for(j=0;j<MAX_GOALS;j++)
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
/*	memcpy(basicBuildOrder[1],basicBuildOrder[0],MAX_LENGTH*4);
}


//Reinitialize programs with random orders
void RACE::resetGeneCode()
{
	int i;
	mutationRate=500+rand()%1000;
	if((pSet->ga.generateBuildOrder)&&(basicLength>0))
	{
		memcpy(Code[0],basicBuildOrder[0],MAX_LENGTH*4);
		memcpy(Code[1],basicBuildOrder[1],MAX_LENGTH*4);
	}
	else
	for(i=MAX_LENGTH;i--;)
	{
		Code[0][i]=rand()%maxBuildTypes;
		Code[1][i]=rand()%maxBuildTypes;
	}
}

void RACE::crossOver(RACE* parent2, RACE* child1, RACE* child2)
{
	int i;
	int counter=MAX_LENGTH;
	for(i=0;i<MAX_LENGTH;i++)
	{
		if(rand()%counter<5)
		{
			int num=MAX_LENGTH-counter;
			memcpy(&child1->Code[0][i-num],&Code[0][i-num],num*4);
			memcpy(&child1->Code[1][i-num],&parent2->Code[1][i-num],num*4);
			memcpy(&child2->Code[1][i-num],&Code[1][i-num],num*4);
			memcpy(&child2->Code[0][i-num],&parent2->Code[0][i-num],num*4);
			counter=MAX_LENGTH; //~~ TODO
			RACE* c=child1;
			child1=child2;
			child2=c;
		}
		counter--;
	}
	int num=MAX_LENGTH-counter;
	memcpy(&child1->Code[0][counter],&Code[0][counter],num*4);
	memcpy(&child1->Code[1][counter],&parent2->Code[1][counter],num*4);
	memcpy(&child2->Code[1][counter],&Code[1][counter],num*4);
	memcpy(&child2->Code[0][counter],&parent2->Code[0][counter],num*4);
	
	child1->mutationRate=(2*mutationRate+parent2->mutationRate)/3;
	child2->mutationRate=(2*parent2->mutationRate+mutationRate)/3;
}


void RACE::initLocations()
{
	int i;
	memcpy(location,pSet->location,sizeof(LOCATION)*MAX_LOCATIONS);
    for(i=MAX_LOCATIONS;i--;)
        {
                adjustMineralHarvest(i);
                adjustGasHarvest(i);
        }
}
*/
RACE::RACE()
{
	/*length=pSet->ga.maxLength;
	if(!initialized) init();
	initLocations();
	resetData();
	resetGeneCode();*/
}


//int RACE::genoToPhaenotype[UNIT_TYPE_COUNT];
//int RACE::phaenoToGenotype[UNIT_TYPE_COUNT];
/*int RACE::isBuildable[UNIT_TYPE_COUNT];
int RACE::isVariable[UNIT_TYPE_COUNT];*/
//int RACE::basicBuildOrder[2][MAX_LENGTH];
//int RACE::basicLength;
/*const UNIT_STATISTICS* RACE::pStats;
const DATA* RACE::pSet;
int RACE::initialized;
int RACE::maxBuildTypes;
const int* RACE::basicMineralHarvestPerSecond;
const int* RACE::basicGasHarvestPerSecond;
const MAP_LOCATION* RACE::pMap;
GOAL RACE::goal[MAX_GOALS];*/
//int RACE::locationList[MAX_LOCATIONS][MAX_LOCATIONS];
//int RACE::lastcounter;
//LAST RACE::last[MAX_LENGTH];
