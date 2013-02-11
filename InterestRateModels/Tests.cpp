
#include <iostream>
#include <math.h>
#include<stdio.h>
#include <ctime>
#include "RandomVariables.h"
#include "Helpers.h"
#include "ShortRate.h"
#include "StockOption.h"
using namespace std;

namespace InterestRateModels
{
void inspect_spot_rate_Hull_White()
{
	int size = 11;
	int time = 365;
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
	double dt = 1.0/time;

	int n = 10000;

	vector<vector<double>> sprices (n, vector<double>(20,1));

	vector<vector<double>> short_rates (n, vector<double>());
	
	vector<double> simulate (n,1);

	for (int c = 0; c<n; c++)
	{
		short_rates.at(c) = w.Generate_Path(dt, time + dt, t);
		simulate.at(c) *= exp(-dt/2 * short_rates.at(c).at(0));
		for (int k = 1; k<time; k++)
		{
			simulate.at(c) *= exp(-dt * short_rates.at(c).at(k)); 
		}
		simulate.at(c) *= exp(-dt/2 * short_rates.at(c).at(time));
		//cout<<simulate.at(c) << "     " << w.Price(0.04/100, 1, 0, mp(1), mp(0), t.at(0))<<endl;
	}
	cout<<"Mean Testing"<<endl;
	cout<<Mean(simulate)<< "   " <<w.Price(0.04/100, 1, 0, mp(1), mp(0), t.at(0))<<endl;
}


void ShortRate_BondPrice()
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
	double dt = 1.0/time;

	int n = 1000;

	
	vector<vector<double>> short_rates (n, vector<double>());
	
	vector<double> simulate (n,1);


	for (int c = 0; c<n; c++)
	{
		short_rates.at(c) = w.Generate_Path(1, 2, t);
		for (int i = 1; i<2; i++)
		{
			simulate.at(c) *= w.Price(short_rates.at(c).at(i), i+1, i, mp(i+1), mp(i), f(i));
		}
		//cout<<simulate.at(c) << "     " << w.Price(0.04/100, 1, 0, mp(1), mp(0), t.at(0))<<endl;
	}
	cout<<"Mean Testing"<<endl;
	double mprice = mp(2);
	double mprice1 = mp(0);
	double instan = f(0);
	double price = w.Price(0.04/100, 2, 0, mprice, mprice1, instan) / w.Price(0.04/100, 1, 0, mp(1), mprice1, instan);
	cout<<Mean(simulate)<< "   " <<price<<endl;
}

void Testing_1_Vasicek_Week_1 ()
{
	Vasicek_Model model (0.18171718, 0.05215587, 0.01759183, 0.04/100);

	int n = 10;

	vector<double> prices(20);
	vector <vector<double>> spot_rates(n, vector<double>(20));
	double margin = 0.01;
	vector<double> face (n, 1);

	vector<vector<double>> paths (n, vector<double>(20));

	vector <double> v (n, 1);

	for (int k = 0; k<n; k++)
	{
		paths[k] = model.Generate_Paths(20, 20);
		for (int i = 0; i <20; i++)
		{
			model.set_AB(i, i+1);
			prices.at(i) = model.price(i,1,paths[k][i]);
			spot_rates[k][i] = 1/(prices.at(i)) -1;
			face[k] *= (spot_rates[k][i]+margin);
			v[k] *= (spot_rates[k][i] + margin + 1)/(spot_rates[k][i] + 1);
		}
	}

	WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\fund.txt", v);
	WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\face.txt", face);
	WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\prices.txt", prices);
	CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\paths.txt", paths);
	CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\spots.txt", spot_rates);

}

void Testing_3_Vasicek_Week_1()
{
	Vasicek_Model model (0.18171718, 0.05215587, 0.01759183, 0.04/100);
	model.set_AB(0, 1);
	cout<<model.price(0, 1, 0.04/100)<<endl;
	vector<vector<double>> paths (10000, vector<double>(12));
	vector<double> prices (10000,1);
	for (int k =0; k<10000; k++)
	{
		paths[k] = model.Generate_Paths(1, 12);
		for (int i = 0; i<12; i++)
		{
			prices[k] = prices[k] * exp (-paths[k][i] /(12));
		}
	}
	cout<<Mean(prices)<<endl;
}

void Testing_2_Vasicek_Week_1 ()
{

	vector<double> t1(10000, 1);
	vector<double> t2(10000,1);

	for (int u = 0; u<10000; u++)
	{
		Vasicek_Model model (0.18171718, 0.05215587, 0.01759183, 0.04/100);

		int n = 10;

		vector<double> prices(20);
		vector<double> prices1(20);
		vector <vector<double>> spot_rates(n, vector<double>(20));
		double margin = 0.01;
		vector<double> face (n, 1);

		vector<vector<double>> paths (n, vector<double>(240));



		vector <double> v (n, 1);

		for (int k = 0; k<n; k++)
		{
			paths[k] = model.Generate_Paths(20, 240);
			for (int i = 0; i <20; i++)
			{
				model.set_AB(i, i+1);
				double discount = 1;
				for (int j = 0; j<12; j++)
				{
					discount = discount * exp(-paths[k][i*12+j] * 1.0 /12);
				}
				prices1.at(i) = model.price(i,1,paths[k][i*12]);
				prices.at(i) = discount;
				spot_rates[k][i] = -log(discount);
				face[k] *= (spot_rates[k][i]+margin);
				v[k] *= (spot_rates[k][i] + margin + 1)/(spot_rates[k][i] + 1);
			}
		}


		for (int t = 0; t<20; t++)
		{
			t1[u] *= prices1[t];
			t2[u] *= prices[t];
		}
	}
	cout<<Mean(t1)<<endl;
	cout<<Mean(t2)<<endl;

	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\fund.txt", v);
	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\face.txt", face);
	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\prices.txt", prices1);
	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\prices1.txt", prices);
	////CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\paths.txt", paths);
	//CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\spots.txt", spot_rates);
}

void Testing_1_HullWhite_Week_1 ()
{

	int size = 11;
	double m[11] = {1.0/12,0.25,0.5,1,2,3,5,7, 10, 20, 30};
	double y[11] = {0.04/100,0.07/100,0.11/100,0.15/100,0.27/100,0.39/100,0.81/100, 1.3/100, 1.91/100, 2.68/100, 3.08/100};

	function<double(double)> f = instantaneous_forward_rates(m,y,size);
	vector<double> t ((int)m[size-1]+1);

	for (int i = 0; i<(int) m[size-1] + 1; i++)
	{
		t[i] = f(i);
	}
	function<double(double)> mp = market_price(m,y,size);

	Hull_White w(0.18171718, 0.01759183,y[0]);
	vector<double> short_rates = w.Generate_Path(1, 20, t);

	vector<double> prices (21,1);

	for (int i = 0; i<21; i++)
	{
		prices.at(i) = w.Price(short_rates.at(i), 30+i, i, mp(i+30), mp(i), t.at(i));
	}
	vector<double> srates (21, 3.08/100);



	for (int k = 0; k<21; k++)
	{
		//srates.at(k) = spot_rates(prices.at(k), 30);
	}


	vector<double> mprices (51);
	for (int i = 0; i<51; i++)
	{
		mprices.at(i) = mp(i);
	}

	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\mprices.txt", mprices);
	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\prices.txt", prices);
	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\spot_rates.txt", srates);
	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\short_rates.txt", short_rates);

}


double prove_week_1 ()
{
	int size = 11;
	int time = 365;
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
	double dt = 1.0/time;

	int n = 1000;

	vector<vector<double>> lprices (n, vector<double>(20,1));
	vector<vector<double>> sprices (n, vector<double>(20,1));

	vector<vector<double>> short_rates (n, vector<double>());
	
	vector<double> simulate (n,1);
	vector<vector<double>> equation(2, vector<double>(n,0));

	vector<double> fund(n,1);

	vector<double> temp_l (n, 1);
	vector<double> temp_d(n,1);
	for (int c = 0; c<n; c++)
	{
		short_rates.at(c) = w.Generate_Path(dt, time*20, t);
		double simulated_price = 1;
		for (int i = 0; i<20; i++)
		{
			lprices[c][i] = w.Price(short_rates[c].at(i*time), 30+i, i, mp(i+30), mp(i), t.at(i*time));
			sprices[c][i] = w.Price(short_rates[c].at(i*time), 1+i, i, mp(i+1), mp(i), t.at(i*time));
			if (i == 0)
			{
				simulated_price *= exp (- short_rates[c].at(0) * dt/2); 
			}
			else
			{
				simulated_price *= exp (- short_rates[c].at(i*time) * dt); 
			}
			for (int k = 1; k<time; k++)
			{
				simulated_price *= exp (- short_rates[c].at(i*time+k) * dt); 
			}
		}
		simulated_price *= exp (- short_rates[c].at(20 * time) * dt/2); 
		simulate[c] = simulated_price;

		/*WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\short_rates.txt", short_rates);*/
		vector<double> lsrates (20, 3.08/100);
		vector<double> ssrates (20, 0.15/100);
		double sum_rates = 0;
		double sum_difference = 0;

		double temp=1;

		for (int k = 0; k<20; k++)
		{
			lsrates.at(k) = spot_rates_continuous(lprices[c][k], 30);
			sum_rates += lsrates.at(k);
			ssrates.at(k) = spot_rates_continuous(sprices[c][k], 1);
			sum_difference += (lsrates.at(k) - ssrates.at(k));
			//cout<<lsrates.at(k)<<"   "<<ssrates.at(k)<<"   "<<sum_difference<<endl;
			temp*=exp(ssrates.at(k));
		}
		//cout<<"long : "<<exp(sum_rates)<<endl;
		//cout<<"difference : "<<exp(sum_difference)<<endl;
		//cout<<"Compare : "<<simulated_price<<"    "<<1.0/temp<<"   "<<sum_rates<<" : "<<exp(sum_rates)<<endl;
		temp_l.at(c) = exp(sum_rates);
		temp_d.at(c) = simulated_price - 1.0/temp;
		//fund[c] = fund_discrete_interest(ssrates, 0.01);
		equation[0][c] = simulated_price * exp(sum_rates);
		equation[1][c] = exp (sum_difference);
	}
	//cout<<"Funding"<<endl;
	//cout<<Mean(fund)<<endl;
	cout<<"Mean of zero bond price : "<<Mean(temp_d)<<endl;
	cout<<"Mean of long term : " << Mean(temp_l)<<endl;
	cout<<"simulated price : "<<Mean(simulate)<<"      "<<w.Price(0.04/100, 20, 0, mp(20), mp(0), t.at(0))<<endl;
	
	//CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\short_rate_paths.txt", short_rates);
	//CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\long_prices.txt", lprices);
	//CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\short_prices.txt", sprices);
	//WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\forward.txt", t);
	//CSVFile("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\equation.txt", equation);
	WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\fund.txt", fund);

	double m0=Mean(equation[0]);
	double m1=Mean(equation[1]);
    cout<<m0<<"   "<<m1<<endl;
	double v0 = variance(equation[0], m0);
	double v1 = variance(equation[1], m1);
	cout<<"Variance : "<<v0<<"   "<<v1<<endl;
	cout<<"95interval : "<<m0-1.96*sqrt(v0)<<"   "<<m0+1.96*sqrt(v0)<<endl;
	cout<<"95interval : "<<m1-1.96*sqrt(v1)<<"   "<<m1+1.96*sqrt(v1)<<endl;
	vector<double> answer (2,0);
	answer[0] = m0;
	answer[1] = m1;
	WriteToFiles("F:\\coop\\Cash Balance Plan\\Simulation\\week_1_hull_white\\answer.txt", answer);
	return 0.0;
}
}