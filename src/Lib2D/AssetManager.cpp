#include <SDL_image.h>
#include <iostream>
#include "AssetManager.h"
#include "Window.h"

AssetManager& AssetManager::Get()
{
    static AssetManager Instance;
    return Instance;
}

AssetManager::AssetManager()
{
    m_window = nullptr;
}

TextureData* AssetManager::LoadTexture(const std::string& _filePath)
{
    auto it = m_textures.find(_filePath);
    if (it != m_textures.end())
    {
        it->second->count++;
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(m_window->m_renderer, _filePath.c_str());
    if (!texture)
        return nullptr;

    TextureData* tData = new TextureData();
    tData->texture = texture;
    tData->count = 1;

    m_textures[_filePath] = tData;

    return tData;
}

void AssetManager::UnsetTexture(const std::string& _filePath)
{
    auto it = m_textures.find(_filePath);
    if (it != m_textures.end())
    {
        it->second->count--;
    }

    if (it->second->count <= 0)
    {
        SDL_DestroyTexture(it->second->texture);
        delete it->second;

        m_textures.erase(it);
    }
}

void AssetManager::SetWindow(Window* _window)
{
    m_window = _window;
}