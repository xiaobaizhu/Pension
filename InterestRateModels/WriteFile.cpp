
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
namespace InterestRateModels
{
void WriteToFiles(string name, vector<double> numbers)
{
	ofstream myfile;
	myfile.open (name);
	int size = numbers.size();
	for (int i= 0; i < size; i++)
	{
		myfile<<numbers.at(i)<<"\n";
	}
	myfile.close();
}


void WriteToFiles(string name, double numbers [], int n)
{
	ofstream myfile;
	myfile.open (name);
	for (int i= 0; i < n; i++)
	{
		myfile<<numbers[i]<<"\n";
	}
	myfile.close();
}

void CSVFile (string name, double numbers [], int col, int row)
{
	ofstream myfile;
	myfile.open (name);
	for (int i= 0; i < col; i++)
	{
		for (int k = 0; k<row; k++)
		{
			myfile<<numbers[k*col + i];
			if (k != row-1)
			{
				myfile<<",";
			}
		}
		myfile<<"\n";
	}
	myfile.close();
}

void CSVFile (string name, double * numbers [], int paths, int n)
{
	ofstream myfile;
	myfile.open (name);
	for (int i= 0; i < n; i++)
	{
		for (int k = 0; k<paths; k++)
		{
			myfile<<numbers[k][i];
			if (k != paths-1)
			{
				myfile<<",";
			}
		}
		myfile<<"\n";
	}
	myfile.close();
}

void CSVFile (string name, vector<vector<double>> paths)
{
	ofstream myfile;
	myfile.open (name);
	int npath = paths.size();
	int n = paths[0].size();
	for (int i = 0; i<n; i++)
	{
		for (int k = 0; k<npath; k++)
		{
			myfile<<paths[k][i];
			if (k != npath-1)
			{
				myfile<<",";
			}
		}
		myfile<<"\n";
	}
	myfile.close();
}
}