#ifndef DARKVORTEX_LAYER_H
#define DARKVORTEX_LAYER_H

#include "tensor.h"
#include <vector>
#include "utils/common.h"

class Layer
{
protected:
	std::vector<Tensor<float>*> inputs;
	std::vector<Tensor<float>*> outputs;
	std::vector<Tensor<float>*> truths;
	
	std::vector<Tensor<float>*> layer_params;
	std::vector<int> learnable_param_index;

	bool freeze; // all parameters are not learnable when freeze is true
	std::vector<float> losses;
	std::vector<float> loss_weights;

public:
	Layer(const LayerParam& config);
	~Layer();

	virtual void forward() = 0;
	virtual void backward() = 0;
	virtual void update() = 0;

	virtual int numInputs() { return -1; }
	virtual int numOutputs() { return -1; }

};

#endif
