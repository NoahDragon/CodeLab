/*------------------------------------------------------------------------------
Wrote in C programming language
Compiled by GNU C Compiler

Trying to fingure out how much time will cost by sqrt(). And is this the major 
factor that affect 'Prime Number.c'?

Date: 2011.02.01
------------------------------------------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

int main()
{
	clock_t start, finish;
	
	start = clock();
	double s;
	
	for(int i =0; i<990000; i++)
	{
		s=sqrt(15318907);
	}

	printf("The sqrt(15318907) is %f.\n", s);	
	finish = clock();


	printf("The total time costs %2f s.\n", (double)(start-finish)/CLOCKS_PER_SEC);
	return 0;
}

/*--------------------------------------------------------------------------------
Result shows zero time consuming, so sqrt() didn't affect the speed of program 
'Prime Number.c'
--------------------------------------------------------------------------------*/
