#include "output_layer.h"

matrix column_softmax(matrix m) //softmaxes each row
{
	int rs = m.get_rows();
	int cs = m.get_columns();

	float* col_sums = new float[cs];
	matrix output;
	output.set_dims(rs, cs);

	for (int j = 0; j < cs; j++)
	{
		col_sums[j] = 0;
	}
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			col_sums[j] = col_sums[j] + (float)exp(m.get_data(i, j));
		}
	}

	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			output.set_data(i, j, (float)(exp(m.get_data(i, j) / col_sums[j])));
		}
	}

	delete[] col_sums;
	return output;
}

output_layer::output_layer(int num_inputs, int num_outputs, loss_function_type loss_func)
{
	type = layer_type::output;
	input_size = num_inputs;
	output_size = num_outputs;
	loss_function = loss_func;

	matrix inp(num_inputs, 1);
	matrix outp(num_outputs, 1);
	input_vector = inp;
	output_vector = outp;
}

matrix output_layer::forward(matrix in_vec)
{
	input_vector = in_vec;
	output_vector = column_softmax(in_vec);
	return output_vector;
}

matrix output_layer::backward(matrix y_b)
{
	switch (loss_function)
	{
	case Cross_Entropy:
		error_vector = output_vector - y_b;
		break;
	}

	return error_vector;
}