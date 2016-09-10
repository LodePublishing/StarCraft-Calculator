#include <stdio.h>
//#include "main.h"
#include "io.h"

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
