#include "genetic.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
//#include "main.h"

unsigned int GENETIC::getCodeLength()
{
	return codeLength;
}

int getCodon(int byte,int num)
{
	return((byte>>num)&3);
}

void GENETIC::printOutCode()
{
	int i,j;
	printf("\n");
	for(i=0;i<5;i++)
	{
	        for(j=0;j<32;j++)
			printf("%i",(Code[i]>>(31-j))&1);
		printf("\n");
	}
}

void GENETIC::printOutDominanceScheme()
{
	int i,j;
	for(i=0;i<MAX_LENGTH_EXPRESSED_CODE;i++)
        {
/*               for(j=0;j<16;j++)
                        printf("%i%i ",(geneCode[2*i]>>(2*j))&1,(geneCode[2*i]>>(2*j+1))&1 );

                for(j=0;j<16;j++)
                        printf("%i%i ",(geneCode[2*i+1]>>(2*j))&1,(geneCode[2*i+1]>>(2*j+1))&1 );

                printf("\n");
                for(j=0;j<16;j++)
                        printf("%i%i ",(geneCode[2*i+MAX_LENGTH_GENETIC_STRING]>>(2*j))&1,(geneCode[2*i+MAX_LENGTH_GENETIC_STRING]>>(2*j+1))&1);
                for(j=0;j<16;j++)
                        printf("%i%i ",(geneCode[2*i+1+MAX_LENGTH_GENETIC_STRING]>>(2*j))&1,(geneCode[2*i+1+MAX_LENGTH_GENETIC_STRING]>>(2*j+1))&1);

                printf("\n");*/
                for(j=0;j<16;j++)
                        printf("%i",(expressed[i]>>(31-j))&1);
		printf(" ");
		for(j=16;j<32;j++)
			printf("%i",(expressed[i]>>(31-j))&1);
		printf(" [%i .. %i]\n",i*32,(i+1)*32);	
        }
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
	//createPhaenotype();
}

int scanPatternB(unsigned short* bitString,unsigned int start) 
{
	int k;
	int j=start%16;
	printf("StartB: %5i  ",start);
//	unsigned int maskeShift=(15<<28);
//	maskeShift=maskeShift>>j;
	for (int i=start/16; i<MAX_LENGTH_EXPRESSED_CODE*2; i++) 
	{
		unsigned int* sub =(unsigned int*)(bitString+i);
		while(j<16)
		{
        	    if(((*sub>>(28-j))&15==15)||((*sub>>(28-j))&15==0))
		    {
			    printf("!! (*sub>>(12+j))=%i",(*sub>>(12+j)));
			    return (i*16+j+4);
		    }
		    //maskeShift >>= 1;
		    j++;
        	}
		j=0;
		//maskeShift=(15<<28);
	}
        return -1;
} 

int scanPatternE(unsigned short* bitString,unsigned int start)
{
        int k;
        int j=start%16;
	printf("StartE: %5i  ",start);
//	unsigned int maskeShift=(15<<28);
//	maskeShift=maskeShift>>j;
        for (int i=start/16; i<MAX_LENGTH_EXPRESSED_CODE*2; i++)
        {
		unsigned int* sub =(unsigned int*)(bitString+i);
                while(j<16)
                {
                    if(((*sub>>(28-j))&15==15)||((*sub>>(28-j))&15==0))
                            return (i*16+j);
                    
//		    maskeShift = maskeShift >> 1;
                    j++;
                }
                j=0;
//		maskeShift=(15<<28);
        }
        return -1;
}


void GENETIC::createPhaenotype()
{
	int i,j,k,l;
	unsigned short* bitString;
	bitString=(unsigned short*)expressed;
	i=scanPatternB(bitString,0);
	printf("I: %i\n",i);
	l=0;
	while((i>0)&&(l<19))
	{
		j=scanPatternE(bitString,i);
		if(j>0)
		{
				printf("%i -> %i\n",i,j);
				for(k=i;k<j;k++)
				{
					Code[l]+=((expressed[k/32]>>(31-k%32))&1)<<((k-i)%32);
					printf("[%i]",((expressed[k/32]>>(31-k%32))&1));	
				}
				printf("\n");
				l++;
			i=scanPatternB(bitString,j);
		}
		else i=-1;
		
	}
}	


void GENETIC::createGenCode()
{
	int i;
	codeLength=4;//rand()%(MAX_LENGTH_EXPRESSED_CODE-MIN_LENGTH_EXPRESSED_CODE)+MIN_LENGTH_EXPRESSED_CODE;
	for(i=0;i<MAX_LENGTH_GENETIC_STRING*2;i++)
		geneCode[i]=rand()+rand();
	constructDominantCode(); // <- first run
}

GENETIC::GENETIC()
{
	geneCode=new unsigned int[MAX_LENGTH_GENETIC_STRING*2];
	expressed=new unsigned int[MAX_LENGTH_EXPRESSED_CODE];
	Code=new unsigned int[20];
}

GENETIC::~GENETIC()
{
	delete[] geneCode;
	delete[] expressed;
	delete[] Code;
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
	child1->codeLength=partner->codeLength;
	child2->codeLength=codeLength;//~~~
	child1->mutateGeneCode();child2->mutateGeneCode();
	child1->constructDominantCode();child2->constructDominantCode();
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
			lokus=rand()%(codeLength*2);
			codon=(rand()%2)*MAX_LENGTH_GENETIC_STRING;
			switch(rand()%6)
			{
				case 0://add two bits at bitposition 31 and 32
					for(j=MAX_LENGTH_GENETIC_STRING-1+codon;j>lokus+codon;j--)
						geneCode[j]=(geneCode[j]>>2)+(geneCode[j-1]<<31)+(geneCode[j-1]<<30);
					geneCode[lokus+codon]=(geneCode[lokus+codon]>>2)+((rand()%4)<<30);
					if((rand()%32==0)&&(codeLength<MAX_LENGTH_EXPRESSED_CODE)) codeLength++;
					break;
				case 1://delete the upper two bits
					for(j=lokus+codon;j<MAX_LENGTH_GENETIC_STRING+codon;j++)
						geneCode[j]=(geneCode[j]<<2);
					geneCode[MAX_LENGTH_GENETIC_STRING-1+codon]+=rand()%4;
					if((rand()%32==0)&&(codeLength>MIN_LENGTH_EXPRESSED_CODE)) codeLength--;
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
