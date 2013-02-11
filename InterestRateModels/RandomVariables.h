
#define _USE_MATH_DEFINES
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>


using namespace std;
namespace InterestRateModels
{
class rv_normal
{
private:
	double mean;
	double sd;
	double * values;
	boost::lagged_fibonacci607 generator;
	boost::normal_distribution<double> nd;

public :
	rv_normal(double m, double s);
	double * generate_n (int n);
	double generate();
};

//drt = a(b-rt)dt + ¦ÒdW.
class Vasicek_Model
{
	
private:
	double alpha;
	double beta;
	double sigma;
    double r0;
	double * values;
	double A;
	double B;
	
	//double Generate_Step (double T, int steps);
public:
	double Generate_Step (double dt, double r, rv_normal& nd);
	Vasicek_Model (double a, double b, double s, double r);
	double* Generate_Path(double T, int steps);
	double price (double start, double length, double r = 0);
	void set_AB (double start, double end);
	vector<double> Vasicek_Model::Generate_Paths (double T, int steps);
};


class Hull_White
{
private:
	double beta;
	double sigma;
	double r0;
	
public:
	Hull_White (double b, double s, double r);
	vector<double> Generate_Path(double dt, int steps, vector<double> fm);
	double Price (double r, double T, double t, double Pm0, double Pmt, double fmt);
};
}
