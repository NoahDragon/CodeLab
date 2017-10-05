#include "Util.h"

int str2int(string s)
{
	int i;
	char buf[10];
	
	strcpy(buf, s.c_str());
	sscanf(buf, "%d", &i);
	
	return i;
}

long str2long(string s)
{
	long l;
	char buf[10];
	
	strcpy(buf, s.c_str());
	sscanf(buf, "%d", &l);
	
	return l;
}