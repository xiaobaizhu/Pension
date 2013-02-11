
#include <string>
#include<vector>
using namespace std;


namespace InterestRateModels
{
void WriteToFiles(string name, double numbers [], int n);
void CSVFile (string name, double numbers [], int col, int row);
void CSVFile (string name, double * numbers [], int paths, int n);
double Mean (vector<double>& numbers);
double variance (vector<double> & numbers, double mean);
void WriteToFiles(string name, vector<double> numbers);
void CSVFile (string name, vector<vector<double>> paths);


}