/****************************************************/
/* File: scanner.cpp                                */
/* scanner for the TINY language                    */
/* Fei Song                                         */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

// allocate global variables
int rowno = 1;
string stopwords[668];
extern FILE * yyin;
extern FILE * yyout;
extern TokenStruct yylval;

void LoadStopwords(string filename)
{
	ifstream file(filename.c_str());
	char line[128];
	int i = 0;
	while(!file.eof())
	{
		file.getline(line,128);
		//string temp(line);
		stopwords[i]=line;
		i++;
	}
	file.close();
}

main( int argc, char * argv[] ) { 
  yyin = stdin;
  yyout = stdout;
  TokenType ttype;
  LoadStopwords("stopwords.txt");
  while( (ttype = getToken()) != ENDFILE )
    printToken( yyout, ttype, yylval );
  return 0;
}

