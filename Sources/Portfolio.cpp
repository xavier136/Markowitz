#include "../Headers/Portfolio.h"
#include <cmath>

//computes the optimal weights in the portfolio using the Markowitz model
void Portfolio::compute_weights(Markowitz model, Matrix covar_mat, Vector returns)
{
	int num_assets = covar_mat.size();
	Vector opt_sol = model.gradientMethod(covar_mat, returns, portfolio_target_return);
	Vector weights(num_assets);
	for (int i = 0; i < num_assets; i++) weights[i] = opt_sol[i];
	portfolio_weights = weights;
}

//computes the portfolio's volatility
void Portfolio::compute_volatility(Matrix covar_mat)
{
	Vector variance = portfolio_weights * (covar_mat * vectorTranspose(portfolio_weights));
	portfolio_volatility = sqrt(variance[0]);
}

//computes the portfolio's return
void Portfolio::compute_return(Vector returns)
{
	Vector actual_return = portfolio_weights * (vectorTranspose(returns));
	portfolio_return = actual_return[0];
}