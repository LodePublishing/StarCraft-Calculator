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


int PRERACE::getPlayer()
{
	return(player);
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
	if((loc==0)||((!pMap->location[loc].force[player][COMMAND_CENTER])&&(!pMap->location[loc].force[0][MINERALS])))
	{
		for(j=45;j--;)
			mineralHarvestPerSecond[loc][j]=0;
	}
	else if((!pMap->location[loc].force[player][COMMAND_CENTER])&&(pMap->location[loc].force[0][MINERALS]))
	{
	//nach naehestem command_center suchen
	}
	else if((pMap->location[loc].force[player][COMMAND_CENTER])&&(!pMap->location[loc].force[0][MINERALS]))
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
			mineralHarvestPerSecond[loc][i]=(pMap->player[player].getBasicMineralHarvestPerSecond(k)*pMap->location[loc].force[0][MINERALS])/8;
		}
	}
	return(1);
};

int PRERACE::adjustGasHarvest(int loc)
{
	if((loc<0)||(loc>=MAX_LOCATIONS))
		return(0);
	int i,j;
	if((loc==0)||((!pMap->location[loc].force[player][COMMAND_CENTER])&&(!pMap->location[loc].force[player][REFINERY])))
	{
		for(j=5;j--;)
			gasHarvestPerSecond[loc][j]=0;
	}
	else if((!pMap->location[loc].force[player][COMMAND_CENTER])&&(pMap->location[loc].force[player][REFINERY]))
	{
	//nach naehestem command_center suchen
	}
	else if((pMap->location[loc].force[player][COMMAND_CENTER])&&(!pMap->location[loc].force[player][REFINERY]))
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
			gasHarvestPerSecond[loc][i]=(pMap->player[player].getBasicGasHarvestPerSecond(k)*pMap->location[loc].force[0][REFINERY]);
		}
	}
	return(1);
};

int PRERACE::loadPlayer(int num)
{
	if((num<=0)||(num>MAX_PLAYER))
		return(0);
	player=num;
	
	setMins(pMap->player[player].getMins());
	setGas(pMap->player[player].getGas());
	setTimer(pMap->player[player].getTimer());
	int i;
	for(i=0;i<MAX_LOCATIONS;i++)
	{
		adjustMineralHarvest(i);
		adjustGasHarvest(i);
	}
	return(1);
};

PRERACE::PRERACE()
{
};