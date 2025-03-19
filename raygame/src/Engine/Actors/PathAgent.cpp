#include "PathAgent.h"
#include <chrono>
#include "SpriteComponent.h"
#include "Wander.h"
enum State
{
    PATHEMPTY = 0,
    PATHFULL,
    WANDER
};

PathAgent::PathAgent() : Actor::Actor()
{
    m_state = PATHEMPTY;
}

PathAgent::~PathAgent()
{
}

void PathAgent::SetNode(Pathfinding::Node* node)
{
    currentNode = node;
    getTransform()->translate({ node->position.x, node->position.y });
    getTransform()->scale({ 20,20 });
    setMaxSpeed(150);
    AddComponent<SpriteComponent>(new SpriteComponent(this, "Images/player.png"));
    m_wander = AddComponent<Wander>(new Wander(this, getMaxSpeed(), 0));
    m_wander->setWeight(0);
}

void PathAgent::CheckState(float deltaTime)
{
    switch (m_state)
    {
        case PATHEMPTY :
        {
            if (!path.empty())
                m_state = PATHFULL;
            else
            {
                m_state = WANDER;
                m_wander->setWeight(1);
                m_wander->enable();
            }
            break;
        }
        case PATHFULL :
        {
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

            distanceToNext -= getMaxSpeed() * deltaTime;
            if (distanceToNext >= 0)
            {
                // we wont get to the target node this frame - so move linearly towards it
                getTransform()->translate(dx * getMaxSpeed() * deltaTime, dy * getMaxSpeed() * deltaTime);
            }
            else
            {
                currentIndex++;
                if (currentIndex >= path.size())
                {
                    // we've reached the end, so stop on the node and clear our path
                    getTransform()->setLocalPosition({ currentNode->position.x, currentNode->position.y });
                    path.clear();
                    m_state = PATHEMPTY;
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
                    getTransform()->setRotation(-atan2(dy, dx));
                }
            }
            break;
        }
        case WANDER :
        {
            if (!path.empty())
            {
                m_wander->disable();
                m_state = PATHFULL;
                getTransform()->setRotation(-atan2(currentNode->position.y - getTransform()->getWorldPosition().y, currentNode->position.x - getTransform()->getWorldPosition().x));
            }
            break;
        }
    }


}

void PathAgent::WrapPosition()
{
    float xpos = getTransform()->getWorldPosition().x;
    float ypos = getTransform()->getWorldPosition().y;


    if (xpos < 0)
    {
        getTransform()->setLocalPosition({ (float)GetScreenWidth(),ypos });
    }

    if (xpos > GetScreenWidth())
    {
        getTransform()->setLocalPosition({ 0,ypos });
    }

    if (ypos < 0)
    {
        getTransform()->setLocalPosition({ xpos,(float)GetScreenHeight() });
    }

    if (ypos > GetScreenHeight())
    {
        getTransform()->setLocalPosition({ xpos, 0 });
    }

}

void PathAgent::start()
{
    Actor::start();
}

void PathAgent::update(float deltaTime)
{
    Actor::update(deltaTime);

    CheckState(deltaTime);
    WrapPosition();
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
}
