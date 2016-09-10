// Einmalige Updates auch nur einmal rein! Nur ueber austauschen rein !
// Todo: Debug messages in eigene Funktion!

#include <stdlib.h>
#include <stdio.h>

#define DATA_SET_SIZE 12
using namespace std;

class Settings
{
	public:
	//Output Switches 0/1
	unsigned char numbers,colors,Detailed_Output;
	//Map Data
	unsigned short Time_To_Enemy,Mineral_Mod,Time_To_Wallin;
	unsigned char Mineral_Blocks,Vespine_Geysirs;
	//Internal Options
	unsigned short Max_Time,Max_Generations,Mutations,Mut_Rate;

	unsigned short s;
	
	unsigned char d;
	signed char t;
	
	char * buffer;

	unsigned short data[DATA_SET_SIZE];

	void Init_Settings()
	{
		printf("Checking input file [settings.txt]...\n");
	FILE * pFileS;
        pFileS = fopen ("settings.txt","rb");
	// Auf Error checken! Evtl nciht da!
	printf("File opened... reading...\n");
	
	fseek (pFileS, 0, SEEK_END);
	size = ftell (pFileS);
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
			while(t>=0)
			{
				data[d]+=(buffer[s-t]-48)*10^t;
				t--;
			}
			d++;
		}
	}
	free(buffer);
	printf("Buffer freed and saved...\n");
	printf("Checking data:\n");
	
	if(d<DATA_SET_SIZE)
	{
		printf("Not enough Data sets found (%i out of expected %i).\n",d,DATA_SET_SIZE);
		printf("Please report this to ClawSoftware and/or get an original copy of the 'settings.txt'\n");
		printf("Using defaults...\n");
		numbers=1;
		colors=1;
		Detailed_Output=1;
		Time_To_Enemy=50;
		Vespine_Geysirs=1;
		Mineral_Mod=100;
		Mineral_Blocks=8;
		Time_To_Wallin=0;
		Max_Time=45;
		Max_Generations=150;
		Mutations=50;
		Mutation_Rate=50;
	}
	else
	{
		numbers=data[0];
		colors=data[1];
		Detailed_Output=data[2];
		Time_To_Enemy=data[3];
		Vespine_Geysirs=data[4];
		Mineral_Mod=data[5];
		Mineral_Blocks=data[6];
		Time_To_Wallin=data[7];
		Max_Time=data[8];
		Max_Generations=data[9];
		Mutations=data[10];
		Mutation_Rate=data[11];
	}

	if((numbers!=0)&&(numbers!=1))
	{
		printf("ERROR: 'Numbers' not correctly initialized [%i].\n",numbers);
		printf("Please use 0 (no numbers) or 1 (numbers in front of the orders)!\n");
		printf("Falling back to default: Numbers = 1\n");
		numbers=1;
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
	if(Time_To_Enemy>300)
	{
		printf("WARNING: 'Time to Enemy' is larger than 5 minutes! [%i]\n",Time_To_Enemy);
		printf("This is not recommended. Try to change the 'settings.txt'\n");	      	
	}
	if(Vespine_Geysirs==0)
	{
		printf("WARNING: 'Vespine Geysirs' is set to 0.\n");
		printf("This is not recommended. No gas can be gathered!\n");
		printf("Try to change the 'settings.txt'\n");
	}
	if(Mineral_Mod<10)
	{
		printf("WARNING: 'Mineral Gathering modificator' is set below 10.\n");
		printf("This is not recommended. Almost no minerals can be gathered!\n");
		printf("Try to change the settings.txt'\n");
	}
	if(Mineral_Blocks==0)
	{
		printf("ERROR: 'Mineral Blocks' is set to zero.\n");
		printf("Are you crazy or what? ;-)\n");
		printf("Falling back to default: Mineral Blocks = 8\n");
	       Mineral_Blocks=8;	
	}
	if(Max_Time<5)
	{
		printf("ERROR: 'Max Time' is set too low. [%i]\n",Max_Time);
		printf("Please use at least 10 minutes.\n");
		printf("Falling back to default: Max Time = 45\n");
	}
	else
	if(Max_Time<10)
	{
		printf("WARNING: 'Max Time is set very low. [%i]\n",Max_Time);
		printf("The program will probably not work very well.\n");
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

	if(Mutation_Rate<5)
	{
		printf("ERROR: 'Mutation Rate' is set too low. [%i]\n",Mutation_Rate);
		printf("Please use at least 5! Remember: 1/Mutation Rate = Probability of a Mutation\n");
	       printf("Falling back to default: Mutation Rate = 50");
       		Mutation_Rate=50;	       
	}
	};
};


