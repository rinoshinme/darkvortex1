#include "blas.h"
#include <cmath>
#include <float.h>

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

void softmax(int N, float* input, float* output, float temperature)
{
	// find largest in input
	float largest = -FLT_MAX;
	for (int i = 0; i < N; ++i)
		if (input[i] > largest)
			largest = input[i];

	float sum = 0;
	for (int i = 0; i < N; ++i)
	{
		output[i] = input[i] - largest;
		sum += exp(output[i]);
	}

	for (int i = 0; i < N; ++i)
	{
		output[i] /= sum;
	}
}

float xentropy(int N, float* x, float* y)
{
	float entropy = 0.0f;
	for (int i = 0; i < N; ++i)
		entropy += x[i] * log(y[i]);
	return entropy;
}

void softmax_cpu(float* input, int batch_size, int sample_size, float temperature, float* output)
{
	for (int i = 0; i < batch_size; ++i)
	{
		float* x = input + i * sample_size;
		float* o = output + i * sample_size;
		softmax(sample_size, x, o, temperature);
	}
}

float xentropy_cpu(float* x, float* y, int batch_size, int sample_size)
{
	float total_loss = 0;
	for (int i = 0; i < batch_size; ++i)
	{
		float* bx = x + i * sample_size;
		float* by = y + i * sample_size;
		total_loss += xentropy(sample_size, bx, by);
	}
}

