#pragma once
#include "nn_layer.h"

enum act_function_type { ReLU = 0, Tanh = 1, Sigmoid = 2, Leaky_ReLU = 3, Hard_Tanh = 4};
class activation_layer : public nn_layer
{
public:
	activation_layer(int num_inputs, int num_outputs, act_function_type func_type);
	matrix forward(matrix in_vec);
	matrix backward(matrix in_vec);
private:
	act_function_type function_type;
};


