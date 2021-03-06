#ifndef Portfolio_h
#define Portfolio_h

#include <vector>
#include "../Headers/Matrix.h"
#include "../Headers/Markowitz.h"

using namespace std;

class Portfolio
{
public:
	Portfolio(double target) { portfolio_target_return = target; };
	void compute_return(Vector& returns);
	void compute_volatility(Matrix& covar_mat);
	void compute_weights(Markowitz& model, Matrix& covar_mat, Vector& returns);
	double get_return() { return portfolio_return; }
	double get_volatility() { return portfolio_volatility; }
	double get_variance() { return portfolio_volatility * portfolio_volatility; }
	double get_target_return() { return portfolio_target_return; }
	Vector get_weights() { return portfolio_weights; }
	
private:
	double portfolio_return;
	double portfolio_volatility;
	double portfolio_target_return;
	Vector portfolio_weights;

};

#endif
