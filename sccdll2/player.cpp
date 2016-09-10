#include "player.h"

int PLAYER::getMins()
{
	return(mins);
};

int PLAYER::getGas()
{
	return(gas);
};

int PLAYER::getTimer()
{
	return(timer);
};

int PLAYER::getPosition()
{
	return(position);
};

int PLAYER::getRace()
{
	return(race);
};

int PLAYER::getSupply()
{
	return(supply);
};

int PLAYER::getMaxSupply()
{
	return(maxSupply);
};

int PLAYER::getBasicMineralHarvestPerSecond(int num)
{
	if(num<0)
		return(0);
	if(num>44)
	return(basicMineralHarvestPerSecond[44]);
	else
	return(basicMineralHarvestPerSecond[num]);
};

int PLAYER::getBasicGasHarvestPerSecond(int num)
{
	if(num<0)
		return(0);
	if(num>4)
	return(basicGasHarvestPerSecond[4]);
	else
	return(basicGasHarvestPerSecond[num]);
};

int PLAYER::setMins(int num)
{
	if(num<0) return(0);
	mins=num*100;
	return(1);
};

int PLAYER::setGas(int num)
{
	if(num<0) return(0);
	gas=num*100;
	return(1);
};

int PLAYER::setTimer(int num)
{
	if(num<0) return(0);
	timer=num;
	return(1);
};

int PLAYER::setPosition(int num)
{
	if(num<0) return(0);
	position=num;
	return(1);
};

int PLAYER::setRace(int num)
{
	if((num<0)||(num>2)) return(0);
	race=num;
	return(1);
};

int PLAYER::setSupply(int num)
{
	if((num<0)||(num>MAX_SUPPLY))
		return(0);
	supply=num;
	return(1);
};

int PLAYER::setMaxSupply(int num)
{
	if((num<0)||(num>MAX_SUPPLY))
		return(0);
	maxSupply=num;
	return(1);
};



int PLAYER::setBasicHarvestPerSecond(int* mining, int* gasing)
{
	//TODO: pruefen ob schon initialisiert
	if((!mining)||(!gasing)) 
		return(0);
	basicMineralHarvestPerSecond=mining;
	basicGasHarvestPerSecond=gasing;
	return(1);
};

int PLAYER::setGoal(GOAL_ENTRY* goal)
{
	if(!goal)
		return(0);
	this->goal=goal;
	return(1);
};