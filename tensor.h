#ifndef DARKVORTEX_TENSOR_H
#define DARKVORTEX_TENSOR_H

#include "utils/shape.h"
#include <cassert>

template<typename T>
class Tensor
{
private:
	T* data;
	T* delta;
#ifdef GPU
	T* data_gpu;
	T* delta_gpu;
#endif
	TensorShape shape;
	int sample_size;

public:
	Tensor(const std::vector<int>& shape)
	{
		TensorShape tshape(shape);
		initWithShape(tshape);
		sample_size = this->shape.c * this->shape.h * this->shape.w;
	}

	Tensor(const TensorShape& shape)
	{
		initWithShape(shape);
	}

	Tensor(int n, int c, int w, int h);
	~Tensor();

	TensorShape getShape() const { return shape; }
	std::vector<int> getShapeVector() const { return shape.toVector(); }
	int numElements() const { return shape.getCount(); }
	const T* dataPtr(int num = 0) const { return data + num * sample_size; }
	const T* deltaPtr(int num = 0) const { return delta + num * sample_size; }
	T* dataPtr(int num = 0) { return data + num * sample_size; }
	T* deltaPtr(int num = 0) { return delta + num * sample_size; }

	// clear delta value for weight parameters
	void zeroGrad();

private:
	void clearDataAndDelta()
	{
		if (data != NULL)
			delete[] data;
		if (delta != NULL)
			delete[] delta;
	}

	void initWithShape(const TensorShape& shape)
	{
		this->shape = shape;
		int count = shape.n * shape.c * shape.h * shape.w;
		data = new T[count];
		delta = new T[count];
		memset(data, 0, count * sizeof(T));
		memset(delta, 0, count * sizeof(T));
	}
};

typedef Tensor<float> Tensorf;
typedef Tensor<double> Tensord;

#endif
