#ifndef DARKVORTEX_DATA_LAYER_H
#define DARKVORTEX_DATA_LAYER_H

#include "../layer.h"

// a sample data layer for generating vector data
class DataLayer : public Layer
{
private:
	// no parameters

public:
	DataLayer(const LayerParam& config) {}
	virtual ~DataLayer() {}

    virtual bool loadConfig(const LayerParam& config) { return true; }
	virtual void reshape();

	void checkInputSize();
	void checkOutputSize();

	virtual void forward();
	virtual void backward() {}
	virtual void update(const UpdateParam& update_param) {}
};

#endif
