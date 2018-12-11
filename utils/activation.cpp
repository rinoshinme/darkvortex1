#include "activation.h"

std::string activation_type_to_string(ActivationType type)
{
	switch (type)
	{
	case ActivationType::LINEAR:
		return "linear";
	case ActivationType::RELU:
		return "relu";
	case ActivationType::TANH:
		return "tanh";
	case ActivationType::SIGMOID:
		return "sigmoid";
	case ActivationType::ELU:
		return "elu";
	case ActivationType::LEAKY_RELU:
		return "leaky_relu";
	default:
		return "unknown";
		break;
	}
}

ActivationType string_to_activation_type(const std::string& name)
{
	if (name == "sigmoid")
		return ActivationType::SIGMOID;
	if (name == "relu")
		return ActivationType::RELU;

	// return RELU as default
	return ActivationType::RELU;
}

float sigmoid_activate(float x);
float relu_activate(float x);
float tanh_activate(float x);
// float elu_activate(float x);
// float leaky_relu_activate(float x);

float sigmoid_gradient(float y);
float relu_gradient(float y);
float tanh_gradient(float y);



