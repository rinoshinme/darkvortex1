#ifndef DARKVORTEX_DATA_LAYER_H
#define DARKVORTEX_DATA_LAYER_H

#include "../layer.h"
#include "../dataset/mnist.h"
#include "../utils/common.h"

// a sample data layer for generating vector data
class DataLayer : public Layer
{
private:
	// temporary buffer for mnist batches
	Tensor<float> data_x;
	Tensor<float> data_y;
	Mnist mnist;
	int batch_size;
	int offset;

	Phase phase;

public:
	DataLayer(const LayerParam& config);
	virtual ~DataLayer() {}

    virtual bool loadConfig(const LayerParam& config) { return true; }
	virtual void reshape();

	void setBatchSize(int bs) { batch_size = bs; }
	int getBatchSize() const { return batch_size; }

	void checkInputSize();
	void checkOutputSize();

	virtual void forward();
	// no backward and update for data layer
	virtual void backward() {}
	virtual void update(const UpdateParam& update_param) {}
};

#endif
