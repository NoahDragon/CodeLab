/*
 Assignment for course Neural Network.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace::std;

struct sample
{
	double s1;
	double s2;
	double result;
};

class BackPropagation
{
public:
   	BackPropagation(int,double);
	~BackPropagation()
	{
		delete [] IHw;
		delete [] HOw;
		delete [] hidden;
		delete [] hiddenError;
		delete [] hThreshold;
		delete [] mHOw;
		delete [] mIHw;
	};

	double BpLearn; // Rate of Learning
	double output;
	double outputDiff; // Different between actural output and desired output
	double *IHw[2]; // Input to Hidden layer weights 2D martix
	double *HOw; // Hidden layer to Output weights 2D martix
	double *hidden; //Hidden layer
	double *hiddenError; //Hidden layer error
	double precision; // Stopping criteria when the absolute rate of change in the average squared error per epoch is sufficiently small
	int nHidden; // The number of nodes in hidden layer
	double error;
	double *hThreshold; // Threshold for hidden layer
	double oThreshold; // Threshold for output
	double momentum; //momentum rate
	double *mHOw; //privous weight during training bwt output and hidden
	double *mIHw[2]; //privous weight bwt during training input and hidden
	double run(struct sample);
	void train(struct sample);

private:
	double sigmoid(double);

};

BackPropagation::BackPropagation(int n,double m)
{
	nHidden = n;
	momentum = m;
	srand((unsigned)time(NULL)); // randomseed
	for (int i = 0; i<2; i++)
	{
		IHw[i] = new double[nHidden];
		mIHw[i] = new double[nHidden];
	}
	for(int i =0; i<2; i++)
		for (int j=0; j<nHidden; j++)
		{
			IHw[i][j] = rand()/(1.0*RAND_MAX)*2-1;
			mIHw[i][j] = 0;
		}
	HOw = new double[nHidden];
	mHOw = new double[nHidden];
	hThreshold = new double[nHidden];
	for(int i =0; i<nHidden; i++)
	{
		HOw[i] = rand()/(1.0*RAND_MAX)*2-1;
		mHOw[i] = 0;
		hThreshold[i] = rand()/(1.0*RAND_MAX)*2-1;
	}
	oThreshold = rand()/(1.0*RAND_MAX)*2-1;
	hidden = new double[nHidden];
	hiddenError = new double[nHidden];
	for(int i = 0; i<nHidden; i++) hiddenError[i] = 0;

}

double BackPropagation::sigmoid(double n)
{
	return (float)(1/(1+exp(-n)));
}

double BackPropagation::run(sample samp)
{
	double s[2] = {samp.s1, samp.s2};

	for(int i=0;i<nHidden;i++)
		hidden[i] = s[0]*IHw[0][i]+s[1]*IHw[1][i];
	for(int i=0;i<nHidden;i++)
		hidden[i] = sigmoid(hidden[i]+hThreshold[i]);

	double sum = 0;
	for(int i=0; i<nHidden; i++)
		sum+=HOw[i]*hidden[i];

	return sigmoid(sum+oThreshold);
}

void BackPropagation::train(sample samp)
{
	double s[2] = {samp.s1, samp.s2};
	int i,j;

	for(i =0; i<nHidden;i++)
		hidden[i] = s[0]*IHw[0][i]+s[1]*IHw[1][i];
	for(i=0;i<nHidden;i++)
		hidden[i] = sigmoid(hidden[i]+hThreshold[i]);

	double sum = 0;
	for(i=0; i<nHidden; i++)
		sum+=HOw[i]*hidden[i];

	output = sigmoid(sum+oThreshold);
	outputDiff = output*(1-output)*(samp.result-output);
    //caculating error
	error += pow(samp.result-output,2);

	//hidden layer error
	for(i = 0; i<nHidden; i++)
		hiddenError[i] =  hidden[i]*(1-hidden[i])*HOw[i]*outputDiff;

	//modify hidden layer to output weights
	for(i = 0; i<nHidden; i++)
	{
		HOw[i] = HOw[i]+BpLearn*hidden[i]*outputDiff+momentum*mHOw[i];
		mHOw[i] = BpLearn*hidden[i]*outputDiff+momentum*mHOw[i];
	}
	
	//modify input to hidden layer weights
	for(i = 0; i<2; i++)
		for(j= 0;j<nHidden;j++)
			IHw[i][j] = IHw[i][j] + BpLearn*s[i]*hiddenError[j];
	for(i = 0; i<nHidden; i++)
		hThreshold[i] += BpLearn*hiddenError[i];
	oThreshold += BpLearn*outputDiff;

}

void main()
{
	BackPropagation bp(2,0.85);
	bp.BpLearn = 0.5;
    
    double n;
	cout<<"Please input the stop precision:"<<endl;
	cin>>n;

	bp.precision = n;

	sample samp[4]; // Four XOR patterns

	samp[0].s1=0;
	samp[0].s2=0;
	samp[0].result=0;

	samp[1].s1=0;
	samp[1].s2=1;
	samp[1].result=1;

	samp[2].s1=1;
	samp[2].s2=0;
	samp[2].result=1;

	samp[3].s1=1;
	samp[3].s2=1;
	samp[3].result=0;

	bp.error = bp.precision + 1;

	ofstream outfile;
	outfile.open("t.txt");
	stringstream ss;
	
	if(outfile.is_open())
	{
		int j =0;
		while(bp.error > bp.precision)
		{
			bp.error = 0;
			for(int i =0; i<4;i++)
				bp.train(samp[i]);
			if(j%10 == 0)
			{
				ss<<bp.error<<endl;
				outfile<<ss.str()<<endl;
			}
			j++;
		}

		cout << "XOR(0,0) = " << bp.run(samp[0]) << endl;
		cout << "XOR(0,1) = " << bp.run(samp[1]) << endl;
		cout << "XOR(1,0) = " << bp.run(samp[2]) << endl;
		cout << "XOR(1,1) = " << bp.run(samp[3]) << endl;
	}
	else cout<<"Can't open file."<<endl;

	outfile.close();
	char ch;
	do{
		cout<<"Please input 'q' to exit:"<<endl;
	    
	    cin>>ch;
	}while(ch!='q');

    //return 0;
}
