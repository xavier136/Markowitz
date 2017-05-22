#ifndef Markowitz_h
#define Markowitz_h
#include "Matrix.h"

using namespace std;

class Markowitz
{
	public:
		Markowitz(double epsilon_, int iter_) { epsilon = epsilon_; max_iteration = iter_; };
		double get_epsilon() { return epsilon; };
		int get_iter() { return max_iteration; };
		Matrix gradientMethod(Matrix& covar_mat, Vector& returns);
		double test();

	private:
		double epsilon;
		int max_iteration;

};

#endif
