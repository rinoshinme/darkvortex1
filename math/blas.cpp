#include "blas.h"

void const_cpu(int N, float alpha, float* x, int inc_x)
{
	for (int i = 0; i < N; ++i)
		x[i * inc_x] = alpha;
}

void axpy_cpu(int N, float alpha, float* x, int inc_x, float* y, int inc_y)
{
	for (int i = 0; i < N; ++i)
		y[i * inc_y] += alpha * x[i * inc_x];
}

void add_cpu(int N, float alpha, float* x, int inc_x)
{
	for (int i = 0; i < N; ++i)
		x[i * inc_x] += alpha;
}

void copy_cpu(int N, float* x, int inc_x, float* y, int inc_y)
{
	for (int i = 0; i < N; ++i)
		y[i * inc_y] = x[i * inc_x];
}

void scale_cpu(int N, float alpha, float* x, int inc_x)
{
	for (int i = 0; i < N; ++i)
		x[i * inc_x] *= alpha;
}


