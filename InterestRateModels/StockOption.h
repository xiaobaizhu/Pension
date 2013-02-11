#include<vector>

using namespace std;
namespace InterestRateModels
{
enum options
{
	call = 1,
	put = 2
};

class Black_Schole
{
private:
	double rate;
	double delta;
	double sigma;
	double S0;
public:
	Black_Schole(double r, double d, double s, double initial);
	vector<double> ListOfPrice (double T, int n, options o, double K);
	
};}

