#pragma once
#include "Scene.h"
#include "NodeMap.h"
#include "PathAgent.h"
class PathAgent;

class SampleScene :
    public Scene
{
public:
    void start() override;
    void update(float deltaTime) override;
    void end() override;
private:
    Pathfinding::NodeMap m_nodeMap;
    PathAgent* m_pathAgent;
};

