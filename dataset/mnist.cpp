#include "mnist.h"
#include <string>
#include <fstream>
#include "../utils/utils.h"
#include "../utils/throw_assert.h"

Mnist::Mnist()
{
	num_train = 0;
	num_test = 0;
}

void Mnist::loadData(const std::string& mnist_dir)
{
	std::string mnist_files[] = {
		"train-images.idx3-ubyte",
		"train-labels.idx1-ubyte",
		"t10k-images.idx3-ubyte",
		"t10k-labels.idx1-ubyte"
	};

	// scan folder and find 4 mnist files
    std::vector<std::string> files = list_dir(mnist_dir, ListDirType::FILE_ONLY);
    for (int i = 0; i < 4; ++i)
        throw_assert(in_vector(mnist_files[i], files), "");
	for (size_t i = 0; i < files.size(); ++i)
	{
		if (string_ends_with(files[i], ".gz"))
			throw_assert(false, ".gz files should be uncompressed!");
	}

	std::cout << "reading data from mnist files\n";
	readImageFile(path_join(mnist_dir, mnist_files[0]), x_train);
	readLabelFile(path_join(mnist_dir, mnist_files[1]), y_train);
	readImageFile(path_join(mnist_dir, mnist_files[2]), x_test);
	readLabelFile(path_join(mnist_dir, mnist_files[3]), y_test);

	num_train = x_train.getShape().n;
	num_test = x_test.getShape().n;
}

void Mnist::readImageFile(const std::string& file, Tensor<unsigned char>& tensor)
{
	std::ifstream stream(file, std::ios::binary);
	if (!stream.is_open())
		return;
	int magic_number = 0;
	int number_of_images = 0;
	int n_rows = 0;
	int n_cols = 0;
	stream.read((char*)&magic_number, sizeof(magic_number));
	stream.read((char*)&number_of_images, sizeof(number_of_images));
	stream.read((char*)&n_rows, sizeof(n_rows));
	stream.read((char*)&n_cols, sizeof(n_cols));
	magic_number = reverseInt(magic_number);
	number_of_images = reverseInt(number_of_images);
	n_rows = reverseInt(n_rows);
	n_cols = reverseInt(n_cols);

#if VORTEX_DEBUG
	std::cout << "magic number = " << magic_number << std::endl;
	std::cout << "number of images = " << number_of_images << std::endl;
	std::cout << "num of rows = " << n_rows << std::endl;
	std::cout << "num of cols = " << n_cols << std::endl;
#endif

	tensor.resize(number_of_images, 1, n_rows, n_cols);
	stream.read((char*)tensor.dataPtr(), number_of_images * n_cols * n_rows * sizeof(char));
	stream.close();
}

void Mnist::readLabelFile(const std::string& file, Tensor<unsigned char>& tensor)
{
	std::ifstream stream(file, std::ios::binary);
	if (!stream.is_open())
		return;
	int magic_number = 0;
	int number_of_images = 0;
	stream.read((char*)&magic_number, sizeof(magic_number));
	stream.read((char*)&number_of_images, sizeof(number_of_images));
	magic_number = reverseInt(magic_number);
	number_of_images = reverseInt(number_of_images);

#if VORTEX_DEBUG
	std::cout << "magic number = " << magic_number << std::endl;
	std::cout << "number of images = " << number_of_images << std::endl;
#endif

	tensor.resize(number_of_images, 1, 1, 1);
	stream.read((char*)tensor.dataPtr(), number_of_images * sizeof(char));
	stream.close();
}

int Mnist::reverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void Mnist::getBatchTrain(int offset, int batch_size, Tensor<float>& x, Tensor<float>& y)
{
	throw_assert((offset >= 0) && (batch_size > 0) && (offset + batch_size) < num_train, "Index out of range");
	TensorShape batch_x_shape(batch_size, 1, 28, 28);
	TensorShape batch_y_shape(batch_size, 10, 1, 1);
	int sample_size = batch_x_shape.sampleSize();
	x.resize(batch_x_shape, false);
	y.resize(batch_y_shape, false);

	// copy x
	for (int i = 0; i < batch_size; ++i)
	{
		unsigned char* x_train_ptr = x_train.dataPtr(offset + i);
		float* x_ptr = x.dataPtr(i);
		for (int j = 0; j < sample_size; ++j)
			x_ptr[j] = float(x_train_ptr[j]);
	}

	// copy y
	for (int i = 0; i < batch_size; ++i)
	{
		unsigned char* y_train_ptr = y_train.dataPtr(offset + i);
		float* y_ptr = y.dataPtr(i);
		int label = *y_train_ptr;
		for (int j = 0; j < 10; ++j)
		{
			if (j == label)
				y_ptr[j] = 1.0f;
			else
				y_ptr[j] = 0.0f;
		}
	}
}
