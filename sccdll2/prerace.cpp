#include "prerace.h"

int PRERACE::setMins(int num)
{
	if(num<0)
		return(0);
	mins=num;
	return(1);
};

int PRERACE::setGas(int num)
{
	if(num<0)
		return(0);
	gas=num;
	return(1);
};

int PRERACE::setTimer(int num)
{
	if(num<0)
		return(0);
	timer=num;
	return(1);
};

int PRERACE::setSupply(int num)
{
	if((num>MAX_SUPPLY)||(num<0))
		return(0);
	supply=num;
	return(1);
};

int PRERACE::setMaxSupply(int num)
{
	if((num>MAX_SUPPLY)||(num<0))
		return(0);
	maxSupply=num;
	return(1);
};

int PRERACE::setMap(MAP* map)
{
	if(!map)
		return(0);
	pMap=map;
	return(1);
};


int PRERACE::getPlayer()
{
	return(playerNum);
};

int PRERACE::getSupply()
{
	return(supply);
};
int PRERACE::getMaxSupply()
{
	return(maxSupply);
};
int PRERACE::getMins()
{
	return(mins);
};
int PRERACE::getGas()
{
	return(gas);
};
int PRERACE::getTimer()
{
	return(timer);
};


int PRERACE::adjustMineralHarvest(int loc)
{
	if((loc<0)||(loc>=MAX_LOCATIONS))
		return(0);
	int i,j;
	if((loc==0)||((!pMap->location[loc].force[playerNum][COMMAND_CENTER])&&(!pMap->location[loc].force[0][MINERALS])))
	{
		for(j=45;j--;)
			mineralHarvestPerSecond[loc][j]=0;
	}
	else if((!pMap->location[loc].force[playerNum][COMMAND_CENTER])&&(pMap->location[loc].force[0][MINERALS]))
	{
	//nach naehestem command_center suchen
	}
	else if((pMap->location[loc].force[playerNum][COMMAND_CENTER])&&(!pMap->location[loc].force[0][MINERALS]))
	{
	//nach naehesten Mineralien suchen
	}

	//TODO: Wenn 2 SPieler an einem sammeln, beide einberechnen!
	else
	{
		int k;
		for(i=45;i--;)
		{
			k=0;
			for(j=0;j<45;j++)
				if(i*8<=j*pMap->location[loc].force[0][MINERALS]) { k=j;j=45;}
			mineralHarvestPerSecond[loc][i]=(player->getBasicMineralHarvestPerSecond(k)*pMap->location[loc].force[0][MINERALS])/8;
		}
	}
	return(1);
};

int PRERACE::adjustGasHarvest(int loc)
{
	if((loc<0)||(loc>=MAX_LOCATIONS))
		return(0);
	int i,j;
	if((loc==0)||((!pMap->location[loc].force[playerNum][COMMAND_CENTER])&&(!pMap->location[loc].force[playerNum][REFINERY])))
	{
		for(j=5;j--;)
			gasHarvestPerSecond[loc][j]=0;
	}
	else if((!pMap->location[loc].force[playerNum][COMMAND_CENTER])&&(pMap->location[loc].force[playerNum][REFINERY]))
	{
	//nach naehestem command_center suchen
	}
	else if((pMap->location[loc].force[playerNum][COMMAND_CENTER])&&(!pMap->location[loc].force[playerNum][REFINERY]))
	{
	//nach naehesten Mineralien suchen
	}
	else
	{
		int k;
		for(i=5;i--;)
		{
			k=0;
			for(j=0;j<5;j++)
				if(i<=j*pMap->location[loc].force[0][REFINERY]) { k=j;j=5;}
			gasHarvestPerSecond[loc][i]=(player->getBasicGasHarvestPerSecond(k)*pMap->location[loc].force[0][REFINERY]);
		}
	}
	return(1);
};

int PRERACE::loadPlayer(int num)
{
	if((num<0)||(num>=MAX_PLAYER))
		return(0);
	playerNum=num; //~```~  player[0]?
	player=&pMap->player[num];	
	pStats=player->goal->getpStats();
	setMins(player->getMins());
	setGas(player->getGas());
	setTimer(player->getTimer());
	int i;
	for(i=0;i<MAX_LOCATIONS;i++)
	{
		adjustMineralHarvest(i);
		adjustGasHarvest(i);
	}
	return(1);
};

int PRERACE::getRun()
{
	return(run);
};

void PRERACE::harvestResources()
{
	int i;
//	int t=(rand()%10)-5;
	for(i=1;i<MAX_LOCATIONS;i++)//~~
	{
		int s=location[i].availible[SCV];
		if(s<56) //~~
		{
			mins+=mineralHarvestPerSecond[i][s];
		       	//~~~ neu berechnen / Tabelle anlegen! sind ja nicht bei jeder Exe gleichviel Mineralien...
			harvestedMins+=mineralHarvestPerSecond[i][s]; //~~~
		}
		else
		{
			mins+=mineralHarvestPerSecond[i][56];
			harvestedMins+=mineralHarvestPerSecond[i][56];
		}
		s=location[i].availible[GAS_SCV];
		if(s<4)
		{
			gas+=gasHarvestPerSecond[i][s];
			harvestedGas+=gasHarvestPerSecond[i][s];
		}
		else
		{
			gas+=gasHarvestPerSecond[i][4];;
			harvestedGas+=gasHarvestPerSecond[i][4];
		}
	}
}



PRERACE::PRERACE()
{
	int i,j;
	run=0;
	player=0;
	mins=0;
	gas=0;
	timer=0;
	supply=0;
	maxSupply=0;
	IP=0;
	harvestedGas=0;
	harvestedMins=0;
	length=0;
	//todo: mehr auf 0 setzen!
	for(i=0;i<MAX_LOCATIONS;i++)
	{
		for(j=0;j<45;j++)
			mineralHarvestPerSecond[i][j]=0;
		for(j=0;j<5;j++)
			gasHarvestPerSecond[i][j]=0;
	};
	for(i=0;i<MAX_LENGTH;i++)
	{
		Code[0][i]=0;
		Code[1][i]=0;
	};
};

int PRERACE::setMap(MAP* map);
MAP* PRERACE::pMap;
int PRERACE::run;
GA* PRERACE::ga;