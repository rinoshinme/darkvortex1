#include "parser.h"
#include "utils.h"

Parser::Parser()
{
    net_param.net_props.clear();
    layer_params.clear();
	data_params.clear();
}

bool Parser::parseModel(const std::string& model_file)
{
	std::vector<ConfigParam> config;
	bool ret = parseModelConfig(model_file, config);
	if (!ret)
		return false;

	/* find net param */
	net_param.net_props.clear();
	std::vector<int> indices;
	for (size_t k = 0; k < config.size(); ++k)
	{
		if (config[k].name == "net")
			indices.push_back(int(k));
	}
	// only 1 net config is allowed
	if (indices.size() != 1)
		return false;
	net_param.net_props = config[indices[0]].props;

	/* find layer params */
	LayerParam param;
	layer_params.clear();
	for (size_t k = 0; k < config.size(); ++k)
	{
		if (k == indices[0])
			continue;

		param.type = string_to_layer_type(config[k].name);
		if (param.type == LayerType::UNKNOWN)
			continue;
		param.layer_props = config[k].props;
		layer_params.push_back(param);
	}
	return true;
}

bool Parser::parseData(const std::string& data_file)
{
	data_params.clear();
	return parseDataConfig(data_file, data_params);
}

bool Parser::parseModelConfig(const std::string& model_file, std::vector<ConfigParam>& config)
{
    std::vector<std::string> lines;
    bool ret = readLines(model_file, lines);
    if (!ret)
        return false;
    
	config.clear();
	ConfigParam param;
	std::string line;
	for (size_t k = 0; k < lines.size(); ++k)
	{
		line = string_strip(lines[k]);
		if (line.empty())
			continue;
		switch (line[0])
		{
		case '[':
		{
			if (param.props.size() > 0)
				config.push_back(param);

			std::string name = line.substr(1, line.size() - 2);
			param.name = name;
			param.props.clear();
			break;
		}
		case '#':
			break;
		default:
		{
			std::vector<std::string> fields = string_split(line, '=');
			if (fields.size() != 2)
				return false;
			std::string key = string_strip(fields[0]);
			std::string val = string_strip(fields[1]);
			param.props[key] = val;
			break;
		}
		}
	}
	if (param.props.size() > 0)
		config.push_back(param);
    return true;
}

bool Parser::parseDataConfig(const std::string& data_file, std::map<std::string, std::string>& config)
{
	std::vector<std::string> lines;
	bool ret = readLines(data_file, lines);
	if (!ret)
		return false;

	config.clear();
	// data file only contains key value pairs
	for (size_t k = 0; k < lines.size(); ++k)
	{
		std::vector<std::string> fields = string_split(lines[k], '=');
		if (fields.size() != 2)
			return false;
		std::string key = string_strip(fields[0]);
		std::string val = string_strip(fields[1]);
		config[key] = val;
	}
	return true;
}

#ifdef VORTEX_DEBUG

#include <iostream>

void Parser::showNetParam()
{
	std::map<std::string, std::string>::const_iterator it;
	for (it = net_param.net_props.cbegin(); it != net_param.net_props.cend(); ++it)
	{
		std::cout << it->first << " - " << it->second << std::endl;
	}
}

void Parser::showLayerParams()
{
	for (size_t k = 0; k < layer_params.size(); ++k)
	{
		std::cout << "-----------------------------------------\n";
		std::cout << "[" << layer_type_to_string(layer_params[k].type) << "]" << std::endl;
		std::map<std::string, std::string>::const_iterator it;
		for (it = layer_params[k].layer_props.cbegin(); it != layer_params[k].layer_props.cend(); ++it)
		{
			std::cout << it->first << " - " << it->second << std::endl;
		}
	}
}

#endif

