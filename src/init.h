#ifndef __INIT_H
#define __INIT_H

struct myBO
{
	int type,race,length,count,code[26],tmp;
};

extern myBO bo[];
void Init();
int TranslateData(int argc, char* argv[]);
#endif
		
