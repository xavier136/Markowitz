#ifndef Matrix_h
#define Matrix_h

#include <vector>
using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Vector operator*(const Matrix& C,const Vector& V);
Vector operator*(const double& a,const Vector& V);
Vector operator+(const double& a,const Vector& V);
Vector operator+(const Vector& V,const Vector& W);
Vector operator-(const Vector& V, const Vector& W);
Vector operator*(const Vector& V,const Vector& W);
Vector exp(const Vector& V);
Matrix operator*(const Matrix& A, const Matrix& B);
Vector operator*(const Vector& A, const Matrix& B);
Matrix vectorTranspose(const Vector& V);
double operator^(const Vector& V,const Vector& W);

#endif