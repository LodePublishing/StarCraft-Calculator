#ifndef __GENETIC_H
#define __GENETIC_H

#include "main.h"
//#include "settings.h"
#define MAX_LENGTH_GENETIC_STRING 384
#define MIN_LENGTH_GENETIC_STRING 50
#define MAX_LENGTH_EXPRESSED_CODE (MAX_LENGTH_GENETIC_STRING/4)
#define MIN_LENGTH_EXPRESSED_CODE (MIN_LENGTH_GENETIC_STRING/4)
#define MAX_LENGTH_CODE MAX_LENGTH_EXPRESSED_CODE
// The center of the storm!
class GENETIC
{
	public:
		unsigned int codeLength;
		unsigned int * geneCode;
		unsigned int * expressed;
		void constructDominantCode();
		void mutateGeneCode();
		void constructCode();
		long calculateGenotypeRelationship(GENETIC * partner);
		long calculateDominanceRelationship(GENETIC * partner);
		long calculateProgramRelationship(GENETIC * partner);
		GENETIC * p1;
		GENETIC * p2;
// => in Race
		virtual void createPhaenotype() {};
		virtual void Calculate() {};
		unsigned int * Code;
		unsigned int getCodeLength();
		void createRandomGenCode();
		void printOutComparison(GENETIC * partner);
		void crossOver(GENETIC * partner,GENETIC * child1,GENETIC * child2);
		GENETIC();
		~GENETIC();
};

#endif
