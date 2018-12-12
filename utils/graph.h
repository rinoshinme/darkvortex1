#ifndef DARKVORTEX_GRAPH_H
#define DARKVORTEX_GRAPH_H

#include "common.h"
#include <vector>
#include <list>
#include <utility>

template<typename T>
struct Node
{
	T val; // index in layer vector
	// std::list<Node*> in_nodes;
	std::vector<std::pair<int, int> > in_nodes; // layer index, tensor index
	// std::list<Node*> out_nodes;
	std::vector<std::pair<int, int> > out_nodes; // layer index, tensor index
	Node(int id) { val = id; }
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
	// intermediate values
	std::vector<LayerInfo> layer_info;

public:
	LayerGraph() {}
	void loadLayers(const std::vector<LayerParam>& layers);
	// LayerGraph(const std::vector<LayerParam>& layers);

	// topology sorting nodes for backprop
	// the output may pose some randomness
	std::vector<int> forwardList();
	std::vector<int> backwardList();

private:
	void parseLayerInfo(const std::vector<LayerParam>& layers);
	void createLayerGraph();
};

#endif
