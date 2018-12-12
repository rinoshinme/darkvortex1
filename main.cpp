#include <iostream>
#include "darkvortex.h"

void test_parser()
{
	std::string model_file("F:/projects/darknet/cfg/alexnet.cfg");
	Parser parser;
	bool ret = parser.parseModel(model_file);
	if (!ret)
		std::cout << "parse failed\n";

	// parser.showNetParam();
	parser.showLayerParams();
}

void test_string_split()
{
	std::string line("abc = def poasd == 010");
	std::vector<std::string> fields = string_split(line, '=');
	for (size_t k = 0; k < fields.size(); ++k)
	{
		std::cout << "-" << fields[k] << "-" << std::endl;
	}
}

void test_network_parser()
{
	std::string model_file("F:/projects/darkvortex1/prj/darkvortex1/doc/fcnet.model");
	Parser parser;
	bool ret = parser.parseModel(model_file);
	if (!ret)
		std::cout << "parse failed\n";
	parser.showNetParam();
	std::cout << "---------------------------------------\n";
	parser.showLayerParams();

	LayerGraph graph;
	graph.loadLayers(parser.layer_params);
	std::vector<int> forward_list = graph.forwardList();
	for (size_t k = 0; k < forward_list.size(); ++k)
		std::cout << forward_list[k] << "->";
	std::cout << std::endl;
	std::vector<int> backward_list = graph.backwardList();
	for (size_t k = 0; k < backward_list.size(); ++k)
		std::cout << backward_list[k] << "->";
	std::cout << std::endl;

}

int main()
{
	test_network_parser();

	std::cout << "finished...\n";

#ifdef _WIN32
	std::getchar();
#endif
}
