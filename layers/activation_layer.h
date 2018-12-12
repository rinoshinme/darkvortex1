#ifndef DARKVORTEX_ACTIVATION_LAYER_H
#define DARKVORTEX_ACTIVATION_LAYER_H

#include "../layer.h"
#include "../utils/activation.h"
#include <string>

/* ActivationLayer may be contained in a computational layer, 
such as ConnectedLayer or Convolutional Layer */
class ActivationLayer : public Layer
{
private:
	ActivationType activation_type;
	Activation* activation;

public:
	ActivationLayer() {}
	~ActivationLayer() {}

	bool loadConfig(const LayerParam& config);
	void reshape();
	void checkInputSize();
	void checkOutputSize();

	void forward();
	void backward();
	// nothing to be done for activation layer
	void update(const UpdateParam& update_param);

public:

};

#endif
