/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for the TINY scanner       */
/* Fei Song                                         */
/* Modified by: Haochen Zhou                          */
/* Date: 2011-10-06                                 */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

using namespace std;

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <ctype.h>
#include <cstring>
#include <string>

typedef enum {
    /* book-keeping tokens */
    ENDFILE, ERROR,
	/*Open Tags*/
	OPENTAG, OPENDOCNO, OPENTEXT, OPENDOC, OPENHEADLINE, OPENOTHERTAG, OPENGRAPHIC,
	/*Close Tags*/
	CLOSETAG, CLOSEDOCNO, CLOSETEXT, CLOSEDOC, CLOSEHEADLINE, CLOSEOTHERTAG, CLOSEGRAPHIC,
    /* reserved words */
    WORD, NUMBER, APOSTROPHIZED, HYPHENATED,
	/*Punctuation Mark*/
	PERIOD, QUESTION, EXCLAMATION, OTHERMARK,
	/*Typo*/
	TYPO,
} TokenType;

struct TokenStruct {
  string value;
  int row;
};

extern string stopwords[668];
extern int rowno;     /* input file row number */

#endif
