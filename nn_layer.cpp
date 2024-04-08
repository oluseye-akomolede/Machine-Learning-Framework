#include "nn_layer.h"

nn_layer::nn_layer()
{

}
matrix nn_layer::get_input_vector()
{
	return input_vector;
}
matrix nn_layer::get_output_vector()
{
	return output_vector;
}
matrix nn_layer::get_error_vector()
{
	return error_vector;
}

int nn_layer::get_input_size()
{
	return input_size;
}

int nn_layer::get_output_size()
{
	return output_size;
}

layer_type nn_layer::get_layer_type()
{
	return type;
}

std::vector<int> nn_layer::get_to_input_layer()
{
	return to_input_layer;
}

void nn_layer::insert_before(nn_layer* nextNode)
{
	next.push_back(nextNode);
	nextNode->insert_after(this);
}

void nn_layer::insert_after(nn_layer* prevNode)
{
	prev.push_back(prevNode);
}

std::vector<nn_layer*> nn_layer::get_prev()
{
	return prev;
}

std::vector<nn_layer*> nn_layer::get_next()
{
	return next;
}

matrix nn_layer::forward(matrix in_vec)
{
	matrix out(0, 0);
	return out;
}
matrix nn_layer::backward(matrix in_vec, float alpha, float beta)
{
	matrix out(0, 0);
	return out;
}
void nn_layer::initialize(int num_inputs, int num_outputs)
{

}