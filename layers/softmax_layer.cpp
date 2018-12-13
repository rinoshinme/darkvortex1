#include "softmax_layer.h"

SoftmaxLayer::SoftmaxLayer()
{
	layer_type = LayerType::SOFTMAX;
}

bool SoftmaxLayer::loadConfig(const LayerParam& config)
{
	// no parameters
	return true;
}

void SoftmaxLayer::reshape()
{
	checkInputSize();
	// do preparation
	softmax_result.resize(inputs[0]->getShape());

	checkOutputSize();
}

void SoftmaxLayer::checkInputSize()
{
	// inputs[0]: activation
	// inputs[1]: ground truth
	throw_assert(numInputs() == 2, "Softmax layer has 2 inputs");
}

void SoftmaxLayer::checkOutputSize()
{
	throw_assert(numOutputs() == 0, "Softmax layer has no input");
}

void SoftmaxLayer::forward()
{
	// calculate softmax loss

}

void SoftmaxLayer::backward()
{
	// back propagate loss to input tensors

}

float SoftmaxLayer::loss()
{
	int batch_size = inputs[0]->getShape().n;
	if (inputs.size() == 0 || batch_size == 0)
		return 0.0f;
	return total_loss / batch_size;
}
