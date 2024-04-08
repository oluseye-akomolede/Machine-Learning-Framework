#pragma once
#include "nn_layer.h"

class linear_layer : public nn_layer
{
public:
	linear_layer(int num_inputs, int num_outputs, bool bias, bool momentum);
	void set_momentum(bool momentum);
	matrix forward(matrix in_vec);
	matrix backward(matrix in_vec, float alpha, float beta);
private:
	bool momentum;
	matrix mom_vec;
	matrix weights;
	bool bias;
};