#include "offline.h"
#include "ReadDoc.h"

int docno = 0; //document number
int rowno = 0; //row number in document file

map<string, vector<postStruct> > Term;
vector<docidStruct> Docid;

string long2str(long l)
{
	char buffer[33];
	sprintf(buffer, "%d", l);
	string s(buffer);
	return s;
}

int main()
{
	readDoc();
	ofstream oid;
	ofstream opost;
	ofstream odic;
	
	oid.open("docids.txt");
	vector<docidStruct>::size_type szid = Docid.size();
	oid << szid << "\n";
	
	for(int i=0; i<szid; i++)
		oid<< Docid[i].docid <<" "<< long2str(Docid[i].line)<<"\n";
	oid.close();
	
	odic.open("dictionary.txt");
	map<string, vector<postStruct> >::size_type szdic = Term.size();
	map<string, vector<postStruct> >::iterator it;
	odic<<szdic<<"\n";
	
	int sum =0;
	
	for(it=Term.begin(); it!=Term.end(); it++)
	{
		vector<postStruct>::size_type sz = (*it).second.size();
		sum+=sz;
		odic<< (*it).first << " " << sz << "\n";
	}
	
	odic.close();
	
	opost.open("postings.txt");
	opost<<sum<<"\n";
	
	for(it = Term.begin(); it!=Term.end(); it++)
	{
		vector<postStruct>::size_type sz = (*it).second.size();
		for(int i=0; i<sz; i++)
			opost<<(*it).second[i].docid<<" "<<(*it).second[i].frequency<<"\n";
	}
	opost.close();
	
	return 0;
}