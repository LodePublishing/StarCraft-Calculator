#include "race.h"

class Player_Zerg: public RACE
{
	unsigned short larvae;
	unsigned char larva[LARVA_MAX]; // larvacounter for producing larvas
	unsigned char larvacounter;
public:
	virtual void Set_Goals();
	virtual void Build(unsigned short what);
	virtual void Calculate();
	virtual void InitRaceSpecific();
	Player_Zerg();
	virtual ~Player_Zerg();
};
