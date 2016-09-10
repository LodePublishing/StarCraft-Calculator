#include <stdio.h>
#include "main.h"
#include "io.h"
#include "anarace.h"
#include "text.h"

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


IO::IO()
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
	clrscr();
}

void IO::screen(ANARACE* anaplayer)
{
	gotoxy(0,0);setColor(37);
	print("Calculating Status:");

	if(pFitnessGraphicsCounter<160) pFitnessGraphicsCounter++;
	if(sFitnessGraphicsCounter<160) sFitnessGraphicsCounter++;
	if(tFitnessGraphicsCounter<160) tFitnessGraphicsCounter++;


	if(anaplayer->maxtFitness>oldtFitness)
	{
		tFitnessGraphicsCounter=0;
		tFitnessDifference=anaplayer->maxtFitness-oldtFitness;
		oldtFitness=anaplayer->maxtFitness;
	}
	
	if(anaplayer->maxsFitness>oldsFitness)
	{
		sFitnessGraphicsCounter=0;
		sFitnessDifference=anaplayer->maxsFitness-oldsFitness;
		oldsFitness=anaplayer->maxsFitness;
	}

	if(anaplayer->timer<anaplayer->pSet->ga.maxTime)
	{
		if(oldpFitness<anaplayer->maxpFitness)
		{
			pFitnessGraphicsCounter=0;
			pFitnessDifference=anaplayer->maxpFitness-oldpFitness;
			oldpFitness=anaplayer->maxpFitness;
		}
	}
	else
	{
	        if((oldpFitness/100)<(anaplayer->maxpFitness/100))
                {
                        pFitnessGraphicsCounter=0;
                        pFitnessDifference=anaplayer->maxpFitness-oldpFitness;
                        oldpFitness=anaplayer->maxpFitness;
                }
	}

	if((pFitnessGraphicsCounter<sFitnessGraphicsCounter)&&(pFitnessGraphicsCounter<tFitnessGraphicsCounter))
		setAt(pFitnessGraphicsCounter);
	else if(sFitnessGraphicsCounter<tFitnessGraphicsCounter)
		setAt(sFitnessGraphicsCounter);
	else setAt(tFitnessGraphicsCounter);

	if(anaplayer->timer<anaplayer->pSet->ga.maxTime)
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
		gotoxy(1,2);sprintf(tmp,"%i runs and %i+ generations remaining. [Total %i generations]      ",anaplayer->pSet->ga.maxRuns-anaplayer->run,anaplayer->pSet->ga.maxGenerations-anaplayer->unchangedGenerations,anaplayer->generation);
		print(tmp);

		gotoxy(0,4);
		print("[res]  [time]  [nice]");
		gotoxy(0,5);
		print("-------------------------");
		setAt(sFitnessGraphicsCounter);
		gotoxy(0,6);sprintf(tmp,"%5.4i",anaplayer->maxsFitness/100);print(tmp);
		setAt(pFitnessGraphicsCounter);
		gotoxy(8,6);if(anaplayer->timer<anaplayer->pSet->ga.maxTime) { sprintf(tmp,"%.2i:%.2i",(anaplayer->pSet->ga.maxTime-anaplayer->timer)/60,(anaplayer->pSet->ga.maxTime-anaplayer->timer)%60);print(tmp);} else { sprintf(tmp," %4i",anaplayer->maxpFitness);print(tmp);};
		setAt(tFitnessGraphicsCounter);
		gotoxy(16,6);sprintf(tmp,"%3i",anaplayer->maxtFitness);print(tmp);

/*	setColor(COLOR_1);
if((calc%80==0)||(calc%80==1)) setColor(COLOR_3); else if((calc%80==78)||(calc%80==79)||(calc%80==2)||(calc%80==3)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,3);print("     ***    ***   ***   *      **     ***");
if((calc%80==2)||(calc%80==3)) setColor(COLOR_3); else if((calc%80==0)||(calc%80==1)||(calc%80==4)||(calc%80==5)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,4);print("   *      *     *      *     *  *       *");
if((calc%80==4)||(calc%80==5)) setColor(COLOR_3); else if((calc%80==2)||(calc%80==3)||(calc%80==6)||(calc%80==7)) setColor(COLOR_2); else setColor(COLOR_1);
	gotoxy(20,5);print("    *    *     *      *     *  *      *  ");
if((calc%80==6)||(calc%80==7)) setColor(COLOR_3); else if((calc%80==4)||(calc%80==5)||(calc%80==8)||(calc%80==9)) setColor(COLOR_2); else setColor(COLOR_1);
	gotoxy(20,6);print("    *   *     *      *     *  *       * ");
if((calc%80==8)||(calc%80==9)) setColor(COLOR_3); else if((calc%80==6)||(calc%80==7)||(calc%80==10)||(calc%80==11)) setColor(COLOR_2);else setColor(COLOR_1);
	gotoxy(20,7);print("***     ***   ***   *  *   **     ***  ");*/

	for(int s=1;s<MAX_LOCATIONS;s++)
		for(int t=UNIT_TYPE_COUNT;t--;)
			tgGoal[s][t]=anaplayer->pSet->goalList.globalGoal[s][t];
					//reset the goals (to sign @ the unit list)


		//bolog logs how long which build order stands there (you know, the gColors ;-)
		//TODO: recognize moved blocks to stress real Mutations

		setColor(37);
	int t=0;
//The Build order List
			for(int s=0;s<5;s++)
			{
				t=0;
				while((t<HEIGHT)&&(anaplayer->program[(s+1)*HEIGHT-t].built==0)) t++;
				gotoxy(WIDTH*s+2,25);
				if((t<HEIGHT)||(anaplayer->program[s*HEIGHT].built>0))
				{
					sprintf(tmp,"[%.2i:%.2i]",(anaplayer->pSet->ga.maxTime-anaplayer->program[(s+1)*HEIGHT-t].time)/60,(anaplayer->pSet->ga.maxTime-anaplayer->program[(s+1)*HEIGHT-t].time)%60);
					print(tmp);
				}
				else print("       ");
			}
			t=0;
			for(int s=MAX_LENGTH;s--;)
			{
				gotoxy((t/HEIGHT)*WIDTH,9+t%HEIGHT);
				t++;
				setColor(37);
				if(anaplayer->program[s].built==1)
				{
					if(bolog[s].order==anaplayer->Code[anaplayer->program[s].dominant][s])
					{
						if(bolog[s].count<160)
							bolog[s].count++;
					} else
					{
						bolog[s].count=0;
						bolog[s].order=anaplayer->Code[anaplayer->program[s].dominant][s];
					}

					if(tgGoal[anaplayer->program[s].location][anaplayer->genoToPhaenotype[anaplayer->Code[anaplayer->program[s].dominant][s]]]>0) //~~~~~~ location=0?
					{
						setColor(34);
						tgGoal[anaplayer->program[s].location][anaplayer->genoToPhaenotype[anaplayer->Code[anaplayer->program[s].dominant][s]]]--;
						print("@");
					} else print(" ");
					setColor(35);
					sprintf(tmp,"%c",error_sm[anaplayer->program[s].success[anaplayer->program[s].dominant].type]);
					print(tmp);
					setAt(bolog[s].count);
					sprintf(tmp,"%s",kurz[anaplayer->pSet->race][anaplayer->genoToPhaenotype[anaplayer->Code[anaplayer->program[s].dominant][s]]].b);
					print(tmp);
					setColor(37);
					if(anaplayer->program[s].needSupply<100)
						sprintf(tmp," %.2i",anaplayer->program[s].needSupply);
					else sprintf(tmp,"%3i",anaplayer->program[s].needSupply);
					print(tmp);
				}
				else print(" ------    ");
			}
		//TODO: In io rein!

		setColor(37);

		t=4;
		gotoxy(66,3);print("Force:");
		for(int s=0;s<EXTRACTOR+2;s++)
			if(anaplayer->pSet->goalList.allGoal[s]>0)
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
				sprintf(tmp,"%s:%2i ",kurz[anaplayer->pSet->race][s].b,anaplayer->location[0].force[s]);
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
			for(int s=0;s<EXTRACTOR+2;s++)
				if((anaplayer->pSet->goalList.allGoal[s]==0)&&(anaplayer->location[0].force[s]))
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
					sprintf(tmp,"%s:%2i ",kurz[anaplayer->pSet->race][s].b,anaplayer->location[0].force[s]);
					print(tmp);
					t++;
					if(t>23) s=EXTRACTOR+2; //konsole...
				}
		}
		calc++; //Graphics counter
}

