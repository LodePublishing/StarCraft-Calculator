#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "init.h"
#include "io.h"



myBO bo[MAX_LENGTH];


void Init()
{
	unsigned char i;
	Max_Build_Types=0;
        for(i=0;i<MAX_GOALS;i++)
	        if(buildable[i]==1)
	        {
		        Build_Av[Max_Build_Types]=i;
			Build_Bv[i]=Max_Build_Types;
		        Max_Build_Types++;
		}
		goal[58].what=0; // Just to be sure :)
		goal[59].what=0;
}


unsigned char TranslateData(int argc, char* argv[])
{
	//TODO: Check unsigned char <> unsigned short counting variables (especially s,t,u)
	
	int s,a,u,translate,zahl,t;
	char * buffer;
	char * IOp;
//	char * gizmo;
	long size=0;
	int i,j,k,f,countr[3];

	struct mySTATS
	{
	        unsigned short code[26];
	        unsigned char length;
	} mystats[3][MAX_GOALS];
	
	race=5;
//	Test=0;
	translate=0;

	if(argc<=1)
	{
		printf("HINT: You may directly start wcc also with h, o, e or z as parameter.\n");
		printf("Press ENTER to continue\n");
		a=getchar();
//		printf("%s",helper);
//		delete helper;
	}
	else
	{
  		     if(UpperCase(argv[1][0])=='T') race=TERRA;
		else if(UpperCase(argv[1][0])=='P') race=ZERG;
		else if(UpperCase(argv[1][0])=='Z') race=PROTOSS;

		else if((argc>2)&&(argv[1][0]=='-'))
		{
			if(UpperCase(argv[1][1])=='I')
			{
				translate=1; // We need a translation of the data later
				IOp = new char [sizeof(argv[2])]; 
				IOp=argv[2];
				FILE * pFile2;
				pFile2 = fopen(IOp,"rb");
				if(pFile2==NULL)
				{
					printf("FATAL ERROR: Build Order File %s not found.\n",IOp);
					printf("Exiting...\n");
					return(1);
				}
				printf("Checking build order input file [%s]...\n",IOp);
				printf("File found. Opening...\n");
				printf("File opened... reading...\n");
			        fseek (pFile2, 0, SEEK_END);
				size = ftell (pFile2);
				buffer = new char [size];
				fseek (pFile2, 0, SEEK_SET);
				fread(buffer,1,size,pFile2);
				fclose(pFile2);
				printf("File closed, data saved [%i Bytes].\n",size);
			} else  // not 'I'
	// B? User called 'scc' with a goal / build order list as parameter
			if(UpperCase(argv[1][1])=='B')
			{
				translate=1; // we need a translation of the data later
				size=0;
				for(t=2;t<argc;t++) size+=sizeof(argv[t])+100;
			//TODO: Find a better formula for size (segmentation faults!)	
				buffer = new char [size];
				for(t=0;t<size;t++)
					buffer[t]=0;
				s=0;
// Analyze the parameters and copy them into a buffer
				for(t=2;t<argc;t++)
				{
					u=0;
					if((argv[t][0]>47)&&(argv[t][0]<58))
					{
						while((argv[t][u]>47)&&(argv[t][u]<58))
						{
							buffer[s+u]=argv[t][u];
							u++;
						}
						s+=u;
						t++;
						u=0;
					}
					if(t<argc)
					{
						while(argv[t][u]>64)
						{
							buffer[s]=argv[t][u];
							u++;s++;
						}
					}
					buffer[s]=10;
					s++;
				}
			} else //not 'B', not 'I'
			{
//				printf("%s",helper);
//			        delete helper;
				return(1);
			}
	         } else //not '-'
		 {
//                 	printf("%s",helper);
//			delete helper;
			return(1);
		 }			 
	} // end of 'not argc<=1'
				
//TODO!! inform the user about the abort...			
	if(translate==1) 

	{
	
	for(t=0;t<MAX_LENGTH;t++)
		{
			for(s=0;s<26;s++) bo[t].code[s]=0;
			bo[t].type=0;
			bo[t].race=5;
			bo[t].length=0;
		}
		s=0;t=0;
		zahl=0;	
		 
		while(s<size)
		{		
			if(buffer[s]==10)
			{
				if(zahl==0)
					t++;
				else 				
					bo[t].count=0;
				zahl=0;
			}
			else if((buffer[s]>47)&&(buffer[s]<58))
			{
				if((s<size-2)&&(buffer[s+2]>47)&&(buffer[s+2]<58))
				{
					setColor(31);
					printf("FATAL ERROR: Count too high! Do not use larger numbers than 99!\n");
					setColor(37);
					printf("Exiting...\n");
					return(1);
				}
				if((s<size-1)&&(buffer[s+1]>47)&&(buffer[s+1]<58))
				{
					zahl=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}
				else zahl=buffer[s]-48;
			}
			else if(buffer[s]>64)
			{
				bo[t].code[(int)(UpperCase(buffer[s])-65)]++;
				bo[t].length++;
				if(zahl>0)
					bo[t].count=zahl;
				else if(bo[t].count==0)
					bo[t].count=1;
				zahl=0;
			}
			s++;
		} // end of buffer checking

		//calculate the relative frequency of letters
		for(t=0;t<MAX_LENGTH;t++)
       	        	if(bo[t].length>0)
				for(s=0;s<26;s++)
				{
					bo[t].code[s]*=100;
					bo[t].code[s]=bo[t].code[s]/bo[t].length;
				}
		delete buffer;

		//Create lists with numbers of chars of the names in stats 	
		for(i=0;i<3;i++)
			for(j=0;j<MAX_GOALS;j++)
			{
				mystats[i][j].length=0;
				for(t=0;t<26;t++) mystats[i][j].code[t]=0;
				
				for(t=0;t<NAME_LENGTH;t++)
					if(stats[i][j].name[t]>64)
					{
						mystats[i][j].length++;
						mystats[i][j].code[(int)(UpperCase(stats[i][j].name[t])-65)]++;
					}
				for(t=0;t<26;t++)
				if(mystats[i][j].length>0)
				{
					mystats[i][j].code[t]*=100;
					mystats[i][j].code[t]=mystats[i][j].code[t]/mystats[i][j].length;
				}
				else  mystats[i][j].code[t]=0;
			} // End of creating relative frequencies out of stats names
			
		// Calculate the distance between the parameter and the stats names
		int Distance;
		for(k=0;k<MAX_LENGTH;k++)
			if(bo[k].count>0)
			{
				f=60000;
				for(i=0;i<3;i++)
					for(j=0;j<MAX_GOALS;j++)
					{
						Distance=0;
						for(t=0;t<26;t++)
							Distance+=bo[k].code[t]*bo[k].code[t]+mystats[i][j].code[t]*mystats[i][j].code[t]-2*bo[k].code[t]*mystats[i][j].code[t];
						if(f>Distance)
						{
							f=Distance;
							bo[k].race=i;
							bo[k].type=j;
							bo[k].tmp=f;
						}
					}
			} // end of calculating distance
		for(i=0;i<3;i++)
			countr[i]=0;
// Counter to determine the race on basis of the frequency of races in the accumulated bo-data...
		for(i=0;i<MAX_LENGTH;i++)
			if(bo[i].race<3)
				countr[bo[i].race]++;
		race=0;
		for(i=0;i<3;i++)
			if(countr[i]>countr[race]) race=i;

	
//... and recheck the whole data on basis of the new information ( so that all bo's are in the same race...

		for(i=0;i<MAX_LENGTH;i++)
			if((bo[i].race!=race)&&(bo[i].race<3))
			{
				f=60000;
				for(j=0;j<MAX_GOALS;j++)
				{
					Distance=0;
					for(t=0;t<26;t++)
					Distance+=(mystats[race][j].code[t]-bo[i].code[t])*(mystats[race][j].code[t]-bo[i].code[t]);
					if(f>Distance)
					{
						f=Distance;
						bo[i].race=race;
						bo[i].type=j;
						bo[i].tmp=f;
					}
				}
			}
		//end of race-recheck
				
/*		if((argc>3)&&(argv[argc-1][0]=='-')&&(UpperCase(argv[argc-1][1])=='T'))
			Test=2;
		else Test=1;*/

		setColor(32);
		printf(" ok\n");
		setColor(37);
	
	}
/*        if(Test>0)
        {
	        for(s=0;s<MAX_GOALS;s++)
	        {
		        goal[s].what=0;
		        goal[s].time=0;
		}
		for(s=0;s<MAX_LENGTH;s++)
			if(bo[s].count>0)
				goal[bo[s].type].what+=bo[s].count;
	}*/

	if(race==5)
        {
	        printf("Press '1' for Terran, '2' for Protoss or '3' for Zerg.\n");
	        while(race==5)
	        {
				race=TERRA;
		        a=getchar();
		        if(((a-49)>=0)&&((a-49)<3)) race=a-49;
		}
		printf("RACE: %i",race);
	}
	return(0);

}
			 
	//TODO: input additional arguments (like 'using defaults', scouttime or everything in settings.txt
	//TODO: Improve the implementation of parameter checking... looks really confusing 
	//Especially the order of the parameters...


