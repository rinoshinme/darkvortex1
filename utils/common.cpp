#include "common.h"

std::string layer_type_to_string(LayerType type)
{
	switch (type)
	{
	case LayerType::ACTIVATION:
		return "activation";
	case LayerType::BATCH_NORM:
		return "batchnorm";
	case LayerType::CONNECTED:
		return "connected";
	case LayerType::CONVOLUTIONAL:
		return "convolutional";
	case LayerType::MAXPOOL:
		return "maxpool";
	case LayerType::SOFTMAX:
		return "softmax";
	case LayerType::DROPOUT:
		return "dropout";
	case LayerType::UNKNOWN:
		return "unknown";
	default:
		return "unknown";
	}
}

LayerType string_to_layer_type(const std::string& name)
{
	if (name == "batchnorm")
		return LayerType::BATCH_NORM;
	if (name == "connected")
		return LayerType::CONNECTED;
	if (name == "convolutional")
		return LayerType::CONVOLUTIONAL;
	if (name == "maxpool")
		return LayerType::MAXPOOL;
	if (name == "softmax")
		return LayerType::SOFTMAX;
	if (name == "dropout")
		return LayerType::DROPOUT;
	if (name == "activation")
		return LayerType::ACTIVATION;
	if (name == "unknown")
		return LayerType::UNKNOWN;
	
	return LayerType::UNKNOWN;
}
