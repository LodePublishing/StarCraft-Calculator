#include "race.h"

class Player_Protoss: public RACE
{
public:
	virtual void Set_Goals();
	virtual void Build(unsigned char what);
	virtual void Calculate();
	virtual void InitRaceSpecific();
	virtual void readjust_goals();
	Player_Protoss();
	virtual ~Player_Protoss();
};
