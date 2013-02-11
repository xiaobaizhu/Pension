namespace InterestRateModels
{


function<double (double)> instantaneous_forward_rates (double maturity[], double yields[], int n);

function<double (double)> market_price (double maturity[], double yields[], int n);


double spot_rates_continuous (double price, double period);

double spot_rates_annual (double price, double period);

double face_amount (double f0, vector<double> srates, double margin);

double fund_discrete_interest (vector<double> srates, double margin, double initial);

double fund_continuous_interest (vector<double> srates, double margin, double initial);

double yield_annualToContinuous (double rate);
}
