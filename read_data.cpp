#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "csv.h"
#include "Matrix.h"
#include "Portfolio.h"
#include "Markowitz.h"
#include <cstring>
#include <iostream>
#include <vector>

using namespace std; 

//g++ -c read_data.cpp
// g++ -c csv.cpp
// g++ -o portfolioSolver csv.o read_data.o
// ./portfolioSolver


double string_to_double( const std::string& s );
void readData(double **data,string fileName);

Vector averageReturn(double **data, int window, int numberAssets);
Matrix covarianceMatrix(double **data, int window, int numberAssets, Vector& average_returns);

int  main (int  argc, char  *argv[])
{
    
    int numberAssets=83;
    int numberReturns=700;
	int window = 100;
	double **returnMatrix=new double*[numberAssets]; // a matrix to store the return data
    //allocate memory for return data
    for(int i=0;i<numberAssets;i++)
		returnMatrix[i]=new double[numberReturns];
	
    //read the data from the file and store it into the return matrix
    string fileName="asset_returns.csv";
	readData(returnMatrix,fileName);
	// returnMatrix[i][j] stores the asset i, return j value
	
	Vector returns = averageReturn(returnMatrix, window, numberAssets);
	Matrix covar_mat = covarianceMatrix(returnMatrix, window, numberAssets, returns);

	Markowitz model(0.01, 100000);
	Matrix Q = model.gradientMethod(covar_mat, returns);


	cout << "La matrice est de taille: " << Q.size() << endl;

	Portfolio portfolio(0.1);
	cout << "Portfolio's target return: " << portfolio.get_target_return() << endl;
    
    for(int i=0;i<numberAssets;i++)
		delete[] returnMatrix[i];
	delete[] returnMatrix;
   
	return 0;
}


double string_to_double( const std::string& s )
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
} 

void readData(double **data,string fileName)
{
	char tmp[20];
	ifstream file (strcpy(tmp, fileName.c_str()));
	Csv csv(file);
	string line;
	if (file.is_open())
	{
		int i=0;
		while (csv.getline(line) != 0) {
         	for (int j = 0; j < csv.getnfield(); j++)
            {
               double temp=string_to_double(csv.getfield(j));
               //cout << "Asset " << j << ", Return "<<i<<"="<< temp<<"\n";
               data[j][i]=temp;
            }
            i++;
		}
		
		file.close();
	}
	else {cout <<fileName <<" missing\n";exit(0);}
}

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

Matrix covarianceMatrix(double **data, int window, int numberAssets, Vector& average_returns)
{
	double covariance = 0;
	Matrix covariance_matrix(numberAssets, Vector(numberAssets));
	for (int i = 0;i<numberAssets;i++)
	{
		for (int j = 0; j < numberAssets; j++)
		{
			covariance = 0;
			for (int k = 0; k < window ; k++)
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
                                                                    
