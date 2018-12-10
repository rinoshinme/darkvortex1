#ifndef DARKVORTEX_SHAPE_H
#define DARKVORTEX_SHAPE_H

#include <vector>

struct TensorShape
{
	int n;
	int c;
	int h;
	int w;

	TensorShape(int n = 1, int c = 1, int h = 1, int w = 1)
	{
		this->n = n;
		this->c = c;
		this->h = h;
		this->w = w;
	}

	TensorShape(const std::vector<int>& shape) : n(1), c(1), h(1), w(1)
	{
		if (shape.size() > 0)
			this->n = shape[0];
		if (shape.size() > 1)
			this->c = shape[1];
		if (shape.size() > 2)
			this->h = shape[2];
		if (shape.size() > 3)
			this->w = shape[3];
	}

	std::vector<int> toVector() const
	{
		std::vector<int> s(4);
		s[0] = n;
		s[1] = c;
		s[2] = h;
		s[3] = w;
		return s;
	}

	int getCount() const
	{
		return n * c * h * w;
	}
};

#endif
