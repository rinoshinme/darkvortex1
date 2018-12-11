#ifndef DARKVORTEX_CONNECTED_LAYER_H
#define DARKVORTEX_CONNECTED_LAYER_H

#include "../layer.h"

class ConnectedLayer : public Layer
{
private:
	bool with_bias;
	int batch_size;
	int num_inputs;
	int num_outputs;

public:
	ConnectedLayer() {}
	~ConnectedLayer() {}

public:
	bool loadConfig(const LayerParam& config);
	void reshape();

	void forward();
	void backward();
	// nothing to be done for activation layer
	void update(const UpdateParam& update_param);

public:
	int NumInputs() { return 1; }
	int NumOutputs() { return 1; }

};

#endif
