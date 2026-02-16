#pragma once
#include "Component.h"
#include "Drawable.h"
#include "Sprite.h"
#include <vector>
#include <string>

class TilemapRenderer : public Component, public Drawable
{
public:
    TilemapRenderer(const std::vector<int>& _tiles, int _width, int _height, int _tileSize, const std::string& _tilesetPath);
    ~TilemapRenderer();

    void Draw(Window* window) override;

private:
    std::vector<int> m_tiles;
    int m_width;
    int m_height;
    int m_tileSize;

    Sprite* m_sprite;
    int m_tilesetColumns;
};
