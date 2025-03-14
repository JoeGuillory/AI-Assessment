#include "BehaviourTree.h"

Status BehaviourTree::tick(Agent* agent, float deltaTime)
{
    if (m_eStatus != BH_RUNNING)
    {
        onInitialize();
    }

    m_eStatus = update(agent, deltaTime);

    if (m_eStatus != BH_RUNNING)
    {
        onTerminate(m_eStatus);
    }
    return m_eStatus;
}

void BehaviourTree::reset()
{
    m_eStatus = BH_INVALID;
}

void BehaviourTree::abort()
{
    onTerminate(BH_ABORTED);
    m_eStatus = BH_ABORTED;
}

bool BehaviourTree::isTerminated() const
{
    return m_eStatus == BH_SUCCESS || m_eStatus == BH_FAILURE;
}

bool BehaviourTree::isRunning() const
{
    return m_eStatus == BH_RUNNING;
}

Status BehaviourTree::getStatus() const
{
    return m_eStatus;
}
