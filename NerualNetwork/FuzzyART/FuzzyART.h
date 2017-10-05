#pragma region headfile
#ifndef FUZZY_ART_HEADFIEL
#define FUZZY_ART_HEADFIEL

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace::std;
#pragma endregion

/***********************************************
Description: this is a work for implement fuzzy 
ART network.
Author: Abner
Date: Mar 26th, 2011
***********************************************/

#pragma region content

#pragma region definition

//Here is the definition of repeatable parameters
#define LEARNINGRATE 0.5 //If set this to 1.0, the fuzzy ART network is fast learning.
#define VIGILANCE 0.6356
#define CHOICE 0.0001
#define CATEGORIES 15 //The maximum number of categories you want to generate
#define INPUTDIMENSION 6 //How many input attributes Iris 4 Bupa 6 or 5
#define ARTDIMENSION INPUTDIMENSION*2
#define INPUTNUMBER 345 //How many input vectors
#define ITERATION_NUM 5 //How many iteration,cant be zero

#pragma endregion

#pragma region TheClass FuzzyART
class FuzzyArt
{
private:
	bool haveInput;
	double alpha; //Choice parameter
	double beta; //Learning rate
	double P; //Vigilance parameter
	double* ArrayInput; //store the address of original input
	double* weights;
	double* inputs;
	double* outputs;
	double* hits; //Record which labeled vector hits the same category.
	void initial();
	void transformInputs(double* inputArray); //inputArray is the original input, through this function it can be transformed to the input that ART need (input with its complement). And it is 2D array. 
	void normalize(double* inputArray);
	double minimum(double a, double b); //find the minimum number between a and b.
	int findnum(double* a,int l, double b); //find a biggest number in array a that is smaller than b, return the index.
	int findnextactivation(double* inputArray,int l); //this is similar to previous one, but it is just suitable for reset activation. like if node j is not the correct node, set the activation of node j to zero.

public:
	FuzzyArt(double* inputArray);
	FuzzyArt();
	~FuzzyArt();
	void setInputs(double* inputArray);
	void train(double* inputArray);
	void train();
	void test(string filePath,double* inputArray, double* lable); //each input vector has lable on it respectively.

};
#pragma endregion

#pragma region Function declearation

#pragma region Create&delete function
FuzzyArt::FuzzyArt(double* inputArray)
{
	haveInput = true;
	ArrayInput = inputArray;
	weights = new double[CATEGORIES*ARTDIMENSION];
	inputs = new double[INPUTNUMBER*ARTDIMENSION];
	outputs = new double[CATEGORIES];
	hits = new double[CATEGORIES*INPUTNUMBER]; //The maximum number of hitting in same category is the total number of input vector.
	initial();
}
FuzzyArt::FuzzyArt()
{
	haveInput = false;
	ArrayInput = NULL;
	weights = new double[CATEGORIES*ARTDIMENSION];
	inputs = new double[INPUTNUMBER*ARTDIMENSION];
	outputs = new double[CATEGORIES];
	hits = new double[CATEGORIES*INPUTNUMBER]; //The maximum number of hitting in same category is the total number of input vector.
	initial();
}

FuzzyArt::~FuzzyArt()
{
	delete weights;
	delete inputs;
	delete outputs;
	delete hits;
}
#pragma endregion

#pragma region initial()
void FuzzyArt::initial()
{
	//set Vigilance, choice, and learning rate;
	P = VIGILANCE;
	alpha = CHOICE;
	beta = LEARNINGRATE;

	//set all weights equal to 1.0;
	for(int i=0; i<CATEGORIES; i++)
		for(int j=0; j<ARTDIMENSION; j++)
			weights[i*ARTDIMENSION+j]=1.0;
	
	for(int i=0; i<CATEGORIES; i++)
		outputs[i] = 0.0;

	for(int i=0; i<CATEGORIES; i++)
		for(int j=0; j<INPUTNUMBER; j++)
			hits[i*INPUTNUMBER+j] = -1;
}
#pragma endregion

#pragma region noramlize(double*)
void FuzzyArt::normalize(double* inputArray)
{
	//use mean normalization
#pragma region mean normalization
/*	
	double* max,* min;
	max = new double[INPUTDIMENSION];
	min = new double[INPUTDIMENSION];

	for(int i=0; i<INPUTDIMENSION; i++)
	{
		max[i] = -1;
		min[i] = -1;
	}

	for(int i=0; i<INPUTNUMBER; i++)
		for(int j=0; j<INPUTDIMENSION; j++)
		{
			if(max[j]==-1)
				max[j]=inputArray[i*INPUTDIMENSION+j];
			if(min[j]==-1)
				min[j]=inputArray[(i+1)*INPUTDIMENSION+j];
			if(inputArray[i*INPUTDIMENSION+j] > max[j])
				max[j] = inputArray[i*INPUTDIMENSION+j];
			if(inputArray[i*INPUTDIMENSION+j] < min[j])
				min[j] = inputArray[i*INPUTDIMENSION+j];
		}

	for(int i=0; i<INPUTNUMBER; i++)
		for(int j=0; j<INPUTDIMENSION; j++)
		{
			inputArray[i*INPUTDIMENSION+j]=(inputArray[i*INPUTDIMENSION+j]-min[j])/(max[j]-min[j]);
		}

	delete max;
	delete min;
*/	
#pragma endregion

#pragma region common normalization
	
	double temp;

	for(int i=0; i<INPUTNUMBER; i++)
	{
		temp = 0.0;
		for(int j=0; j<INPUTDIMENSION; j++)
			temp+=pow(inputArray[i*INPUTDIMENSION+j],2);
		for(int j=0; j<INPUTDIMENSION; j++)
			inputArray[i*INPUTDIMENSION+j]=inputArray[i*INPUTDIMENSION+j]/sqrt(temp);
	}
	
#pragma endregion
}
#pragma endregion

#pragma region transformInputs(double*)
void FuzzyArt::transformInputs(double* inputArray)
{
	normalize(inputArray);
	for(int i=0; i<INPUTNUMBER; i++)
		for(int j=0; j<ARTDIMENSION; j++)
		{
			if(j<INPUTDIMENSION)
				inputs[i*ARTDIMENSION+j] = inputArray[i*INPUTDIMENSION+j];
			else
				inputs[i*ARTDIMENSION+j] = 1-inputArray[i*INPUTDIMENSION+(j-INPUTDIMENSION)]; //the complement of input
		}
}
#pragma endregion

#pragma region setInputs(double*)
void FuzzyArt::setInputs(double* inputArray)
{
	haveInput = true;
	ArrayInput = inputArray;
}
#pragma endregion

#pragma region minimum(double,double)
double FuzzyArt::minimum(double a, double b)
{
	if(a>b)
		return b;
	else
		return a;
}
#pragma endregion

#pragma region findnextactivation(double*,int)
int FuzzyArt::findnextactivation(double* inputArray, int l)
{
	int length = l;
	int index = 0;
	bool flag = false;
	double temp = inputArray[0];
	
	for(int i=0; i<length; i++)
	{
		if(temp<inputArray[i])
		{
			temp = inputArray[i];
			index = i;
			flag = true;
		}
	}
	if(flag)
		return index;
	else
		return -1;
}
#pragma endregion

#pragma region findnum(double*,int,double)
int FuzzyArt::findnum(double* a,int l, double b)
{
	int length = l;
	int index = 0;
	//int temp = 0;
	bool flag = false; // check if it find a smaller one
	for(int i=0; i<length; i++)
	{
		if(flag)
		{
			if(a[i]>a[index]&&a[i]<b)
				index = i;
		}
		else
		{
			if(a[i]<b)
			{
				index = i;
				flag = true;
			}
		}
	}
	if(!flag)//cant find smaller number than b
		return -1;
	return index;
}
#pragma endregion

#pragma region train(double*)
void FuzzyArt::train(double* inputArray)
{
	if(!haveInput)
		setInputs(inputArray);
	//set inputs
	transformInputs(ArrayInput);

	int iteration = 0;
	double* activation;
	double temp = 0.0;
	int num; //record which node is the winner.
	double sum1,sum2;//sum1 and sum2 are set for checking vigilance
	double weightSum;
	
	activation = new double[CATEGORIES];

	while(iteration<ITERATION_NUM)
	{
		for(int i=0; i<INPUTNUMBER; i++)
		{
			sum1 = 0.0;
			sum2 = 0.0;
			temp = 0.0;
			for(int j=0; j<CATEGORIES; j++)
				activation[j] = 0.0;
			for(int j=0; j<CATEGORIES; j++)
			{
				weightSum = 0.0;
				for(int k=0; k<ARTDIMENSION; k++)
					weightSum+= weights[j*ARTDIMENSION+k];
				//find the biggest activation in output nodes
				for(int k=0; k<ARTDIMENSION; k++)
					activation[j] += minimum(inputs[i*ARTDIMENSION+k],weights[j*ARTDIMENSION+k])/(alpha+weightSum); 
				if(activation[j]>temp)
				{
					temp = activation[j];
					num = j;
				}

			}
			for(int k=0; k<ARTDIMENSION; k++)
			{
				sum1+= minimum(inputs[i*ARTDIMENSION+k],weights[num*ARTDIMENSION+k]);
				sum2+= inputs[i*ARTDIMENSION+k];
			}
			
			//check vigilance
			if((double)(sum1/sum2)>=P)
			{
				outputs[num] = 1.0;
				//set new weights
				for(int k=0; k<ARTDIMENSION; k++)
					weights[num*ARTDIMENSION+k] = beta*minimum(inputs[i*ARTDIMENSION+k],weights[num*ARTDIMENSION+k])+(1-beta)*weights[num*INPUTDIMENSION+k];
			}
			else
			{
				while((double)(sum1/sum2)<P)
				{
					activation[num] = 0.0;
					sum1 = 0.0;
					sum2 = 0.0;
					num = findnextactivation(activation,CATEGORIES);
					if(num==-1)
						break;
					for(int k=0; k<ARTDIMENSION; k++)
					{
						sum1+= minimum(inputs[i*ARTDIMENSION+k],weights[num*ARTDIMENSION+k]);
						sum2+= inputs[i*ARTDIMENSION+k];
					}
				}
				if(num!=-1)
				{
					outputs[num] = 1.0;
					//set new weights
					for(int k=0; k<ARTDIMENSION; k++)
						weights[num*ARTDIMENSION+k] = beta*minimum(inputs[i*ARTDIMENSION+k],weights[num*ARTDIMENSION+k])+(1-beta)*weights[num*ARTDIMENSION+k];
				}
			}
		
		}

		iteration++;
	}

}
#pragma endregion

#pragma region train()
void FuzzyArt::train()
{
	if(haveInput)
		train(ArrayInput);
	else
		cout<<"Please set input vectors for program."<<endl;
}
#pragma endregion

#pragma region test(string,double*, double*)
void FuzzyArt::test(string filePath,double* ia,double* label)
{
	ofstream outputfile;
	outputfile.open(filePath.c_str());
	if(!outputfile.is_open())
	{
		cout<<"Cant open file "<<filePath<<endl;
		return;
	}

	double activation,temp,weightSum;
	int num=0;

	transformInputs(ia);

	for(int i=0; i<INPUTNUMBER; i++)
	{
		temp = 0.0;
		for(int j=0; j<CATEGORIES; j++)
		{
			weightSum = 0.0;
			activation = 0.0;

			for(int k=0; k<ARTDIMENSION; k++)
				weightSum+= weights[j*ARTDIMENSION+k];
			//find the biggest activation in output nodes
			for(int k=0; k<ARTDIMENSION; k++)
				activation += minimum(inputs[i*ARTDIMENSION+k],weights[j*ARTDIMENSION+k])/(alpha+weightSum); 
			if(activation>temp)
			{
				temp = activation;
				num = j;
			}

		}
		hits[num*INPUTNUMBER+i]=label[i];
	}
	int numClass1, numClass2, numTotal, numAccuracy, numFalse, class1, class2, class1tal,class2tal;
	outputfile<<"Learning Rate = "<<beta<<endl;
	outputfile<<"P = "<< P<<endl;
	outputfile<<"Categories = "<< CATEGORIES << endl;
	outputfile<<"Iterations = "<< ITERATION_NUM <<endl<<endl;
	numTotal = numAccuracy = numFalse = 0;
	class1=class2 =0;
	class1tal=class2tal=0;
	for(int i=0; i<CATEGORIES; i++)
	{
		numClass1=numClass2=0;
		if(outputs[i]==0)
			continue;
		for(int j=0; j<INPUTNUMBER; j++)
		{
			if(hits[i*INPUTNUMBER+j]!=-1)
			{
				outputfile<<hits[i*INPUTNUMBER+j]<<" ";
				if(hits[i*INPUTNUMBER+j]==1)
					numClass1++;
				else
					numClass2++;
			}
		}
		if(numClass1!=0||numClass2!=0)
		{
			if(numClass1>numClass2)
			{
				outputfile<<"* Total number of hits:"<< numClass1+numClass2<<" This Node"<<i<<" category represent class 1."<<"TP="<<((double)numClass1/((double)numClass2+(double)numClass1))<<" FP="<<((double)numClass2/((double)numClass2+(double)numClass1));
				numAccuracy+=numClass1;
				numFalse+=numClass2;
				numTotal+=numClass1;
				numTotal+=numClass2;
				class1+= numClass1;
				class1tal+=numClass1+numClass2;
			}
			else
			{
				if(numClass1==numClass2)
				{
					numTotal+=numClass1;
					numTotal+=numClass2;
					outputfile<<"* Total number of hits:"<< numClass1+numClass2<<" on this Node"<<i;
				}
				else
				{
					numTotal+=numClass1;
					numTotal+=numClass2;
					numAccuracy+=numClass2;
					numFalse+=numClass1;
					class2 += numClass2;
					class2tal+=numClass1+numClass2;
					outputfile<<"* Total number of hits:"<< numClass1+numClass2<<" This Node"<<i<<" category represent class 2."<<"TP="<<((double)numClass2/((double)numClass2+(double)numClass1))<<" FP="<<((double)numClass1/((double)numClass2+(double)numClass1));
				}
			}
		}
		outputfile<<endl;
	}

	outputfile<<"The accuracy for this ART system is: " <<(double)numAccuracy/(double)numTotal<<endl;
	outputfile<<"The FPR for this ART system is: " <<(double)numFalse/(double)numTotal<<endl;
	outputfile<<(double)class1/(double)class1tal<<"%"<<(double)class2/(double)class2tal<<endl;
	outputfile.close();
}
#pragma endregion

#pragma endregion

#endif
#pragma endregion
