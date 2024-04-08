#include "input_layer.h"

input_layer::input_layer(int num_inputs, int num_outputs)
{
	input_size = num_inputs;
	output_size = num_outputs;
	error_size = num_outputs;
	type = layer_type::input;

	matrix inp(num_inputs, 1);
	matrix outp(num_outputs, 1);
	input_vector = inp;
	output_vector = outp;

}

matrix input_layer::forward(matrix in_vec)
{
	
	input_vector = in_vec;
	output_vector = in_vec;
	return in_vec;

}