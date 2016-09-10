#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include "io.h"

Settings settings;


void Settings::Fatal(char * strn)
{ 
	setColor(31);
	printf("FATAL ERROR: ");
	setColor(37);
	printf("%s\nExiting...",strn);
}

int Settings::Init()
{
	const unsigned short power[4]={1,10,100,1000};
	unsigned short size,s;
	unsigned char d;
	signed char t;
	unsigned short data[DATA_SET_SIZE];
	char * buffer;
	d=0;
 	
	for(s=0;s<DATA_SET_SIZE;s++)
		data[s]=0;
 //map laden!
	
	printf("Checking input file [settings.txt]...\n");
	FILE * pFileS;
        pFileS = fopen ("settings.txt","rb");
	
	if(pFileS==NULL)
	{
		Fatal("Settings file settings.txt not found!");
		//return(1);
	}
	else
	{
	printf("File found. Reading...\n");

	fseek (pFileS, 0, SEEK_END);
	size = ftell (pFileS);
	buffer = new char [size];
	fseek (pFileS, 0, SEEK_SET);
	fread(buffer,1,size,pFileS);
	fclose(pFileS);
	printf("File closed, data saved [%i Bytes].\n",size);
	s=0;d=0;
	
	while(s<size)
	{
		if((buffer[s]>=48)&&(buffer[s]<58)&&(d<DATA_SET_SIZE))
		{
			t=0;
			s++;
			while((buffer[s]>=48)&&(buffer[s]<58)&&(s<size))
			{
				t++;s++;
			}
			if(t>3)
			{
				Fatal("Do not use numbers bigger than 9999 in the settings.txt file!");
				delete buffer;
				return(1);
			}
			while(t>=0)
			{
				data[d]+=(buffer[s-t-1]-48)*power[t];
				t--;
			}
			d++;
		}
		s++;
	}

	//TODO: Check for additional numbers and print out an error !

	delete buffer;
	printf("Buffer freed and saved, checking data:\n");
	

	}

	if(d<DATA_SET_SIZE)
	{
		setColor(31);
		printf("Not enough Data sets found (%i out of expected %i).\n",d,DATA_SET_SIZE);
		setColor(37);
		printf("Please report this to ClawSoftware and/or get an original copy of the 'settings.txt'\n");
		printf("Using defaults...\n");
		gColors=1;
		Detailed_Output=1;
		Console24Lines=1;
		Gizmo=1;
		Mineral_Mod=100;
		Max_Time=45;
		Max_Generations=150;
		Verbose=1;
		generateBuildOrder=1;
	}
	else
	{
		gColors=data[0];
		Detailed_Output=data[1];
		Console24Lines=data[2];
		Gizmo=data[3];
		Mineral_Mod=data[4];
		Max_Time=data[5];
		Max_Generations=data[6];
		Verbose=data[7];
		generateBuildOrder=data[8];
	}

	

        if((gColors!=0)&&(gColors!=1))
        {
               printf("ERROR: 'Colors' not correctly initialized [%i].\n",gColors);
	       printf("Please use 0 (white/black) or 1 (gColors to stress changes in the BO)!\n");
	       printf("Falling back to default: Colors = 1\n");
	       gColors=1;
	}
	
	if((Detailed_Output!=0)&&(Detailed_Output!=1))
	 {
	       printf("ERROR: 'Detailed_Output' not correctly initialized [%i].\n",Detailed_Output);
	       printf("Please use 0 (more readable) or 1 (timestamp in front of each order)!\n");
	       printf("Falling back to default: Detailed_Output = 0\n");
	       Detailed_Output=0;
	 }

	if((Console24Lines!=0)&&(Console24Lines!=1))
	{
		printf("ERROR: 'Line correction' is not correctly initialized [%i].\n",Console24Lines);
		printf("Please use 0 (for 25 line consoles like the linux text console) or 1 (standard)!\n");
		printf("Falling back to default: Line_Correction = 1\n");
		Console24Lines=1;
	}

	if((Gizmo!=0)&&(Gizmo!=1))
	{
		printf("ERROR: 'Gizmo' is not correctly initialized [%i].\n",Gizmo);
		printf("Please use 0 (no scrolling text) or 1 (scrolling gizmo text :)!\n");
		printf("Falling back to default: Gizmo = 1\n");
		Gizmo=1;
	}

	if(Mineral_Mod<10)
	{
		printf("WARNING: 'Mineral Gathering modificator' is set below 10.\n");
		printf("This is not recommended. Almost no minerals can be gathered!\n");
		printf("Try to change the 'settings.txt'\n");
	}

	if(Max_Time<5)
	{
		printf("ERROR: 'Max Time' is set too low. [%i]\n",Max_Time);
		printf("Please use at least 10 minutes.\n");
		printf("Falling back to default: Max Time = 45\n");
		Max_Time=45;
	}
	else
	if(Max_Time<10)
	{
		printf("WARNING: 'Max Time' is set very low. [%i]\n",Max_Time);
		printf("The program will probably not work very well.\n");
		printf("Try to change the 'settings.txt'\n");
	} else if(Max_Time>120)
	{
		printf("WARNING: 'Max Time' is set very high. [%i]\n",Max_Time);
		printf("Crazy or what? ;) Well... prepare for a looong run :p\n");
		printf("Try to change the 'settings.txt'\n");		
	}

	if(Max_Generations<10)
	{
		printf("ERROR: 'Max Generations' is set too low. [%i]\n",Max_Generations);
		printf("The program is useless with this setting.\n");
		printf("Falling back to default: Max Generations = 150");
		Max_Generations=150;
	}
	else if(Max_Generations<50)
	{
		printf("WARNING: 'Max Generations' is set very low. [%i]\n",Max_Generations);
		printf("It is not very likely that the program will find an optimal solution.\n");
	       printf("Try to change the 'settings.txt'.\n");
	}	       
	
	if((Verbose!=0)&&(Verbose!=1))
	{
		printf("ERROR: 'Verbose' not correctly initialized [%i].\n",Verbose);
                printf("Please use 0 (no verbose output) or 1 (verbose output)!\n");
		printf("Falling back to default: Verbose = 1\n");
	        Verbose=1;
		printf("Verbose: %i\n",Verbose);
	}

	printf("Reformatting Data Minutes -> Seconds\n");
	Max_Time*=60;
	
	setColor(32);
	printf("'settings.txt' successfully checked!\n");
	setColor(37);
	return(0);
};

Settings::Settings()
{
	#ifdef WIN32
	scr=CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	#endif	 //-> io
}

Settings::~Settings()
{
	#ifdef WIN32
	CloseHandle(scr);
	#endif	
}
