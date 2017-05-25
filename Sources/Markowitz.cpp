#include "../Headers/Markowitz.h"
#include <iostream>

using namespace std;

Vector Markowitz::gradientMethod(Matrix& covar_mat, Vector& returns, double target)
{
	double d = covar_mat.size();
	double e = d + 2;
	Matrix Q = Matrix(e, Vector(e));

	//Builds the Q matrix
	for (int i = 0; i < e; i++) 
	{
		for (int j = 0; j < e; j++)
		{
			if (i >= d && j >= d)
			{
				Q[i][j] = 0;
			}
			else if (j == d && i < d)
			{
				Q[i][j] = -1 * returns[i];
			}
			else if (j == (d + 1) && i < d)
			{
				Q[i][j] = -1;
			}
			else if (i == (d + 1) && j < d)
			{
				Q[i][j] = -1;
			}
			else if (i == d && j < d)
			{
				Q[i][j] = -1 * returns[j];
			}
			else 
			{
				Q[i][j] = covar_mat[i][j];
			}
		}
	}

	//Builds the B vector
	Vector B(Q.size());

	for (int i = 0; i < d; i++) B[i] = 0;
	B[d] = -target;
	B[d + 1] = -1;

	//Builds initial point X0: in this case equally weighted portfolio
	Vector X0(Q.size());
	
	for (int i = 0; i < d; i++) X0[i] = 1/d;
	X0[d] = 1;
	X0[d + 1] = 1;

	// Builds the initial S0 and P0
	Vector S0 = B - (Q * X0);
	Vector P0 = S0;

	//runs the optimisation
	Vector Solution = S0 * vectorTranspose(S0);
	int iteration = 0;
	double Alphak = 0.0;
	double Betak = 0.0;

	while (Solution[0] > epsilon)
	{
		Alphak = Solution[0] / (P0 * (Q * vectorTranspose(P0)))[0];
		X0 = X0 + Alphak * P0;
		S0 = S0 - Alphak * (Q * P0);
		Betak = (S0 * vectorTranspose(S0))[0] / (Solution[0]);
		P0 = S0 + Betak * P0;
		Solution = S0 * vectorTranspose(S0);
		iteration++;
		if (iteration == max_iteration)
		{
			cout << "Algorithm didn't converge try increasing the maximum number of iterations" << endl;
			break;
		}
	}


	return X0;
}
