#ifndef DARKVORTEX_ACTIVATION_LAYER_H
#define DARKVORTEX_ACTIVATION_LAYER_H

#include "../layer.h"
#include "../utils/activation.h"
#include <string>

class ActivationLayer : public Layer
{
private:
	ActivationType type;
	Activation* activation;

public:
	ActivationLayer(const LayerParam& config);
	~ActivationLayer();

	void forward();
	void backward();
	// nothing to be done for activation layer
	void update() {}

public:
	int NumInputs() { return 1; }
	int NumOutputs() { return 1; }

};

#endif
