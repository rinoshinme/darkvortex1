#ifndef DARKVORTEX_IMAGE_DATA_LAYER_H
#define DARKVORTEX_IMAGE_DATA_LAYER_H

#include "data_layer.h"

class ImageDataLayer : public DataLayer
{
private:
	// image enhancement params
	float angle;
	float hue;
	float saturation;
	float exposure;
	float aspect;
};

#endif
