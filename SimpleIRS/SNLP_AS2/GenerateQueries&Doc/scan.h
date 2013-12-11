/****************************************************/
/* File: scan.h                                     */
/* The interface function for the TINY scanner      */
/* Fei Song                                         */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

#include <fstream.h>
#include <stdlib.h>
// returns the next token from the input file
TokenType getToken(void);

void LoadStopwords(string);
#endif
