#ifndef DARKVORTEX_SOFTMAX_LAYER_H
#define DARKVORTEX_SOFTMAX_LAYER_H

#include "../layer.h"

class SoftmaxLayer : public Layer
{
private:
	float temperature; // default value is 1.0f
	float total_loss; // loss for total batch
	Tensor<float> softmax_result; // temporary values
	
public:
	SoftmaxLayer();

	bool loadConfig(const LayerParam& config);
	void reshape();

	void checkInputSize();
	void checkOutputSize();

	void forward();
	void backward();
	void update(const UpdateParam& update_param) {}

	float loss();
};

#endif
