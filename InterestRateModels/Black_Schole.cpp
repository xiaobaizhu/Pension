
#include "RandomVariables.h"
#include <vector>
#include "StockOption.h"
namespace InterestRateModels
{


Black_Schole::Black_Schole(double r, double d, double s, double initial)
{
	rate = r;
	delta = d;
	sigma = s;
	S0 = initial;
}
vector<double> Black_Schole::ListOfPrice(double T, int n, options o, double K)
{
	vector<double> prices (n);
	rv_normal nd(0,1);
	double* randoms = nd.generate_n(n);
	double deterministic = S0 * exp((rate - delta - 0.5 * sigma * sigma) * T);
	double volatility = sigma * sqrt(T);
	double discount = exp (-rate * T);
	for (int i = 0; i<n; i++)
	{
		prices[i] =  deterministic * exp (volatility*randoms[i]);
		if (o == call)
		{
			prices[i] = max (prices[i] - K, double(0));
		}
		else
		{
			prices[i]  = max (K-prices[i], double(0));
		}
		prices[i] *= discount;
	}
	return prices;
}
}