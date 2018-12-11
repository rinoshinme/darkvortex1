#ifndef DARKVORTEX_DATA_LAYER_H
#define DARKVORTEX_DATA_LAYER_H

#include "../layer.h"

class DataLayer : public Layer
{
private:
	// image enhancement params
	float angle;
	float hue;
	float saturation;
	float exposure;
	float aspect;

public:
	DataLayer(const LayerParam& config) {}
	~DataLayer() {}

	bool loadConfig(const LayerParam& config) {}
	void reshape() {}

	void forward() {}
	void backward() {}
	// nothing to be done for activation layer
	void update() {}

public:
	int NumInputs() { return 1; }
	int NumOutputs() { return 1; }
};

#endif
