#pragma once
#include "BehaviourTree.h"
#include <vector>

class Composite : public BehaviourTree
{
public:
	Composite* add(BehaviourTree* child);
	void remove(BehaviourTree* child);
	void clear();

protected:
	typedef std::vector<BehaviourTree*> Behaviours;
	Behaviours m_children;
};
