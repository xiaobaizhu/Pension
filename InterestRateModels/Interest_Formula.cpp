#include <math.h>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
namespace InterestRateModels
{
double yield_rate_zerobond (double price, double time)
{
	return log(1.0/price)/time;
}

double zero_bond_price (double yield, double time)
{
	return exp (-time * yield);
}


function<double (double)> instantaneous_forward_rates (double maturity[], double yields[], int n)
{
	double * a = new double[n], * b = new double[n];
	b[0] = yields[0];
	a[0] = 0;
	for (int i = 1; i <n; i++)
	{
		double c;
		c = a[i-1] * maturity[i-1] + b[i-1];
		double p1 = zero_bond_price(yields[i-1], maturity[i-1]);
		double p2 = zero_bond_price(yields[i], maturity[i]);

		a[i] = 1 / (maturity[i-1] * (maturity[i] - maturity[i-1]) - (maturity[i] * maturity[i] - maturity[i-1] * maturity[i-1])/2) * (log(p2/p1) + (maturity[i] - maturity[i-1]) * c);
		b[i] = c - a[i] * maturity[i-1];
		//cout<<a[i]<<"   "<<b[i]<<endl;
	}

	return [=](double x) 
	{
		for (int j = 0; j<n; j++)
		{
			if (x <= maturity[j])
			{
				return x*a[j] + b[j];
			}
		}
		return maturity[n-1] * a[n-1] + b[n-1];
	};
}

function<double (double)> market_price (double maturity[], double yields[], int n)
{
	double * a = new double[n], * b = new double[n];
	b[0] = yields[0];
	a[0] = 0;
	for (int i = 1; i <n; i++)
	{
		double c;
		c = a[i-1] * maturity[i-1] + b[i-1];
		double p1 = zero_bond_price(yields[i-1], maturity[i-1]);
		double p2 = zero_bond_price(yields[i], maturity[i]);

		a[i] = 1 / (maturity[i-1] * (maturity[i] - maturity[i-1]) - (maturity[i] * maturity[i] - maturity[i-1] * maturity[i-1])/2) * (log(p2/p1) + (maturity[i] - maturity[i-1]) * c);
		b[i] = c - a[i] * maturity[i-1];
		//cout<<a[i]<<"   "<<b[i]<<endl;
	}

	return [=](double x) 
	{

		if (x<=maturity[0])
		{
			return zero_bond_price(yields[0], x);
		}
		for (int i = 1; i<n; i++)
		{
			if (x<=maturity[i])
			{
				double part = exp(-a[i] * (x*x-maturity[i-1]*maturity[i-1])/2-b[i]*(x-maturity[i-1]));
				double price = zero_bond_price(yields[i-1], maturity[i-1]);
				return price * part;
			}
		}
		return zero_bond_price(yields[n-1], x);
	};
}

double spot_rates_continuous (double price, double period)
{
	return -log(price)/period;
}

double spot_rates_annual (double price, double period)
{
	//cout<<period<<"    "<<pow(1.0/price, 1.0/period)-1<<endl;
	return pow(1.0/price, 1.0/period)-1;
}

double face_amount (double f0, vector<double> srates, double margin)
{
	int n = srates.size();
	double face = f0;
	for (int i = 0; i<n; i++)
	{
		face *= exp(srates.at(i) +  margin);
	}
	return face;
}

double fund_discrete_interest (vector<double> srates, double margin, double initial)
{
	//you have the discrete interest
	int n = srates.size();
	double v = initial;
	for (int i = 0; i<n; i++)
	{
		v *= ((1 + srates.at(i) + margin)/(1+srates.at(i)));
	}
	return v;
}

double fund_continuous_interest (vector<double> srates, double margin, double initial)
{
	//you have the continuous intereset
	int n = srates.size();
	double v = initial;
	for (int i = 0; i<n; i++)
	{
		v *= ((exp(srates.at(i)) + margin)/(exp(srates.at(i))));
	}
	return v;
}

double yield_annualToContinuous (double rate)
{
	return log(1 + rate);
}
}