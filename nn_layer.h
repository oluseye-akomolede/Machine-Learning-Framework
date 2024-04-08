#pragma once
#include "Framework.h"


enum layer_type {activation,input,linear,output};
class nn_layer
{
public:
	nn_layer();
	matrix get_input_vector();
	matrix get_output_vector();
	matrix get_error_vector();

	int get_input_size();
	int get_output_size();

	layer_type get_layer_type();
	std::vector<int> get_to_input_layer();
	void insert_before(nn_layer* in);
	void insert_after(nn_layer* in);

	std::vector<nn_layer*> get_prev();
	std::vector<nn_layer*> get_next();
	

	virtual matrix forward(matrix in_vec);
	virtual matrix backward(matrix in_vec, float alpha, float beta);
	virtual void initialize(int num_inputs, int num_outputs);

protected:
	layer_type type;
	int input_size;
	int output_size;
	int error_size;

	matrix input_vector;
	matrix output_vector;
	matrix error_vector;

	std::vector<int> to_input_layer;
	std::vector<nn_layer*> next;
	std::vector<nn_layer*> prev;




	
};
