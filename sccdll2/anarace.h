#ifndef __ANARACE_H
#define __ANARACE_H

//#include "main.h"
//#include "settings.h"
#include "prerace.h"

class SCCDLL_API ANARACE: public PRERACE
{
private:
		int buildGene(int what);
public:
//Output:

		struct Success
		{
			int what; // what kind of error
			int type; // unit number
			int loc; // location
		} success;
	
        struct Program
        {
                int needSupply,haveSupply,built,dominant,haveMinerals,haveGas,time,mins,gas,temp,location,type;
				Success success[2];
        } program[MAX_LENGTH];

//        static int initialized;

struct Building
{
        int RB; // Remaining Buildtime
        int type; // Type of Building
        int unitCount; //number of units which are moving... currently ONLY for movements...
        int IP;
        int facility; // in what facility it was produced
        int location;
        int goal; //For movement!
		int onTheRun;
        // TODO: Aus Optimierungsgruenden: Eine logforce Variable die _Alle_ Einheiten mitzaehlt
} building[MAX_BUILDINGS]; //Building declaration in main.h*/

        int generation;
        int maxpFitness;
        int maxsFitness;
		int maxtFitness;
        int unchangedGenerations;
	
//Controls:
	void calculate(); 
	void resetData(); //resets all data to standard values
	ANARACE();
};

#endif //__ANARACE_H
