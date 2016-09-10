#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io.h"

Settings settings;


void Settings::Fatal(char * strn)
{ 
	setColor(31);
	printf("FATAL ERROR: ");
	setColor(37);
	printf("%s\nExiting...",strn);
}

unsigned char Settings::Init()
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
		colors=1;
		Detailed_Output=1;
		Console24Lines=1;
		Gizmo=1;
		Time_to_Enemy=50;
		Vespene_Geysirs=1;
		Mineral_Mod=100;
		Mineral_Blocks=8;
		Time_to_Wallin=0;
		Scout_Time=160;
		Max_Time=45;
		Max_Generations=150;
		Mutations=50;
		Mutation_Rate=50;
		Verbose=1;
		generateBuildOrder=1;
	}
	else
	{
		colors=data[0];
		Detailed_Output=data[1];
		Console24Lines=data[2];
		Gizmo=data[3];
		Time_to_Enemy=data[4];
		Vespene_Geysirs=data[5];
		Mineral_Mod=data[6];
		Mineral_Blocks=data[7];
		Time_to_Wallin=data[8];
		Scout_Time=data[9];
		Max_Time=data[10];
		Max_Generations=data[11];
		Mutations=data[12];
		Mutation_Rate=data[13];
		Verbose=data[14];
		generateBuildOrder=data[15];
	}

	

        if((colors!=0)&&(colors!=1))
        {
               printf("ERROR: 'Colors' not correctly initialized [%i].\n",colors);
	       printf("Please use 0 (white/black) or 1 (colors to stress changes in the BO)!\n");
	       printf("Falling back to default: Colors = 1\n");
	       colors=1;
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

	if(Time_to_Enemy>300)
	{
		printf("WARNING: 'Time to Enemy' is larger than 5 minutes! [%i]\n",Time_to_Enemy);
		printf("This is not recommended. Try to change the 'settings.txt'\n");	      	
	}

	if(Vespene_Geysirs==0)
	{
		printf("WARNING: 'Vespene Geysirs' is set to 0.\n");
		printf("This is not recommended. No gas can be gathered!\n");
		printf("Try to change the 'settings.txt'\n");
	
	}
	else if(Vespene_Geysirs>4)
	{
		 printf("ERROR: 'Vespene Geysirs' not correctly initialized [%i].\n",Vespene_Geysirs);
                printf("Please use less than 4 Vespene Geysirs!\n");
		printf("Falling back to default: Vespene Geysirs = 1\n");
		Vespene_Geysirs=1;
	}

	if(Mineral_Mod<10)
	{
		printf("WARNING: 'Mineral Gathering modificator' is set below 10.\n");
		printf("This is not recommended. Almost no minerals can be gathered!\n");
		printf("Try to change the 'settings.txt'\n");
	}

	if(Mineral_Blocks==0)
	{
		printf("ERROR: 'Mineral Blocks' is set to zero.\n");
		printf("Are you crazy or what? ;-)\n");
		printf("Falling back to default: Mineral Blocks = 8\n");
	        Mineral_Blocks=8;	
	}
	else if(Mineral_Blocks>31)
	{
		printf("WARNING: 'Mineral Blocks' is set very high! (%i)\n",Mineral_Blocks);
		printf("This is not recommended. Mineral Mining Calculation will be very inaccurate...\n");
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

	if(Scout_Time/60 >Max_Time)
	{
		printf("ERROR: 'Scout Time' is set too high. [%i]\n",Scout_Time);
		printf("Please keep it below 'Max Time'.\n");
		printf("Falling back to default: Scout Time = 160\n");
		Scout_Time=160;
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
	
	if(Mutations==0)
	{
		printf("WARNING: 'Mutations' is set to zero.\n");
		printf("This is only useful if you want to test an own build order and determine its speed\n");
		printf("Optimization is set OFF!\n");
	} else
	if(Mutations<10)
	{
		printf("WARNING: 'Mutations' is set very low.\n");
		printf("The program will probably not be able to determine the optimal solution!\n");
		printf("Try to change the 'settings.txt'.\n");
	}
	else 
	if(Mutations>200)
	{
		printf("WARNING: 'Mutations' is set very high. (%i)\n",Mutations);
		printf("The program will probably not be able to determine the optimal solution!\n");
		printf("Try to change the 'settings.txt'.\n");
	}

	if(Mutation_Rate<5)
	{
		printf("ERROR: 'Mutation Rate' is set too low. [%i]\n",Mutation_Rate);
		printf("Please use at least 5! Remember: 1/Mutation Rate = Probability of a Mutation\n");
	        printf("Falling back to default: Mutation Rate = 50");
       		Mutation_Rate=50;	       
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

unsigned char Settings::InitGoal(char I[11])
{
	const unsigned short power[4]={1,10,100,1000};
        unsigned short size,s,count_goals;
        unsigned char d;
        signed char t;
        unsigned short data[2*MAX_GOALS];
        char * buffer;
	FILE * pFileS;
	
	printf("Moving on to %s...\n",I);

	for(s=0;s<MAX_GOALS;s++)
	{
		goal[s].what=0;
		goal[s].time=0;
		buildable[s]=0;
		data[2*s]=0;
		data[2*s+1]=0;
	}

	printf("Checking input file [%s]...\n",I);
	
        pFileS = fopen (I,"rb");
	if(pFileS==NULL)
	{
		printf("[%s]:",I);Fatal("Goal file not found!");
		return(1);		
	};
	printf("File found. Reading... ");
	fseek (pFileS, 0, SEEK_END);
	size = ftell (pFileS);
	printf("[%i Bytes]\n",size);
	buffer = new char [size];
	fseek (pFileS, 0, SEEK_SET);
	fread(buffer,1,size,pFileS);
	fclose(pFileS);
	printf("File closed, data saved.\n");
	s=0;d=0;
	
	while(s<size)
	{
		if((buffer[s]>=48)&&(buffer[s]<58))
		{
			t=0;
			s++;
			while((buffer[s]>=48)&&(buffer[s]<58)&&(s<size))
			{
				t++;s++;
			}
			if(t>3)
			{
				printf("[%s]: ",I);
				Fatal("Do not use numbers bigger than 9999 in the goal file!");
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
	delete buffer;
	printf("Buffer freed and saved...\n");
	printf("Analyzing data and setting goals...\n");
// TODO: Maybe additional checks of the data sets here...

	count_goals=0;

	for(s=0;s<60;s++)
	{
		if((stats[race][s].type==3)&&(data[s*2]>1))
		{
			printf("ERROR: Research projects cannot be build more than a single time.\n");
			printf("Section %s in %s: Using 1 instead of %i...\n",stats[race][s].name,I,data[s*2]);
			data[s*2]=1;
		}
		if((data[s*2+1]>0)&&(data[s*2+1]*60+stats[race][s].BT >= Max_Time))
		{
			printf("ERROR: Build Time nearly exceeds Max Time!\n");
			printf("Try to increase Max Time [%i] in 'settings.txt' or reduce the goal time [%i] in %s!\n",Max_Time/60,data[s*2+1],I);
			printf("Disabling goal time for %s...\n",stats[race][s].name);
			data[s*2+1]=0;
		}
		goal[s].what=data[s*2];
		goal[s].time=data[s*2+1];
		count_goals+=goal[s].what;
	}
	
	printf("Reformatting Data Minutes -> Seconds\n");
	for(s=0;s<60;s++)
		goal[s].time*=60;
	setColor(32);
	printf("All goals [%i] successfully initialized!\n\n",count_goals);
	setColor(37);
	return(0);
}

void Settings::AdjustMining()
{
	int i,j,k;
	const int * miningp[45];
	switch(race)
	{
		case 0:for(i=0;i<45;i++) miningp[i]=&mining_t[i];for(i=0;i<5;i++) gasing[i]=gasing_t[i];break;
		case 1:for(i=0;i<45;i++) miningp[i]=&mining_p[i];for(i=0;i<5;i++) gasing[i]=gasing_p[i];break;
		case 2:for(i=0;i<45;i++) miningp[i]=&mining_z[i];for(i=0;i<5;i++) gasing[i]=gasing_z[i];break;
	}

	for(i=0;i<45;i++)
		if(i*8<45*Mineral_Blocks)
		{
			k=0;
			for(j=0;j<45;j++)
			{
				if(i*8<=j*Mineral_Blocks) { k=j;j=45;} 
			}
			mining[i]=*miningp[k]*Mineral_Blocks*Mineral_Mod/800;
		}
	    else mining[i]=*miningp[44]*Mineral_Blocks*Mineral_Mod/800;
}

Settings::Settings()
{
	#ifdef WIN32
	scr=CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	#endif	
}

Settings::~Settings()
{
	#ifdef WIN32
	CloseHandle(scr);
	#endif	
}
