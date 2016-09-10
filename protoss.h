#include "race.h"

class Player_Protoss: public RACE
{
public:
	virtual void Set_Goals();
	virtual void Build(unsigned short what);
	virtual void Calculate();
	virtual void InitRaceSpecific();
	Player_Protoss();
	virtual ~Player_Protoss();
};
