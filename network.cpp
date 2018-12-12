#include "network.h"
#include "utils/utils.h"
#include "utils/graph.h"
#include "layers/activation_layer.h"
#include "layers/connected_layer.h"

Network::Network(const std::string& model_file)
{
	parser.parseModel(model_file);

	// construct layer topology for forward and backward pass
	layer_graph.loadLayers(parser.layer_params);
	forward_list = layer_graph.forwardList();
	backward_list = layer_graph.backwardList();

	// parse network parameters
	std::map<std::string, std::string> net_props = parser.net_param.net_props;
	batch_size = option_find_int1(net_props, "batch", 1);

	buildNetwork();
}

void Network::buildNetwork()
{
	// parse layer parameters and construct layers
	std::vector<LayerParam> layer_params = parser.layer_params;
	layers.resize(layer_params.size());
	for (size_t i = 0; i < layers.size(); ++i)
	{
		LayerType t = layer_params[i].type;
		switch (t)
		{
		case LayerType::ACTIVATION:
			layers[i] = new ActivationLayer;
			layers[i]->loadConfig(layer_params[i]);
			break;
		case LayerType::CONNECTED:
			layers[i] = new ConnectedLayer;
			layers[i]->loadConfig(layer_params[i]);
			break;
		default:
			break;
		}
	}

	for (size_t i = 0; i < layers.size(); ++i)
	{
		// construct input tensors for current layer
		// layers are adjusted in forward_list order


		// reshape layer output size and weight size
		layers[i]->reshape();
	}
}

void Network::forward()
{
	for (size_t i = 0; i < forward_list.size(); ++i)
	{
		layers[forward_list[i]]->forward();
	}
}

void Network::backward()
{
	for (size_t i = 0; i < backward_list.size(); ++i)
	{
		layers[backward_list[i]]->backward();
	}
}
