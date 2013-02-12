

#include <iostream>
#include <math.h>
#include<stdio.h>
#include <ctime>
#include "RandomVariables.h"
#include "Helpers.h"
#include "ShortRate.h"
#include "StockOption.h"
#include "Tests.h"
using namespace std;
using namespace InterestRateModels;

#define path 50

int main()
{
	int size = 11;
	int time = 1;
	double m[11] = {1.0/12,0.25,0.5,1,2,3,5,7, 10, 20, 30};
	double y[11] = {0.04/100,0.07/100,0.11/100,0.15/100,0.27/100,0.39/100,0.81/100, 1.3/100, 1.91/100, 2.68/100, 3.08/100};


	function<double(double)> f = instantaneous_forward_rates(m,y,size);
	vector<double> t ((int)m[size-1]*time+1);

	for (int i = 0; i<(int) m[size-1] *time+1; i++)
	{
		t[i] = f(double(i)/time);
	}
	function<double(double)> mp = market_price(m,y,size);

	Hull_White w(0.18171718, 0.01759183,y[0]);

	int n = 1;

	for (int i = 0; i<n; i++)
	{
		vector<double> short_rate = w.Generate_Path(1.0/time, 20, t);
		w.Price(short_rate.at(19), 49, 19, mp(49), mp(19), f(19));
	}
	system("pause");
	return 0;
}









