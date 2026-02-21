#include "SceneManager.h"
#include "AScene.h"
#include "CollisionSystem.h"

SceneManager::SceneManager()
{
	m_changeScene = true;
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager Instance;
	return Instance;
}

SceneManager::~SceneManager()
{
	for (auto& pair : m_scene)
	{
		delete pair.second;
	}
}

AScene* SceneManager::GetCurrentScene()
{
	return m_scene[m_currentScene];
}

void SceneManager::ChangeScene(const std::string& _id)
{
	m_nextScene = _id;
	m_changeScene = true;
}

void SceneManager::Update(float _dt)
{
	if (m_changeScene)
	{
		m_scene[m_currentScene]->Exit();

		CollisionSystem::GetInstance().ClearAll();

		m_currentScene = m_nextScene;

		m_scene[m_currentScene]->Enter();

		m_changeScene = false;
	}
	m_scene[m_currentScene]->Update(_dt);
}

void SceneManager::Draw(Window* _window)
{
	m_scene[m_currentScene]->Draw(_window);
}

void SceneManager::AddScene(const std::string& _id, AScene* _scene)
{
	m_scene[_id] = _scene;
}

AScene* SceneManager::FindSceneById(const std::string& _id)
{
	return m_scene[_id];
}

void SceneManager::SetStartScene(const std::string& _id)
{
	m_currentScene = _id;
	m_nextScene = _id;
}



