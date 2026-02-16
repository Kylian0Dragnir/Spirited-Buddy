#include "Entity.h"

Entity::~Entity()
{
	for (Component* c : m_components)
		delete c;
}

void Entity::Update(float _dt)
{
	auto updatables = GetAllComponents<Updatable>();

	for (Updatable* u : updatables)
	{
		u->Update(_dt);
	}
}

void Entity::Draw(Window* _window)
{
	auto drawables = GetAllComponents<Drawable>();

	for (Drawable* d : drawables)
	{
		d->Draw(_window);
	}
}
