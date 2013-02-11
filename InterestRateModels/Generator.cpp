
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include "RandomVariables.h"
#include <windows.h>
namespace InterestRateModels
{
rv_normal::	rv_normal(double m = 0, double s = 1)
	{
		mean = m;
		sd = s;
		SYSTEMTIME st;
		GetSystemTime (&st);
		generator.seed(st.wSecond*100+st.wMilliseconds);
	}

double* rv_normal::	generate_n (int n)
	{	
		values = new double[n];
		for (int i = 0; i<n; i++)
		{
			values[i] = nd(generator) * sd + mean;
		}
		return values;
	}
double rv_normal::generate()
{
	return nd(generator) * sd + mean;
}
}