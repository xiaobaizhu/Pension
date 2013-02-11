

#include "Helpers.h"
#include<vector>
namespace InterestRateModels
{
double Mean (vector<double>& numbers)
{
	double sum = 0;
	int size = numbers.size();
	for (int i = 0; i <size; i ++)
	{
		sum += numbers[i];
	}
	return sum/size;
}


double variance (vector<double> & numbers, double mean)
{
	double sum = 0;
	int size = numbers.size();
	for (int i = 0; i <size; i ++)
	{
		sum += (numbers[i]-mean)*(numbers[i]-mean);
	}
	return sum/(size-1)/size;
}
}
