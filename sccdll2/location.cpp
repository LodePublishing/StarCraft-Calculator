#include "location.h"
#include "string.h"

int MAP_LOCATION::setName(const char* line)
{
	if(!line)
		return(0);
	strcpy(name,line);
	return(1);
};

int MAP_LOCATION::setMineralCount(int num)
{
	if(num<0)
		return(0);
	mineralCount=num;
	return(1);
};


int MAP_LOCATION::setMineralDistance(int num)
{
	if(num<0)
		return(0);
	mineralDistance=num;
	return(1);
};

int MAP_LOCATION::setGeysirCount(int num)
{
	if(num<0)
		return(0);
	geysirCount=num;
	return(1);
};


const char* MAP_LOCATION::getName()
{
	return(name);
};

int MAP_LOCATION::getMineralCount()
{
	return(mineralCount);
};

int MAP_LOCATION::getMineralDistance()
{
	return(mineralDistance);
};

int MAP_LOCATION::getGeysirCount()
{
	return(geysirCount);
};


MAP_LOCATION::MAP_LOCATION()
{
	int i,j;
	strcpy(name,"Error!");
	mineralCount=0;
	mineralDistance=0;
	geysirCount=0;
	for(i=0;i<MAX_LOCATIONS;i++)
		distance[i]=0;
	for(i=0;i<MAX_PLAYER;i++)
		for(j=0;j<UNIT_TYPE_COUNT;j++)
			force[i][j]=0;
};