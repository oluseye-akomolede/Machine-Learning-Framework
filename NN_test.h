#pragma once
#include "NeuralNetwork.h"
class NN_test : public NeuralNetwork
{
public:
	NN_test();
private:
	input_layer* input1;
	linear_layer* lin_layer;
	activation_layer* act_layer;
	linear_layer* lin_layer2;
	activation_layer* act_layer2;
	linear_layer* lin_layer3;
	output_layer* output1;
};
