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
    CONNECTED,
    MAXPOOL,
    SOFTMAX,
    CONVOLUTIONAL,
    BATCH_NORM,
};

struct NetParam
{
    std::map<std::string, std::string> net_props;
};

struct LayerParam
{
    LayerType type;
    std::map<std::string, std::string> layer_props;
};

#endif
