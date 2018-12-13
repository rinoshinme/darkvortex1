#ifndef DARKVORTEX_OPTIMIZER_H
#define DARKVORTEX_OPTIMIZER_H

#include "utils/learning_rate_generator.h"

enum class OptimizerType
{
	SGD,
	Momentum,
	Adam,
};

class Network;

class Optimizer
{
private:
	float base_learning_rate;
	LearningRatePolicy policy;
	int max_iters;
	int max_epoch;

private:
	// optimizer type
	Network* network;
	Phase phase;
	OptimizerType type;

	Optimizer();

public:
	void setPhase(Phase phase) { this->phase = phase; }
	void setTrain() { this->phase = Phase::Train; }
	void setTest() { this->phase = Phase::Test; }

public:
	void step();

};

#endif
