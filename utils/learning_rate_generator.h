#ifndef DARKVORTEX_LEARNING_RATE_GENERATOR_H
#define DARKVORTEX_LEARNING_RATE_GENERATOR_H

#include <vector>

enum LearningRatePolicy
{
	CONSTANT,
	STEP,	// constant step : decay lr every k steps
	STEPS,	// decay lr when num_iter go over a step in steps
	EXP,
	POLY,
	UNKNOWN,
};

class LearningRateGenerator
{
protected:
	float base_learning_rate;

public:
	LearningRateGenerator(float blr) { base_learning_rate = blr; }
	virtual ~LearningRateGenerator() {}

	virtual float getLearningRate(int num_iters) { return base_learning_rate; }
};

class ConstantLearningRateGenerator : public LearningRateGenerator
{
public:
	ConstantLearningRateGenerator(float blr)
		: LearningRateGenerator(blr) {}
};

class StepLearningRateGenerator : public LearningRateGenerator
{
private:
	int step;
	float ratio;

public:
	StepLearningRateGenerator(float blr, int step, float ratio)
		: LearningRateGenerator(blr)
	{
		this->step = step;
		this->ratio = ratio;
	}

	float getLearningRate(int num_iters)
	{
		int n = num_iters / step;
		float lr = base_learning_rate;
		for (int i = 0; i < n; ++i)
			lr *= ratio;
		return lr;
	}
};

class StepsLearningRateGenerator : public LearningRateGenerator
{
private:
	std::vector<int> steps;
	float ratio;
public:
	StepsLearningRateGenerator(float blr, const std::vector<int>& steps, float ratio)
		: LearningRateGenerator(blr)
	{
		this->steps = steps;
		this->ratio = ratio;
	}

	float getLearningRate(int num_iters)
	{
		int n = 0;
		while (n < steps.size() && num_iters < steps[n])
			n += 1;
		float lr = base_learning_rate;
		for (int i = 0; i < n; ++i)
			lr *= ratio;
		return lr;
	}
};

class ExpLearningRateGenerator : public LearningRateGenerator
{
private:
	float gamma;

public:
	ExpLearningRateGenerator(float blr, float gamma)
		: LearningRateGenerator(blr)
	{
		this->gamma = gamma;
	}

	float getLearningRate(int num_iters)
	{
		return std::pow(gamma, num_iters);
	}
};

#endif
