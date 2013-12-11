/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY scanner           */
/* Fei Song                                         */
/* Modified by: Haochen Zhou                          */
/* Date: 2011-10-06                                 */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

#include "globals.h"
#include <stack>

// prints a token and its value to the output file 
void printToken( FILE *, TokenType, TokenStruct & );
string lowerstr(string);
bool checkStopwords(string);


#endif
