#pragma once
#include <map>
#include <string>
#include "Lib2D/Drawable.h"
#include "Updatable.h"

class AScene;

class SceneManager : public Drawable, public Updatable
{

private:

	std::map<std::string,AScene*> m_scene;
	std::string m_currentScene;
	std::string m_nextScene;
	bool m_changeScene;
	SceneManager();

public:

	static SceneManager& GetInstance();
	~SceneManager();

	AScene* GetCurrentScene();
	void ChangeScene(const std::string& _id);
	void Update(float _dt) override;
	void Draw(Window* _window) override;
	void AddScene(const std::string& _id, AScene* _scene);
	AScene* FindSceneById(const std::string& _id);
	void SetStartScene(const std::string& _id);
};

