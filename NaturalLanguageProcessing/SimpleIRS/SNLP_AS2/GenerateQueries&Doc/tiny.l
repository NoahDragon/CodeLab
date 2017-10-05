/****************************************************/
/* File: tiny.l                                     */
/* FLex specification for the TINY language         */
/* Fei Song                                         */
/* Modified by: Haochen Zhou                          */
/* Date: 2011-10-06                                 */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"

TokenStruct yylval;
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
words  		{letter}+
newline     [\r\n]
whitespace  [ \t]+

%%

"<num>"|"<DOCID>"          	  { yylval.row = rowno; return OPENDOCNO; }
"</num>"|"</DOCID>"        	  { yylval.row = rowno; return CLOSEDOCNO;}
"<narr>"|"<TEXT>"          	  { yylval.row = rowno; return OPENTEXT;}
"</narr>"|"</TEXT>"           { yylval.row = rowno; return CLOSETEXT;}
"<desc>"		     { yylval.row = rowno; return OPENDOC;}
"</desc>"      	     { yylval.row = rowno; return CLOSEDOC;}
"<title>"|"<HEADLINE>"             { yylval.row = rowno; return OPENHEADLINE;}
"</title>"|"</HEADLINE>"           { yylval.row = rowno; return CLOSEHEADLINE;}
"<P>"|"<top>"				 { yylval.row = rowno; return OPENOTHERTAG;}
"</P>"|"</top>"				 { yylval.row = rowno; return CLOSEOTHERTAG;}

"<GRAPHIC>"					{ yylval.row = rowno; return OPENGRAPHIC;}
"</GRAPHIC>"				{ yylval.row = rowno; return CLOSEGRAPHIC;}

"<"[^/^>]*">"		 { yylval.row = rowno; return OPENTAG;}
"</"[^>]*">"		 { yylval.row = rowno; return CLOSETAG;}

({words}'{letter}{0,2})|({letter}{0,2}'{words})|({letter}{0,2}'{words}'{letter}{0,1}) { yylval.row = rowno; 
																						yylval.value = yytext;
																						return APOSTROPHIZED;}
({words}'{letter}{3,})|({letter}{3,}'{words})	{ yylval.row = rowno;
												  yylval.value = yytext;
												  return TYPO;}
({words})+-({words})+ 		{ yylval.row = rowno;
												  yylval.value = yytext;
												  return HYPHENATED;}
{words}							 { yylval.row = rowno;
								   yylval.value = yytext;
								   return WORD;}
([0-9]+)|([0-9]*\.[0-9]+)        { yylval.row = rowno; 
								   yylval.value = yytext; 
								   return NUMBER;}
"\."				 			 { yylval.row = rowno; return PERIOD;}
"\?"				 			 { yylval.row = rowno; return QUESTION;}
"!"					 			 { yylval.row = rowno; return EXCLAMATION;}
[><&/\\$\)\("\[\]=\+%\*\';\:,\-] { yylval.row = rowno;
								   yylval.value = yytext;
								   return OTHERMARK;}
								   
{newline}       { rowno++; }
{whitespace}    {/*skip white space*/}

					   
.               { yylval.row = rowno; 
                  yylval.value = yytext; 
                  return ERROR; }

%%

TokenType getToken(void) { 
  return (TokenType)yylex(); 
}

