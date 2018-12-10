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

public:
	Tensor(const std::vector<int>& shape)
	{
		TensorShape tshape(shape);
		initWithShape(tshape);
	}

	Tensor(const TensorShape& shape)
	{
		initWithShape(shape);
	}

	Tensor(int n, int c, int w, int h);
	~Tensor();

	TensorShape getShape() const { return shape; }
	std::vector<int> getShapeVector() const { return shape.toVector(); }
	int getCount() const { return shape.getCount(); }

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



#endif
