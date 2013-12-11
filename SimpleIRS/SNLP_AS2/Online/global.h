#ifndef _GLOBAL_H_
#define _GLOBAL_H_

using namespace std;

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <map>
#include <math.h>
#include <algorithm>
#include <termios.h>
#include <unistd.h>


static string dictionary = "dictionary.txt";
static string postings = "postings.txt";
static string docids = "docids.txt";
static string docs = "documents.out";

extern int totalNumTerms;
extern int totalNumEntries;
extern int totalNumDocs;

struct docDetailStruct{
	string docid;
	string title;
	string content;
};

struct postStruct{
	int docno;
	int frequency;
};

struct docidStruct{
	string docid;
	long line;
};

struct weightStruct{
	int docno;
	int weight;
};

extern vector<weightStruct> weight;
extern map<string, vector<postStruct> > Term;
extern vector<docidStruct> Docid;
#endif
