#pragma once
#include "nn_layer.h"

enum loss_function_type {Cross_Entropy};
class output_layer : public nn_layer
{
public:
	output_layer(int num_inputs, int num_outputs, loss_function_type loss_func);
	matrix forward(matrix in_vec);
	matrix backward(matrix y_b);
private:
	loss_function_type loss_function;
};
