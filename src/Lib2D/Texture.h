#pragma once
#include <string>

struct SDL_Texture;

class Texture
{
	SDL_Texture* m_texture;
	std::string m_filepath;

public:

	Texture(const std::string& _filePath);
	Texture();

	~Texture();

	bool Load(const std::string& _filePath);

	void* GetDataPtr() { return m_texture; }
	void SetDataPtr(void* _texture);
};

