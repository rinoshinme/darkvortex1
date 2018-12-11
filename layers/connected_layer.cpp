#include "connected_layer.h"

bool ConnectedLayer::loadConfig(const LayerParam& config)
{
	std::string with_bias_str = option_find_str1(config.layer_props, "with_bias", "true");
	if (with_bias_str == "true")
		with_bias = true;
	else
		with_bias = false;

	TensorShape shape = inputs[0]->getShape();
	batch_size = shape.n;
	num_inputs = shape.c;
	num_outputs = option_find_int(config.layer_props, "outputs");

	return true;
}

void ConnectedLayer::reshape()
{
	// inputs are copied from outputs of previous layer
	outputs.resize(1);
	TensorShape shape(batch_size, num_outputs, 1, 1);
	outputs[1] = new Tensor<float>(shape);

	weights.resize(2);
	// weight
	weights[0] = new Tensor<float>(TensorShape(num_inputs, num_outputs));
	// bias
	weights[1] = new Tensor<float>(TensorShape(num_outputs));
}

void ConnectedLayer::forward()
{
	// use input and weight to calculate output

}

void ConnectedLayer::backward()
{

}

void ConnectedLayer::update(const UpdateParam& update_param)
{

}
