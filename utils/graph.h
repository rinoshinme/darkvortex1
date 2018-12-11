#ifndef DARKVORTEX_GRAPH_H
#define DARKVORTEX_GRAPH_H

#include "common.h"
#include <vector>
#include <list>

template<typename T>
struct Node
{
	T val; // index in layer vector
	std::list<Node*> in_nodes;
	std::list<Node*> out_nodes;
};

class LayerGraph
{
private:
	struct LayerInfo
	{
		std::string name;
		std::vector<std::string> inputs;
		std::vector<std::string> outputs;
	};

private:
	std::vector<Node<int>*> nodes;
	std::vector<LayerInfo> layer_info;

public:
	LayerGraph(const std::vector<LayerParam>& layers);

	// topology sorting nodes for backprop
	std::vector<int> forwardList();
	std::vector<int> backwardList();

private:
	void parseLayerInfo(const std::vector<LayerParam>& layers);
	void createLayerGraph();
};

#endif
