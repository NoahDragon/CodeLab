/****************************************************/
/* File: util.cpp                                   */
/* Utility functions for the TINY scanner           */
/* Fei Song                                         */
/* Modified by: Haochen Zhou                          */
/* Date: 2011-10-06                                 */
/****************************************************/

#include "util.h"

stack<TokenType> checktoken;
bool switchflag = false; //Omit content in irrelvent tags
bool numkeep = false; //only number in id should be kept
bool usefulinfo = false; // check if the word is under useful tag.
// prints a token and its value to the output file

string lowerstr(string str)
{
	string s = str;
	  for(int i=0; i<s.size();i++)
		s[i] = tolower(s[i]);
	return s;
}

bool checkStopwords(string a)//a must contain a string with lowercase.
{
	for(int i=0; i < 668; i++)
	{
		if(a.compare(stopwords[i])==0)
			return true;
	}
	return false;
}

void printToken( FILE * listing, TokenType token, TokenStruct & tokenStruct ) { 
  switch (token) { 
	// Tags
	case OPENTAG: 
			switchflag = true;
			checktoken.push(token);
		break;
	case CLOSETAG: 
			switchflag = false;
			if(!checktoken.empty()&&checktoken.top()==OPENTAG)
				checktoken.pop();
			else
				fprintf(listing, "TAGERROR: TAG, Row: %d\n", tokenStruct.row);
		break;
    case OPENDOCNO:
			usefulinfo = true;
			if(!switchflag)
			{
				fprintf( listing, "$ID\n" ); 
				numkeep = true;
			}
			checktoken.push(token);
		break;
    case CLOSEDOCNO: 
			usefulinfo = false;
			numkeep = false;
			if(!checktoken.empty()&&checktoken.top()==OPENDOCNO)
				checktoken.pop();
			else
				fprintf(listing, "TAGERROR: DOCNO, Row: %d\n", tokenStruct.row);
		break;
    case OPENTEXT: 
			usefulinfo = true;
			if(!switchflag)
				fprintf( listing, "$NARR\n" );
			checktoken.push(token);
		break;
    case CLOSETEXT:
			usefulinfo = false;
			if(!checktoken.empty()&&checktoken.top()==OPENTEXT)
				checktoken.pop();
			else
				fprintf(listing, "TAGERROR: TEXT, Row: %d\n", tokenStruct.row);
		break;
    case OPENDOC: 
			usefulinfo = true;
			if(!switchflag)
				fprintf( listing, "$DESC\n" );
			checktoken.push(token);			
		break;
    case CLOSEDOC: 
			usefulinfo = false;
			if(!checktoken.empty()&&checktoken.top()==OPENDOC)
				checktoken.pop();
			else
				fprintf(listing, "TAGERROR: DOC, Row: %d\n", tokenStruct.row);
		break;
	case OPENGRAPHIC:
			usefulinfo = true;
			if(!switchflag)
				fprintf( listing, "$DESC\n" );
			checktoken.push(token);	
		break;
	case CLOSEGRAPHIC:
			usefulinfo = false;
			if(!checktoken.empty()&&checktoken.top()==OPENGRAPHIC)
				checktoken.pop();
			else
				fprintf(listing, "TAGERROR: DOC, Row: %d\n", tokenStruct.row);
		break;
    case OPENHEADLINE: 
			usefulinfo = true;
			if(!switchflag)
				fprintf( listing, "$TITLE\n" ); 
			checktoken.push(token);	
		break;
    case CLOSEHEADLINE: 
			usefulinfo = false;
			if(!checktoken.empty()&&checktoken.top()==OPENHEADLINE)
				checktoken.pop();
			else
				fprintf(listing, "TAGERROR: HEADLINE, Row: %d\n", tokenStruct.row);
		break;
		
	case OPENOTHERTAG:
			checktoken.push(token);
		break;
	case CLOSEOTHERTAG:
			if(!checktoken.empty()&&checktoken.top()==OPENOTHERTAG)
				checktoken.pop();
			else
				fprintf(listing, "TAGERROR: OTHER, Row: %d\n", tokenStruct.row);
		break;

	//Punctuation
	case PERIOD: break;
	case QUESTION: break;
	case EXCLAMATION: break;
	case OTHERMARK: break;
	
    case ENDFILE: fprintf( listing, "EOF\n" ); break;

    case NUMBER:
		if(!switchflag&&numkeep&&usefulinfo)
			fprintf( listing, "%s\n", tokenStruct.value.c_str() );
      break;
 
	case WORD:
	{
	  if(!switchflag&&usefulinfo)
	  {
		string s = lowerstr(tokenStruct.value);
		if(!checkStopwords(s))
			fprintf( listing, "%s\n", s.c_str());
	  }
	}
      break;
	case APOSTROPHIZED:
	{
	  if(!switchflag&&usefulinfo)
	  {
		string s = lowerstr(tokenStruct.value);

		if(!checkStopwords(s)&&s.length()>3)
			fprintf( listing, "%s\n", s.c_str());
	  }
	}
	  break;
	case TYPO:
	{
	  if(!switchflag&&usefulinfo)
	  {
		string s = lowerstr(tokenStruct.value);
		string f,b;
		int pos = s.find("'");
		f = s.substr(0,pos);
		b = s.substr(pos+1,s.length());
	  
		if(!checkStopwords(f))
			fprintf( listing, "%s\n", f.c_str());

		if(!checkStopwords(b))
			fprintf( listing, "%s\n", b.c_str());
	  }
	}
	  break;
	case HYPHENATED:
	{
	  if(!switchflag&usefulinfo)
	  {
		string s = lowerstr(tokenStruct.value);
		string f,b;
		int pos = s.find("-");
		f = s.substr(0,pos);
		b = s.substr(pos+1,s.length());
		if(f.length()>3&&b.length()>3)
		{
			if(!checkStopwords(f))
				fprintf(listing, "%s\n", f.c_str());
			if(!checkStopwords(b))
				fprintf(listing, "%s\n", b.c_str());
		}
		else
			fprintf( listing, "%s\n", s.c_str());
	  }
	}
	  break;
	 
    case ERROR:
	  if(!switchflag&usefulinfo)
		fprintf( listing, "ERROR: %s\n", tokenStruct.value.c_str() );
      break;
    default: // should never happen 
      fprintf( listing, "Unknown token: %d\n", token );
  }
}
