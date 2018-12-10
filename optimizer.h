#ifndef DARKVORTEX_OPTIMIZER_H
#define DARKVORTEX_OPTIMIZER_H



enum class Phase
{
	Train,
	Test,
};

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
