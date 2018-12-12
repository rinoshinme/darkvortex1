#ifndef DARKVORTEX_TENSOR_H
#define DARKVORTEX_TENSOR_H

#include "utils/shape.h"
#include "math/blas.h"
#include <cassert>
#include "opencv_all.h"

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
	bool with_delta;

public:
	Tensor()
	{
		data = NULL;
		delta = NULL;
		shape = TensorShape(0, 0, 0, 0);
		sample_size = 0;
	}

	Tensor(const std::vector<int>& shape, bool with_delta = true)
	{
		TensorShape tshape(shape);
		initWithShape(tshape, with_delta);
		sample_size = this->shape.c * this->shape.h * this->shape.w;
	}

	Tensor(const TensorShape& shape, bool with_delta = true)
	{
		initWithShape(shape, with_delta);
	}

	Tensor(int n, int c, int w, int h, bool with_delta = true)
	{
		TensorShape shape(n, c, w, h);
		initWithShape(shape, with_delta);
	}

	~Tensor()
	{
		clearDataAndDelta();
	}

	TensorShape getShape() const { return shape; }
	std::vector<int> getShapeVector() const { return shape.toVector(); }
	int numElements() const { return shape.getCount(); }
	const T* dataPtr(int num = 0) const { return data + num * sample_size; }
	const T* deltaPtr(int num = 0) const { return delta + num * sample_size; }
	T* dataPtr(int num = 0) { return data + num * sample_size; }
	T* deltaPtr(int num = 0) { return delta + num * sample_size; }
	bool hasDelta() const { return with_delta; }

	void resize(TensorShape new_shape, bool with_delta = true)
	{
		if (shape == new_shape)
			return;

		// absolutely clean data
		clearDataAndDelta();

		shape = new_shape;
		sample_size = shape.sampleSize();
		int count = shape.getCount();
		if (count > 0)
			initWithShape(shape, with_delta);
	}

	void resize(int n, int c, int h, int w, bool with_delta = true)
	{
		TensorShape shape(n, c, h, w);
		resize(shape, with_delta);
	}

	// clear delta value for weight parameters
	void zeroGrad()
	{
		if (!with_delta)
			return;
		int count = shape.getCount();
		if (count > 0)
			const_cpu(count, 0, delta, 1);
	}

	void createDelta()
	{
		if (this->with_delta)
			return;
		int count = shape.getCount();
		if (count > 0)
		{
			delta = new T[count];
			memset(delta, 0, count * sizeof(T));
		}
		this->with_delta = true;
	}

private:
	void clearDataAndDelta()
	{
		if (data != NULL)
			delete[] data;
		if (delta != NULL)
			delete[] delta;
	}

	void initWithShape(const TensorShape& shape, bool with_delta = true)
	{
		this->with_delta = with_delta;
		this->shape = shape;
		int count = shape.n * shape.c * shape.h * shape.w;
		data = new T[count];
		memset(data, 0, count * sizeof(T));

		if (with_delta)
		{
			delta = new T[count];
			memset(delta, 0, count * sizeof(T));
		}
	}

#ifdef OPENCV
public:
	/* convert data or delta into opencv Mat */
	std::vector<cv::Mat> toCvMats(bool data_or_delta)
	{
		if (data_or_delta)
			return toCvMats(data, shape);
		else
			return toCvMats(delta, shape);
	}
private:
	std::vector<cv::Mat> toCvMats(T* data, TensorShape& shape)
	{
		// opencv data arrange is (h, w, c)
		std::vector<cv::Mat> images;
		int n = shape.n;
		int sample_size = shape.sampleSize();
		int sz[] = { shape.h, shape.w, shape.c };
		for (int i = 0; i < n; ++i)
		{
			cv::Mat cube(3, sz, CV_32F);
			
			// copy data
			float* mat_data = (float*)cube.data;
			T* sample_data = data + i * sample_size;

			for (int h = 0; h < shape.h; ++h)
			{
				for (int w = 0; w < shape.w; ++w)
				{
					for (int c = 0; c < shape.c; ++c)
					{
						mat_data[h * (shape.w * shape.c) + w * shape.c + c] = sample_data[c * (shape.h * shape.w) + h * shape.w + w];
					}
				}
			}
			images.push_back(cube);
		}
		return images;
	}
#endif


private:
	// no copy constructor and assignment operator
	Tensor(const Tensor<T>& t) {}
	Tensor<T>& operator=(const Tensor<T>& t) {}
};

typedef Tensor<float> Tensorf;
typedef Tensor<double> Tensord;

#endif
