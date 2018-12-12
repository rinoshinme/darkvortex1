#include "connected_layer.h"
#include "../math/blas.h"
#include "../math/gemm.h"
#include "activation_layer.h"

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

	std::string activation = option_find_str(config.layer_props, "activation");

	// inlayer activation should be either linear, relu or sigmoid
	// no parameters are given
	if (activation == "relu" || activation == "linear" || activation == "sigmoid")
	{
		LayerParam param;
		param.type = LayerType::ACTIVATION;
		param.layer_props["activation"] = activation;
		activation_layer = new ActivationLayer;
		activation_layer->loadConfig(param);
	}
	else
	{
		activation_layer = NULL;
	}
	return true;
}

void ConnectedLayer::reshape()
{
	// inputs are copied from outputs of previous layer
	outputs.resize(1);
	TensorShape shape(batch_size, num_outputs, 1, 1);
	outputs[1] = new Tensor<float>(shape);

	if (with_bias)
		weights.resize(2);
	else
		weights.resize(1);
	weights[0] = new Tensor<float>(TensorShape(num_outputs, num_inputs));
	if (with_bias)
		weights[1] = new Tensor<float>(TensorShape(num_outputs));

	if (activation_layer != NULL)
	{
		// reshape activation layer
		activation_layer->addInput(this->outputs[0]);
		activation_layer->reshape();
	}
}

void ConnectedLayer::checkInputSize()
{
	throw_assert((numInputs() == 1), "Connected layer should have 1 input tensor");
}

void ConnectedLayer::checkOutputSize()
{
	throw_assert(numOutputs() == 1, "Connected layer should have 1 output tensor");
}

Tensor<float>* ConnectedLayer::getOutputTensor(int idx)
{
	if (activation_layer != NULL)
		return activation_layer->getOutputTensor(idx);
	else
		return outputs[idx];
}

void ConnectedLayer::forward()
{
	// use input and weight to calculate output
	const_cpu(batch_size * num_outputs, 0, outputs[0]->dataPtr(), 1);
	int m = batch_size;
	int n = num_outputs;
	int k = num_inputs;
	float* a = inputs[0]->dataPtr();
	float* b = weights[0]->dataPtr();
	float* c = outputs[0]->dataPtr();

	gemm(false, true, m, n, k, 1, a, k, b, k, 1, c, n);
	if (with_bias)
	{
		float* bias = weights[1]->dataPtr();
		for (int t = 0; t < batch_size; ++t)
			axpy_cpu(num_outputs, 1, c + t * num_outputs, 1, bias, 1);
	}
	
	if (activation_layer)
		activation_layer->forward();
}

void ConnectedLayer::backward()
{
	// use output data and output delta to calculate input delta and weight grads
	if (activation_layer)
		activation_layer->backward();

	// do backprop for weight layer

}

void ConnectedLayer::update(const UpdateParam& update_param)
{

}
