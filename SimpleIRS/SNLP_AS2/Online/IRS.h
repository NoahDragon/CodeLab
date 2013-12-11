#ifndef _IRS_H_
#define _IRS_H_

#include "global.h"

string getTitle(int);
docDetailStruct getDetail(int);

bool checkid(string);
bool title(string);
bool metasymbol(string);
bool narr(string);
int mygetch();
void showDetail(int, int);

#endif
