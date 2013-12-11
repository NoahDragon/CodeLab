#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;
extern int docno ; //document number
extern int rowno ; //row number in document file

static string docfilename = "documents.out";

struct postStruct{
	int docno;
	int frequency;
};

struct docidStruct{
	string docid;
	long line;
};

extern map<string, vector<postStruct> > Term;
extern vector<docidStruct> Docid;
#endif