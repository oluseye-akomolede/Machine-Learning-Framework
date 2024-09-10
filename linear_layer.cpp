#include "linear_layer.h"

linear_layer::linear_layer(int num_inputs, int num_outputs, bool in_bias, bool in_momentum)
{
	type = layer_type::linear;
	input_size = num_inputs;
	output_size = num_outputs;
	error_size = num_outputs;
	bias = in_bias;
	momentum = in_momentum;

	matrix inp(num_inputs, 1);
	matrix outp(num_outputs, 1);
	input_vector = inp;
	output_vector = outp;
	

	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0.0, 0.05);
	if (bias == true)
	{
		weights.set_dims(output_size, input_size + 1);
		for (int i = 0; i < output_size; i++)
		{
			for (int j = 0; j < input_size + 1; j++)
			{
				weights.set_data(i, j, distribution(generator));
				//std::cout << weights.get_data(i, j) << std::endl;
			}
		}
	}
	else
	{
		weights.set_dims(output_size, input_size);
		for (int i = 0; i < output_size; i++)
		{
			for (int j = 0; j < input_size; j++)
			{
				weights.set_data(i, j, distribution(generator));
				
			}
		}
	}

}

void linear_layer::set_momentum(bool in_momentum)
{
	momentum = in_momentum;
}

matrix linear_layer::forward(matrix in_vec)
{
	if (in_vec.get_rows() != input_size)
	{
		throw("input vector sizes do not match!");
	}
	
	matrix output;

	input_vector = in_vec;
	if (bias == false)
	{
		output = weights * in_vec; //num_outpusxbatch_size = num_outputsxnum_inputs * num_inputsxbatch_size
	}
	else
	{
		matrix in_vec2;
		int rs = in_vec.get_rows();
		int cs = in_vec.get_columns();

		in_vec2.set_dims(rs + 1, cs);

		for (int i = 0; i < rs + 1; i++)
		{
			for (int j = 0; j < cs; j++)
			{
				if (i == rs)
				{
					in_vec2.set_data(i, j, (float)1.0);
				}
				else
				{
					in_vec2.set_data(i, j, in_vec.get_data(i, j));
				}
			}
		}

		output = weights * in_vec2;
	}

	output_vector = output;
	return output;
}

matrix linear_layer::backward(matrix in_vec, float alpha, float beta)
{
	if (in_vec.get_rows() != error_size)
	{
		throw("Error vector sizes do not match!");
	}
	else
	{
		error_vector = (weights.T()) * in_vec;
		matrix in_vec2;
		if (bias == true)
		{
			
			int cs = input_vector.get_columns();
			int rs = input_vector.get_rows();

			in_vec2.set_dims(rs + 1, cs);
			for (int i = 0; i < rs + 1; i++)
			{
				for (int j = 0; j < cs; j++)
				{
					if (i == rs)
					{
						in_vec2.set_data(i, j, (float)1.0);
					}
					else
					{
						in_vec2.set_data(i, j, input_vector.get_data(i, j));
					}
				}
			}

			matrix temp = error_vector;
			matrix temp2;
			int rs2 = error_vector.get_rows() - 1;
			int cs2 = error_vector.get_columns();
			temp2.set_dims(rs2, cs2);

			for (int i = 0; i < rs2; i++)
			{
				for (int j = 0; j < cs2; j++)
				{
					temp2.set_data(i, j, temp.get_data(i, j));
				}
			}

			error_vector = temp2;
			



		}
		else
		{
			in_vec2 = input_vector;
		}

		float layer_norm = (float)1.0 / (float)input_vector.get_columns();

		if (momentum == true)
		{
			matrix delta;
			delta = (in_vec * (in_vec2.T())) * ((float)(-1 * alpha * layer_norm));
			mom_vec = delta + mom_vec * beta;
			weights = (weights + mom_vec);
		}
		else
		{
			matrix delta;
			delta = (in_vec * (in_vec2.T())) * ((float)(-1 * alpha * layer_norm));
			weights = weights + delta;
		}

		return error_vector;
	}
}