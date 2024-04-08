#include "nn_optimizer.h"

nn_optimizer::nn_optimizer()
{
	alpha = 0.9;
	beta = 0.9;
	alpha_update = -0.01;
	beta_update = -0.01;
	current_alpha = 0.9;
	current_beta = 0.9;
}

nn_optimizer::nn_optimizer(float alph, float bet, float alpha_up, float beta_up)
{
	alpha = alph;
	beta = bet;
	alpha_update = alpha_up;
	beta_update = beta_up;
	current_alpha = alpha;
	current_beta = beta;
}

void nn_optimizer::update_alpha(int timestepa)
{
	current_alpha = alpha * exp(alpha_update * timestepa);
}

void nn_optimizer::update_beta(int timestepb)
{
	current_beta = beta * exp(beta_update * timestepb);
}

void nn_optimizer::update_alpha_beta(int timestepa, int timestepb)
{
	current_alpha = alpha * exp(alpha_update * timestepa);
	current_beta = beta * exp(beta_update * timestepb);
}

float nn_optimizer::get_current_alpha()
{
	return current_alpha;
}

float nn_optimizer::get_current_beta()
{
	return current_beta;
}