#pragma once

enum Status
{
	BH_INVALID,
	BH_SUCCESS,
	BH_FAILURE,
	BH_RUNNING,
	BH_ABORTED
};


class Agent;

// Base class for actions, conditions and composites
class BehaviourTree
{
public:
	BehaviourTree() : m_eStatus(BH_INVALID) {}
	virtual ~BehaviourTree() {}

public:
	virtual Status update(Agent* agent, float deltaTime) = 0;
	virtual void onInitialize() {}
	virtual void onTerminate(Status status) {}

	Status tick(Agent* agent, float deltaTime);
	void reset();
	void abort();

	bool isTerminated() const;
	bool isRunning() const;

	Status getStatus() const;

private:
	Status m_eStatus;
};
