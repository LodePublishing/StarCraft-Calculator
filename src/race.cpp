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
			gasHarvestPerSecond[0][j]=0;
	}
	else
	if(location[loc].force[MINERALS]>0)//TODO Check auf Hauptgebaeude machen! Fernsammeln!
	{
		for(int i=45;i--;)
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
	if(loc==0)
	{
		for(int j=5;j--;)
			gasHarvestPerSecond[0][j]=0;
	}
	else
	if(location[loc].force[REFINERY]>0)//TODO Check auf Hauptgebaeude machen! Fernsammeln!
	{
		for(int i=5;i--;)
		if(i*8<45*location[loc].force[REFINERY])
        	        	{
			int k=0;
        	                	for(int j=0;j<5;j++)
                		                if(i*8<=j*location[loc].force[REFINERY]) { k=j;j=45;}
			gasHarvestPerSecond[loc][i]=basicGasHarvestPerSecond[k]*location[loc].force[REFINERY]/8;
		}
		else gasHarvestPerSecond[loc][i]=basicGasHarvestPerSecond[44]*location[loc].force[REFINERY]/8;
	}
}

/*void RACE::Calculate(SETTINGS* settings)
{
//ZERG: Larvenproduktion!  CREEP!
//PROTOSS: Bauen: Hin und rueckfahren! PYLON!
	int timeout=0;
	int time=0;
        ready=0;
//	int tSupply,tMax_Supply;
                for(time=0;(time<settings->ga.maxTime)&&(!ready)&&(IP<MAX_LENGTH);time++)
                {

//TODO: evtl ueberlegen IP zu springen... also erstmal feststellen, warum nicht gebuildet werden kann und dann in einem Ruck resources und btimes hochsetzen...
                        if(Code[0][IP]>Code[1][IP]) //dominance
                        {
                                program[IP].dominant=0;
                                Build(genoToPhaenotype[Code[0][IP]]);
                                if(ok==0)
                                        {program[IP].dominant=1;Build(genoToPhaenotype[Code[1][IP]]);}
                        }
                        else
                        {
                                program[IP].dominant=1;
                                Build(genoToPhaenotype[Code[1][IP]]);
                                if(ok==0) {program[IP].dominant=0;Build(genoToPhaenotype[Code[1][IP]]);}
                        }
                        timeout++;//evtl versuchen umzuschreiben, dass er mehrere Befehle pro Sekunde machen kann ... TODO
                        if(suc) program[IP].success=suc; //TODO ???
                        else
                        if((ok==1)||(timeout>133)) //~~~~Well... 266 is the max time for battle cruisers... so if the program will come to a battle cruiser queue, a value of 267 is probably important... on the other hand it totally slows down any other things... Well let's try 2 minutes...
                                //and: also problems when there aren't many drones around...
                                //evtl eine Rueckverfolgung einbauen...
                                //mmmh... oder erst neu versuchen, wenn sich etwas geaendert hat... z.B. Gebaeude fertig! TODO
                        {
                                if(timeout<=133) program[IP].time=time;
                                else
                                {
//                                        program[IP].success=TIME_OUT;
                                        program[IP].time=20000;
                                }
                                program[IP].need_Supply=Max_Supply-Supply;//tMax_Supply-tSupply;
                                program[IP].have_Supply=Max_Supply;//tMax_Supply;
                                timeout=0;
                                IP++;
                        }

//TODO: in bo_t wird location (program[].location) immer 0...

//			tSupply=Supply;
//			tMax_Supply=Max_Supply;
                        BuildingRunning=0;
                        Harvest_Resources();
			Building* build=&building[MAX_BUILDINGS-1];
                        for(int j=MAX_BUILDINGS;j--;build=&building[j])
                                if(build->RB)
                                {
                                        BuildingRunning=1;
                                        if(!(--build->RB))
                                        {
                                                const UNIT_STATISTICS* stat=&settings->pStats[build->type];
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
//in Building nur eine facility gespeichert wird...
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
						if(stat->supply<0) {Supply-=stat->supply;Max_Supply-=stat->supply;};
						//~~~~
						location[0].force[build->type]+=build->unitCount;
						location[0].availible[build->type]+=build->unitCount;
						location[build->location].force[build->type]+=build->unitCount;
						location[build->location].availible[build->type]+=build->unitCount;
						if(???stat.create>0) //one additional unit (zerglings, scourge, comsat, etc.)
					        { //here no unitCount! ~~~
							location[build->location].force[gpStats[build->type].create]++;
                                                        location[build->location].availible[gpStats[build->type].create]++;
                                                        location[0].force[gpStats[build->type].create]++;
                                                        location[0].availible[gpStats[build->type].create]++;
					                // ~~~~ Ja... geht schon... aber kann ja auch mal was anderes sein...
					        }
						program[build->IP].built=1;
						program[build->IP].location=build->location;
//					        if((  location[build->location].force[build->type]
						
						//evtl noch location==0 als 'egal wo' einfuehren
						for(int i=0;i<MAX_GOALS;i++)
							if((goal[i].unit>0)&&((goal[i].location==0)||(build->location==goal[i].location))&&(build->type==goal[i].unit)&&((goal[i].time==0)||(time<=goal[i].time)))
							{
//								i=MAX_GOALS;			->Mehrere Goals  koennen auf einen Schlag erfuellt werden!
								ftime[build->type]=time;
							}
						
					        ready=1;
					        for(int i=MAX_GOALS;i--;)
							
							ready&=( ( ((goal[i].location==0)&&(goal[i].count<=location[0].force[goal[i].unit]))||((goal[i].location>0)&&(goal[i].count<=location[goal[i].location].force[goal[i].unit])) )&&((goal[i].time>=ftime[i])||(goal[i].time==0)));
						// oder: irgendeine location... TODO: Problem: die Einheiten koennen irgendwo sein, also nicht gesammelt an einem Fleck...
                                        }
                                }
                //Scoutpeon
/*              if((settings.Scout_Time>0)&&(timer==settings.Scout_Time)&&((peonmins>0)||(peongas>0)))
                {
                        if(peonmins>0)
                                peonmins--;
                        else peongas--;
                }*/
/*
        }
        length=IP;
	timer=time;
        CalculateFitness();
	//TODO: Auch voruebergehende Ziele miteinberechnen (Bewegungen!)
	//Also quasi eine zweite Goalreihe rein um scvs/Einheiten zu belohnen die bestimmte Orte besetzen... erstmal nur scvs... also z.B. int tempGoal...
	//mmmh... aber was reinschreiben? baue barracks bei Ort bla => belohne EINMAL ein scv bei ort bla
}

// falschen Standort ueber distances abrechnen! (100-distance oder so... je nach dem wieviele am falschen Ort sind!)


void RACE::CalculateFitness()
{
	int bonus[MAX_LOCATIONS][UNIT_TYPE_COUNT]; // temporary data to check whether a bonus is already given (only applies if force > goal)
	pFitness=0;
	sFitness=0;
	sFitness=(harvested_mins+harvested_gas); //TODO: evtl gas und mins (wie urspruenglich eigentlich) in Verhaeltnis setyen wieviel es jeweils Geysire/Mineralien gibt...

//TODO: Nicht alle Einheiten am Ort? => Ort egal sein lassen aber zur Zeit hinzuzaehlen
	// Nicht alle Einheiten ueberhaupt gebaut UND nicht alle am Ort => nur viertel Bonus fuer Einheiten die nicht am Ort sind

	if(ready==0)
        {
	         timer=settings.Max_Time;
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
							sumup+=location[j].force[goal[i].unit]*(100-gMap[j].distance[goal[i].location]);
							bon-=location[j].force[goal[i].unit];
						}
						else 
						{
							sumup+=bon*(100-gMap[j].distance[goal[i].location]);
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
							pFitness+=(goal[i].time*sumup)/(goal[i].count*settings.Max_Time);
					}
					else pFitness+=sumup/goal[i].count;
					
					
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
	for(int i=MAX_LOCATIONS;i--;)
	       for(int j=UNIT_TYPE_COUNT;j--;)
		       bonus[i][j]=0;
	
	for(int i=MAX_GOALS;i--;)
		if(location[goal[i].location].force[goal[i].unit]<goal[i].count)
			bonus[goal[i].location][goal[i].unit]+=goal[i].count-location[goal[i].location].force[goal[i].unit];
	
	for(int i=MAX_BUILDINGS;i--;)
                if((building[i].RB>0)&&(bonus[building[i].type][building[i].location]>0))
		{
		//erstmal ohne Zeit...
			pFitness+=((building[i].RB*100)/((location[building[i].location].force[building[i].type]+bonus[building[i].type][building[i].location])*gpStats[building[i].type].BT));
			/*
			
			if((goal[building[i].type].time>0)&&(location[building[i].location].force[building[i].type]==0))
				
				

				
	                	pFitness+=(building[i].RB*100*goal[building[i].type].time*location[0].force[i])/(goal[building[i].type].count*gpStats[building[i].type].BT*settings.Max_Time);
			else 				   		
				pFitness+=((building[i].RB*100)/(goal[building[i].type].count*gpStats[building[i].type].BT));*/
/*			bonus[building[i].location][building[i].type]--;
		}
	}
	else   // all goals fulfilled, fitness <- timer 
	{
		pFitness=settings.Max_Time-timer;
		for(int i=MAX_GOALS;i--;)
			if(goal[i].count>0)
	                	pFitness+=100;
	}
}
*/


/*void RACE::Build(int what)
{
        const Stats* stat=&gpStats[what];
        ok=0;
	suc=OK;
	if(what<=EXTRACTOR+1)
	{
//TODO: Array und testen wo der comp am meisten haengenbleibt und abbricht... moeglichst dann nach oben bringen!

        if(
((stat->prerequisite[0]==0)||(location[0].force[stat->prerequisite[0]]>0))&&
((stat->prerequisite[1]==0)||(location[0].force[stat->prerequisite[1]]>0))&&
((stat->prerequisite[2]==0)||(location[0].force[stat->prerequisite[2]]>0))&&
( ((stat->facility[0]>0)&&(location[0].availible[stat->facility[0]]>0))||
  ((stat->facility[1]>0)&&(location[0].availible[stat->facility[1]]>0))||
  ((stat->facility[2]>0)&&(location[0].availible[stat->facility[2]]>0))||
  ((stat->facility[0]==0)&&(stat->facility[1]==0)&&(stat->facility[2]==0))
)&&
(mins>=stat->mins+stat->upgrade_cost*location[0].force[what])&&
(gas>=stat->gas+stat->upgrade_cost*location[0].force[what])&&
((Supply>=stat->supply)||(stat->supply<=0))&&
(nr<255)&&
((stat->facility2==0)||(location[0].availible[stat->facility2]>0)))
 
/*
		
if(
((stat->prerequisite[0]>0)&&(location[0].force[stat->prerequisite[0]]==0))||
((stat->prerequisite[1]>0)&&(location[0].force[stat->prerequisite[1]]==0))||
((stat->prerequisite[2]>0)&&(location[0].force[stat->prerequisite[2]]==0)))
	suc=ENOUGH_FORCE;
else 
if( 
((stat->facility[0]>0)&&(location[0].availible[stat->facility[0]]==0))||
((stat->facility[1]>0)&&(location[0].availible[stat->facility[1]]==0))||
((stat->facility[2]>0)&&(location[0].availible[stat->facility[2]]==0))||
((stat->facility2>0)&&(location[0].availible[stat->facility2]==0)))
	suc=ENOUGH_AVAILIBLE;	
else 
if(mins>=stat->mins+stat->upgrade_cost*location[0].force[what])
	suc=ENOUGH_MINERALS;
else
if(gas>=stat->gas+stat->upgrade_cost*location[0].force[what])
	suc=ENOUGH_GAS;
else
if((Supply>=stat->supply)||(stat->supply<=0))
	suc=SUPPLY_SATISFIED;
else
if(nr<255)
	suc=TOO_MANY_BUILDINGS;
else*/
		/*{
			//Zuerst: availible pruefen ob am Ort gebaut werden kann
			//Wenn nicht => +/- absteigen bis alle locations durch sind
			int fac,loc,kk;
			kk=0;
			loc=window;fac=0;
			if((stat->facility2==0)||(location[loc].availible[stat->facility2]>0))
				for(fac=3;fac--;)
					if( ((stat->facility[fac]>0)&&(location[loc].availible[stat->facility[fac]]>0)) || ((stat->facility[fac]==0)&&(fac==0))) 
					{
						kk=1;
						break; // ?
					}
			if(kk==0)
			{
				for(loc=1;loc<MAX_LOCATIONS;loc++)
				{
					if((stat->facility2==0)||(location[loc].availible[stat->facility2]>0))
					{
						for(fac=3;fac--;)
	        		                        if( ((stat->facility[fac]>0)&&(location[loc].availible[stat->facility[fac]]>0)) || ((stat->facility[fac]==0)&&(fac==0)))
        	        		                {
                	        				kk=1;
	                	        	                break;
        	                	        	}
						break;
					}	
				}
			}
//			bewegliche Sachen ueberdenken...
//				evtl zusaetzliche Eigenschaft 'speed' einbauen (muss sowieso noch...)... bei speed>0 ... mmmh... trifft aber auch nur auf scvs zu ... weil bringt ja wenig erst mit der hydra rumzulaufen und dann zum lurker... mmmh... aber waere trotzdem zu ueberlegen...
//				auch noch ueberlegen, wenn z.B. mit scv ohne kommandozentrale woanders gesammelt wird...
//	Phagen ueber Phagen...			
			if(kk==1)
				{
					building[nr].facility=stat->facility[fac];
					building[nr].location=loc;
					building[nr].unitCount=1; //~~
				        building[nr].RB=stat->BT+3200*(stat->facility2==what); //~~ hack :/
				        mins-=stat->mins+stat->upgrade_cost*location[0].force[what];
				        gas-=stat->gas+stat->upgrade_cost*location[0].force[what];
				        building[nr].type=what;
				        if((stat->supply>0)||((gpStats[stat->facility[0]].supply<0)&&(stat->facility_type==IS_LOST))) Supply-=stat->supply;
				        switch(stat->facility_type)
				        {
						case IS_LOST:
							if(stat->facility[fac]>0)
							{
								location[loc].availible[stat->facility[fac]]--;
								location[0].availible[stat->facility[fac]]--;
								Supply+=gpStats[stat->facility[fac]].supply; 
							}
							if(stat->facility2>0)
							{
								location[loc].availible[stat->facility2]--;
								location[0].availible[stat->facility2]--;
								Supply+=gpStats[stat->facility2].supply;
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
								Supply+=gpStats[stat->facility2].supply; // <- nicht noetig :/
							}
							break;
						case NEEDED_UNTIL_COMPLETE_IS_LOST:
							if(stat->facility2>0)
							{
								location[loc].availible[stat->facility2]--;
								location[0].availible[stat->facility2]--;
								Supply+=gpStats[stat->facility2].supply; // <- nicht noetig :/
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
								// Supply?
							}
							if(stat->facility2>0)
							{
								location[loc].availible[stat->facility2]--;
								location[0].availible[stat->facility2]--;
							}
							break;
						default:break;
				        }

//				        building[nr].on_the_run=0;
				        building[nr].IP=IP;
				        ok=1;
				} //kk!=1?
				else suc=ENOUGH_AVAILIBLE;
		}
	}
else
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
		case MOVE_TO_HERE:if((start!=window)&&(nr<255)&&(IP+1<MAX_LENGTH))
					  //move ALL units (type specified in IP+1) at that location!
				{
					IP++;
					int what=0;
					if((Code[0][IP]>Code[1][IP])&&(gpStats[genoToPhaenotype[Code[0][IP]]].speed>0)&&(location[start].availible[genoToPhaenotype[Code[0][IP]]]>0))
	                        	{
       		                        	program[IP].dominant=0;
						what=genoToPhaenotype[Code[0][IP]];
						ok=1;
	                        	}
                		        else if((gpStats[genoToPhaenotype[Code[1][IP]]].speed>0)&&(location[start].availible[genoToPhaenotype[Code[1][IP]]]>0))
		                        {
               	             			program[IP].dominant=1;
						what=genoToPhaenotype[Code[1][IP]];
						ok=1;
					}
					else if(location[start].availible[SCV]>0) 
					{
						what=SCV;
						ok=1;
					}
//					else  ?? alle durchsuchen bis ein scv gefunden wurde? mmmh...
						
					if(ok)
					{
						program[IP-1].built=1;
	                                        building[nr].facility=0;
        	                                building[nr].location=window;
                        	               	building[nr].type=what;
						building[nr].RB=gMap[start].distance[window]*100/gpStats[what].speed;
						building[nr].IP=IP;
						if((IP+1<MAX_LENGTH)&&((Code[0][IP+1]==Code[program[IP].dominant][IP])||(Code[1][IP+1]==Code[program[IP].dominant][IP])))
							{
								if(location[start].availible[what]>12)
									building[nr].unitCount=12;
								else building[nr].unitCount=location[start].availible[what];
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
	if(ok) program[IP].built=1;
}

/*      else
      if((gRace==ZERG)&&(what==BREAK_UP_BUILDING)&&(BuildingRunning>0))
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
                                                program[IP].built=1;
                                                program[building[n].IP].built=1;
                                        }*/
//        if((suc==OK)&&(ok==0))
  //              suc=TECHNOLOGY_AVAILIBLE;
/*        if(suc==OK)
        {
                protein[what]++;
                totalProteins[what]++;
        }*/
//TODO: Verwandtschaftsgrad fuer crossing over feststellen!	
/*	if(ok)
	{
		nr=255;
                for(int j=MAX_BUILDINGS;j--;)
                	if(building[j].RB==0) // calculate new position for new building (some kind of hash table function...)
                        {
                        	nr=j;
                                break;
                        }
	}

}*/


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
					mins+=mineralHarvestPerSecond[i][s]; //~~~ neu berechnen / Tabelle anlegen! sind ja nicht bei jeder Exe gleichviel Mineralien...
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

void RACE::mutateGeneCode(int generateBuildOrder)
{
        if(length==0) return;
	if(rand()%100==0)
        {
       		if(mutationRate>100)
                	mutationRate-=rand()%100;
                else mutationRate+=rand()%100;
        }

        for(int x=length;x--;)
                if(rand()%mutationRate==0)//mutationRate==0)
                        switch(rand()%6)
                        {
                                //TODO: wenn generateBuildOrder==1 dann bleibts stehen!
                                case 0://delete one variabel entry and move - Mehrere Schmieden/Kasernen etc. zulassen!
                                        if((!generateBuildOrder)||((isVariable[phaenoToGenotype[Code[0][x]]]==1)&&(isVariable[phaenoToGenotype[Code[1][x]]]==1)))
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
                                        if(generateBuildOrder)
                                                while(isVariable[y]==0) y=rand()%maxBuildTypes;
                                        Code[0][x]=y;
                                        y=rand()%maxBuildTypes;
                                        if(generateBuildOrder)
                                                while(isVariable[y]==0) y=rand()%maxBuildTypes;
                                        Code[1][x]=y;
					};break;
                                case 2://change one entry
					{
	                                        int k=rand()%2;
        	                                if(isVariable[phaenoToGenotype[Code[k][x]]]==1)
                	                        {
                        	                        int y=rand()%maxBuildTypes;//Optimieren
                                	                if(generateBuildOrder)
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


void RACE::resetLocations(LOCATION* loc)
{
	memcpy(location,&loc,sizeof(LOCATION)*MAX_LOCATIONS);
}

// Reset all ongoing data (between two runs)
void RACE::resetData(MISC* misc) // resets all data to standard starting values
{
	for(int i=UNIT_TYPE_COUNT;i--;)
		ftime[i]=0;
	for(int i=MAX_BUILDINGS;i--;)
	{
	       building[i].RB=0;
	       building[i].type=255;
	       building[i].IP=0;
	       building[i].location=0;
	       building[i].unitCount=0;
	}
	for(int i=MAX_LENGTH;i--;)
	{
		program[i].built=0;
		program[i].success=0;
		program[i].haveSupply=0;
		program[i].needSupply=0;
		program[i].time=0;
		program[i].mins=0;
		program[i].gas=0;
		program[i].temp=0;
		program[i].dominant=0;
	}
	pFitness=0;
	sFitness=0;
	harvested_gas=0;
	harvested_mins=0;
	IP=0;
	ok=0;
	suc=0;
	ready=0;
	nr=0;
	start=1;window=1;prev=1; //location 0 is for globalForce, so take location 1 for starting point instead
	timer=misc->timer;
	mins=misc->mins;
	gas=misc->gas;
	supply=misc->supply;
	maxSupply=misc->maxSupply;
}


void RACE::init(SETTINGS* set)
{
        pStats=set->pStats;
        basicMineralHarvestPerSecond=set->misc.pMineralHarvestPerSecond;
        basicGasHarvestPerSecond=set->misc.pGasHarvestPerSecond;
        adjustGoals(set); //goals und buildable kopieren, goalcount etc.
	generateBasicBuildOrder();
        initialized=1;
}


void RACE::adjustGoals(SETTINGS* set)
{
// TODO: Maybe additional checks of the data sets here...
//Anfangsforce checken
        maxBuildTypes=0;
        for(int i=0;i<UNIT_TYPE_COUNT;i++)
                if(isBuildable[i]==1)
                {
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
void RACE::resetGeneCode(int generateBuildOrder)
{
	mutationRate=500+rand()%1000;
	if((generateBuildOrder)&&(basicLength>0))
	{
		memcpy(Code[0],basicBuildOrder[0],MAX_LENGTH*2);
		memcpy(Code[1],basicBuildOrder[1],MAX_LENGTH*2);
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
                        counter=MAX_LENGTH;
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

RACE::RACE(SETTINGS* set)
{
	memcpy(location,set->location,sizeof(LOCATION)*MAX_LOCATIONS);
	memcpy(isBuildable,set->goalList.isBuildable,UNIT_TYPE_COUNT);
	memcpy(isVariable,set->goalList.isVariable,UNIT_TYPE_COUNT);
        if(!initialized) init(set);
	for(int i=MAX_LOCATIONS;i--;)
	{
		adjustMineralHarvest(i);
		adjustGasHarvest(i);
	}	
	resetData(&set->misc);
	resetGeneCode(set->ga.generateBuildOrder);
}

