#ifndef _WEIGHT_H_
#define _WEIGHT_H_

#include "global.h"

void calculateWeight(string*, int); //args: array string, length
int inWeightList(int); // Check the weight list to find out if the doc already in list.
void sortWeight();
bool sortRule(const weightStruct &, const weightStruct &);

#endif