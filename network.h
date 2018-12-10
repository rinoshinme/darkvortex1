#ifndef DARKVORTEX_NETWORK_H
#define DARKVORTEX_NETWORK_H

#include <vector>
#include <string>
#include "utils/common.h"

class Layer;

template<typename T>
class Tensor;

class Network
{
private:
	std::vector<Layer*> layers;

public:
	Network(const std::string& model_file);
	~Network();

	void loadWeights(const std::string& weight_file);
	void saveWeights(const std::string& weight_file);

	void Forward();
	void Backward();

	// get all params
	std::vector<Tensor<float>*> getParams();
	std::vector<Tensor<float>*> getLearnableParams();

private:


};

#endif
