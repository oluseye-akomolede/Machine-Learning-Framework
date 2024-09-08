#include "NN_test.h"
NN_test::NN_test()
{
	input1 = new input_layer(784, 784);
	lin_layer = new linear_layer(784, 300, true, false);
	act_layer = new activation_layer(300, 300, act_function_type::Leaky_ReLU);
	lin_layer2 = new linear_layer(300, 300, true, false);
	act_layer2 = new activation_layer(300, 300, act_function_type::Hard_Tanh);
	lin_layer3 = new linear_layer(300, 10, true, false);

	output1 = new output_layer(10, 10, loss_function_type::Cross_Entropy);

	input_layers.insert(input_layers.end(), input1);
	output_layer_out = output1;

	lin_layer3->insert_before((nn_layer*)output1);
	act_layer2->insert_before((nn_layer*)lin_layer3);
	lin_layer2->insert_before((nn_layer*)act_layer2);
	act_layer->insert_before((nn_layer*)lin_layer2);
	lin_layer->insert_before((nn_layer*)act_layer);
	input1->insert_before((nn_layer*)lin_layer);
}