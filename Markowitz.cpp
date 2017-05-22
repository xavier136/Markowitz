#include "Markowitz.h"
#include "Matrix.h"

using namespace std;

Matrix Markowitz::gradientMethod(Matrix& covar_mat, Vector& returns)
{
	double d = covar_mat.size();
	double e = d + 2;
	Matrix Q = Matrix(e, Vector(e));

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
	return Q;
}
