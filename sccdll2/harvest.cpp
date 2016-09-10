#include "harvest.h"


HARVEST_SPEED::HARVEST_SPEED()
{
	int i;
	for(i=0;i<45;i++) 
		minerals[i]=0;
	for(i=0;i<5;i++) 
		gas[i]=0;
};