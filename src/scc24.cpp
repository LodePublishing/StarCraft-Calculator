#include "settings.h"
#include "soup.h"

int main(int argc[], int argv[])
{
	SETTINGS* set=new SETTINGS();
        RACE::pSet=set;
        ANARACE::pSet=set;
	SOUP* soup=new SOUP(set);
	while(soup->newGeneration());
/*while(!soup->complete)
{
	soup->run(); //make a run and put the best one in statistics
	io.print(soup->statistics,RUN);		
}
soup.make_additional_statistics();
io.print(soup.statistics,FINAL); // file/screen
io.save(soup.statistics);*/
	delete soup;
	delete set;
	return(0);
}


