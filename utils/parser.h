#ifndef DARKVORTEX_PARSER_H
#define DARKVORTEX_PARSER_H

#include <string>
#include <cstdio>
#include <string>
#include "common.h"

class Parser
{
public:
    /* netwise parameters, such as base learning rate, weight decay, learning rate policy */
    NetParam net_param;
    /* per-layer params. */
    std::vector<LayerParam> layer_params;
    
public:
    Parser();
    bool parseModel(const std::string& model_file);
    bool parseData(const std::string& data_file);
    
};

#endif
