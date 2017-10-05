#include "Weight.h"

bool sortRule(const weightStruct& a, const weightStruct& b)
{
	return a.weight>b.weight;
}

void sortWeight()
{
	if(weight.size()>0)
		sort(weight.begin(),weight.end(), sortRule);
}

int inWeightList(int no)
{
	vector<weightStruct>::size_type sz = weight.size();
	for(int i=0; i<sz; i++)
		if(weight[i].docno==no)
			return i;
	return 0;
}

void calculateWeight(string* sp, int n)
{
	for(int i=0; i<n; i++)
	{
		vector<postStruct>::size_type sz = Term[sp[i]].size();

		if(sz>0)
		{
			double idf = log((double)totalNumDocs/(double)sz);
			for(int j=0; j<sz; j++)
			{
				double wij = idf*(double)Term[sp[i]][j].frequency;
				int k = inWeightList(Term[sp[i]][j].docno);
				if(k>0)
				{
					weight[k].weight+=wij;
				}
				else{
					weightStruct ws = {Term[sp[i]][j].docno,wij};
					weight.push_back(ws);
				}
			}
		}
	}

	sortWeight();
}