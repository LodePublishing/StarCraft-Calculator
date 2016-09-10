#include "soup.h"
SOUP::SOUP()
{
	for(int i=MAX_PLAYER-1;i--;) player[i]=new RACE;
	for(int i=RUNNINGS-1;i--;) statistics[i]=new STATISTICS;
	settings=new SETTINGS;
}
~SOUP::SOUP()
{
	for(int i=MAX_PLAYER-1;i--;) delete player[i];
	for(int i=RUNNINGS-1;i--;) delete statistics[i];
	delete settings;
}

void SOUP::init()
{
	settings.init();
	player::init();
	player[0]->Set_Goals(&settings);
        player[0]->AdjustMining();
        player[0]->generateBasicBuildorder();
        for(int i=MAX_PLAYER;i--;)
	        player[i]->Restart();
}

void SOUP::run()
{

}
