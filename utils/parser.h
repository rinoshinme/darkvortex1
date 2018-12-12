#ifndef DARKVORTEX_PARSER_H
#define DARKVORTEX_PARSER_H

#include <string>
#include <cstdio>
#include <string>
#include "common.h"

#ifndef _WIN32
// for MAC OS and LINUX
#define VORTEX_DEBUG
#endif

class Parser
{
public:
    /* netwise parameters, such as base learning rate, weight decay, learning rate policy */
    NetParam net_param;
    /* per-layer params. */
    std::vector<LayerParam> layer_params;
	/* data config params */
	std::map<std::string, std::string> data_params;
    
public:
    Parser();
	bool parseModel(const std::string& model_file);
	bool parseData(const std::string& data_file);

private:
	bool parseModelConfig(const std::string& model_file, std::vector<ConfigParam>& config);
	bool parseDataConfig(const std::string& data_file, std::map<std::string, std::string>& config);

#ifdef VORTEX_DEBUG
public:
	void showNetParam();
	void showLayerParams();
#endif
};

#endif
