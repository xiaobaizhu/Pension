#include "stdafx.h"
#include "CppUnitTest.h"
#include "RandomVariables.h"
#include "Helpers.h"
#include "ShortRate.h"
#include "StockOption.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace InterestRateModels;
namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(yield_rate_zerobond(1.05, 2), 0.03);
		}

	};
}