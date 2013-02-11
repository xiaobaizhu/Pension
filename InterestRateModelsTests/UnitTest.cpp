#include	<stdio.h>
#include "stdafx.h"
#include "RandomVariables.h"
#include "Helpers.h"
#include "ShortRate.h"
#include "StockOption.h"
#include <functional>


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace InterestRateModels;
using namespace std;

namespace InterestRateModelsTests
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestMethod1()
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
	
	w.Price(0.04/100, 1.0/12, 0, 1/1.0004, 1,f(0)).Equals(1/1.0004); 
		};
	};
}
