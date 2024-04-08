#include "NeuralNetwork.h"
NeuralNetwork::NeuralNetwork()
{
	first_run = true;
	first_update_run = true;
}

void NeuralNetwork::initialize()
{
	
}

matrix NeuralNetwork::forward(matrix input)
{
	//first input layer always gets the first input vector
	input_layers[0]->forward(input);
	
	if (first_run == true)
	{
		internal_queue.insert(internal_queue.end(), (nn_layer*)output_layer_out);
		int i = 0;

		while (i < internal_queue.size())
		{
			nn_layer* tempnn = internal_queue[i];
			std::vector<nn_layer*> temp_prev = tempnn->get_prev();

			int num_prev = temp_prev.size();

			for (int j = 0; j < num_prev; j++)
			{
				bool b_found = false;
				int num_curr_nodes = internal_queue.size();
				for (int k = 0; k < num_curr_nodes; k++)
				{
					if (temp_prev[j] == internal_queue[k])
					{
						b_found = true;
						break;
					}
				}

				if (b_found == false)
				{
					internal_queue.insert(internal_queue.end(), (nn_layer*)temp_prev[j]);

				}
			}

			i++;
		}

		first_run = false;
	}

	int num_nodes = internal_queue.size();
	for (int q = 0; q < num_nodes; q++)
	{
		int i = num_nodes - q - 1;
		nn_layer* temp_node = internal_queue[i];
		std::vector<nn_layer*> temp_prev = temp_node->get_prev();
		int num_prev = temp_prev.size();
		if (num_prev > 0)
		{
			matrix input_vector;

			for (int j = 0; j < num_prev; j++)
			{
				if (j == 0)
				{
					input_vector = temp_prev[j]->get_output_vector();
				}
				else
				{
					input_vector = input_vector + temp_prev[j]->get_output_vector();
				}
			}

			matrix output;
			switch (temp_node->get_layer_type())
			{
			case layer_type::linear:
				output = ((linear_layer*)temp_node)->forward(input_vector);
				break;
			case layer_type::activation:
				output = ((activation_layer*)temp_node)->forward(input_vector);
				break;
			case layer_type::output:
				output = ((output_layer*)temp_node)->forward(input_vector);
				break;
			}

			if (first_update_run == true)
			{
				std::vector<int> temp_list = temp_node->get_to_input_layer();
				int num_rec = temp_list.size();

				for (int j = 0; j < num_rec; j++)
				{
					
					update_vec_m.insert(update_vec_m.end(), output);
					update_vec_i.insert(update_vec_i.end(), temp_list[j]);
				}
			}

		}
		else
		{
			if (temp_node->get_layer_type() == layer_type::input)
			{
				//do nothing
			}
			else
			{
				throw("No previous nodes specified for a non-input layer!");
			}
		}
	}



	first_update_run = false;
	return output_layer_out->get_output_vector();
}

void NeuralNetwork::backward(matrix y_data, float alpha, float beta)
{
	int num_nodes = internal_queue.size();

	for (int i = 0; i < num_nodes; i++)
	{
		nn_layer* temp_node = internal_queue[i];
		if (temp_node->get_layer_type() == layer_type::output)
		{
			((output_layer*)temp_node)->backward(y_data);
		}
		else
		{
			std::vector<nn_layer*> temp_next = temp_node->get_next();
			int num_next = temp_next.size();

			if (num_next > 0)
			{
				matrix error_vec;
				for (int j = 0; j < num_next; j++)
				{
					if (j == 0)
					{
						error_vec = temp_next[j]->get_error_vector();
					}
					else
					{
						error_vec = error_vec + temp_next[j]->get_error_vector();
					}

					if (temp_node->get_layer_type() == layer_type::activation)
					{
						((activation_layer*)temp_node)->backward(error_vec);
					}
					else if (temp_node->get_layer_type() == layer_type::linear)
					{
						((linear_layer*)temp_node)->backward(error_vec, alpha, beta);
					}
				}
			}
			else
			{
				throw("No next nodes for a non-output node!");
			}
		}
	}
}

void NeuralNetwork::train(matrix input, matrix y_data, float alpha, float beta)
{
	//Now we update our input vectors for recurrence.
	this->forward(input);
	this->backward(y_data, alpha, beta);
	int num_updates = update_vec_m.size();
	for (int i = 0; i < num_updates; i++)
	{
		((input_layer*)input_layers[update_vec_i[i]])->forward(update_vec_m[i]);
	}


}

float NeuralNetwork::evaluate(matrix input, matrix y_data)
{
	matrix ev_output = forward(input);
	int rs = ev_output.get_rows();
	int cs = ev_output.get_columns();

	int pred_count = 0;

	for (int j = 0; j < cs; j++)
	{
		float highest_pred = -INFINITY;
		int pred_idx = 0;
		float highest_actual = -INFINITY;
		int actual_idx = 0;

		float d_out = 0;
		float y_out = 0;

		for (int i = 0; i < rs; i++)
		{
			d_out = ev_output.get_data(i, j);
			y_out = y_data.get_data(i, j);
			if (d_out > highest_pred)
			{
				highest_pred = ev_output.get_data(i, j);
				pred_idx = i;
			}
			if (y_out > highest_actual)
			{
				highest_actual = y_data.get_data(i, j);
				actual_idx = i;
			}
		}
		if (pred_idx == actual_idx)
		{
			pred_count++;
		}

	}

	return (float)pred_count / (float)cs;
}