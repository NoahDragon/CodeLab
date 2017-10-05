#include "IRS.h"
#include "Loaddata.h"
#include "Weight.h"
#include "Util.h"

int totalNumTerms = 0;
int totalNumEntries = 0;
int totalNumDocs = 0;

vector<weightStruct> weight;
map<string, vector<postStruct> > Term;
vector<docidStruct> Docid;

/*
This mygetch() references from the Internet,
it implements the getch() function.
http://bytes.com/topic/c/answers/503640-getch-linux
*/
int mygetch(void)
{
	struct termios oldt,
	newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}


bool checkid(string s)
{
	if(s.compare("$ID")==0)
		return true;
	else
		return false;
}

bool title(string s)
{
	if(s.compare("$TITLE")==0)
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

bool narr(string s)
{
	if(s.compare("$NARR")==0)
		return true;
	else
		return false;
}

void showDetail(int no, int i)
{
	docDetailStruct ds;
	ds = getDetail(weight[(i-1)*10+no].docno);
	cout<<"--------------- Document ID: <"<<ds.docid<<"> ---------------"<<endl;
	if(ds.title.length()>0)
	{
		cout<<"TITLE:"<<endl;
		cout<<ds.title<<endl;
	}
	if(ds.content.length()>0)
	{
		cout<<"CONTENT:"<<endl;
		cout<<ds.content<<endl;
	}
}

docDetailStruct getDetail(int no)
{
	docDetailStruct ds;
	ds.docid = Docid[no].docid;
	
	ifstream id(docs.c_str());
	int line = Docid[no].line;
	char s[50];
	
	for(int i=1; i<=line+2; i++)
		id.getline(s, 50);
	string temp = s;
	
	while(true)
	{
		if(checkid(temp))
			break;
		if(title(temp))
		{
			string t;
			id.getline(s,50);
			temp = s;
			do{
			t+=temp+" ";
			id.getline(s,50);
			temp = s;
			}while(!metasymbol(temp));
			ds.title = t;
		}
		if(narr(temp))
		{
			string t;
			id.getline(s,50);
			temp = s;
			do{
			t+=temp+" ";
			id.getline(s,50);
			temp = s;
			}while(!metasymbol(temp));
			ds.content = t;
		}
	}
	return ds;
}

string getTitle(int no)
{
	ifstream id(docs.c_str());
	int line = Docid[no].line;
	char s[50];
	
	for(int i=1; i<=line+2; i++)
		id.getline(s, 50);
	string temp = s;
	bool istile = true;
	
	while(!title(temp))
	{
		id.getline(s,50);
		temp = s;
		if(checkid(temp))
		{
			istile = false;
			break;
		}
	}

	if(istile)
	{
		string t;
		id.getline(s,50);
		temp = s;
		int i = 0;
		do{
			t+=temp+" ";
			id.getline(s,50);
			temp = s;
			i++;
		}while(!metasymbol(temp)&&i<8);
		
		id.close();
		return t;
	}
	
	else
	{
		id.close();
		return "<NO TITLE>";
	}
}

int main()
{
	cout<<"LOADING DATA~~PLEASE BE PATIENT."<<endl;
	
	termData();
	docData();
	
	cout<<"Total number of terms: <"<< totalNumTerms<<"> Total number of documents: <"<<totalNumDocs<<">"<<endl;
	while(true)
	{
		string q;
		
		cout<<"Please input the query that you want to search:(Input quit to exit)"<<endl;
		char buf[1028];
		cin.getline(buf,1028);
		q = buf;
		if(q.compare("quit")==0)
			break;
		
		int i=0, j=0;
		string temp;
		vector<string> query;
		while(i<q.length())
		{
			temp="";
			while(j<q.length()&&q[j]==' ')
				j++;
			while(j<q.length()&&q[j]!=' ')
			{
				temp=temp+q[j];
				j++;
			}
			query.push_back(temp);
			i=j;
		}
	
		string * pq = new string[query.size()];
	
		for(i=0; i<query.size(); i++)
		{
			pq[i]=query[i];
		}

		calculateWeight(pq, query.size());

		cout<<"The relevent documents are listed below:"<<endl;
		i=1;
		while(true)
		{
			if(weight.size()>0)
			{
				cout<<"---------------"<<i<<"/"<<weight.size()/10+1<<"pages"<<"---------------"<<endl;
				if(weight.size()<=10||weight.size()-(i-1)*10<=10)
					for(j=0; j<weight.size();j++)
					{
						cout<<"NUM_"<<j<<": "<<getTitle(weight[(i-1)*10+j].docno)<<endl;
					}
				else
					for(j=0; j<10;j++)
					{
						cout<<"NUM_"<<j<<": "<<getTitle(weight[(i-1)*10+j].docno)<<endl;
					}
				cout<<"Next press n; privous press b; press num to view details; Or press any other key to input a new quary."<<endl;
				char c;
				c=mygetch();

				if(c=='n')
				{
					i++;
					if(i>weight.size()/10)
					{
						cout<<"Already in last page."<<endl;
						i--;
					}
				}
				else if(c=='b')
				{
					i--;
					if(i<=0)
					{
						cout<<"No previous pages."<<endl;
						i++;
					}
				}
				else if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					showDetail(atoi(&c),i);
/*
					switch(c)
					{
						case '0':
							showDetail(0,i);
							break;
						case '1':
							showDetail(1,i);
							break;
						case '2':
							showDetail(2,i);
							break;
						case '3':
							showDetail(3,i);
							break;
						case '4':
							showDetail(4,i);
							break;
						case '5':
							showDetail(5);
							break;
						case '6':
							showDetail(6);
							break;
						case '7':
							showDetail(7);
							break;
						case '8':
							showDetail(8);
							break;
						case '9':
							showDetail(9);
							break;
						default:
							break;
					}
*/
					cout<<"<<<<<<<<<<<<<<<<<<<<<<Press any key to return>>>>>>>>>>>>>>>>>>>"<<endl;
					mygetch();
				}
				else
					break;
			}
			else
			{
				cout<<"Can't find any documents related to your quary."<<endl;
				break;
			}
		}
	}
	return 0;
}
