#include <stdio.h>
#include "C:\sc\sccdll2\main.h"
#include "io.h"
#include "C:\sc\sccdll2\text.h"

void setColor(unsigned char c)
{
//	if(gColors==0) return;
	#ifdef WIN32
	SetConsoleTextAttribute(scr,colorsWin32[c-31]);
	#elif __linux__
	printf("\033[0;%d;40m",c);
	#endif
};

void setAt(unsigned char cnt)
{
	if(cnt<4) setColor(37);//White
	else if(cnt<8) setColor(36);//Cyan
	else if(cnt<16) setColor(32);//Green
	else if(cnt<32) setColor(33);//Orange
	else if(cnt<64) setColor(31);//Red
	else setColor(34);//Blue
};

#ifdef WIN32
HANDLE scr;
void print(const char * x) {DWORD num; WriteConsole(scr,x,strlen(x),&num,0); }
#endif


IO::IO(const GA* ga)
{
    pFitnessGraphicsCounter=0;
    pFitnessDifference=0;
    sFitnessGraphicsCounter=0;
    sFitnessDifference=0;
	tFitnessGraphicsCounter=0;
	tFitnessDifference=0;
    oldsFitness=0;
    oldpFitness=0;
	oldtFitness=0;
	calc=0;
	this->ga=ga;
#ifdef WIN32
	scr=CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	SetConsoleActiveScreenBuffer(scr);
#endif	 //-> io
	clrscr();
}

IO::~IO()
{
	#ifdef WIN32
		CloseHandle(scr);
	#endif
}


void IO::screen(ANARACE* anaplayer)
{
	int s,t;

	gotoxy(0,0);setColor(37);
	print("Calculating Status:");

	if(pFitnessGraphicsCounter<160) pFitnessGraphicsCounter++;
	if(sFitnessGraphicsCounter<160) sFitnessGraphicsCounter++;
	if(tFitnessGraphicsCounter<160) tFitnessGraphicsCounter++;

	if(anaplayer->getMaxtFitness()>oldtFitness)
	{
		tFitnessGraphicsCounter=0;
		tFitnessDifference=anaplayer->getMaxtFitness()-oldtFitness;
		oldtFitness=anaplayer->getMaxtFitness();
	}
	
	if(anaplayer->getMaxsFitness()>oldsFitness)
	{
		sFitnessGraphicsCounter=0;
		sFitnessDifference=anaplayer->getMaxsFitness()-oldsFitness;
		oldsFitness=anaplayer->getMaxsFitness();
	}
	
	if(anaplayer->getTimer()<ga->maxTime)
	{
		if(oldpFitness<anaplayer->getMaxpFitness())
		{
			pFitnessGraphicsCounter=0;
			pFitnessDifference=anaplayer->getMaxpFitness()-oldpFitness;
			oldpFitness=anaplayer->getMaxpFitness();
		}
	}
	else
	{
		   if((oldpFitness/100)<(anaplayer->getMaxpFitness()/100))
	       {
                   pFitnessGraphicsCounter=0;
                   pFitnessDifference=anaplayer->getMaxpFitness()-oldpFitness;
                   oldpFitness=anaplayer->getMaxpFitness();
           }
	}

	if((pFitnessGraphicsCounter<sFitnessGraphicsCounter)&&(pFitnessGraphicsCounter<tFitnessGraphicsCounter))
		setAt(pFitnessGraphicsCounter);
	else if(sFitnessGraphicsCounter<tFitnessGraphicsCounter)
		setAt(sFitnessGraphicsCounter);
	else setAt(tFitnessGraphicsCounter);

	if(anaplayer->getTimer()<ga->maxTime)
	{
		if(pFitnessGraphicsCounter<=16)
		{
			sprintf(tmp," got faster solution! [-%2i]   ",pFitnessDifference);
			print(tmp);
		}
		else
		if(sFitnessGraphicsCounter<=16)
		{
			sprintf(tmp," improved resources! [+%4i]   ",sFitnessDifference/100);
			print(tmp);
		}
		else
			      print(" optimizing resources . . .    ");
	}
	else
	{
		if(pFitnessGraphicsCounter<=16)
		{
			sprintf(tmp," another goal complete! [+%3i]",pFitnessDifference);
			print(tmp);
		}
		else
		if(sFitnessGraphicsCounter<=16)
		{
			sprintf(tmp," improved resources! [+%4i]  ",sFitnessDifference/100);
			print(tmp);
		}
		else
    			      print(" searching . . .              ");
	}


		setColor(37);
		gotoxy(1,2);sprintf(tmp,"%i runs and %i+ generations remaining. [Total %i generations]      ",ga->maxRuns-anaplayer->getRun(),ga->maxGenerations-anaplayer->getUnchangedGenerations(),anaplayer->getGeneration());
		print(tmp);

		gotoxy(0,4);
		print("[res]  [time]  [nice]");
		gotoxy(0,5);
		print("-------------------------");
		setAt(sFitnessGraphicsCounter);
		gotoxy(0,6);sprintf(tmp,"%5.4i",anaplayer->getMaxsFitness()/100);print(tmp);
		setAt(pFitnessGraphicsCounter);
		gotoxy(8,6);
		if(anaplayer->getTimer()<ga->maxTime) 
		{ 
			sprintf(tmp,"%.2i:%.2i",(ga->maxTime-anaplayer->getTimer())/60,(ga->maxTime-anaplayer->getTimer())%60);
			print(tmp);
		} 
		else 
		{ 
			sprintf(tmp," %4i",anaplayer->getMaxpFitness());
			print(tmp);
		};
		setAt(tFitnessGraphicsCounter);
		gotoxy(16,6);sprintf(tmp,"%3i",anaplayer->getMaxtFitness());print(tmp);

	setColor(COLOR_1);
if((calc%80==0)||(calc%80==1)) setColor(COLOR_3); else if((calc%80==78)||(calc%80==79)||(calc%80==2)||(calc%80==3)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,3);print("     ***    ***   ***   *      **     ***");
if((calc%80==2)||(calc%80==3)) setColor(COLOR_3); else if((calc%80==0)||(calc%80==1)||(calc%80==4)||(calc%80==5)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,4);print("   *      *     *      *     *  *       *");
if((calc%80==4)||(calc%80==5)) setColor(COLOR_3); else if((calc%80==2)||(calc%80==3)||(calc%80==6)||(calc%80==7)) setColor(COLOR_2); else setColor(COLOR_1);
	gotoxy(20,5);print("    *    *     *      *     *  *      *  ");
if((calc%80==6)||(calc%80==7)) setColor(COLOR_3); else if((calc%80==4)||(calc%80==5)||(calc%80==8)||(calc%80==9)) setColor(COLOR_2); else setColor(COLOR_1);
	gotoxy(20,6);print("    *   *     *      *     *  *       * ");
if((calc%80==8)||(calc%80==9)) setColor(COLOR_3); else if((calc%80==6)||(calc%80==7)||(calc%80==10)||(calc%80==11)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,7);print("***     ***   ***   *  *   **     ***  ");
	
	for(s=1;s<MAX_LOCATIONS;s++)
		for(t=UNIT_TYPE_COUNT;t--;)
			tgGoal[s][t]=anaplayer->getPlayer()->goal->globalGoal[s][t];
					//reset the goals (to sign @ the unit list)

	for(s=1;s<MAX_LOCATIONS;s++)
		for(t=0;t<UNIT_TYPE_COUNT;t++)
			tgGoal[s][t]-=anaplayer->getMap()->location[s].force[anaplayer->getPlayerNum()][t];
/*			~~~~
			goals halt abziehen :/*/


		//bolog logs how long which build order stands there (you know, the gColors ;-)
		//TODO: recognize moved blocks to stress real Mutations

		setColor(37);
//The Build order List

			t=0;
			for(s=MAX_LENGTH;s--;)
			{
				gotoxy((t/HEIGHT)*WIDTH,9+t%HEIGHT);
				t++;
				setColor(37);
				if(anaplayer->getProgramIsBuilt(s))
				{
					if(bolog[s].order==anaplayer->phaenoCode[s])
					{
						if(bolog[s].count<160)
							bolog[s].count++;
					} else
					{
						bolog[s].count=0;
						bolog[s].order=anaplayer->phaenoCode[s];
					}

					if(tgGoal[anaplayer->getProgramLocation(s)][anaplayer->phaenoCode[s]]>0) //~~~~~~ location=0?
					{
						setColor(34);
						tgGoal[anaplayer->getProgramLocation(s)][anaplayer->phaenoCode[s]]--;
						print("@");
					} else print(" ");
					setColor(35);
					sprintf(tmp,"%c",error_sm[anaplayer->getProgramSuccessType(s)]);
					print(tmp);
					setAt(bolog[s].count);
					sprintf(tmp,"%s",kurz[anaplayer->getPlayer()->getRace()][anaplayer->phaenoCode[s]].b);
					print(tmp);
					setColor(37);
//					sprintf(tmp,"%i",anaplayer->getProgramTemp(s));
//					sprintf(tmp,"%i",anaplayer->getProgramTime(s));
					sprintf(tmp,"%i",anaplayer->getProgramHaveMinerals(s)/100);
//					if(anaplayer->getProgramNeedSupply(s)<100)
//						sprintf(tmp," %.2i",anaplayer->getProgramNeedSupply(s));
//					else sprintf(tmp,"%3i",anaplayer->getProgramNeedSupply(s));
					print(tmp);
				}
				//else print(" ------    ");
			}
		//TODO: In io rein!

		setColor(37);

		t=4;
		gotoxy(66,3);print("Force:");
		for(s=0;s<EXTRACTOR+2;s++)
			if(anaplayer->getPlayer()->goal->allGoal[s]>0)
			{
				if(globalForcelog[s].order==anaplayer->location[0].force[s])
				{
				      if(globalForcelog[s].count<160)
								globalForcelog[s].count++;
				}
				else
				{
					globalForcelog[s].count=0;
					globalForcelog[s].order=anaplayer->location[0].force[s];
				}

				setAt(globalForcelog[s].count);
			       gotoxy(70,t);
				sprintf(tmp,"%s:%2i ",kurz[anaplayer->getPlayer()->getRace()][s].b,anaplayer->location[0].force[s]);
				print(tmp);
				t++;
				if(t>23) s=EXTRACTOR+2; //konsole...
				//Well... it can't print out more than ~20 goals :/
			}
		if(t<=23) //konsole...
		{
			gotoxy(66,t);
			setColor(37);
			print("non-goals:");
			t++;
			for(s=0;s<EXTRACTOR+2;s++)
				if((anaplayer->getPlayer()->goal->allGoal[s]==0)&&(anaplayer->location[0].force[s]))
				{
					if(globalForcelog[s].order==anaplayer->location[0].force[s])
					{
						if(globalForcelog[s].count<160)
							globalForcelog[s].count++;
					}
					else
					{
						globalForcelog[s].count=0;
						globalForcelog[s].order=anaplayer->location[0].force[s];
					}
					setAt(globalForcelog[s].count);
					gotoxy(70,t);
					sprintf(tmp,"%s:%2i ",kurz[anaplayer->getPlayer()->getRace()][s].b,anaplayer->location[0].force[s]);
					print(tmp);
					t++;
					if(t>23) s=EXTRACTOR+2; //konsole...
				}
		}
		calc++; //Graphics counter
};

