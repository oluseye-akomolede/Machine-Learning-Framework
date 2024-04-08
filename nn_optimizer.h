#pragma once
#include <random>
class nn_optimizer
{
public:
	nn_optimizer();
	nn_optimizer(float alph, float bet, float alpha_up, float beta_up);
	void update_alpha(int timestepa);
	void update_beta(int timestepb);
	void update_alpha_beta(int timestepa, int timestepb);
	float get_current_alpha();
	float get_current_beta();
private:
	float alpha;
	float beta;
	float alpha_update;
	float beta_update;
	float current_alpha;
	float current_beta;
};
