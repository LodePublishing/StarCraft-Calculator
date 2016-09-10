#include "map.h"
#include "string.h"

const char* MAP::getName()
{
	return(name);
};

int MAP::getMaxLocations()
{
	return(maxLocations);
};

int MAP::getMaxPlayer()
{
	return(maxPlayer);
};

int MAP::setName(const char* line)
{
	if(!line)
		return(0);
	strcpy(name,line);
	return(1);
};

int MAP::setMaxLocations(int num)
{
	if(num<=0)
		return(0);
	maxLocations=num;
	return(1);
};

int MAP::setMaxPlayer(int num)
{
	if((num<1)||(num>MAX_PLAYER))
		return(0);
	maxPlayer=num;
	return(1);
};


MAP::MAP()
{
	name=new char[64];
	strcpy(name,"Error!");
	maxLocations=0;
	maxPlayer=0;
};

MAP::~MAP()
{
	delete name;
}