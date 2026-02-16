#pragma once
#include <vector>
#include "Updatable.h"
#include "Lib2D/Drawable.h"
#include "Component.h"

class Entity : public Updatable, public Drawable
{
	std::vector<Component*> m_components;


public:
	Entity() = default;
	~Entity();
	friend class AScene;

	template<typename T, typename... Args>
	T* AddComponent(Args&& ...args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

		T* component = new T(std::forward<Args>(args)...);
		m_components.push_back(component);
		component->SetOwner(this);
		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		for (Component* c : m_components)
		{
			if (auto cast = dynamic_cast<T*>(c))
				return cast;
		}

		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetAllComponents()
	{
		std::vector<T*> result;

		for (Component* c : m_components)
		{
			if (auto cast = dynamic_cast<T*>(c))
				result.push_back(cast);
		}

		return result;
	}

	void Update(float _dt) override;
	void Draw(Window* _window) override;
};

