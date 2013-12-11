#include "Loaddata.h"
#include "Util.h"

void termData()
{
	fstream t(dictionary.c_str(), ios::in);
	fstream p(postings.c_str(), ios::in);
	
	string t1,t2;
	string p1,p2;
	
	t>>t1;
	totalNumTerms = str2int(t1);
	p>>p1;
	totalNumEntries = str2int(p1);
	
	while(!t.eof()&&!p.eof())
	{
		t>>t1>>t2;
		int loop = str2int(t2);

		vector<postStruct> vp;
		
		for(int i=0; i<loop; i++)
		{
			p>>p1>>p2;
			postStruct p={str2int(p1),str2int(p2)};
			vp.push_back(p);
		}
		
		Term[t1] = vp;
	}
	
	t.close();
	p.close();
}

void docData()
{
	fstream d(docids.c_str(), ios::in);
	string d1,d2;
	
	d>>d1;
	totalNumDocs = str2int(d1);
	
	while(!d.eof())
	{
		d>>d1>>d2;
		docidStruct ds={d1,str2long(d2)};
		Docid.push_back(ds);
	}
	
	d.close();
}
