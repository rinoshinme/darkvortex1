#include "network.h"
#include "utils/utils.h"

Network::Network(const std::string& model_file)
{
	parser.parseModel(model_file);

	// parse network parameters


	// parse layer parameters and construct layers
}
