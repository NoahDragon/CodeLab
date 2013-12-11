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
	double s3;
	double s4;
	double s5;
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
		//delete [] mHOw;
		//delete [] mIHw;
	};

	double BpLearn; // Rate of Learning
	double output;
	double outputDiff; // Different between actural output and desired output
	double *IHw[5]; // Input to Hidden layer weights 2D martix
	double *HOw; // Hidden layer to Output weights 2D martix
	double *hidden; //Hidden layer
	double *hiddenError; //Hidden layer error
	double precision; // Stopping criteria when the absolute rate of change in the average squared error per epoch is sufficiently small
	int nHidden; // The number of nodes in hidden layer
	double error;
	double *hThreshold; // Threshold for hidden layer
	double oThreshold; // Threshold for output

	double momentum; //momentum rate
	//double *mHOw; //privous weight during training bwt output and hidden
	//double *mIHw[5]; //privous weight bwt during training input and hidden

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
	for (int i = 0; i<5; i++)
	{
		IHw[i] = new double[nHidden];
		//mIHw[i] = new double[nHidden];
	}
	for(int i =0; i<5; i++)
		for (int j=0; j<nHidden; j++)
		{
			IHw[i][j] = rand()/(1.0*RAND_MAX)*2-1;
			//mIHw[i][j] = 0;
		}
	HOw = new double[nHidden];
	//mHOw = new double[nHidden];
	hThreshold = new double[nHidden];
	for(int i =0; i<nHidden; i++)
	{
		HOw[i] = rand()/(1.0*RAND_MAX)*2-1;
		//mHOw[i] = 0;
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
	double s[5] = {samp.s1, samp.s2, samp.s3, samp.s4, samp.s5};

	for(int i=0;i<nHidden;i++)
		hidden[i] = s[0]*IHw[0][i]+s[1]*IHw[1][i]+s[2]*IHw[2][i]+s[3]*IHw[3][i]+s[4]*IHw[4][i];
	for(int i=0;i<nHidden;i++)
		hidden[i] = sigmoid(hidden[i]+hThreshold[i]);

	double sum = 0;
	for(int i=0; i<nHidden; i++)
		sum+=HOw[i]*hidden[i];

	return sigmoid(sum+oThreshold);
}

void BackPropagation::train(sample samp)
{
	double s[5] = {samp.s1, samp.s2, samp.s3, samp.s4, samp.s5};
	int i,j;

	for(i =0; i<nHidden;i++)
		hidden[i] = s[0]*IHw[0][i]+s[1]*IHw[1][i]+s[2]*IHw[2][i]+s[3]*IHw[3][i]+s[4]*IHw[4][i];
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
		HOw[i] = HOw[i]+BpLearn*hidden[i]*outputDiff/*+momentum*mHOw[i]*/;
		//mHOw[i] = BpLearn*hidden[i]*outputDiff+momentum*mHOw[i];
	}
	
	//modify input to hidden layer weights
	for(i = 0; i<5; i++)
		for(j= 0;j<nHidden;j++)
			IHw[i][j] = IHw[i][j] + BpLearn*s[i]*hiddenError[j];
	for(i = 0; i<nHidden; i++)
		hThreshold[i] += BpLearn*hiddenError[i];
	oThreshold += BpLearn*outputDiff;

}

void main()
{
	BackPropagation bp(5,0.85);
	bp.BpLearn = 0.5;
    
    double n;
	cout<<"Please input the stop precision:"<<endl;
	cin>>n;

	bp.precision = n;

	sample samp[6]; // Four XOR patterns

	samp[0].s1=1;
	samp[0].s2=2;
	samp[0].s3=3;
	samp[0].s4=2;
	samp[0].s5=1;
	samp[0].result=1;

	samp[1].s1=2;
	samp[1].s2=4;
	samp[1].s3=5;
	samp[1].s4=4;
	samp[1].s5=2;
	samp[1].result=1;

	samp[2].s1=1;
	samp[2].s2=2;
	samp[2].s3=3;
	samp[2].s4=4;
	samp[2].s5=5;
	samp[2].result=0;

	samp[3].s1=3;
	samp[3].s2=4;
	samp[3].s3=2;
	samp[3].s4=3;
	samp[3].s5=4;
	samp[3].result=0;

	samp[4].s1=5;
	samp[4].s2=6;
	samp[4].s3=7;
	samp[4].s4=2;
	samp[4].s5=1;
	samp[4].result=0;

	samp[5].s1=1;
	samp[5].s2=1;
	samp[5].s3=2;
	samp[5].s4=1;
	samp[5].s5=1;
	samp[5].result=1;

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
			for(int i =0; i<6;i++)
				bp.train(samp[i]);
			//if(j%10 == 0)
			{
				ss<<bp.error<<endl;
				outfile<<ss.str()<<endl;
			}
			j++;
		}

		cout << "5 bit symmetry(1,2,3,2,1) = " << bp.run(samp[0]) << endl;
		cout << "5 bit symmetry(2,4,5,4,2) = " << bp.run(samp[1]) << endl;
		cout << "5 bit symmetry(1,2,3,4,5) = " << bp.run(samp[2]) << endl;
		cout << "5 bit symmetry(3,4,2,3,4) = " << bp.run(samp[3]) << endl;
		cout << "5 bit symmetry(5,6,7,2,1) = " << bp.run(samp[4]) << endl;
		cout << "5 bit symmetry(1,1,2,1,1) = " << bp.run(samp[5]) << endl;
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
