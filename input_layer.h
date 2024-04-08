#pragma once
#include "nn_layer.h"

class input_layer: public nn_layer
{
public:
	input_layer(int num_inputs, int num_ouputs);
	matrix forward(matrix in_vec);
private:

};
