
#include <math.h>
namespace InterestRateModels
{
double SalaryProject_Step (double current, double ratio)
{
	return current*ratio;
}

double* SalaryProject (double current, double ratio, double T, int n)
{
	double * projected_salaries = new double[n];
	projected_salaries[0] = current;
	for (int i= 1; i<n; i++)
	{
		projected_salaries[i] = projected_salaries[i-1] * pow(ratio, T/n);
	}
	return projected_salaries;
}

double* CashValue (double interest[], double salary[], double credit_Ratio[], int n)
{
	double* cash_balance = new double[n+1];
	cash_balance[0] = 0;
	for (int i = 0; i<n; i++)
	{
		cash_balance[i+1] = (salary[i] * credit_Ratio[i] + cash_balance[i]) * (1 + interest[i]);
	}

	return cash_balance;
}
}