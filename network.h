#ifndef DARKVORTEX_NETWORK_H
#define DARKVORTEX_NETWORK_H

#include <vector>
#include <string>
#include "utils/common.h"
#include "utils/parser.h"
#include "utils/graph.h"

class Layer;

template<typename T>
class Tensor;

class Network
{
private:
	std::vector<Layer*> layers;

	Parser parser; // parse configuration file
	LayerGraph layer_graph;	// construct forward list and backward list
	std::vector<int> forward_list;
	std::vector<int> backward_list;
	
	int batch_size;

#ifdef GPU
	int gpu_index;
#endif

public:
	Network(const std::string& model_file);
	~Network();

	void buildNetwork();

	void loadWeights(const std::string& weight_file) {}
	void saveWeights(const std::string& weight_file) {}

	void forward();
	void backward();

	// get all params
	std::vector<Tensor<float>*> getParams();
	std::vector<Tensor<float>*> getLearnableParams();
	int getBatchSize() const { return batch_size; }

private:
};

#endif
