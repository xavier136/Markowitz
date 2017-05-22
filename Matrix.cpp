#include "Matrix.h"
#include <cmath>

Vector operator*(const Matrix& C,const Vector& V)
{
   int d = C.size();
   Vector W(d);
   for (int j=0; j<d; j++)
   {
      W[j]=0.0;
      for (int l=0; l<d; l++) W[j]=W[j]+C[j][l]*V[l];
   }
   return W;
}

Vector operator+(const Vector& V,const Vector& W)
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = V[j] + W[j];
   return U;
}

Vector operator+(const double& a,const Vector& V)
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = a + V[j];
   return U;
}

Vector operator*(const double& a,const Vector& V)
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = a*V[j];
   return U;
}

Vector operator*(const Vector& V,const Vector& W)
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = V[j] * W[j];
   return U;
}

Vector exp(const Vector& V)
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = exp(V[j]);
   return U;
}

double operator^(const Vector& V,const Vector& W)
{
   double sum = 0.0;
   int d = V.size();
   for (int j=0; j<d; j++) sum = sum + V[j]*W[j];
   return sum;
}

Matrix product(const Matrix& A, const Matrix& B)
{
	int d = A.size();
	int c = B[0].size();
	Matrix W(d, Vector(d));
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < d; j++)
		{
			W[j][i] = 0.0;
			for (int l = 0; l<d; l++) W[j][i] = W[j][i] + A[j][l] * B[l][i];
		}
	}
	return W;
}

Matrix vectorTranspose(const Vector& V)
{
	int d = V.size();
	Matrix M(d, Vector(1));
	for (int i = 0; i < d; i++) M[i][0] = V[i];
	return M;
}