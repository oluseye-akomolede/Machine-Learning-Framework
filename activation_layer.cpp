#include "activation_layer.h"

activation_layer::activation_layer(int num_inputs, int num_outputs, act_function_type func_type)
{
	type = layer_type::activation;
	input_size = num_inputs;
	output_size = num_outputs;
	function_type = func_type;

	matrix inp(num_inputs, 1);
	matrix outp(num_outputs, 1);
	input_vector = inp;
	output_vector = outp;
	
}

matrix activation_layer::forward(matrix in_vec)
{
	matrix output;
	switch (function_type)
	{
	case Sigmoid:
		output = sigm(in_vec);
		break;
	case Tanh:
		output = m_tanh(in_vec);
		break;
	case ReLU:
		output = relu(in_vec);
		break;
	case Leaky_ReLU:
		output = leaky_relu(in_vec);
		break;
	case Hard_Tanh:
		output = hard_tanh(in_vec);
		break;
	default:
		throw("Incorrect activation function specified");
		break;

	}

	input_vector = in_vec;
	output_vector = output;
	return output;
}

matrix activation_layer::backward(matrix in_vec)
{
	matrix output;
	switch (function_type)
	{
	case Sigmoid:
		output = (in_vec) ^ (output_vector) ^ (((output_vector * (float)-1.0) + (float)1));
		break;
	case Tanh:
		output = (in_vec) ^ (((output_vector^output_vector)*(float)-1 + (float)1));
		break;
	case ReLU:
		output = (in_vec) ^ (diff_relu(input_vector));
		break;
	case Leaky_ReLU:
		output = (in_vec) ^ (diff_leaky_relu(input_vector));
		break;
	case Hard_Tanh:
		output = (in_vec) ^ (diff_hard_tanh(input_vector));
		break;
	default:
		throw("Incorrect activation function specified!");

	}

	error_vector = output;
	return output;
}