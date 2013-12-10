#include "FuzzyART.h"

#pragma region strToNum
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
#pragma endregion

#pragma region ReadIrisDataset(string, double*)
bool ReadIrisDataset(string filepath, double* outputArray)
{
	ifstream inputfile;
	inputfile.open(filepath.c_str());
	if(inputfile.is_open())
	{
		char t;
		int k = 0;
		while(!inputfile.eof())
		{
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
			outputArray[k*(INPUTDIMENSION+1)+0] = strToNum<double>(s1);
			// because of the structure of file, the 2 to 5 columns are the attributes.
			string s2(num[2]);
			outputArray[k*(INPUTDIMENSION+1)+1] = strToNum<double>(s2);
			string s3(num[3]);
			outputArray[k*(INPUTDIMENSION+1)+2] = strToNum<double>(s3);
			string s4(num[4]);
			outputArray[k*(INPUTDIMENSION+1)+3] = strToNum<double>(s4);
			string s5(num[5]);
			outputArray[k*(INPUTDIMENSION+1)+4] = strToNum<double>(s5);
			k++;
		}
		inputfile.close();
		return true;
	}
	else
		return false;

}
#pragma endregion

#pragma region  ReadBupaDataset(string, double*)
bool ReadBupaDataset(string filePath, double* outputArray)
{
	//read data from file
	ifstream inputfile;
	inputfile.open("bupa.data");
	if(inputfile.is_open())
	{
		char t;
		int k = 0;
		while(!inputfile.eof())
		{
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
			outputArray[k*(INPUTDIMENSION+1)+0] = strToNum<double>(s1);
			// because of the structure of file, the 1 to 6 columns are the attributes.
			string s2(num[0]);
			outputArray[k*(INPUTDIMENSION+1)+1] = strToNum<double>(s2);
			string s3(num[1]);
			outputArray[k*(INPUTDIMENSION+1)+2] = strToNum<double>(s3);
			string s4(num[2]);
			outputArray[k*(INPUTDIMENSION+1)+3] = strToNum<double>(s4);
			string s5(num[3]);
			outputArray[k*(INPUTDIMENSION+1)+4] = strToNum<double>(s5);
			string s6(num[4]);
			outputArray[k*(INPUTDIMENSION+1)+5] = strToNum<double>(s6);
			string s7(num[5]);
			outputArray[k*(INPUTDIMENSION+1)+6] = strToNum<double>(s7);
			k++;
		}
		inputfile.close();
		return true;
	}
	else
		return false;
}
#pragma endregion

void main()
{
#pragma region Iris
/*	
	double* IrisDatasetForTrain,* IrisDatasetForTest, * DatafromFile, *Label;
	IrisDatasetForTrain = new double[ITERATION_NUM*4];
	IrisDatasetForTest = new double[ITERATION_NUM*4];
	DatafromFile = new double[150*5];
	Label = new double[150];
	if(!ReadIrisDataset("Iris.data", DatafromFile))
		cout<<"Error reading file."<<endl;
	
	for(int i=0; i<INPUTNUMBER; i++)
	{
		Label[i] = DatafromFile[i*5];

		for(int j=0; j<INPUTDIMENSION; j++)
		{
			IrisDatasetForTrain[i*INPUTDIMENSION+j]=DatafromFile[i*5+j+1];
			IrisDatasetForTest[i*INPUTDIMENSION+j]=DatafromFile[i*5+j+1];
		}
		
	}
	FuzzyArt fuzzy(IrisDatasetForTrain);
	fuzzy.train();
	fuzzy.test("Output_Iris.dat",IrisDatasetForTest, Label);
*/	
#pragma endregion

#pragma region Bupa
	
	double* BupaDatasetForTrain,* BupaDatasetForTest, * DatafromFile, *Label;
	BupaDatasetForTrain = new double[ITERATION_NUM*INPUTDIMENSION];
	BupaDatasetForTest = new double[ITERATION_NUM*INPUTDIMENSION];
	DatafromFile = new double[345*(INPUTDIMENSION+1)];
	Label = new double[345];
	if(!ReadBupaDataset("bupa.data", DatafromFile))
		cout<<"Error reading file."<<endl;

	for(int i=0; i<INPUTNUMBER; i++)
	{
		Label[i] = DatafromFile[i*(INPUTDIMENSION+1)];

		for(int j=0; j<INPUTDIMENSION; j++)
		{
			BupaDatasetForTrain[i*INPUTDIMENSION+j]=DatafromFile[i*(INPUTDIMENSION+1)+j+1];
			BupaDatasetForTest[i*INPUTDIMENSION+j]=DatafromFile[i*(INPUTDIMENSION+1)+j+1];
		}

	}
	FuzzyArt fuzzy(BupaDatasetForTrain);
	fuzzy.train();
	fuzzy.test("Output_Bupa.dat",BupaDatasetForTest, Label);
	
#pragma endregion

}
