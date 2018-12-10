#ifndef DARKVORTEX_ACTIVATION_H
#define DARKVORTEX_ACTIVATION_H

#include <cmath>

enum class ActivationType
{
	LINEAR,
	RELU,
	TANH,
	SIGMOID,
	ELU,
	LEAKY_RELU,
};

class Activation
{
protected:
	ActivationType type;
public:
	// subclasses may have more parameters
	Activation(ActivationType type) { this->type = type; }
	// calculate activation
	virtual float operator()(float x) const { return activate(x); }

	virtual float activate(float x) const = 0;
	virtual float gradient(float y) const = 0;

	virtual void activate_array(float* x, float* y, int n)
	{
		for (int i = 0; i < n; ++i)
			y[i] = activate(x[i]);
	}

	virtual void gradient_array(float* y, int n, float* delta)
	{
		for (int i = 0; i < n; ++i)
			delta[i] = gradient(y[i]);
	}
};

class LinearActivation : public Activation
{
private:
	float k;
	float b;
public:
	LinearActivation(float k = 1.0f, float b = 0.0f) : Activation(ActivationType::LINEAR)
	{
		this->k = k;
		this->b = b;
	}

	float activate(float x) const { return k * x + b; }
	float gradient(float y) const { return k; }
};

class SigmoidActivation : public Activation
{
public:
	SigmoidActivation() : Activation(ActivationType::SIGMOID) {}
	
	float activate(float x) { return 1.0f / (1 + exp(-x)); }
	float gradient(float y) { return y * (1 - y); }
};

class ReluActivation : public Activation
{
public:
	ReluActivation() : Activation(ActivationType::RELU) {}

	float activate(float x) { return (x > 0) ? x : 0.0f; }
	float gradient(float y) { return (y > 0) ? 1.0f : 0.0f; }
};

class EluActivation : public Activation
{
public:
	EluActivation() : Activation(ActivationType::ELU) {}

	float activate(float x) { return (x > 0) ? x : exp(x) - 1; }
	float gradient(float y) { return (y > 0) ? 1.0f : (y + 1); }
};

class LeakyReluActivation : public Activation
{
private:
	float alpha;

public:
	LeakyReluActivation(float a) : Activation(ActivationType::LEAKY_RELU)
	{
		alpha = a;
	}

	float activate(float x) { return (x > 0) ? x : alpha * x; }
	float gradient(float y) { return (y > 0) ? 1.0f : alpha; }
};

#endif
