#include "Component.h"

Component::Component()
{
	m_owner = nullptr;
	m_name = nullptr;
	m_enabled = true;
}

Component::Component(Actor* owner, const char* name)
{
	m_owner = owner;
	m_name = name;
	m_enabled = true;
}
