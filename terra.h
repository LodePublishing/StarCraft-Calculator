#include "race.h"

class Player_Terra: public RACE
{
	// availible starports with control towers and factories with machine shops
	unsigned char av_starport,av_factory;
public:
	virtual void Set_Goals();
	virtual void Build(unsigned short what);
	virtual void Calculate();
	virtual void InitRaceSpecific();
	Player_Terra();
	virtual ~Player_Terra();
};
