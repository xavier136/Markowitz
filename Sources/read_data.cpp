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
    
	Vector v;
	v.push_back(0.0);
	v.push_back(0.05);
	v.push_back(0.1);

	BackTest backtest(83, 700, 100, 12, v);
	backtest.getData();
	backtest.initBackTest();
	double **returnMatrix = backtest.get_returnData();
	backtest.runBackTest();

	//cout << "Method 2: " << returnMatrix[0][0] << endl;

	
	//Vector returns = averageReturn(returnMatrix, window, numberAssets);
	//Matrix covar_mat = covarianceMatrix(returnMatrix, window, numberAssets, returns);
	Markowitz model(0.000001, 200000);	
	Portfolio portfolio(0.2);
	//portfolio.compute_weights(model, covar_mat, returns);
	//portfolio.compute_volatility(covar_mat);
	//portfolio.compute_return(returns);
	//double sigma = portfolio.get_volatility();
	//double r = portfolio.get_return();
	//cout << "Portfolio's volatility: " << sigma << endl;
	//cout << "Portfolio's return: " << r << endl;

    
	backtest.deleteData();
   
	return 0;
}



