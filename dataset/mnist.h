#ifndef DARKVORTEX_MNIST_H
#define DARKVORTEX_MNIST_H

#include <vector>
#include "../tensor.h"

class Mnist
{
public:
	// input n x 1 x 28 x 28
	// output n x 10
	Tensor<unsigned char> x_train;
	Tensor<unsigned char> y_train;
	Tensor<unsigned char> x_test;
	Tensor<unsigned char> y_test;
	int num_train;
	int num_test;

	Mnist(const std::string& mnist_dir);

	void getBatchTrain(int offset, int batch_size, Tensor<float>& x, Tensor<float>& y);

private:
	void readImageFile(const std::string& file, Tensor<unsigned char>& tensor);
	void readLabelFile(const std::string& file, Tensor<unsigned char>& tensor);
	int reverseInt(int i);
};

#endif
