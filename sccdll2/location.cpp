#include "location.h"
#include "string.h"

int MAP_LOCATION_BASIC::setName(const char* line)
{
	if(!line)
		return(0);
	strcpy(name,line);
	return(1);
};

int MAP_LOCATION_BASIC::setMineralCount(int num)
{
	if(num<0)
		return(0);
	mineralCount=num;
	return(1);
};


int MAP_LOCATION_BASIC::setMineralDistance(int num)
{
	if(num<0)
		return(0);
	mineralDistance=num;
	return(1);
};

int MAP_LOCATION_BASIC::setGeysirCount(int num)
{
	if(num<0)
		return(0);
	geysirCount=num;
	return(1);
};

int MAP_LOCATION_BASIC::setDistance(int num,int dist)
{
	if((num<0)||(num>=MAX_LOCATIONS)||(dist<0))
		return(0);
	distance[num]=dist;
	return(1);
};

const char* MAP_LOCATION_BASIC::getName()
{
	return(name);
};

int MAP_LOCATION_BASIC::getMineralCount()
{
	return(mineralCount);
};

int MAP_LOCATION_BASIC::getMineralDistance()
{
	return(mineralDistance);
};

int MAP_LOCATION_BASIC::getGeysirCount()
{
	return(geysirCount);
};

int MAP_LOCATION_BASIC::getDistance(int num)
{
	if((num<0)||(num>=MAX_LOCATIONS))
		return(0);
	return(distance[num]);
}


MAP_LOCATION_BASIC::MAP_LOCATION_BASIC()
{
	int i,j;
	strcpy(name,"Error!");
	mineralCount=0;
	mineralDistance=0;
	geysirCount=0;
	for(i=0;i<MAX_LOCATIONS;i++)
		setDistance(i,0);
	for(i=0;i<MAX_PLAYER;i++)
		for(j=0;j<UNIT_TYPE_COUNT;j++)
			force[i][j]=0;
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

int MAP_LOCATION::setDistance(int num,int dist)
{
	if((num<0)||(num>=MAX_LOCATIONS)||(dist<0))
		return(0);
	distance[num]=dist;
	return(1);
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

int MAP_LOCATION::getDistance(int num)
{
	if((num<0)||(num>=MAX_LOCATIONS))
		return(0);
	return(distance[num]);
};

MAP_LOCATION::MAP_LOCATION()
{
	int i,j;
	mineralCount=0;
	mineralDistance=0;
	geysirCount=0;
	for(i=0;i<MAX_LOCATIONS;i++)
		setDistance(i,0);
	for(j=0;j<UNIT_TYPE_COUNT;j++)
	{
			force[j]=0;
			availible[j]=0;
	};
};
