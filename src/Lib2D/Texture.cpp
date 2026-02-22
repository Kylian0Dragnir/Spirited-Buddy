#include "Texture.h"
#include "SDL_image.h"
#include "AssetManager.h"

Texture::Texture(const std::string& _filePath)
{
	m_texture = nullptr;
	Load(_filePath);
}

Texture::Texture()
{
	m_texture = nullptr;
}

Texture::~Texture()
{
	if (m_filepath == "")
		return;

	if (m_texture)
		AssetManager::Get().UnsetTexture(m_filepath);
}

bool Texture::Load(const std::string& _filePath)
{
	m_filepath = _filePath;

	if (m_texture)
		AssetManager::Get().UnsetTexture(m_filepath);

	TextureData* tdata = AssetManager::Get().LoadTexture(_filePath.c_str());
	m_texture = tdata->texture;

	return m_texture != nullptr;
}

void Texture::SetDataPtr(void* _texture)
{
	m_texture = (SDL_Texture*)_texture;
}