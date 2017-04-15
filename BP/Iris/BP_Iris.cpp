#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace::std;

struct sample
{
	double pw;
	double pl;
	double sw;
	double sl;
	double result[3];
	int trueType;
};

class BackPropagation
{
public:
   	BackPropagation(int,int,double);
	~BackPropagation()
	{
		delete [] IHw;
		delete [] HOw;
		delete [] hidden;
		delete [] hiddenError;
		delete [] hThreshold;
		delete [] output;
		delete [] outputDiff;
		delete [] oThreshold;
		delete [] mHOw;
		//delete [] mIHw;
	};

	double BpLearn; // Rate of Learning
	double *output;
	double *outputDiff; // Different between actural output and desired output
	double *IHw[4]; // Input to Hidden layer weights 2D martix
	double *HOw[3]; // Hidden layer to Output weights 2D martix
	double *hidden; //Hidden layer
	double *hiddenError; //Hidden layer error
	double precision; // Stopping criteria when the absolute rate of change in the average squared error per epoch is sufficiently small
	int nHidden; // The number of nodes in hidden layer
	int nOutput; // The number of nodes in output layer
	double error;
	double *hThreshold; // Threshold for hidden layer
	double *oThreshold; // Threshold for output

	double momentum; //momentum rate
	double *mHOw[3]; //privous weight during training bwt output and hidden
	//double *mIHw[4]; //privous weight bwt during training input and hidden

	double run(struct sample);
	void train(struct sample);

private:
	double sigmoid(double);

};

BackPropagation::BackPropagation(int n,int l,double m)
{
	nHidden = n;
	nOutput = l;
	momentum = m;
	
	output = new double[nOutput];
	outputDiff = new double[nOutput];
	srand((unsigned)time(NULL)); // randomseed
	for (int i = 0; i<4; i++)
	{
		IHw[i] = new double[nHidden];
		//mIHw[i] = new double[nHidden];
	}
	for(int i =0; i<4; i++)
	{
		for (int j=0; j<nHidden; j++)
		{
			IHw[i][j] = rand()/(1.0*RAND_MAX)*2.0-1.0;
			//mIHw[i][j] = 0;
		}
	}

	for(int i = 0; i<nOutput;i++)
		mHOw[i] = new double[nHidden];

	for (int i = 0; i<nOutput; i++)
	{
		HOw[i] = new double[nOutput];
	}

	hThreshold = new double[nHidden];
	for(int i =0; i<nOutput; i++)
	{
		for(int j = 0; j<nHidden; j++)
		{
			HOw[i][j] = rand()/(1.0*RAND_MAX)*2.0-1.0; //i is output node, j is hidden node.
			mHOw[i][j] = 0.0;
		}
		
		hThreshold[i] = rand()/(1.0*RAND_MAX)*2.0-1.0;
	}
	oThreshold = new double[nOutput];
	for (int i =0; i<nOutput; i++)
	{
		oThreshold[i] = rand()/(1.0*RAND_MAX)*2.0-1.0;
	}
	hidden = new double[nHidden];
	hiddenError = new double[nHidden];
	for(int i = 0; i<nHidden; i++) hiddenError[i] = 0.0;

}

double BackPropagation::sigmoid(double n)
{
	return (float)(1.0/(1.0+exp(-n)));
}

double BackPropagation::run(sample samp)
{
	double s[4] = {samp.pw/100.0, samp.pl/100.0, samp.sw/100.0, samp.sl/100.0};

	for(int i=0;i<nHidden;i++)
		hidden[i] = s[0]*IHw[0][i]+s[1]*IHw[1][i]+s[2]*IHw[2][i]+s[3]*IHw[3][i];
	for(int i=0;i<nHidden;i++)
		hidden[i] = sigmoid(hidden[i]+hThreshold[i]);

	double sum[3] = {0};
	for(int i=0; i<nOutput; i++)
	{	
		for(int j=0; j<nHidden; j++)
			sum[i]+=HOw[i][j]*hidden[j];
	}

	for(int i =0; i<nOutput; i++)
	{
		output[i] = sigmoid(sum[i]+oThreshold[i]);
	}

	return 1.0;
}

void BackPropagation::train(sample samp)
{
	double s[4] = {samp.pw/100.0, samp.pl/100.0, samp.sw/100.0, samp.sl/100.0};
	int i,j;

	for(i =0; i<nHidden;i++)
		hidden[i] = s[0]*IHw[0][i]+s[1]*IHw[1][i]+s[2]*IHw[2][i]+s[3]*IHw[3][i];
	for(i=0;i<nHidden;i++)
		hidden[i] = sigmoid(hidden[i]+hThreshold[i]);

	double sum[3] = {0};
	for(i=0; i<nOutput; i++)
	{	
		for(j=0; j<nHidden; j++)
			sum[i]+=HOw[i][j]*hidden[j];
	}
	for(i =0; i<nOutput; i++)
	{
		output[i] = sigmoid(sum[i]+oThreshold[i]);
		outputDiff[i] = output[i]*(1-output[i])*(samp.result[i]-output[i]);
		//caculating error
		error += pow(samp.result[i]-output[i],2);
	}
	double sumeration = 0.0;
	//hidden layer error
	for(i = 0; i<nHidden; i++)
	{
		for(j = 0; j<nOutput;j++)
		{
			sumeration += HOw[j][i]*outputDiff[j];
		}
		hiddenError[i] =  hidden[i]*(1-hidden[i])*sumeration;
	}

	//modify hidden layer to output weights
	for(j =0; j<nOutput; j++)
	{
		for(i = 0; i<nHidden; i++)
		{
			HOw[j][i] += BpLearn*hidden[i]*outputDiff[j]+momentum*mHOw[j][i];
			mHOw[j][i] = BpLearn*hidden[i]*outputDiff[j]+momentum*mHOw[j][i];
		}
	}	
	//modify input to hidden layer weights
	for(i = 0; i<4; i++)
		for(j= 0;j<nHidden;j++)
			IHw[i][j] += BpLearn*s[i]*hiddenError[j];
	for(i = 0; i<nHidden; i++)
		hThreshold[i] += BpLearn*hiddenError[i];
	for(j=0; j<nOutput; j++)
		oThreshold[j] += BpLearn*outputDiff[j];

}

/*************************************************************
Function: strToNum
Author: panpan3210
From:http://panpan.blog.51cto.com/489034/107732
*************************************************************/
template<class T>
T strToNum(const string& str)  //String to number
{
  stringstream ss(str);
  T temp;
  ss >> temp;
  if ( ss.fail() ) {
    string excep = "Unable to format ";
    excep += str;
    throw (excep);
  }
  return temp;
}

void main()
{
	BackPropagation bp(4,3,0.85);
	bp.BpLearn = 0.2; // set learning rate
    
    double n;
	cout<<"Please input the stop precision:"<<endl;
	cin>>n;

	bp.precision = n;

	ifstream inputfile;
	inputfile.open("data");
	sample *samp = new sample[150];

	if(inputfile.is_open())
	{
		//char line[25];
		int k = 0;
		char t;
		
		while(!inputfile.eof())
		{
			//inputfile.getline(line,25);
			t = inputfile.get();
			char *num[6];
			for(int i =0; i<6; i++)
				num[i] = new char[3];
			
			int j =0;
			while(t!=0x0D&&t!=0x0A) //not enter
			{
				int i =0;
				while(t!=0x20&&t!=0x0D&&t!=0x0A&&!inputfile.eof()) //not space
				{
					num[j][i]=t;
					t = inputfile.get();
					i++;
				}
				if(t == 0x0D || t == 0x0A)
					break;
				if(t == 0x20)
					t = inputfile.get();
				else
					break;
				j++;
			}
			
			try
			{
				string s1(num[1]);
				if(strToNum<int>(s1)<=2&&strToNum<int>(s1)>1)
				{
					samp[k].result[2]=(double)1.0;
					samp[k].result[1]=(double)0.0;
					samp[k].result[0]=(double)0.0;
					samp[k].trueType = 2;
				}
				else if(strToNum<int>(s1)<=1&&strToNum<int>(s1)>0)
				{
					samp[k].result[2]=(double)0.0;
					samp[k].result[1]=(double)1.0;
					samp[k].result[0]=(double)0.0;
					samp[k].trueType = 1;
				}
				else
				{
					samp[k].result[2]=(double)0.0;
					samp[k].result[1]=(double)0.0;
					samp[k].result[0]=(double)1.0;
					samp[k].trueType = 0;
				}
				//samp[k].result = (double)strToNum<double>(s1)/3.0;
				string s2(num[2]);
				samp[k].pw = strToNum<double>(s2);
				string s3(num[3]);
				samp[k].pl = strToNum<double>(s3);
				string s4(num[4]);
				samp[k].sw = strToNum<double>(s4);
				string s5(num[5]);
				samp[k].sl = strToNum<double>(s5);
				k++;
			}
			catch (string& e) 
			{
				cerr << "exception:" << e << endl;
			}
			//if(inputfile.eof())
			//	break;
			//else
			//	t = inputfile.get();
		}
		
		inputfile.close();
		bp.error = bp.precision + 1.0;

		ofstream outfile;
		outfile.open("t.txt");
		stringstream ss;
		
		if(outfile.is_open())
		{
			int j =0;
			while(bp.error > bp.precision)
			{
				bp.error = 0;
				for(int i =0; i<100;i++)
					bp.train(samp[i]);
				if(j%1000 == 0)
				{
					ss<<bp.error<<endl;
					outfile<<ss.str()<<endl;
				}
				cout<<"bp.error="<<bp.error<<endl;
				j++;
			}

			for(int i = 0; i<150; i++)
			{
				bp.run(samp[i]);
				cout<< "Iris("<<samp[i].trueType<<","<<samp[i].pw<<","<<samp[i].pl<<","<<samp[i].sw<<","<<samp[i].sl<<") = ("<<bp.output[0]<<","<<bp.output[1]<<","<<bp.output[2]<<") <"<<i+1<<">"<<endl;
			}
		}
		else
			cout<<"Can't open file."<<endl;

		outfile.close();
	}
	else
		cout<<"Can't open data file."<<endl;

	char ch;
	do{
		cout<<"Please input 'q' to exit:"<<endl;
	    
	    cin>>ch;
	}while(ch!='q');

    //return 0;
}
