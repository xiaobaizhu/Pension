
#include "RandomVariables.h"

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

using namespace std;

//drt = a(b-rt)dt + ¦ÒdW.
namespace InterestRateModels
{
//
Vasicek_Model::Vasicek_Model(double a, double b, double s, double r)
{
	alpha = a;
	beta = b;
	sigma = s;
	r0 = r;
	A = 0;
}

double Vasicek_Model::price (double start, double length, double r )
{
	if (length = 0)
	{
		return 1;

	}
	if (A == 0)
	{
		set_AB (start, start +length);
		r = r0;
	}
    return A * exp (- B * r);
	
}

double Vasicek_Model::Generate_Step (double dt, double r, rv_normal& nd)
{
	double rv = nd.generate();
	return rv * sigma * sqrt((1-exp(-2*alpha*dt))/(2*alpha)) + exp (-alpha *dt) * r + beta * (1 - exp(-alpha *dt));
}

double * Vasicek_Model::Generate_Path (double T, int steps)
{
	double * values = new double [ steps + 1 ];
	values [0] = r0;
	rv_normal nd (0,1);
	double dt = T/steps;
	for (int i = 1; i<steps+1; i++)
	{
		values [i] = Generate_Step(dt, values[i-1], nd);
	}
	return values;
}

vector<double> Vasicek_Model::Generate_Paths (double T, int steps)
{
	vector<double> values (steps + 1);
	values [0] = r0;
	rv_normal nd (0,1);
	double dt = T/steps;
	for (int i = 1; i<steps+1; i++)
	{
		values [i] = Generate_Step(dt, values[i-1], nd);
	}
	return values;
}

void Vasicek_Model::set_AB (double start, double end)
{
	B = 1/alpha * ( 1 - exp (- alpha * (end - start)));
	A = exp ( (beta - sigma * sigma / (2 * alpha * alpha)) * ( B - end + start) - sigma * sigma / (4*alpha) * B * B);
}
}

