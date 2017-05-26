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
	int window = 100;
	int numberAssets = 83;
	int numberReturns = 700;
	int testing_window = 12;
	double accuracy = 0.000001;
	int max_iter = 200000;
    
	//list of target returns
	Vector v;
	v.push_back(0.0);
	v.push_back(0.05);
	v.push_back(0.1);

	//BackTest Execution
	BackTest backtest(numberAssets, numberReturns, window, testing_window, v, accuracy , max_iter);
	backtest.getData();
	backtest.initBackTest();
	backtest.runBackTest();
  	backtest.deleteData();
   
	return 0;
}



