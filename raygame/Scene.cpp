#include "Scene.h"
#include "Transform2D.h"

Scene::Scene()
{
    
    m_world = new MathLibrary::Matrix3();
}

MathLibrary::Matrix3* Scene::getWorld()
{
    return m_world;
}

void Scene::addUIElement(Actor* actor)
{
    m_UIElements.addActor(actor);

    //Adds all children of the UI to the scene
    for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
    {
        m_UIElements.addActor(actor->getTransform()->getChildren()[i]->getOwner());
    }
}

bool Scene::removeUIElement(int index)
{
    return m_UIElements.removeActor(index);
}

bool Scene::removeUIElement(Actor* actor)
{
    return m_UIElements.removeActor(actor);
}

void Scene::addActor(Actor* actor)
{
    if(!m_actors.Contains(actor))
        m_actors.Add(actor);
    for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
    {
        m_actors.Add(actor->getTransform()->getChildren()[i]->getOwner());
    }
}

bool Scene::removeActor(int index)
{
    if (m_actors.Contains(m_actors[index]))
    {
        m_actors.Remove(m_actors[index]);
        return true;
    }
    return false;
}

bool Scene::removeActor(Actor* actor)
{
    if (m_actors.Contains(actor))
    {
        m_actors.Remove(actor);
        return true;
    }
    return false;
}

void Scene::start()
{
    m_started = true;
}

void Scene::update(float deltaTime)
{
    //Updates all actors
    for (int i = 0; i < m_actors.Length(); i++)
    {
        if (!m_actors[i]->getStarted())
            m_actors[i]->start();

        m_actors[i]->update(deltaTime);
    }

    //Checks collision for all actors
    for (int i = 0; i < m_actors.Length(); i++)
    {
        for (int j = 0; j < m_actors.Length(); j++)
        {
            if (m_actors[i]->checkForCollision(m_actors[j]) && j != i && m_actors[j]->getStarted())
                m_actors[i]->onCollision(m_actors[j]);
        }
    }
}

void Scene::updateUI(float deltaTime)
{
    //Calls update for all actors in UI array
    for (int i = 0; i < m_UIElements.getLength(); i++)
    {
        if (!m_UIElements.getActor(i)->getStarted())
            m_UIElements.getActor(i)->start();

        m_UIElements.getActor(i)->update(deltaTime);
    }
}

void Scene::draw()
{
    //Calls draw for all actors in the array
    for (int i = 0; i < m_actors.Length(); i++)
    {
        m_actors[i]->draw();
    }
}

void Scene::drawUI()
{
    //Calls draw for all actors in UI array
    for (int i = 0; i < m_UIElements.getLength(); i++)
    {
        m_UIElements.getActor(i)->draw();
    }
}

void Scene::end()
{
    //Calls end for all actors in the array
    for (int i = 0; i < m_actors.Length(); i++)
    {
        if (m_actors[i]->getStarted())
            m_actors[i]->end();
    }

    m_started = false;
}