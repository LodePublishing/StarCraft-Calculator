#include "settings.h"
#include "statistics.h"
#include "race.h"
class SOUP
{
	private:
		RACE* player[MAX_PLAYER];
		int run_number;
	public:
		SOUP();
		~SOUP();
		void init();
		void run(); //one generation, copies stats and results of best individual and average values of the soup in 'best'
		STATISTICS* statistics[RUNNINGS]; //list of result of all best of all runs
		SETTINGS* settings;
}





