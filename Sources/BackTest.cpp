#include "../Headers/BackTest.h"
#include "../Headers/Matrix.h"
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include "../Headers/csv.h"
#include <fstream>

//converts string to double
double string_to_double(const std::string& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
}

//reads data from the data csv file
void readData(double **data, string fileName)
{
	char tmp[20];
	ifstream file(strcpy(tmp, fileName.c_str()));
	Csv csv(file);
	string line;
	if (file.is_open())
	{
		int i = 0;
		while (csv.getline(line) != 0) {
			for (int j = 0; j < csv.getnfield(); j++)
			{
				double temp = string_to_double(csv.getfield(j));
				//cout << "Asset " << j << ", Return "<<i<<"="<< temp<<"\n";
				data[j][i] = temp;
			}
			i++;
		}

		file.close();
	}
	else { cout << fileName << " missing\n";exit(0); }
}

//computes the average return for each asset over a fixed period
Vector averageReturn(double **data, int window, int numberAssets)
{
	double mean = 0;
	Vector returns;
	for (int i = 0;i<numberAssets;i++)
	{
		mean = 0;
		for (int j = 0;j<window;j++)
		{
			double temp = data[i][j];
			mean = mean + temp / window;
		}

		returns.push_back(mean);
	}
	return returns;
}
//computes the variance covariance matrix of the assets over a fixed period
Matrix covarianceMatrix(double **data, int window, int numberAssets, Vector& average_returns)
{
	double covariance = 0;
	Matrix covariance_matrix(numberAssets, Vector(numberAssets));
	for (int i = 0;i<numberAssets;i++)
	{
		for (int j = 0; j < numberAssets; j++)
		{
			covariance = 0;
			for (int k = 0; k < window; k++)
			{
				double temp_1 = data[i][k];
				double temp_2 = data[j][k];

				covariance = covariance + ((temp_1 - average_returns[i]) * (temp_2 - average_returns[j])) / (window - 1);
			}
			covariance_matrix[i][j] = covariance;
		}
	}
	return covariance_matrix;
}


// retrieves the data from the csv file
void BackTest::getData()
{
	double **returnMatrix = new double*[num_assets]; // a matrix to store the return data
	//allocate memory for return data
	for (int i = 0;i< num_assets;i++)
		returnMatrix[i] = new double[num_returns];

	//read the data from the file and store it into the return matrix
	string fileName = "Resources/asset_returns.csv";
	readData(returnMatrix, fileName);
	returnData = returnMatrix;
}

// deletes the return data matrix from the memory
void BackTest::deleteData()
{
	for (int i = 0;i<num_assets;i++)
		delete[] returnData[i];
	delete[] returnData;
}

// initializes the backtest and builds the portfolios
void BackTest::initBackTest()
{
	vector<Portfolio> new_portfolios;
	for (int i = 0; i < target_returns.size(); i++)
	{
		Portfolio portfolio(target_returns[i]);
		new_portfolios.push_back(portfolio);
	}
	portfolios = new_portfolios;
}

// runs the full backTest
void BackTest::runBackTest()
{
	int start = 0;
	int finish = in_sample_size + start;

	// initializes the training data matrix
	double **training_data = new double*[num_assets]; 
	for (int i = 0;i< num_assets;i++)
		training_data[i] = new double[in_sample_size];

	// initializes the testing data matrix
	double **testing_data = new double*[num_assets];
	for (int i = 0;i< num_assets;i++)
		testing_data[i] = new double[out_sample_size];

	ofstream myfile1, myfile2;
	myfile1.open("BackTest_returns.csv");
	myfile2.open("BackTest_variances.csv");
	
	while (start <= (num_returns - in_sample_size - out_sample_size))
	{
		//builds the training dataset
		for (int j = 0; j < num_assets; j++)
		{
			for (int i = start; i < finish; i++)
			{
				training_data[j][i - start] = returnData[j][i];
			}
		}

		//builds the testing dataset
		for (int j = 0; j < num_assets; j++)
		{
			for (int i = finish; i < (finish + out_sample_size); i++)
			{
				testing_data[j][i-finish] = returnData[j][i];
			}
		}

		Vector average_training_returns = averageReturn(training_data, in_sample_size, num_assets);
		Matrix training_covar_mat = covarianceMatrix(training_data, in_sample_size, num_assets, average_training_returns);

		Vector average_testing_returns = averageReturn(testing_data, out_sample_size, num_assets);
		Matrix testing_covar_mat = covarianceMatrix(testing_data, out_sample_size, num_assets, average_testing_returns);

		Markowitz model(accuracy, iterations);

		for (int i = 0; i < portfolios.size(); i++)
		{
			//computes the weights using the in_sample data
			portfolios[i].compute_weights(model, training_covar_mat, average_training_returns);

			//computes the return and volatility using the out_sample data and weights
			portfolios[i].compute_return(average_testing_returns);
			portfolios[i].compute_volatility(testing_covar_mat);

			cout << "Portfolio " << i + 1 << " oos return : " << portfolios[i].get_return() << " oos volatility : " << portfolios[i].get_volatility() << endl;

			//saves the returns and variances into two separated csv files
			myfile1 << portfolios[i].get_return();
			myfile2 << portfolios[i].get_variance();

			if (i != (portfolios.size() - 1))
			{
				myfile1 << ",";
				myfile2 << ",";

			}
			

		}

		myfile1 << endl;
		myfile2 << endl;


		cout << "------------------------------------------" << endl;
		
		start += 12;
		finish = in_sample_size + start;
	}

	//deletes training dataset
	for (int i = 0;i<num_assets;i++)
		delete[] training_data[i];
	delete[] training_data;

	//deletes testing dataset
	for (int i = 0;i<num_assets;i++)
		delete[] testing_data[i];
	delete[] testing_data;

	//close files
	myfile1.close();
	myfile2.close();


}

