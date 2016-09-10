#include "genetic.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

unsigned int GENETIC::getCodeLength()
{
	return codeLength;
}

int getCodon(int byte,int num)
{
	return((byte>>num)&3);
}

void GENETIC::constructDominantCode()
{
	int i,j;
	for(i=0;i<MAX_LENGTH_EXPRESSED_CODE;i++)
	{
		expressed[i]=0;
		for(j=0;j<16;j++) //16 Codons!
			expressed[i]+=((getCodon(geneCode[2*i],2*j)+getCodon(geneCode[2*i+MAX_LENGTH_GENETIC_STRING],2*j)>3)<<j)
  				     +((getCodon(geneCode[2*i+1],2*j)+getCodon(geneCode[2*i+1+MAX_LENGTH_GENETIC_STRING],2*j)>3)<<(16+j));
	}
	constructCode();
	//createPhaenotype();
        //Calculate();
}


inline static unsigned int readbit(unsigned int array,int position)
{
        return ((array>>position)&1);
}

void GENETIC::constructCode()
{
        unsigned int i,j,t,Start,Ende,l;
        l=0;
	Ende=0;
	while(l<MAX_LENGTH_CODE)
	{
		t=1;
		for(i=Ende;(t<4)&&(t>0)&&(i<((MAX_LENGTH_EXPRESSED_CODE<<5)-4));i++)
	        {
	                t=0;
	                for(j=0;j<4;j++)
	                        t+=readbit(expressed[(i+j)>>5],(i+j)%32);
	        }
		if(i>=((MAX_LENGTH_EXPRESSED_CODE<<5)-4)) return;
		Start=i+3;
		t=1;
		for(i=Start;(t<4)&&(t>0)&&(i<((MAX_LENGTH_EXPRESSED_CODE<<5)-4));i++)
	        {
	                t=0;
	                for(j=0;j<4;j++)
	                        t+=readbit(expressed[(i+j)>>5],(i+j)%32);
	        }
		if(i>=((MAX_LENGTH_EXPRESSED_CODE<<5)-4)) return;
		Ende=i-1;
		for(i=Start;i<Ende;i++)
			Code[l]+=readbit(expressed[i>>5],i%32)<<(i-Start);
		l++;
		Ende+=4;
	}
}



void GENETIC::createRandomGenCode()
{
	int i;
	for(i=0;i<MAX_LENGTH_GENETIC_STRING*2;i++)
		geneCode[i]=rand()+rand();
	constructDominantCode(); // <- first run
}

void GENETIC::crossOver(GENETIC * partner, GENETIC * child1, GENETIC * child2)
{
	int counter,i,j,num,lokus,mask1,mask2,mask3,mask4;
	counter=MAX_LENGTH_GENETIC_STRING;
	GENETIC * c;
	
	for(i=0;i<MAX_LENGTH_GENETIC_STRING;i++)
	{
		if(rand()%counter<4)
		{
			num=MAX_LENGTH_GENETIC_STRING-counter;
			
			memcpy(&child1->geneCode[i-num],&geneCode[i-num],4*num);
			memcpy(&child1->geneCode[i+counter],&partner->geneCode[i+counter],4*num);
			memcpy(&child2->geneCode[i+counter],&geneCode[i+counter],4*num);
			memcpy(&child2->geneCode[i-num],&partner->geneCode[i-num],4*num);

			lokus=2*(rand()%16);
                        mask1=0;mask2=0;mask3=0;mask4=0;

                        for(j=0;j<lokus;j++)
                        {
                                mask1+=child1->geneCode[i-num]&(1<<j);
                                mask2+=child2->geneCode[i+counter]&(1<<j);
                                mask3+=child1->geneCode[i+counter]&(1<<j);
                                mask4+=child2->geneCode[i-num]&(1<<j);
                        }
                        for(j=lokus;j<16;j++)
                        {
                                mask1+=geneCode[i-num]&(1<<j);
                                mask2+=geneCode[i+counter]&(1<<j);
                                mask3+=partner->geneCode[i-num]&(1<<j);
                                mask4+=partner->geneCode[i+counter]&(1<<j);
                        }
			child1->geneCode[i-num]=mask1;child1->geneCode[i+counter]=mask3;
			child2->geneCode[i-num]=mask4;child2->geneCode[i+counter]=mask2;

                        lokus=2*(rand()%16);
                        mask1=0;mask2=0;mask3=0;mask4=0;

                        for(j=0;j<lokus;j++)
                        {
                                mask1+=child1->geneCode[i]&(1<<j);
                                mask2+=child2->geneCode[i+MAX_LENGTH_GENETIC_STRING]&(1<<j);
                                mask3+=child1->geneCode[i+MAX_LENGTH_GENETIC_STRING]&(1<<j);
                                mask4+=child2->geneCode[i]&(1<<j);
                        }
                        for(j=lokus;j<16;j++)
                        {
                                mask1+=geneCode[i]&(1<<j);
                                mask2+=geneCode[i+MAX_LENGTH_GENETIC_STRING]&(1<<j);
                                mask3+=partner->geneCode[i]&(1<<j);
                                mask4+=partner->geneCode[i+MAX_LENGTH_GENETIC_STRING]&(1<<j);
                        }
                        child1->geneCode[i]=mask1;child1->geneCode[i+MAX_LENGTH_GENETIC_STRING]=mask3;
                        child2->geneCode[i]=mask4;child2->geneCode[i+MAX_LENGTH_GENETIC_STRING]=mask2;
			
			counter=MAX_LENGTH_GENETIC_STRING;
			c=child1;
			child1=child2;
			child2=c;
		}
		counter--;
	}
	//TODO: length bei crossover beachten. Wenn Ende erreicht, dann Laenge vom ersten uebernehmen
	num=MAX_LENGTH_GENETIC_STRING-counter;
	memcpy(&child1->geneCode[counter],&geneCode[counter],num*4);
        memcpy(&child1->geneCode[counter+MAX_LENGTH_GENETIC_STRING],&partner->geneCode[counter+MAX_LENGTH_GENETIC_STRING],num*4);
        memcpy(&child2->geneCode[counter+MAX_LENGTH_GENETIC_STRING],&geneCode[counter+MAX_LENGTH_GENETIC_STRING],num*4);
        memcpy(&child2->geneCode[counter],&partner->geneCode[counter],num*4);
	child1->p1=this;child2->p1=this;
	child1->p2=partner;child2->p2=partner;
	child1->mutateGeneCode();child2->mutateGeneCode();
	child1->constructDominantCode();child2->constructDominantCode();
}

void GENETIC::printOutComparison(GENETIC * partner)
{
	printf("Comparison THIS  <--->  the other one\n\n");
	printf("Phaenotype relationship: %i\n",calculateProgramRelationship(partner));
	printf("Dominance code relationship: %i\n",calculateDominanceRelationship(partner));
	printf("Genotype relationship: %i\n\n",calculateGenotypeRelationship(partner));
	printf("With parents:\n\n");
	printf("Phaenotype: %4i	 <-->  %4i\n",calculateProgramRelationship(p1)+calculateProgramRelationship(p2),partner->calculateProgramRelationship(partner->p1)+partner->calculateProgramRelationship(partner->p2));
	printf("Dominance : %4i  <-->  %4i\n",calculateDominanceRelationship(p1)+calculateDominanceRelationship(p2),partner->calculateDominanceRelationship(partner->p1)+partner->calculateDominanceRelationship(partner->p2));
	printf("Genotype  : %4i  <-->  %4i\n",calculateGenotypeRelationship(p1)+calculateGenotypeRelationship(p2),partner->calculateGenotypeRelationship(partner->p1)+partner->calculateGenotypeRelationship(partner->p2));
}

long GENETIC::calculateGenotypeRelationship(GENETIC * partner)
{
	int i,j;
	long difference;
	difference=0;
	for(i=0;i<MAX_LENGTH_GENETIC_STRING;i++)
		for(j=0;j<16;j++)
		{
			difference+=(getCodon(geneCode[i],2*j)-getCodon(partner->geneCode[i],2*j))*(getCodon(geneCode[i],2*j)-getCodon(partner->geneCode[i],2*j)) + (getCodon(geneCode[i+MAX_LENGTH_GENETIC_STRING],2*j)-getCodon(partner->geneCode[i+MAX_LENGTH_GENETIC_STRING],2*j))*(getCodon(geneCode[i+MAX_LENGTH_GENETIC_STRING],2*j)-getCodon(partner->geneCode[i+MAX_LENGTH_GENETIC_STRING],2*j));
		}
	return difference;
}

long GENETIC::calculateProgramRelationship(GENETIC * partner)
{
	int i,j;
        long difference;
        difference=0;
        for(i=0;i<MAX_LENGTH_CODE;i++)
        	difference+=(Code[i]%256-partner->Code[i]%256)*(Code[i]%256-partner->Code[i]%256);
        return difference;
}

long GENETIC::calculateDominanceRelationship(GENETIC * partner)
{
	int i,j;
        long difference;
	difference=0;
	for(i=0;i<MAX_LENGTH_EXPRESSED_CODE;i++)
		for(j=0;j<32;j++)
	                difference+=(((expressed[i]>>j)&1)-((partner->expressed[i]>>j)&1))*(((expressed[i]>>j)&1)-((partner->expressed[i]>>j)&1));
	return difference;
}

void GENETIC::mutateGeneCode() // TODO: report the mutation
{
	unsigned short i,j;
	unsigned short lokus,codon;
	for(i=0;i</*setup.getMutations()*/MAX_LENGTH_GENETIC_STRING;i++)
		if(rand()%MAX_LENGTH_GENETIC_STRING/*setup.getMutationRate()*/==0)
		{
			lokus=rand()%(MAX_LENGTH_GENETIC_STRING);
			codon=(rand()%2)*MAX_LENGTH_GENETIC_STRING;
			switch(rand()%6)
			{
				case 0://add two bits at bitposition 31 and 32
					for(j=MAX_LENGTH_GENETIC_STRING-1+codon;j>lokus+codon;j--)
						geneCode[j]=(geneCode[j]>>2)+(geneCode[j-1]<<31)+(geneCode[j-1]<<30);
					geneCode[lokus+codon]=(geneCode[lokus+codon]>>2)+((rand()%4)<<30);
					break;
				case 1://delete the upper two bits
					for(j=lokus+codon;j<MAX_LENGTH_GENETIC_STRING+codon;j++)
						geneCode[j]=(geneCode[j]<<2);
					geneCode[MAX_LENGTH_GENETIC_STRING-1+codon]+=rand()%4;
					break;
				case 2:
				case 3:
				case 4:
				case 5://change one bit
					geneCode[lokus+codon]^=(rand()%2)<<(rand()%32);break;
				/*
					
				move&insert block
				move&replace block
				copy&replace block
				copy&insert block
				exchange two blocks
					break;*/
			}
		}
}

GENETIC::GENETIC()
{
        geneCode=new unsigned int[MAX_LENGTH_GENETIC_STRING*2];
        expressed=new unsigned int[MAX_LENGTH_EXPRESSED_CODE];
        Code=new unsigned int[MAX_LENGTH_CODE];
}

GENETIC::~GENETIC()
{
        delete[] geneCode;
        delete[] expressed;
        delete[] Code;
}

