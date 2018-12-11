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

int main()
{
	test_parser();
	// test_string_split();

	std::cout << "finished...\n";

#ifdef _WIN32
	std::getchar();
#endif
}
