#include "race.h"
#include "settings.h"
#include <stdlib.h>

// TODO: recheck the speed of the units in zerg.cpp, protoss.cpp and terra.cpp
// TODO: Implement the locations of buildings (expansion, wallin, ...)

void RACE::CalculateFitness()
{
	unsigned char i;
	unsigned char bonus[MAX_GOALS]; // temporary data to check whether a bonus is already given (only applies if force > goal)
	pFitness=0;
	sFitness=0;
		
	sFitness=(harvested_mins*settings.Mineral_Blocks*settings.Mineral_Mod/800+harvested_gas/settings.Vespene_Geysirs);
	if(ready==0)
        {
	         timer=settings.Max_Time;
		 for(i=0;i<MAX_GOALS;i++)
                 	if(goal[i].what>0)
	        	{
	                	if(goal[i].what>force[i])
				{
					if(ftime[i]>0) // ftime => when the last item is built 
					{
			//not all goals met and not below time
						if(goal[i].time>0)
							pFitness+=(100*goal[i].time*force[i])/(goal[i].what*ftime[i]);
						else pFitness+=(100*force[i])/goal[i].what;
					}
					else 
					{
						if(goal[i].time>0)
							pFitness+=(100*goal[i].time*force[i])/(goal[i].what*settings.Max_Time);
			        		else pFitness+=(100*force[i])/goal[i].what;
					}
				}
				else //force >= goal
				{
				if((goal[i].time>0)&&(ftime[i]>goal[i].time))
					pFitness+=(goal[i].time*100/ftime[i]);
				else pFitness+=100;
					
					if(goal[i].what<force[i])
						sFitness-=(force[i]-goal[i].what)*(stats[race][i].mins+stats[race][i].gas);
				}
		}
// TODO: Check for very small 'goal.time' values, probably in scc.cpp!!	 
	for(i=0;i<MAX_GOALS;i++)
		bonus[i]=goal[i].what-force[i];
	for(i=0;i<MAX_BUILDINGS;i++)
                if((building[i].RB>0)&&(goal[building[i].type].what>force[building[i].type])&&(bonus[building[i].type]>0))
		{
			if((goal[building[i].type].time>0)&&(force[building[i].type]==0))
	                	pFitness+=(building[i].RB*100*goal[building[i].type].time*force[i])/(goal[building[i].type].what*stats[race][building[i].type].BT*settings.Max_Time);
			else 				   		
				pFitness+=((building[i].RB*100)/(goal[building[i].type].what*stats[race][building[i].type].BT));
			bonus[building[i].type]--;
		}
	}
	else   // all goals fulfilled, fitness <- timer 
	{
		pFitness=settings.Max_Time-timer;
		for(i=0;i<MAX_GOALS;i++)
	               	if(goal[i].what>0)
	                	pFitness+=100;
	}
}


//Check whether all goals are reached and do some after-completion stuff 
void RACE::CheckReady(unsigned char j)
{
	unsigned char i;

	force[building[j].type]++;
	
	program[building[j].IP].built=1;
	if(((force[building[j].type]>=goal[building[j].type].what)&&(ftime[building[j].type]==0))||(goal[building[j].type].what==0))
		ftime[building[j].type]=timer;
	
	if(stats[race][building[j].type].type<RESEARCH)
		availible[building[j].type]++;
	else
		availible[building[j].type]=1;
	ready=1;
	for(i=0;i<MAX_GOALS;i++)
		ready&=((goal[i].what<=force[i])&&((goal[i].time>=ftime[i])||(goal[i].time==0)));
}

void RACE::Build(int what)
{
        const Stats * stat;
        stat=&stats[race][what];
        ok=0;
	if(what<EXTRACTOR-1)
	{
//TODO: Array und testen wo der comp am meisten haengenbleibt und abbricht... moeglichst dann nach oben bringen!

	if(((stat->prerequisite[0]==0)||(force[stat->prerequisite[0]]>0))&&((stat->prerequisite[1]==0)||(force[stat->prerequisite[1]]>0))&&((stat->prerequisite[2]==0)||(force[stat->prerequisite[2]]>0))&&((stat->facility==0)||(availible[stat->facility]>0))&&(mins>=(stat->mins+(stat->type==UPGRADE)*force[what]*stat->tmp))&&(gas>=(stat->gas+(stat->type==UPGRADE)*force[what]*stat->tmp))&&( (Supply>=stat->supply) || (stat->supply==0))&&((stat->type!=RESEARCH)||((force[what]==0)&&(availible[what]==1))) &&((stat->type!=UPGRADE)||((force[what]<=2)&&(availible[what]==1)))&&(peonmins+peongas*(race!=PROTOSS)>=1*(stat->type==BUILDING))&&(nr<255)&&((what!=EXTRACTOR)||(Vespene_Av>0)))
	
                {
                        Produce(what);
                        if(stat->facility>0) availible[stat->facility]--;
                }
	}
else

        if(what==ONE_MINERAL_DRONE_TO_GAS)
        {
                if((force[EXTRACTOR]>0)&&(peonmins>0))
	        {
                                ok=1;
                                peonmins--;
                                peongas++;
                                program[IP].built=1;
	        }
        }
        else
        if(what==ONE_GAS_DRONE_TO_MINERAL)
        {
                if(peongas>0)
         {
                        ok=1;
                        peonmins++;
                        peongas--;
                        program[IP].built=1;
        }
        }
        else
        if(what==EXTRACTOR)
        {
                if(Vespene_Av>0)
                {
                        Vespene_Av--;
                        Vespene_Extractors++;
                        Produce(what);
                }
        }
      else
      if((race==ZERG)&&(what==BREAK_UP_BUILDING)&&(BuildingRunning>0))
                        {
                                min=5000;
                                n=0;
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
                                                ok=1;

//        if((suc==OK)&&(ok==0))
  //              suc=TECHNOLOGY_AVAILIBLE;
/*        if(suc==OK)
        {
                protein[what]++;
                totalProteins[what]++;
        }*/
}


void RACE::Harvest_Resources()
			
{
	if(peonmins<56)
	{
		mins+=mining[peonmins];
		harvested_mins+=mining[peonmins];
	} else
	{
		mins+=mining[56];
		harvested_mins+=mining[56];
	}
	if(peongas>0)//peongas<5*Vespene_Extractors)
	{
		if(peongas<4)
		{
			//TODO: Mehrere VespExt beachten!
			gas+=gasing[peongas/*/Vespene_Extractors*/]/**Vespene_Extractors*/;
			harvested_gas+=gasing[peongas/*Vespene_Extractors*/]/*Vespene_Extractors*/;
		}
		else
		{
			gas+=gasing[4];//*Vespene_Extractors;
        	        harvested_gas+=gasing[4];//*Vespene_Extractors;
      		
		}
	}
/*	} else if(Vespene_Extractors>0)
	{
		gas+=gasing[4]*Vespene_Extractors;
		harvested_gas+=gasing[4]*Vespene_Extractors;
	}*/
}

// Account the costs of a production
void RACE::Produce(unsigned char what)
{
	int i;
	building[nr].RB=stats[race][what].BT;
	mins-=stats[race][what].mins;
	gas-=stats[race][what].gas;
	building[nr].type=what;
	Supply-=stats[race][what].supply;
	building[nr].on_the_run=0;
	if(stats[race][what].type>2) // Researches, Upgrades
		availible[what]=0;
	if(stats[race][what].type==UPGRADE)
	{
		building[nr].RB+=force[what]*3200;
		mins-=stats[race][what].tmp*force[what];
		gas-=stats[race][what].tmp*force[what];
        }
					
	building[nr].IP=IP;
	ok=1;
        nr=255;
        for(i=0;i<MAX_BUILDINGS;i++) if(building[i].RB==0)
        {
                nr=i;
                i=MAX_BUILDINGS;
        }
}

void RACE::Mutate()
{
        unsigned char k,ta,tb,i,x,y,tmp[MAX_LENGTH];
        //length=MAX_LENGTH;
        if(length==0) return;

        for(x=0;x<MAX_LENGTH;x++)
                if(rand()%1000==0)
                {

                        switch(rand()%3)
                        {
                                //TODO: wenn generateBuildOrder==1 dann bleibts stehen!
                                case 0://delete one variabel entry and move - Mehrere Schmieden/Kasernen etc. zulassen!
                                        if((settings.generateBuildOrder==0)||((Variabel[Build_Bv[Code[x][0]]]==1)&&(Variabel[Build_Bv[Code[x][1]]]==1)))
                                        for(y=x;y<MAX_LENGTH-1;y++)
                                        {
                                                Code[y][0]=Code[y+1][0];
                                                Code[y][1]=Code[y+1][1];
                                        };
                                        break;
                                case 1://add one variabel entry
                                        for(y=MAX_LENGTH-1;y>x;y--)
                                        {
                                                Code[y][0]=Code[y-1][0];
                                                Code[y][1]=Code[y-1][1];
                                        }
                                        y=rand()%Max_Build_Types;
                                        if(settings.generateBuildOrder==1)
                                                while(Variabel[y]==0) y=rand()%Max_Build_Types;
                                        Code[x][0]=y;
                                        y=rand()%Max_Build_Types;
                                        if(settings.generateBuildOrder==1)
                                                while(Variabel[y]==0) y=rand()%Max_Build_Types;
                                        Code[x][1]=y;
                                        break;

                                case 2://change one entry
                                        k=rand()%2;
                                        if(Variabel[Build_Bv[Code[x][k]]]==1)
                                        {
                                                y=rand()%Max_Build_Types;//Optimieren
                                                if(settings.generateBuildOrder==1)
                                                        while(Variabel[y]==0) y=rand()%Max_Build_Types;
                                                Code[x][k]=y;
                                        };break;
                        }
                }
                else
                if(rand()%MAX_LENGTH==0)
                {
                //exchange two entries
                        y=rand()%MAX_LENGTH; //TODO: Aendern in bevorzugtes Ziel => Naehe
                        if(abs(x-y)>(MAX_LENGTH/2)) y=rand()%MAX_LENGTH;
                        if(x!=y)
                        {
                                k=rand()%2;
                                ta=Code[x][k];
                                Code[x][k]=Code[y][k];
                                Code[y][k]=ta;
                        }
                }
                else
                if(rand()%MAX_LENGTH==0)
                {
                //exchange two entries
                        y=rand()%MAX_LENGTH; //TODO: Aendern in bevorzugtes Ziel => Naehe
                        if(abs(x-y)>(MAX_LENGTH/2)) y=rand()%MAX_LENGTH;
                        if(x!=y)
                        {
                                ta=Code[x][0];
                                Code[x][0]=Code[y][0];
                                Code[y][0]=ta;
                                ta=Code[x][1];
                                Code[x][1]=Code[y][1];
                                Code[y][1]=ta;
                        }
                } else

                //move a block of orders  [a..b..ta..tb..c..d] -> [a..ta..tb..b..c..d]
                //TODO switch ta and tb if tb<ta
                if(rand()%MAX_LENGTH==0)
                {
                        ta=rand()%length;
                        tb=rand()%length;
                        x=rand()%length; //move it here
                        if((ta<tb)&&(x>tb))
                        {
                                for(i=0;i<x-tb;i++) tmp[i]=Code[i+tb][0];
                                for(i=ta;i<tb;i++) Code[i+x-tb][0]=Code[i][0];
                                for(i=0;i<x-tb;i++) Code[ta+i][0]=tmp[i];
                                for(i=0;i<x-tb;i++) tmp[i]=Code[i+tb][1];
                                for(i=ta;i<tb;i++) Code[i+x-tb][1]=Code[i][1];
                                for(i=0;i<x-tb;i++) Code[ta+i][1]=tmp[i];
                }
                        else
                        if((ta<tb)&&(x<ta))
                        {
                                for(i=0;i<ta-x;i++)     tmp[i]=Code[i+x][0];
                                for(i=ta;i<tb;i++) Code[x+i-ta][0]=Code[i][0];
                                for(i=0;i<ta-x;i++) Code[tb-x][0]=tmp[i];
                                for(i=0;i<ta-x;i++)     tmp[i]=Code[i+x][1];
                                for(i=ta;i<tb;i++) Code[x+i-ta][1]=Code[i][1];
                                for(i=0;i<ta-x;i++) Code[tb-x][1]=tmp[i];
                        }
                }

}

// Reset all ongoing data (between two runs)
void RACE::Init()
{
	unsigned char i;
	for(i=0;i<MAX_GOALS;i++)
        {
               force[i]=0;
	       ftime[i]=0;
               if(stats[race][i].type<RESEARCH)
	               availible[i]=0;
	       else
	               availible[i]=1;//Researches that can be researched only once
	}
	for(i=0;i<MAX_BUILDINGS;i++)
	{
	       building[i].RB=0;
	       building[i].type=255;
	       building[i].IP=0;
	}
	for(i=0;i<MAX_LENGTH;i++)
	{
		program[i].built=0;
		program[i].success=0;
		program[i].have_Supply=0;
		program[i].need_Supply=0;
		program[i].time=0;
		program[i].mins=0;
		program[i].gas=0;
		program[i].temp=0;
		program[i].dominant=0;
	}
        pFitness=0;
	sFitness=0;
        mins=50;
        gas=0;
	peonmins=4;
	peongas=0;
	IP=0;ok=0;timer=0;n=0;min=0;suc=0;ready=0;nr=0;
	availible[VESPENE_GEYSIRS]=settings.Vespene_Geysirs;
	InitRaceSpecific();
}


void RACE::generateBasicBuildorder()
{
	//problem wieder mit keep/castle
	unsigned char i,j,k,pre[MAX_GOALS],build_max,sup;
	build_max=0;
	for(j=0;j<2;j++)
	for(i=0;i<MAX_LENGTH;i++)
		Basic[i][j]=0;
	Basic_Length=0;

	switch(race)
	{
		case TERRA:
			Basic[0][0]=Build_Bv[SCV];
			Basic[1][0]=Build_Bv[SCV];
			Basic[2][0]=Build_Bv[SCV];
			Basic[3][0]=Build_Bv[SCV];
			Basic[4][0]=Build_Bv[SCV];
			Basic[5][0]=Build_Bv[SCV];
			Basic[6][0]=Build_Bv[SUPPLY_DEPOT];
			if(need_Gas==1)
			{
				Basic[7][0]=Build_Bv[REFINERY];
				Basic[8][0]=Build_Bv[ONE_MINERAL_SCV_TO_GAS];
				Basic[9][0]=Build_Bv[ONE_MINERAL_SCV_TO_GAS];
				Basic[10][0]=Build_Bv[ONE_MINERAL_SCV_TO_GAS];
			};
			i=10;sup=8;
			break;
		case PROTOSS:
			Basic[0][0]=Build_Bv[PROBE];
			Basic[1][0]=Build_Bv[PROBE];
			Basic[2][0]=Build_Bv[PROBE];
			Basic[3][0]=Build_Bv[PROBE];
			Basic[4][0]=Build_Bv[PROBE];
			Basic[5][0]=Build_Bv[PYLON];
			if(need_Gas==1)
			{
				Basic[6][0]=Build_Bv[ASSIMILATOR];
				Basic[7][0]=Build_Bv[ONE_MINERAL_PROBE_TO_GAS];
				Basic[8][0]=Build_Bv[ONE_MINERAL_PROBE_TO_GAS];
				Basic[9][0]=Build_Bv[ONE_MINERAL_PROBE_TO_GAS];
			};
			i=9;sup=8;
			break;
		case ZERG:
			Basic[0][0]=Build_Bv[DRONE];
			Basic[1][0]=Build_Bv[DRONE];
			Basic[2][0]=Build_Bv[DRONE];
			Basic[3][0]=Build_Bv[DRONE];
			Basic[4][0]=Build_Bv[DRONE];
			Basic[5][0]=Build_Bv[OVERLORD];

			if(need_Gas==1)
			{
				Basic[6][0]=Build_Bv[EXTRACTOR];
				Basic[7][0]=Build_Bv[ONE_MINERAL_DRONE_TO_GAS];
				Basic[8][0]=Build_Bv[ONE_MINERAL_DRONE_TO_GAS];
				Basic[9][0]=Build_Bv[ONE_MINERAL_DRONE_TO_GAS];
			};
			i=9;sup=8;
			break;
	}

	for(j=0;j<MAX_GOALS;j++)
		if(force[j]>0) pre[j]=force[j]; else pre[j]=0;	
//TODO: Problem bei KEEPs
	if(settings.generateBuildOrder==1)
	{
	for(k=0;k<MAX_LENGTH;k++)
	{
		j=0;
		while((j<build_max)&&(i<MAX_LENGTH-20))
		{
			if(((pre[j]<goal[j].what)&&(goal[j].what>0))||((buildable[j]>0)&&(force[j]==0)&&(pre[j]<buildable[j])))
			{
				if((stats[race][j].facility>0)&&(pre[stats[race][j].facility]==0))
					j=stats[race][j].facility;
                	        else if((stats[race][j].prerequisite[0]>0)&&(pre[stats[race][j].prerequisite[0]]==0))
	                                j=stats[race][j].prerequisite[0];
        	                else if((stats[race][j].prerequisite[1]>0)&&(pre[stats[race][j].prerequisite[1]]==0))
                	                j=stats[race][j].prerequisite[1];
				else if((stats[race][j].prerequisite[2]>0)&&(pre[stats[race][j].prerequisite[2]]==0))
					j=stats[race][j].prerequisite[2];
/*				else if((stats[race][j].type==UPGRADE)&&(stats[race][j].special>0)&&(pre[TIER3]==0))
					j=TIER3;
				else if((stats[race][j].special>0)&&(pre[TIER2]==0))
					j=TIER2;
				else if((stats[race][j].special>0)&&(pre[TIER3]==0))
					j=TIER3;*/
				else
				{
					//building!
					if(stats[race][j].type==BUILDING)//&&(race=ZERG))
					{
						i++;
						Basic[i][0]=Build_Bv[DRONE];
					} else
					
					if((stats[race][j].type==UNIT)&&(stats[race][j].supply>sup))
					{
						i++;
						switch(race)
						{
							case TERRA:Basic[i][0]=Build_Bv[SUPPLY_DEPOT];pre[SUPPLY_DEPOT]++;sup+=8;break;
							case PROTOSS:Basic[i][0]=Build_Bv[PYLON];pre[PYLON]++;sup+=8;break;
							case ZERG:Basic[i][0]=Build_Bv[OVERLORD];pre[OVERLORD]++;sup+=8;break;
							default:break;
						};
					};
					i++;
					if((stats[race][j].type==UNIT)&&(stats[race][j].supply>0)) sup-=stats[race][j].supply;
					Basic[i][0]=Build_Bv[j];
					pre[j]++;
					j++;
				}
			} else j++;
		}
	}
	}
	Basic_Length=i+1;
	for(j=0;j<MAX_LENGTH;j++)
		Basic[j][1]=Basic[j][0];
}


//Reinitialize programs with random orders
void RACE::Restart()
{
	unsigned char i;
	for(i=0;i<MAX_LENGTH;i++)
	{
		if(settings.generateBuildOrder==1)
		{
			Code[i][0]=Basic[i][0];
			Code[i][1]=Basic[i][1];
		}
		else
		{
			Code[i][0]=rand()%Max_Build_Types;
			Code[i][1]=rand()%Max_Build_Types;
		}
		program[i].built=0;
		program[i].success=0;
	// TODO: Maybe later implement a whole function to create a start list
	// ... mmmh... maybe just something with Set_Goals...
	// would decrease the time until the program can start time-optimization
	// but maybe we loose a possible solution... well...
		program[i].time=20000;
		program[i].temp=0;
	// TODO: Maybe implement later researches / updates / certain buildings only one time per build order... Trying to research things more than once is senseless...
	}
	timer=settings.Max_Time;
	IP=0;
	length=MAX_LENGTH;
}

RACE::RACE()
{
}

