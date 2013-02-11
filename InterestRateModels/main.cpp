

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
	prove_week_1();
	//inspect_spot_rate_Hull_White();
	//ShortRate_BondPrice();



	//Testing_1_HullWhite_Week_1();
	//Black_Schole black (0.08, 0, 0.3, 40);
	//options o = call;
	//vector<double> prices(black.ListOfPrice(0.25, 1000000, o, 40));
	//cout<<"finish"<<endl;
	//double mean = Mean(prices);
	//cout<<mean<<endl;
	//cout<<sqrt(variance(prices, mean))<<endl;
	//clock_t start, end;

	//double m [size] = {0.25,0.5,1,2,5, 10};
	//
	//double y [size] = {0.055,0.0576,0.0612,0.0644,0.0658, 0.0666};

	//double m[size] = {1.0/12,0.25,0.5,1,2,3,5,7, 10, 20, 30};
	//double y[size] = {0.04/100,0.07/100,0.11/100,0.15/100,0.27/100,0.39/100,0.81/100, 1.3/100, 1.91/100, 2.68/100, 3.08/100};

	//function<double(double)> f = instantaneous_forward_rates(m,y,size);

	//double dt = 1.0/12;
	//double * t = new  double[(int) m[size-1] * 12 + 1];
	//for (int i =0; i<(int) m[size-1] * 12 + 1; i++)
	//{
	//	t [i] = f(dt * i);
	//}
	//Hull_White w(0.18171718, 0.01759183,y[0]);
	//double *bond_prices = new double [(int) m[size-1] * 12 + 1];
	//function<double(double)> mp = market_price(m,y,size);
	//for (int j = 0; j<(int) m[size-1] * 12 + 1; j++)
	//{
	//	double start_time = double(j) / 12;
	//	bond_prices[j] = mp(start_time);

	//}
	//mp(double(11)/12);
	//WriteToFiles("F:\\coop\\bond_prices.txt", bond_prices, (int) m[size-1] * 12 + 1);
	//double *p[361];
	//double *pr = new double[61*path];
	////start=clock();
	//for (int k = 0 ; k<path; k++)
	//{
	//	p[k] = w.Generate_Path(dt,(int) m[size-1] * 12 + 1, t);
	//	for (int i = 0; i<61; i++)
	//	{
	//		double start_time = double(i) / 12;
	//		if (i==60)
	//		{
	//			//cout<<p[k][i]<<"  "<<bond_prices[i+60]<<endl;
	//		}
	//		pr[i + 61 * k] = w.Price(p[k][i], start_time + 5, start_time, bond_prices[i+60], bond_prices[i], t[i]);
	//		//cout<<pr[i+path*k]<<"   "<<i+path*k<<endl;
	//	}
	//}

	//end=clock();
	//cout<<end-start<<endl;
	//Vasicek_Model model (0.5,0.05,0.05,0.04);
	//double prices [61*5];
	////start = clock();
	//double rates [61*5];

	//for (int k = 0; k<5; k++)
	//{
	//	double * c = model.Generate_Path(5, 60);
	//	for (int i = 0; i < 61; i++)
	//	{
	//		double j = double(i)/12;
	//		prices[i+61*k] = model.price (j, 5, c[i]);
	//		cout<<prices[i]<<"   "<<c[i]<<endl;
	//		rates [i + 61*k] = c[i];
	//	}
	//}
	//CSVFile("C:\\Users\\Mike\\Desktop\\coop\\bla.txt", prices, 61, 5);
	//CSVFile("C:\\Users\\Mike\\Desktop\\coop\\bla1.txt", rates, 61, 5);
	//end=clock();*/

	//WriteToFiles("F:\\coop\\instantaneous.txt", t, (int) m[size-1] * 12 + 1);
	//CSVFile("F:\\coop\\short_rate.txt", p,path, 61);
	//CSVFile("F:\\coop\\price_paths.txt", pr,61,path);
	////cout<<end-start<<endl;

	system("pause");
	return 0;
}









