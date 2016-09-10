#include "harvest.h"

int HARVEST_SPEED::getHarvestMineralSpeed(int num)
{
	if((num<0)||(num>=45))
		return(0);
	return(minerals[num]);
};

int HARVEST_SPEED::getHarvestGasSpeed(int num)
{
	if((num<0)||(num>=5))
		return(0);
	return(gas[num]);
};
int HARVEST_SPEED::setHarvestMineralSpeed(int num,int speed)
{
	if((num<0)||(num>=45)||(speed<0))
		return(0);
	minerals[num]=speed;
	return(1);
};
int HARVEST_SPEED::setHarvestGasSpeed(int num,int speed)
{
	if((num<0)||(num>=5)||(speed<0))
		return(0);
	gas[num]=speed;
	return(1);
};

HARVEST_SPEED::HARVEST_SPEED()
{
	int i;
	for(i=0;i<45;i++)
		setHarvestMineralSpeed(i,0);
	for(i=0;i<5;i++)
		setHarvestGasSpeed(i,0);
};