#ifndef DARKVORTEX_LAYER_H
#define DARKVORTEX_LAYER_H

#include "tensor.h"
#include <vector>
#include "utils/common.h"
#include "utils/utils.h"
#include "utils/throw_assert.h"

class Layer
{
protected:
	LayerType layer_type;

	std::vector<Tensor<float>*> inputs;
	std::vector<Tensor<float>*> outputs;
	
	bool has_weights; // weight layer or not
	std::vector<Tensor<float>*> weights; // weight and bias

	bool freeze; // all parameters are not learnable when freeze is true
	std::vector<int> learnable_param_index;

public:
	Layer() {}
	virtual ~Layer() { /* no operations are needed */ }

	// load layer parameters
	virtual bool loadConfig(const LayerParam& config) = 0;
	// add input tensor to layer input.
	virtual void addInput(Tensor<float>* tensor) { inputs.push_back(tensor); }
	// construct outputs and weights from input and layer params
	virtual void reshape() = 0;
	// check sizes
	virtual void checkInputSize() = 0;
	virtual void checkInputOutputSize() = 0;

	// get input/output tensors for layer construction
	virtual Tensor<float>* getInputTensor(int idx) { return inputs[idx]; }
	virtual Tensor<float>* getOutputTensor(int idx) { return outputs[idx]; }

	virtual void forward() = 0;
	virtual void backward() = 0;

	// no operation for default layers, like activation layer
	virtual void update(const UpdateParam& update_param) = 0;

	virtual int numInputs() { return int(inputs.size()); }
	virtual int numOutputs() { return int(outputs.size()); }
	// create output tensors from input tensors

	virtual void loadWeight(FILE* fp) {}
	virtual void saveWeight(FILE* fp) {}
};

#endif
