#include "graph.h"
#include "utils.h"

void LayerGraph::parseLayerInfo(const std::vector<LayerParam>& layers)
{
	layer_info.clear();
	int def_index = 0;
	
	for (size_t k = 0; k < layers.size(); ++k)
	{
		LayerInfo info;
		
		std::map<std::string, std::string>::const_iterator it;
		// search name LayerParam
		it = layers[k].layer_props.find("name");
		if (it != layers[k].layer_props.cend())
			info.name = it->second;
		else
		{
			char buf[256];
			sprintf(buf, "default_layer_name_%02d", def_index);
			def_index += 1;
			info.name = buf;
		}
		// search input
		it = layers[k].layer_props.find("input");
		if (it != layers[k].layer_props.cend())
		{
			std::vector<std::string> inputs = string_split(it->second, ',');
			for (size_t n = 0; n < inputs.size(); ++n)
				info.inputs.push_back(string_strip(inputs[n]));
		}
		// search output
		it = layers[k].layer_props.find("output");
		if (it != layers[k].layer_props.cend())
		{
			std::vector<std::string> outputs = string_split(it->second, ',');
			for (size_t n = 0; n < outputs.size(); ++n)
				info.outputs.push_back(string_strip(outputs[n]));
		}

		layer_info.push_back(info);
	}
}

void LayerGraph::createLayerGraph()
{

}
