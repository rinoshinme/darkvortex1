/*
 * common data structures.
 */
#ifndef DARKVORTEX_COMMON_H
#define DARKVORTEX_COMMON_H

#include <vector>
#include <map>
#include <string>

enum class LayerType
{
	ACTIVATION,
    CONNECTED,
    MAXPOOL,
    SOFTMAX,
    CONVOLUTIONAL,
	DROPOUT,
    BATCH_NORM,
	UNKNOWN, // layer types not supported
};

std::string layer_type_to_string(LayerType type);
LayerType string_to_layer_type(const std::string& name);

struct ConfigParam
{
	std::string name;
	std::map<std::string, std::string> props;
};

struct NetParam
{
    std::map<std::string, std::string> net_props;
};

struct LayerParam
{
	// each layer should have name, input, output 
    LayerType type;
    std::map<std::string, std::string> layer_props;
};

struct UpdateParam
{
	float learning_rate;
	float decay;
	float moment;
	// ...
};

#endif
