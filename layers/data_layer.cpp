#include "data_layer.h"

DataLayer::DataLayer(const LayerParam& config)
{
	std::string mnist_folder("F:/projects/data/mnist");
	mnist.loadData(mnist_folder);
	batch_size = 1;
	offset = 0;
}

void DataLayer::reshape()
{
	outputs.resize(2);
	outputs[0] = &data_x;
	outputs[1] = &data_y;
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
	throw_assert(batch_size > 0, "batch size should be positive");
	int num_train = mnist.num_train;
	if (offset + batch_size > num_train)
		offset = 0;

	mnist.getBatchTrain(offset, batch_size, data_x, data_y);
	offset += batch_size;
	// tensor in outputs automatically updated.
}
