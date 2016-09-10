#include "settings.h"
#include "map.h"
#include "goal.h"
#include "debug.h"
#include <stdio.h> 
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int SETTINGS::setMaxTime(int num) //maximum time of build order in seconds
{
	if(num<300) return(0);
	ga.maxTime=num;
	return(1);
};

int SETTINGS::setMaxTimeOut(int num) //timeout for building
{
	if(num<30) return(0);
	ga.maxTimeOut=num;
	return(1);
};

int SETTINGS::setMaxLength(int num)
{
	if((num<10)||(num>96)) return(0);
	ga.maxLength=num;
	return(1);
};

int SETTINGS::setMaxRuns(int num)
{
	if(num==0) return(0);
	ga.maxRuns=num;
	return(1);
};

int SETTINGS::setMaxGenerations(int num)
{
	if((num<25)||(num>5000)) return(0);
	ga.maxGenerations=num;
	return(1);
};

int SETTINGS::setPlayerCount(int num)
{
	if((num<=0)||(num>MAX_PLAYER))
		return(0);
	ga.playerCount=num;
	return(1);
};

int SETTINGS::setMapCount(int num)
{
	if((num<0)||(num>=MAX_MAPS))
		return(0);
	ga.mapCount=num;
	return(1);
};

int SETTINGS::setGoalCount(int num)
{
	if((num<0)||(num>=MAX_GOAL_ENTRIES))
		return(0);
	ga.goalCount=num;
	return(1);
};


int SETTINGS::setPreprocessBuildOrder(int num)
{
	if(num==1)
		ga.preprocessBuildOrder=1;
	else
	if(num==0) 
		ga.preprocessBuildOrder=0;
	else return(0);
	return(1);
};

int SETTINGS::setCurrentMap(int num)
{
	//TODO: initialisiert? bei 0 gibts immer bloede Probleme
	if((num<0)||(num>ga.mapCount))
		return(0);
	ga.currentMap=num;
	soup.setMap(&map[num]);
	setPlayerCount(map[num].getMaxPlayer());
	return(1);
};


int SETTINGS::setGoal(int goal, int player)
{
	if((goal<0)||(goal>=getGoalCount()))
		return(0);
	return(soup.setGoal(&goalEntry[goal], player));
};

int SETTINGS::getMaxTime()
{
	return(ga.maxTime);
};

int SETTINGS::getMaxTimeOut()
{
	return(ga.maxTimeOut);
};

int SETTINGS::getMaxLength()
{
	return(ga.maxLength);
};

int SETTINGS::getMaxRuns()
{
	return(ga.maxRuns);
};

int SETTINGS::getMaxGenerations()
{
	return(ga.maxGenerations);
};

int SETTINGS::getPreprocessBuildOrder()
{
	return(ga.preprocessBuildOrder);
};

int SETTINGS::getCurrentMap()
{
	return(ga.currentMap);
};

int SETTINGS::getGoalCount()
{
	return(ga.goalCount);
};

int SETTINGS::getPlayerCount()
{
	return(ga.playerCount);
};

int SETTINGS::getMapCount()
{
	return(ga.mapCount);
};

int SETTINGS::getHarvestMineralsSpeed(int r,int n)
{
	if((r<0)||(r>3))
		return(0);
	return(harvestSpeed[r].getHarvestMineralSpeed(n));
};

int SETTINGS::getHarvestGasSpeed(int r,int n)
{
	if((r<0)||(r>3))
		return(0);
	return(harvestSpeed[r].getHarvestGasSpeed(n));
};


int SETTINGS::getDistance(int l1,int l2)
{
	if((l1<0)||(l1>=MAX_LOCATIONS))
		return(0);
	return(map[ga.currentMap].location[l1].getDistance(l2));
};

int SETTINGS::getGoal(GOAL_ENTRY &goal,int num)
{
	if((num<0)||(num>=getGoalCount()))
		return(0);
	goal=(goalEntry[num]);
	return(1);
};


//=> in race schreiben! :-) Bzw. in settings nur die Datei an sich laden, in ein array speichern und dann zur Auswahl geben
// zu dem player[4] Problem... evtl pointer auf 4 Klassen machen...
int SETTINGS::loadGoalFile(const char* goalFile) //~~~
{
	char line[1024],old[1024];
	FILE* pFile;
	char* buffer;
	char item[1024];
	char param1[1024];
	char param2[1024];
	char param3[1024];
	int ln=0;
	int value1=0,value2=0,value3=0;

	int i;

	item[0]='\0';param1[0]='\0';param2[0]='\0';param3[0]='\0';

	if((pFile = fopen (goalFile,"r"))==NULL)
	{
		debug.toLog(0,"ERROR: (loadGoalFile) %s: Could not open file!",goalFile);
		return(0); 
	}
	
	//"unit name" "count" "time" "location"
	while(fgets(line,sizeof(line),pFile)!=NULL)
	{
		++ln;
		line[strlen(line)-1]='\0';
		if((line[0]=='#')||(line[0]=='\0')) continue;
		strcpy(old,line);
		strcpy(item,"");
		strcpy(param1,"");
		strcpy(param2,"");

		if((buffer=strtok(line,"\""))!=NULL) strcpy(item,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param1,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param2,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param3,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL)
		{
			debug.toLog(0,"WARNING: (loadGoalFile) %s: Line %d [%s]: Too many parameters.",goalFile,ln,old);
			continue;
		}
		value1=atoi(param1);value2=atoi(param2);value3=atoi(param3);
		
		if((value1<0)||(value2<0)||(value3<0))
		{
			debug.toLog(0,"WARNING: (loadGoalFile) %s: Line %d [%s]: Value below zero.",goalFile,ln,old);
			continue;
		}

		if(!strcmp(item,"@RACE"))
		{
			if(!strcmp(param1,"Terra")) goalEntry[getGoalCount()].setRace(TERRA);
				else if(!strcmp(param1,"Protoss")) goalEntry[getGoalCount()].setRace(PROTOSS);
				else if(!strcmp(param1,"Zerg")) goalEntry[getGoalCount()].setRace(ZERG);
				else
				{
					debug.toLog(0,"ERROR: (loadGoalFile) %s: Line %d [%s]: Invalid race.",goalFile,ln,old);
					fclose(pFile);
					return(0);
				}
		}
		else 
			if(!goalEntry[getGoalCount()].isRaceInitialized())
			{
				debug.toLog(0,"ERROR: (loadGoalFile) %s: Line %d [%s]: @RACE must be the first line.",goalFile,ln,old);
				fclose(pFile);
				return(0);
			}
		else
			{

//Aufbau der goal datei: "Einheitname" LEER "Anzahl" LEER "Zeit" LEER "Ort"
				for(i=0;i<REFINERY;i++) 
					if((strstr(stats[goalEntry[getGoalCount()].getRace()][i].name,item)!=NULL)&&(value2<=getMaxTime())&&(value3<=MAX_LOCATIONS)) //TODO: strcmp durch 'erstes auftauchen' vertauschen
					{
						//TODO: values checken!
			 			//TODO: evtl statt Ortsnummer einfach den Ortsnamen nehmen
						//TODO: evtl statt Ortsnummer einfach den Ortsnamen nehmen
						if(!goalEntry[getGoalCount()].addGoal(i,value1,60*value2,value3))
							debug.toLog(0,"WARNING: (loadGoalFile) %s: Line %d [%s]: Problems with adding goal.",goalFile,ln,old);
						i=REFINERY+1;
						break;
					}
				if(i!=REFINERY+1)
					debug.toLog(0,"WARNING: (loadGoalFile) %s: Line %d [%s]: No unit name matched this goal.",goalFile,ln,old);
			}
	} //end while

	goalEntry[getGoalCount()].adjustGoals();
	setGoalCount(getGoalCount()+1);
	fclose(pFile);
	return(1);
};


int SETTINGS::loadSettingsFile(const char* settingsFile)
{
	char line[1024],old[1024];
	FILE* pFile;
	char* buffer;
	char item[1024];
	char param[1024];
	int ln=0;
	int value=0;
	int mode=0;
	
	item[0]='\0';param[0]='\0';

	if((pFile = fopen (settingsFile,"r"))==NULL)
	{
		debug.toLog(0,"ERROR: (loadSettingsFile) %s: Could not open file!",settingsFile);
		return(0);
	}

	while(fgets(line,sizeof(line),pFile)!=NULL)
	{
		++ln;
		line[strlen(line)-1]='\0';
		if((line[0]=='#')||(line[0]=='\0')) continue;
		strcpy(old,line);
		strcpy(item,"");
		strcpy(param,"");
		if((buffer=strtok(line,"\""))!=NULL) strcpy(item,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param,buffer);
		if((buffer=strtok(NULL,"\""))!=NULL)
		{
			debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Too many parameters.",settingsFile,ln,old);
			continue;
		}
		value=atoi(param);
		
		if(value<0)
		{
			debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Value below zero.",settingsFile,ln,old);
			continue;
		}

		if(mode==0)
		{
			if(!strcmp(item,"@SETTINGS")) mode=1;
			else 
			{
				if(!strcmp(item,"@END"))
					debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Lonely @END.",settingsFile,ln,old);
				else
					debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Line is outside a block but is not marked as comment.",settingsFile,ln,old);
			}
			
		}
		else if(mode>0)
		{
			if(!strcmp(item,"@END"))
				mode=0;
			else if(!strcmp(item,"@SETTINGS"))
				debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: New @SETTINGS block found within a @SETTINGS block.",settingsFile,ln,old);
			else if(mode==1)
			{
				if(!strcmp(item,"Max Time"))
				{
					//TODO evtl alles in set... rein
					if(!setMaxTime(value))
						debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Max Time too low.",settingsFile,ln,old);
				}
				else if(!strcmp(item,"Max Timeout"))
				{
					if(!setMaxTimeOut(value))
						debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Max Timeout too low.",settingsFile,ln,old);
				}
				else if(!strcmp(item,"Max Length"))
				{
					if(!setMaxLength(value))
						debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Max Length out of range.",settingsFile,ln,old);
				}

				else if(!strcmp(item,"Max Runs"))
				{
					if(!setMaxRuns(value))
						debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Max Runs too low.",settingsFile,ln,old);
				}
				
				else if(!strcmp(item,"Preprocess Buildorder"))
				{
					if(!setPreprocessBuildOrder(value))
						debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Preprocess Buildorder out of Range.",settingsFile,ln,old);
				}
				else if(!strcmp(item,"Max unchanged Generations"))
				{
					if(!setMaxGenerations(value))
						debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Max Generations out of range.",settingsFile,ln,old);
				}
				else
					debug.toLog(0,"WARNING: (loadSettingsFile) %s: Line %d [%s]: Unknown entry.",settingsFile,ln,old);
			}
		}// END if(mode>0)
	}// END while
	return(1);
};

int SETTINGS::loadHarvestFile(const char* harvestFile)
{
	char line[1024],old[1024];
	FILE* pFile;
	char* buffer;
	char item[1024],param[1024];
	int ln=0;
	int value=0;
	int mode=0,modeRace=0;
	int i=0;
	if((pFile = fopen (harvestFile,"r"))==NULL)
	{
		debug.toLog(0,"ERROR: (loadHarvestFile) %s: Could not open file!",harvestFile);
		return(0); 
	}

	item[0]='\0';param[0]='\0';

	while(fgets(line,sizeof(line),pFile)!=NULL)
	{
		++ln;
		line[strlen(line)-1]='\0';
		if((line[0]=='#')||(line[0]=='\0')) continue;
		strcpy(old,line);
		strcpy(item,"");
		strcpy(param,"");
		value=0;
		if((buffer=strtok(line,"\""))!=NULL) strcpy(item,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL)
		{
			debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Too many parameters.",harvestFile,ln,old);
			continue;
		}

		if((value=atoi(param))<0)
		{
			debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Value below zero.",harvestFile,ln,old);
			continue;
		}

		if(mode==0) //Out of any block
		{
			if(!strcmp(item,"@HARVESTDATA")) 
				mode=1;
			else if(!strcmp(item,"@END"))
				debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Lonely @END.",harvestFile,ln,old);
			else 
				debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Line is outside a block but is not marked as comment.",harvestFile,ln,old);
		
		}
		else if(mode==1)		
		{
			if(modeRace==0)
			{
				if(!strcmp(item,"@TERRA"))
					modeRace=1;
				else if(!strcmp(item,"@PROTOSS"))
					modeRace=2;
				else if(!strcmp(item,"@ZERG"))
					modeRace=3;
				else if(!strcmp(item,"@END"))
					mode=0;
				else 
					debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: @TERRA, @PROTOSS or @ZERG expected.",harvestFile,ln,old);
			}
			else if(modeRace>0)
			{
				if(!strcmp(item,"@END"))
					modeRace=0;
				else if(!strcmp(item,"Mineral Harvest"))
				{
					i=0;
					buffer=strtok(param," ");
					while((buffer!=NULL)&&(i<45))				
					{
						if(!harvestSpeed[modeRace-1].setHarvestMineralSpeed(i++,(value=atoi(buffer))))
						{
							debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Values out of range.",harvestFile,ln,old);
							break;
						}
						buffer=strtok(NULL," ");
					}
					if(i<45)
					{
						debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Missing entries.",harvestFile,ln,old);
						for(;i<45;i++)
							//~~
							harvestSpeed[modeRace-1].setHarvestMineralSpeed(i++,value);
					}
				}
				else
				if(!strcmp(item,"Gas Harvest"))
				{
					i=0;
					buffer=strtok(param," ");
					while((buffer!=NULL)&&(i<5))
					{
						if(!harvestSpeed[modeRace-1].setHarvestGasSpeed(i++,(value=atoi(buffer))))
						{
							debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Values out of range.",harvestFile,ln,old);
							break;
						}
						buffer=strtok(NULL," ");
					}
					if(i<5)
					{
						debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Missing entries",harvestFile,ln,old);
						for(;i<5;i++)
							//~~
							harvestSpeed[modeRace-1].setHarvestGasSpeed(i++,value);
					}
				}
				else 
					debug.toLog(0,"WARNING: (loadHarvestFile) %s: Line %d [%s]: Unknown entry.",harvestFile,ln,old);
			}
		}
		else
			debug.toLog(0,"ERROR: (loadHarvestFile) %s: Line %d [%s]: Serious bug.",harvestFile,ln,item);
	}// END while
	return(1);
};





int SETTINGS::loadMapFile(const char* mapFile)
{
	char line[1024],old[1024];
	FILE* pFile;
	char* buffer;
	char item[1024],param1[1024],param2[1024],param3[1024];
//	char* item
//	char item[1024];
//	char param[1024];
//	char tmp[1024];
	int ln=0;
	int value1=0,value2=0,value3=0;
	int mode=0,modeLocation=0,modePlayer=-1;
	int i=0;
	if((pFile = fopen (mapFile,"r"))==NULL)
	{
		debug.toLog(0,"ERROR: (loadMapFile) %s: Could not open file!",mapFile);
		return(0); 
	}

	item[0]='\0';param1[0]='\0';param2[0]='\0';param3[0]='\0';

	int distanceCount=0;
	
	while(fgets(line,sizeof(line),pFile)!=NULL)
	{
		++ln;
		line[strlen(line)-1]='\0';
		if((line[0]=='#')||(line[0]=='\0')) continue;
		strcpy(old,line);
		strcpy(item,"");
		strcpy(param1,"");strcpy(param2,"");strcpy(param3,"");
		value1=0;value2=0;value3=0;
		if((buffer=strtok(line,"\""))!=NULL) strcpy(item,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param1,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param2,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL) strcpy(param3,buffer);strtok(NULL,"\"");
		if((buffer=strtok(NULL,"\""))!=NULL)
		{
			debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Too many parameters.",mapFile,ln,old);
			continue;
		}

		if(((value1=atoi(param1))<0)||((value2=atoi(param2))<0)||((value3=atoi(param3))<0))
		{
			debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Value below zero.",mapFile,ln,old);
			continue;
		}

		if(mode==0) //Out of any block
		{
			if(!strcmp(item,"@MAP")) 
				mode=1;
			else if(!strcmp(item,"@LOCATION"))
			{
				if((value1>0)&&(value1<=MAX_LOCATIONS)) 
				{
					mode=2;
					modeLocation=value1;
				}
				else debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Location out of range.",mapFile,ln,old);
			}
			else if(!strcmp(item,"@PLAYER"))
			{
				if((value1>=0)&&(value1<=getPlayerCount()))
				{
					mode=3;
					modePlayer=value1;
				}
				else debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Player is out of range.",mapFile,ln,old);
			}
			else if(!strcmp(item,"@END"))
				debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Lonely @END.",mapFile,ln,old);
			else 
				debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Line is outside a block but is not marked as comment.",mapFile,ln,old);
		
		}
		else if(mode>0)		
		{
			if(mode==1) // MAP Block
			{
				if(!strcmp(item,"Name"))
				{
					if(!map[getMapCount()].setName(param1))
						debug.toLog(0,"ERROR: (loadMapFile) %s: Line %d [%s]: Name not set!",mapFile,ln,old);
				}
				else if(!strcmp(item,"Max Locations"))
				{
					if(!map[getMapCount()].setMaxLocations(value1))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Max Locations out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"Max Players"))
				{
					if((!map[getMapCount()].setMaxPlayer(value1))||(!setPlayerCount(value1)))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Max Player out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"@END"))
					mode=0;
				else 
					debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Unknown entry. GRR",mapFile,ln,old);
			}
			else if(mode==2) // LOCATION Block
			{
				if(!strcmp(item,"Name"))
				{
					if(!map[getMapCount()].location[modeLocation-1].setName(param1))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Name invalid.",mapFile,ln,old);
				}
				else if(!strcmp(item,"Mineral Distance"))
				{
					if(!map[getMapCount()].location[modeLocation-1].setMineralDistance(value1))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Mineral Distance out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"Distances"))
				{
					//~~ wenn maxLocations noch nicht initialisiert...
					distanceCount=0;
					buffer=strtok(param1," ");
					while((buffer!=NULL)&&(distanceCount<map[getMapCount()].getMaxLocations()))
					{
						if(!map[getMapCount()].location[modeLocation-1].setDistance(distanceCount++,(value1=atoi(buffer))) )
						{
							debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Values out of range",mapFile,ln,old);
							break;
						}
						buffer=strtok(NULL," ");
					}
			
					if(distanceCount<map[getMapCount()].getMaxLocations())
					{
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Missing entries",mapFile,ln,old);
						for(;distanceCount<map[getMapCount()].getMaxLocations();distanceCount++)
							map[getMapCount()].location[modeLocation-1].setDistance(distanceCount,0);
					}
				}
				else if(!strcmp(item,"@PLAYER"))
				{
					if((value1>=0)&&(value1<=getPlayerCount()))
					{
						mode=4;
						modePlayer=value1;
					}
					else 
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Value out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"@END"))
					mode=0;
				else 
					debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Unknown entry!.",mapFile,ln,old);
			}
			else if(mode==3) //PLAYER Block
			{
				if(!strcmp(item,"Race"))
				{
					if(!strcmp(param1,"Terra")) 
					{
						map[getMapCount()].player[modePlayer].setRace(TERRA);
						map[getMapCount()].player[modePlayer].setHarvest(&harvestSpeed[TERRA].minerals[0],&harvestSpeed[TERRA].gas[0]);
					}
					else if(!strcmp(param1,"Protoss")) 
					{
						map[getMapCount()].player[modePlayer].setRace(PROTOSS);
						map[getMapCount()].player[modePlayer].setHarvest(&harvestSpeed[PROTOSS].minerals[0],&harvestSpeed[PROTOSS].gas[0]);
					}
					else if(!strcmp(param1,"Zerg")) 
					{
						map[getMapCount()].player[modePlayer].setRace(ZERG);
						map[getMapCount()].player[modePlayer].setHarvest(&harvestSpeed[ZERG].minerals[0],&harvestSpeed[ZERG].gas[0]);
					}
					else 
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Invalid race.",mapFile,ln,old);
				}
				else if(!strcmp(item,"Starting Point"))
				{
					if(!map[getMapCount()].player[modePlayer].setPosition(value1))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Starting Point out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"Starting Minerals"))
				{
					if(!map[getMapCount()].player[modePlayer].setMins(value1*100))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Starting Minerals out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"Starting Gas"))
				{
					if(!map[getMapCount()].player[modePlayer].setGas(value1*100))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Starting Gas out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"Starttime"))
				{
					if(!map[getMapCount()].player[modePlayer].setTimer(value1))
						debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Start time out of range.",mapFile,ln,old);
				}
				else if(!strcmp(item,"@END"))
					mode=0;
				else
					debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Unknown entry.",mapFile,ln,old);
			}
			else if(mode==4) // PLAYER Block in LOCATION Block
			{
				//TODO: MAPDaten in seperate Mapfiles!
				if(!strcmp(item,"@END"))
					mode=2;
				else
				{
					for(i=0;i<UNIT_TYPE_COUNT;i++) 
					if(strstr(stats[map[getMapCount()].player[modePlayer].getRace()][i].name,item)!=NULL)
						{
/*							if(value1*stats[map[getMapCount()].player[modePlayer].getRace()][i].supply+map[getMapCount()].player[modePlayer].getSupply()<=MAX_SUPPLY)
							{
								if(stats[map[getMapCount()].player[modePlayer].getRace()][i].supply>0)
									map[getMapCount()].player[modePlayer].setSupply(map[getMapCount()].player[modePlayer].getSupply()-stats[map[getMapCount()].player[modePlayer].getRace()][i].supply*map[getMapCount()].location[modeLocation-1].force[modePlayer][i]);
								else map[getMapCount()].player[modePlayer].setMaxSupply(map[getMapCount()].player[modePlayer].getMaxSupply()+stats[map[getMapCount()].player[modePlayer].getRace()][i].supply*map[getMapCount()].location[modeLocation-1].force[modePlayer][i]);*/
								
								map[getMapCount()].location[0].force[modePlayer][i]=value1;
								//location[modePlayer][0].availible[i]=value1;
								map[getMapCount()].location[modeLocation-1].force[modePlayer][i]=value1;
								//location[modePlayer][modeLocation-1].availible[i]=value1;
								/*if(stats[map[getMapCount()].player[modePlayer].getRace()][i].supply>0)
									map[getMapCount()].player[modePlayer].setSupply(map[getMapCount()].player[modePlayer].getSupply()+stats[map[getMapCount()].player[modePlayer].getRace()][i].supply*value1);
								else map[getMapCount()].player[modePlayer].setMaxSupply(map[getMapCount()].player[modePlayer].getMaxSupply()-stats[map[getMapCount()].player[modePlayer].getRace()][i].supply*value1);*/
								//TODO: Begrenzungen bei researches und upgrades und nichtbaubaren Sachen!
//							};
							i=UNIT_TYPE_COUNT+1;
							break;
						};
					if(i!=UNIT_TYPE_COUNT+1) debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: No matching unit name.",mapFile,ln,item);
				}
			}
			else
				debug.toLog(0,"WARNING: (loadMapFile) %s: Line %d [%s]: Unknown entry. OMFG",mapFile,ln,item);

		}// END if(mode>0)
	}// END while



//	misc.supply=misc.maxSupply-misc.supply;
//	if(misc.maxSupply<misc.supply)
//		print("Warning: max supply is lower than supply.\n");
	map[getMapCount()].adjustSupply();
	map[getMapCount()].adjustDistanceList();
	setMapCount(getMapCount()+1);
	return(1);
};

const GA* SETTINGS::getGa()
{
	return(&ga);
};

int SETTINGS::initSoup()
{
	int tmp=0;
	if((tmp=soup.setParameters(&ga))!=1) return(100-tmp);
	if((tmp=soup.initSoup())!=1) return(200-tmp);
	return(1);
}


ANARACE* SETTINGS::newGeneration()
{
	return(soup.newGeneration());
};

void SETTINGS::loadDefaults()
{
	setMaxTime(MAX_TIME);
	setMaxTimeOut(MAX_TIMEOUT);
	setMaxLength(MAX_LENGTH);
	setMaxRuns(MAX_RUNS);
	setMaxGenerations(MAX_GENERATIONS);
	setPlayerCount(MAX_PLAYER);
	setPreprocessBuildOrder(0);
}

SETTINGS::SETTINGS()
{
	loadDefaults();
	srand(time(NULL));
}
