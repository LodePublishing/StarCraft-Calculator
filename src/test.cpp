#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "genetic.h"
#include "population.h"
int main()
{
	srand(time(NULL));
	GENETIC a,b,c,d;
	a.createGenCode();b.createGenCode();
	a.crossOver(&b,&c,&d);

	c.printOutComparison(&d);
	
	
	return 0;
}
