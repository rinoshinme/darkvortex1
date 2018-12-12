#include "graph.h"
#include "utils.h"
#include <set>
#include <cassert>
#include <utility>
#include <queue>
#include "throw_assert.h"

void LayerGraph::loadLayers(const std::vector<LayerParam>& layers)
{
	parseLayerInfo(layers);
	createLayerGraph();
}

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
	// network input has no input values
	// network output has no output values

	/* create input map and output map for layer tensors
	 map from name of tensor to layer index */
	std::map<std::string, std::pair<int, int> > input_map;
	std::map<std::string, std::pair<int, int> > output_map;
	for (size_t i = 0; i < layer_info.size(); ++i)
	{
		std::vector<std::string>& inputs = layer_info[i].inputs;
		for (size_t k = 0; k < inputs.size(); ++k)
			input_map[inputs[k]] = std::make_pair(int(i), int(k));

		std::vector<std::string>& outputs = layer_info[i].outputs;
		for (size_t k = 0; k < outputs.size(); ++k)
			output_map[outputs[k]] = std::make_pair(int(i), int(k));
	}

	size_t num_layers = layer_info.size();
	nodes.resize(num_layers);
	for (size_t i = 0; i < num_layers; ++i)
	{
		nodes[i] = new Node<int>(int(i)); // 1 node for each layer

		// since each layer has tensor names as input and output
		// search each layer for input layer and output layer

		std::map<std::string, std::pair<int, int> >::const_iterator it;

		std::vector<std::string>& inputs = layer_info[i].inputs;
		// set only compares equality?
		std::set<std::pair<int, int> > input_layer_indices = std::set<std::pair<int, int> >();
		for (size_t k = 0; k < inputs.size(); ++k)
		{
			it = output_map.find(inputs[k]);
			// assert(it != output_map.cend(), "each input node should have a source"); 
			throw_assert(it != output_map.cend(), "each input node should have a source");
			std::pair<int, int> layer_index = it->second;
			if (input_layer_indices.find(layer_index) == input_layer_indices.cend())
			{
				nodes[i]->in_nodes.push_back(layer_index);
				input_layer_indices.insert(layer_index);
			}
		}

		std::vector<std::string>& outputs = layer_info[i].outputs;
		std::set<std::pair<int, int> > output_layer_indices = std::set<std::pair<int, int> >();
		for (size_t k = 0; k < outputs.size(); ++k)
		{
			it = input_map.find(outputs[k]);
			// assert(it != input_map.cend(), "each output should have a destination");
			throw_assert(it != input_map.cend(), "each output should have a destination");
			std::pair<int, int> layer_index = it->second;
			if (output_layer_indices.find(layer_index) == output_layer_indices.cend())
			{
				nodes[i]->out_nodes.push_back(layer_index);
				output_layer_indices.insert(layer_index);
			}
		}
	}
}

std::vector<int> LayerGraph::forwardList()
{
	std::map<int, int> in_degree_map; // layer index -> in_degree
	std::queue<int> zero_degree_queue;
	for (size_t k = 0; k < nodes.size(); ++k)
	{
		int in_degree = int(nodes[k]->in_nodes.size());
		in_degree_map.insert(std::make_pair(int(k), in_degree));
		if (in_degree == 0)
			zero_degree_queue.push(int(k));
	}

	std::vector<int> indices;
	while (!zero_degree_queue.empty())
	{
		int idx = zero_degree_queue.front();
		zero_degree_queue.pop();

		indices.push_back(idx); // add into final result

		std::vector<std::pair<int, int> >& subsequent_nodes = nodes[idx]->out_nodes;
		// decrement in degree of all subsequent nodes by 1
		for (size_t k = 0; k < subsequent_nodes.size(); ++k)
		{
			int subsequent_layer_index = subsequent_nodes[k].first;
			in_degree_map[subsequent_layer_index] -= 1;
			if (in_degree_map[subsequent_layer_index] == 0)
				zero_degree_queue.push(subsequent_layer_index);
		}
	}
	return indices;
}

std::vector<int> LayerGraph::backwardList()
{
	std::map<int, int> out_degree_map; // layer index -> in_degree
	std::queue<int> zero_degree_queue;
	for (size_t k = 0; k < nodes.size(); ++k)
	{
		int out_degree = int(nodes[k]->out_nodes.size());
		out_degree_map.insert(std::make_pair(int(k), out_degree));
		if (out_degree == 0)
			zero_degree_queue.push(int(k));
	}

	std::vector<int> indices;
	while (!zero_degree_queue.empty())
	{
		int idx = zero_degree_queue.front();
		zero_degree_queue.pop();

		indices.push_back(idx); // add into final result

		std::vector<std::pair<int, int> >& subsequent_nodes = nodes[idx]->in_nodes;
		// decrement in degree of all subsequent nodes by 1
		for (size_t k = 0; k < subsequent_nodes.size(); ++k)
		{
			int subsequent_layer_index = subsequent_nodes[k].first; // layer index
			out_degree_map[subsequent_layer_index] -= 1;
			if (out_degree_map[subsequent_layer_index] == 0)
				zero_degree_queue.push(subsequent_layer_index);
		}
	}
	return indices;
}
