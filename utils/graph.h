#ifndef DARKVORTEX_GRAPH_H
#define DARKVORTEX_GRAPH_H

#include "common.h"
#include <vector>
#include <list>

template<typename T>
struct Node
{
	T val;
	std::list<Node*> in_nodes;
	std::list<Node*> out_nodes;
};

template<typename T>
class Graph
{
private:
	std::vector<Node*> nodes;
public:
	Graph(const std::vector<LayerParam>& layers);

	// topology sorting nodes for backprop
	std::vector<Node*> forwardList();
	std::vector<Node*> backwardList();
};


#endif
