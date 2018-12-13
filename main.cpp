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

void test_list_dir()
{
	std::string mnist_dir("F:/projects/data/mnist");
	std::vector<std::string> files = list_dir(mnist_dir, ListDirType::FILE_ONLY);
	if (files.size() == 0)
	{
		std::cout << "no files in directory\n";
		return;
	}
	for (size_t k = 0; k < files.size(); ++k)
	{
		std::cout << files[k] << std::endl;
	}
}

void test_mnist()
{
	std::string mnist_dir("F:/projects/data/mnist");
	Mnist mnist;
	mnist.loadData(mnist_dir);

	Tensor<float> batch_x;
	Tensor<float> batch_y;
	int batch_size = 5;
	mnist.getBatchTrain(0, batch_size, batch_x, batch_y);

	// show labels
	for (int i = 0; i < batch_size; ++i)
	{
		for (int j = 0; j < 10; ++j)
			std::cout << batch_y(i, j) << " ";
		std::cout << std::endl;
	}

	std::cout << batch_x.getShape() << std::endl;

#ifdef OPENCV
	// show images
	std::vector<cv::Mat> images = batch_x.toCvMats(true);
	for (size_t k = 0; k < images.size(); ++k)
	{
		std::cout << images[k].rows << ", " << images[k].cols << ", " << images[k].channels() << std::endl;
		cv::imshow("image", images[k]);
		cv::waitKey(0);
	}
#endif
}

int main()
{
	// test_network_parser();
	test_mnist();
	// test_list_dir();

	std::cout << "finished...\n";

#ifdef _WIN32
	std::getchar();
#endif
}
