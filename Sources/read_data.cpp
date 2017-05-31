#include "../Headers/csv.h"
#include "../Headers/Matrix.h"
#include "../Headers/Portfolio.h"
#include "../Headers/Markowitz.h"
#include "../Headers/BackTest.h"
#include <iostream>
#include <vector>

using namespace std; 

int  main (int  argc, char  *argv[])
{
	//initial parameters
	int window = 100;
	int numberAssets = 83;
	int numberReturns = 700;
	int testing_window = 12;
	double accuracy = 0.00001;
	int max_iter = 200000;
    
	//list of target returns
	Vector targets;
	for (double k = 0; k <= 0.1000008; k += 0.0052632) // 0.1/19 roughly equals 0.0052632
	{
		if (k == 0.1000008)
		{
			targets.push_back(0.1); //makes sure that the last target return is 0.1
		}
		else 
		{
			targets.push_back(k);
		}
	}
	
	//BackTest Execution
	BackTest backtest(numberAssets, numberReturns, window, testing_window, targets, accuracy , max_iter);
	backtest.getData();
	backtest.initBackTest();
	backtest.runBackTest();
  	backtest.deleteData();
   

	return 0;
}



