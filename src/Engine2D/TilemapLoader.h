#pragma once
#include <string>
#include "Lib2D/Vector2f.h"

class AScene;

class TilemapLoader
{
public:
    static void Load(const std::string& path, AScene* scene, const std::string& tilesetPath, Vector2f scale = { 1.f, 1.f });
};
