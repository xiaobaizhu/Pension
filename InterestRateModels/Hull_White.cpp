
#include "RandomVariables.h"


namespace InterestRateModels
{

	Hull_White::Hull_White (double b, double s, double r)
	{
		beta = b;
		sigma = s;
		r0 = r;
	}
	vector<double> Hull_White::Generate_Path(double dt, int steps, vector<double> fm)
	{
		vector<double> rate (steps + 1);
		double * alphat = new double[steps + 1];
		rate.at(0) = r0;
		alphat[0] = fm.at(0);
		rv_normal nd(0,1);
		for (int i = 1 ; i < steps + 1; i++)
		{
			double normal = nd.generate();
			alphat [i] = fm.at(i) + (sigma*sigma/(2*beta*beta))*pow((1-exp(-beta*dt*i)),2);
			rate.at(i) = rate.at(i-1) * exp(-beta*dt) + alphat[i]-alphat[i-1] *exp (-beta*dt) + sqrt((sigma*sigma/(2*beta))*(1-exp(-2*beta*dt)))*normal;
		}
		return rate;
	}

	double Hull_White::Price(double r, double T, double t, double Pm0, double Pmt, double fmt)
	{
		double price;
		if (T-t== 0)
		{
			return 1;
		}
		double B = 1/beta*(1-exp(-beta * (T-t)));
		double A = Pm0/Pmt * exp (B * fmt - sigma*sigma/(4*beta)*(1-exp(-2*beta*t))*B*B);
		price = A*exp(-B*r);
		return price;
	}


}