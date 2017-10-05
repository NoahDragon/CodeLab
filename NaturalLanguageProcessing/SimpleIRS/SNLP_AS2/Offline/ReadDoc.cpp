#include "ReadDoc.h"

bool id(string s)
{
	if(s.compare("$ID")==0)
		return true;
	else
		return false;
}

bool metasymbol(string s)
{
	if(s[0] == '$')
		return true;
	else
		return false;
}

void readDoc()
{
	ifstream file(docfilename.c_str());
	char term[64];
	string temp;
	while(!file.eof())
	{
		file.getline(term,64);
		temp = term;
		rowno++;
		
		if(id(temp))
		{
			docno++;
			file.getline(term,64);
			temp = term;
			docidStruct d = {temp, rowno};
			rowno++;
			Docid.push_back(d);
		}
		else if(metasymbol(temp))
		{
			continue;
		}
		else
		{
			if(Term[temp].size() > 0 )
			{
				vector<int>::size_type sz = Term[temp].size();
				bool numexist = false;
				for(int i=0; i<sz; i++)
				{
					if(Term[temp][i].docno == docno)
					{
						Term[temp][i].frequency++;
						numexist = true;
					}
				}
				if(!numexist)
				{
					postStruct p = {docno, 1};
					Term[temp].push_back(p);
				}
			}
			else
			{
				postStruct p = {docno, 1};
				vector<postStruct> ps;
				ps.push_back(p);
				Term[temp] = ps;
			}
		}
	}
	file.close();
}