#ifndef DARKVORTEX_DATA_LAYER_H
#define DARKVORTEX_DATA_LAYER_H

#include "../layer.h"

class DataLayer : public Layer
{
private:

public:
	DataLayer(const LayerParam& config) {}
	virtual ~DataLayer() {}

    virtual bool loadConfig(const LayerParam& config) { return true; }
	virtual void reshape() {}

	virtual void forward() {}
	virtual void backward() {}
	// nothing to be done for activation layer
	virtual void update() {}

public:
	int NumInputs() { return 1; }
	int NumOutputs() { return 1; }
};

#endif
