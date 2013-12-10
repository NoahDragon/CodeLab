#ifndef _SOM_CLASS
#define _SOM_CLASS

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <tchar.h>

using namespace::std;

//Output is 2D
#define OUTPUT_X 30
#define OUTPUT_Y 30
#define INITIAL_WIDTH 30
#define INPUT_DIMENSIONS 5  // 6 BUPA // 4 IRIS
#define INPUT_VECTORS 345	//345 bupa data // 150 Iris Data
#define INITIAL_LEARNINGRATE 0.1
#define MAX_ITERATIONS 100
#define NO_CHANGE 5	//if winning node in network didn't change for certain amount of time, the network is stable.
#define DISTANCE_TOLERANCE 0.5

double random()
{
	srand((unsigned)time(NULL)); // random seed
	return (double)rand()/RAND_MAX;
}
template<class T>
string num2str(T i)
{
	stringstream ss;
	ss<<i;
	return ss.str();
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
	if ( ss.fail() ) 
	{
		string excep = "Unable to format ";
		excep += str;
		throw (excep);
	}
	return temp;
}

class SOM_NET
{
private:
	int outputLayer[OUTPUT_X][OUTPUT_Y];	//output
	int winnerLabel[OUTPUT_X][OUTPUT_Y];	//test how winning node discrete 
	int    iterations;
	double weights[INPUT_DIMENSIONS][OUTPUT_X*OUTPUT_Y];	//weights
	double inputlayer[INPUT_VECTORS][INPUT_DIMENSIONS];	//input
	int inputLabel[INPUT_VECTORS];	//the label in dataset
	int vector;
	double learningrate;
	double learningrateConstant;
	double width;	//initial width
	double widthConstant; 
	double activation;
	double oldActivation;	//the previous distance between nodes.
	//double distanceTolerance;
	int nochangeCount;	//how many times the map doesn't change winning node
	int    winningNode[INPUT_VECTORS][2];	//winning node in output layer
	
	void normalizeWeights();
	void normalizeInput();
	void initializeWeights();
	void initializeOutputMap();
	void initialInputLayer();
	double adjustLearningrate(int i);	//i represents for iterations
	double adjustWidth(int i);
	void initial();
	void setinitial();
	void neighborDistance(); 
	void adjustWeights();
	double gaussionFunction(int x1, int y1, int x2, int y2);


public:
	SOM_NET();
	~SOM_NET(){}

	void train();
	void exportFile(string fileadress);
 };

 SOM_NET::SOM_NET()
 {
	 initial();
	 initializeWeights();
	 initializeOutputMap();
	 initialInputLayer();
	 
 }
/*
 void SOM_NET::normalizeWeights()
 {
	 for ( int i=0; i<INPUT_VECTORS; i++)
	 {
		 double total = 0.0;
		 for ( int j=0; j<INPUT_DIMENSIONS; j++)
		 {
			for(int k=0; k<OUTPUT_X*OUTPUT_Y;k++)
				 total += weights[i][j][k] * weights[i][j][k];
			double temp = sqrt(total);
		 //for( int j=0; j<INPUT_DIMENSIONS; j++)
			for(int k=0; k<OUTPUT_X*OUTPUT_Y;k++)
				 weights[i][j][k] = weights[i][j][k] / temp;
		 }
	 }
 }
 */
 void SOM_NET::normalizeWeights()
 {
		 double total = 0.0;
		 for ( int j=0; j<OUTPUT_X*OUTPUT_Y; j++)
		 {
			 for(int k=0; k<INPUT_DIMENSIONS;k++)
				 total += weights[k][j] * weights[k][j];
			 double temp = sqrt(total);
			 //for( int j=0; j<INPUT_DIMENSIONS; j++)
			 for(int k=0; k<INPUT_DIMENSIONS;k++)
				 weights[k][j] = weights[k][j] / temp;
		 }
 }
void SOM_NET::normalizeInput()
{
	for ( int i=0; i<INPUT_VECTORS; i++)
	{
		double total = 0.0;
		for ( int j=0; j<INPUT_DIMENSIONS; j++)
		{
			total += inputlayer[i][j] * inputlayer[i][j];
		}
		double temp = sqrt(total);
		for( int j=0; j<INPUT_DIMENSIONS; j++)
		{
			inputlayer[i][j] = inputlayer[i][j] / temp;
		}      
	}
	/*
	for ( int i=0; i<INPUT_VECTORS; i++)
		for ( int j=0; j<INPUT_DIMENSIONS; j++)
			inputlayer[i][j] = inputlayer[i][j] / 100.0;
	*/
}
void SOM_NET::initializeWeights()
{
	//initialize weights
	//for (int i=0; i<INPUT_VECTORS; i++)
		for (int j=0; j<INPUT_DIMENSIONS; j++)
			for(int k=0; k<OUTPUT_X*OUTPUT_Y; k++)
				weights[j][k] = (double) rand()/RAND_MAX;
	normalizeWeights(); 
	/*//test initial weights
	ofstream initweights;
	initweights.open("initWeights.dat");
	string s ="";
	if(initweights.is_open())
	{
		for(int i=0; i<OUTPUT_X; i++)
		for (int j=0; j<OUTPUT_Y; j++)
		{
			s = "["+num2str(i)+","+num2str(j)+"]: ";
			for(int k=0; k<INPUT_DIMENSIONS; k++)
			{
				s+=num2str(weights[k][i*OUTPUT_Y+j])+" ";				
			}
			initweights<<s<<endl;
			s="";
		}
		initweights.close();
	}
	else
		cout<<"Can't open initWeights.dat file."<<endl;
		*/
}
void SOM_NET::initializeOutputMap()
{
	//initialize the output layer
	for(int i=0; i<OUTPUT_X; i++)
		for(int j=0; j<OUTPUT_Y; j++)
		{
			outputLayer[i][j] = 0;
			winnerLabel[i][j] = 0;
		}
	//winningNode[0] = 0;
	//winningNode[1] = 0;
}
// for IRIS data INPUT_DEMINTION is 4
/*void SOM_NET::initialInputLayer()
{
	//read data from file
	ifstream inputfile;
	inputfile.open("data");
	if(inputfile.is_open())
	{
		char t;
		int k = 0;
		//int j = 0;
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
			string s1(num[1]);
			inputLabel[k] = strToNum<int>(s1);
			// because of the structure of file, the 2 to 5 columns are the attributes.
			string s2(num[2]);
			inputlayer[k][0] = strToNum<double>(s2);
			string s3(num[3]);
			inputlayer[k][1] = strToNum<double>(s3);
			string s4(num[4]);
			inputlayer[k][2] = strToNum<double>(s4);
			string s5(num[5]);
			inputlayer[k][3] = strToNum<double>(s5);
			k++;
		}
		inputfile.close();
		normalizeInput();
	}
	else
		cout<<"Can't open file."<<endl;

	//test initial inputs
	ofstream initInputs;
	initInputs.open("initInputs.dat");
	string s ="";
	if(initInputs.is_open())
	{
		for(int i=0; i<INPUT_VECTORS; i++)
			//for (int j=0; j<OUTPUT_Y; j++)
			{
				s = "Label:"+num2str(inputLabel[i])+": ";
				for(int k=0; k<INPUT_DIMENSIONS; k++)
				{
					s+=num2str(inputlayer[i][k])+" ";				
				}
				initInputs<<s<<endl;
				s="";
			}
			initInputs.close();
	}
	else
		cout<<"Can't open initInputs.dat file."<<endl;
}*/


void SOM_NET::initialInputLayer() //for BUPA data INPUT_DEMINTION is 6
{
	//read data from file
	ifstream inputfile;
	inputfile.open("bupa.data");
	if(inputfile.is_open())
	{
		char t;
		int k = 0;
		//int j = 0;
		while(!inputfile.eof())
		{
			//inputfile.getline(line,25);
			t = inputfile.get();
			char *num[7];
			for(int i =0; i<7; i++)
				num[i] = new char[3];

			int j =0;
			while(t!=0x0D&&t!=0x0A) //not enter
			{
				int i =0;
				while(t!=0x2C&&t!=0x0D&&t!=0x0A&&!inputfile.eof()) //not space
				{
					num[j][i]=t;
					t = inputfile.get();
					i++;
				}
				if(t == 0x0D || t == 0x0A)
					break;
				if(t == 0x2C)
					t = inputfile.get();
				else
					break;
				j++;
			}
			string s1(num[6]);
			inputLabel[k] = strToNum<int>(s1);
			// because of the structure of file, the 1 to 6 columns are the attributes.
			string s2(num[0]);
			inputlayer[k][0] = strToNum<int>(s2);
			string s3(num[1]);
			inputlayer[k][1] = strToNum<int>(s3);
			string s4(num[2]);
			inputlayer[k][2] = strToNum<int>(s4);
			string s5(num[3]);
			inputlayer[k][3] = strToNum<int>(s5);
			string s6(num[4]);
			inputlayer[k][4] = strToNum<int>(s6);
			//string s7(num[5]);
			//inputlayer[k][5] = strToNum<double>(s7);
			k++;
		}
		inputfile.close();
		normalizeInput();
	}
	else
		cout<<"Can't open file."<<endl;
}

double SOM_NET::adjustLearningrate(int i)
{
	//adjust learning rate function
	learningrate = INITIAL_LEARNINGRATE*exp(-(double)i/learningrateConstant);
	if(learningrate<=0.0)
		exit(0);
	return learningrate;
}
double SOM_NET::adjustWidth(int i)
{
	//adjust width function
	width = INITIAL_WIDTH*exp(-(double)i/widthConstant);
	return width;
}
void SOM_NET::setinitial()
{
	//initialize all other parameters
	learningrate = (double)INITIAL_LEARNINGRATE;
	width = (double)INITIAL_WIDTH;
	iterations = 0;
	activation = 0.0;
	//oldDistance = 1000.0;
	nochangeCount = 0;
	oldActivation = 0.0;

	//weights = new double[OUTPUT_X*OUTPUT_Y*INPUT_VECTORS*INPUT_DIMENSIONS];
	//inputlayer = new double[INPUT_VECTORS*INPUT_DIMENSIONS];
	//winningNode[0] = 0;	//represent X bias in output map
	//winningNode[1] = 0;	//represent Y bias in output map
}
void SOM_NET::initial()
{
	setinitial();
	for(int i=0;i<INPUT_VECTORS;i++)
	{
		winningNode[i][0] = width/2;	//represent X bias in output map
		winningNode[i][1] = width/2;	//represent Y bias in output map
	}
	learningrateConstant = 1000;
	widthConstant = 100/log((double)INITIAL_WIDTH); 
}
double SOM_NET::gaussionFunction(int x1, int y1, int x2, int y2)
{
	int dx = x1-x2;
	int dy = y1-y2;
	return exp(-(pow((double)dx,2)+pow((double)dy,2))/(2*pow(width,2)));
}
void SOM_NET::neighborDistance()
{
	int xLow,xUp,yLow,yUp; //the neighbor range
	bool flagChange = false;
	xLow=winningNode[vector][0]-width/2;
	xUp=winningNode[vector][0]+width/2;
	yLow=winningNode[vector][1]-width/2;
	yUp=winningNode[vector][1]+width/2;
	//adjust neighbor range into output map
	if(xLow<0)	xLow=0;
	if(xUp>=OUTPUT_X)	xUp=OUTPUT_X-1;
	if(yLow<0)	yLow=0;
	if(yUp>=OUTPUT_Y)	yUp=OUTPUT_Y-1;
/*
	for(int i=xLow; i<=xUp; i++)
		for(int j=yLow; j<=yUp; j++)
		{
			if(outputLayer[i][j]!=5)
			{
				for(int k=0; k<INPUT_DIMENSIONS; k++)
					distance+=pow((inputlayer[vector][k]-weights[vector][k][i*OUTPUT_X+j]),2);
				//oldDistance = distance;	
				if(distance<oldDistance)
				{
					oldDistance = distance;
					winningNode[0] = i;
					winningNode[1] = j;
				}
			}
			distance = 0.0;
		}
		*/
	for(int i=xLow; i<=xUp; i++)
		for(int j=yLow; j<=yUp; j++)
		{
			if(outputLayer[i][j]!=5)
			{
				for(int k=0; k<INPUT_DIMENSIONS; k++)
					activation+=inputlayer[vector][k]*weights/*[vector]*/[k][i*OUTPUT_Y+j];
				//oldDistance = distance;	
				if(activation>oldActivation)
				{
					oldActivation = activation;
					winningNode[vector][0] = i;
					winningNode[vector][1] = j;
					flagChange = true;
				}
			}
			activation = 0.0;
		}
		if(flagChange == true)
			nochangeCount = 0;
		else
			nochangeCount++;
		if(iterations>0 /*&& flag == true*/)
		{
			if(width<2.0)
			{
				outputLayer[winningNode[vector][0]][winningNode[vector][1]] = 5;
				winnerLabel[winningNode[vector][0]][winningNode[vector][1]] = inputLabel[vector];
			}
		}
		//flag = false;
		/*
	if(iterations>0)
	{
		if(oldDistance<DISTANCE_TOLERANCE)
		{
			outputLayer[winningNode[0]][winningNode[1]] = 5;
			winnerLabel[winningNode[0]][winningNode[1]] = inputLabel[vector];
		}
		
		//if(iterations=MAX_ITERATIONS-1)
		//	outputLayer[winningNode[0]][winningNode[1]] = 5;
	}*/
}
void SOM_NET::adjustWeights()
{
	int xLow,xUp,yLow,yUp; //the neighbor range
	//the neighborhood between winning node
	xLow=winningNode[vector][0]-width/2;
	xUp=winningNode[vector][0]+width/2;
	yLow=winningNode[vector][1]-width/2;
	yUp=winningNode[vector][1]+width/2;
	//adjust neighbor range into output map
	if(xLow<0)	xLow=0;
	if(xUp>=OUTPUT_X)	xUp=OUTPUT_X-1;
	if(yLow<0)	yLow=0;
	if(yUp>=OUTPUT_Y)	yUp=OUTPUT_Y-1;

	for(int i=xLow; i<=xUp; i++)
		for(int j=yLow; j<=yUp; j++)
		{
			if(outputLayer[i][j]!=5)
			{
				for(int k=0; k<INPUT_DIMENSIONS; k++)
				{
					weights/*[vector]*/[k][i*OUTPUT_Y+j]+= learningrate*gaussionFunction(i,j,winningNode[vector][0],winningNode[vector][1])*(inputlayer[vector][k]-weights/*[vector]*/[k][i*OUTPUT_Y+j]);
					
					//if(weights/*[vector]*/[k][i*OUTPUT_X+j]<0.0)
					//	weights/*[vector]*/[k][i*OUTPUT_X+j] = 0.0;
					//else if(weights/*[vector]*/[k][i*OUTPUT_X+j]>1.0)
					//	weights/*[vector]*/[k][i*OUTPUT_X+j] = 1.0;
					
				}
			}
		}
	//normalizeWeights();
}
void SOM_NET::train()
{
	for(int i=0; i<INPUT_VECTORS; i++)
	{
		//iterations = 0;
		vector = i;
		while(iterations<MAX_ITERATIONS)
		{
			neighborDistance();
			adjustWeights();
			cout<<"Vectors:"<<i<<"********"<<"Iterations:"<<iterations<<"********"<<"Distance:"<<oldActivation<<"********"<<"Width:"<<width<<endl;
			//if(oldDistance<DISTANCE_TOLERANCE) break;
			if(width<2.0) break;
			iterations++;
			adjustWidth(iterations);
			adjustLearningrate(iterations);
		}
		setinitial();
	}
}
void SOM_NET::exportFile(string fileaddress)
{
	ofstream outfile,outweights;
	outfile.open(const_cast<char*>(fileaddress.c_str()));
	outweights.open("weights.dat");
	stringstream ss;
	string s = "";
	string s1 = "";
	//char* c ="";
	if(outfile.is_open()&&outweights.is_open())
	{
		for(int i=0; i<OUTPUT_X; i++)
		{
			for(int j=0; j<OUTPUT_Y; j++)
			{
				//_itot(outputLayer[i][j],c,10);
				s1 = "["+num2str(i)+","+num2str(j)+"]: ";
				for(int k=0; k<INPUT_DIMENSIONS; k++)
					s1+=num2str(weights[k][i*OUTPUT_Y+j])+" ";

				if(outputLayer[i][j] == winnerLabel[i][j])
					s += "  ";
				else
					s += /*num2str(outputLayer[i][j])+*/num2str(winnerLabel[i][j])+" ";
				outweights<<s1<<endl;
				//outfile << ss.str() << " ";
			}
			outfile<<s<<endl;
			s1="";
			s="";
		}
		outweights.close();
		outfile.close();
	}
	else
		cout<<"Can't open file."<<endl;
}
#endif
