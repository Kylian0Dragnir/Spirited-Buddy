#pragma once
#include <map>
#include <string>

struct SDL_Renderer;
class Window;
struct SDL_Texture;

struct TextureData
{
	SDL_Texture* texture;
	int count;
};

class AssetManager
{
public:
	static AssetManager& Get();
	TextureData* LoadTexture(const std::string& _filePath);

	void UnsetTexture(const std::string& _filePath);
	void SetWindow(Window* _window);

private:
	AssetManager();
	Window* m_window;
	std::map<std::string, TextureData*> m_textures;
};

