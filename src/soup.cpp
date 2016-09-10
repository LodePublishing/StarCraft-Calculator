#include "soup.h"
#include "settings.h"
#include "race.h"

SOUP::SOUP(SETTINGS *set)
{
	for(int i=MAX_PLAYER-1;i--;) player[i]=new RACE(set);
//	for(int i=RUNNINGS-1;i--;) statistics[i]=new STATISTICS;
	settings=set;
};

SOUP::~SOUP()
{
	delete [] player;
//	delete [] statistics;
};

void SOUP::run()
{
};
