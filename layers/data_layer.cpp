#include "data_layer.h"

void DataLayer::reshape()
{
	outputs.resize(2);

	// batchsize is only set explicitly at start. i.e. data layer
	int batch_size = network->getBatchSize();
	TensorShape xshape(batch_size, 384, 1, 1); // MNIST size
	TensorShape yshape(batch_size, 10, 1, 1);
	outputs[0] = new Tensor<float>(xshape);
	outputs[1] = new Tensor<float>(yshape);
}

void DataLayer::checkInputSize()
{
	throw_assert(numInputs() == 0, "DataLayer should have no input tensor");
}

void DataLayer::checkOutputSize()
{
	throw_assert(numOutputs() == 2, "DataLayer should have 2 output tensors");
}

void DataLayer::forward()
{

}
