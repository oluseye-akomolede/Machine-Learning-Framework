#pragma once
#include "Framework.h"
#include "nn_layer.h"
#include "input_layer.h"
#include "activation_layer.h"
#include "output_layer.h"
#include "linear_layer.h"

class NeuralNetwork
{
public:
	NeuralNetwork();
	virtual void initialize();
	matrix forward(matrix input);
	void backward(matrix y_data, float alpha, float beta);
	void train(matrix input, matrix y_data, float alpha, float beta);
	float evaluate(matrix input, matrix y_data);

protected:
	std::vector<matrix> update_vec_m;
	std::vector<int> update_vec_i;
	std::vector<input_layer*> input_layers;
	output_layer* output_layer_out;
	std::vector<nn_layer*> internal_queue;
	bool first_run;
	bool first_update_run;
};
