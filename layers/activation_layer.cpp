#include "activation_layer.h"
#include "../utils/utils.h"

bool ActivationLayer::loadConfig(const LayerParam& config)
{
	layer_type = LayerType::ACTIVATION;

	std::string activation_type_str = option_find_str1(config.layer_props, "activation", "relu");
	if (activation_type_str == "relu")
	{
		activation = new ReluActivation;
	}
	else if (activation_type_str == "leaky_relu")
	{
		float alpha = option_find_float1(config.layer_props, "alpha", 0.1f);
		activation = new LeakyReluActivation(alpha);
	}
	else
	{
		// default relu
		activation = new ReluActivation;
	}
	return true;
}

void ActivationLayer::reshape()
{
	size_t numInput = inputs.size();
	outputs.resize(numInput);
	for (int i = 0; i < numInput; ++i)
	{
		TensorShape shape = inputs[i]->getShape();
		outputs[i] = new Tensor<float>(shape);
	}
}

void ActivationLayer::forward()
{
	for (int i = 0; i < inputs.size(); ++i)
	{
		this->activation->activate_array(inputs[i]->dataPtr(), outputs[i]->dataPtr(), inputs[i]->numElements());
	}
}

void ActivationLayer::backward()
{
	for (int i = 0; i < inputs.size(); ++i)
	{
		this->activation->gradient_array(outputs[i]->dataPtr(), outputs[i]->numElements(), inputs[i]->deltaPtr());
	}
}
