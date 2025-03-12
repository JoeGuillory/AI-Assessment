#include "PathAgent.h"

PathAgent::PathAgent() : Actor::Actor()
{
}

PathAgent::~PathAgent()
{
}

void PathAgent::SetNode(Pathfinding::Node* node)
{
    currentNode = node;
    getTransform()->translate({ node->position.x, node->position.y });
}

void PathAgent::start()
{
    Actor::start();
}

void PathAgent::update(float deltaTime)
{
    Actor::update(deltaTime);

    if (path.empty()) return;

    // find out how far we have to go to the next node
    float dx = currentNode->position.x - getTransform()->getLocalPosition().x;
    float dy = currentNode->position.y - getTransform()->getLocalPosition().y;
    float distanceToNext = sqrtf(dx * dx + dy * dy);

    // normalize the vector to the next node
    if (distanceToNext > 0)
    {
        dx /= distanceToNext;
        dy /= distanceToNext;
    }

    distanceToNext -= speed * deltaTime;
    if (distanceToNext >= 0)
    {
        // we wont get to the target node this frame - so move linearly towards it
        getTransform()->translate(dx * speed * deltaTime, dy * speed * deltaTime);
    }
    else
    {
        currentIndex++;
        if (currentIndex >= path.size())
        {
            // we've reached the end, so stop on the node and clear our path
            getTransform()->setLocalPosition({ currentNode->position.x, currentNode->position.y });
            path.clear();
        }
        else
        {
            // move on to the next node
            Pathfinding::Node* oldNode = currentNode;
            currentNode = path[currentIndex];

            // get the unit vectore from the old node to the new one
            dx = currentNode->position.x - oldNode->position.x;
            dy = currentNode->position.y - oldNode->position.y;
            float mag = sqrtf(dx * dx + dy * dy);
            dx /= mag;
            dy /= mag;

            // move along the path from the previous node to the new current node by the amount by which we overshot
            // (which is -distanceToNext)
            getTransform()->setLocalPosition({ oldNode->position.x - distanceToNext * dx,  oldNode->position.y - distanceToNext * dy });
        }
    }
    
}

void PathAgent::GoToNode(Pathfinding::Node* node)
{
    switch (searchType)
    {
    case 1:
        path = DijkstrasSearch(currentNode, node);
        currentIndex = 0;
        break;
    case 2:
        path = AStar(currentNode, node);
        currentIndex = 0;
        break;
    default:
        path = DijkstrasSearch(currentNode, node);
        currentIndex = 0;
    }
}

void PathAgent::end()
{
    Actor::end();
}

void PathAgent::draw()
{
    Actor::draw();
    DrawCircle(getTransform()->getWorldPosition().x, getTransform()->getWorldPosition().y, 8, { 255,255,0,255 });
}
