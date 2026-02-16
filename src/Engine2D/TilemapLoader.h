#pragma once
#include <string>

class AScene;

class TilemapLoader
{
public:
    static void Load(const std::string& path, AScene* scene, const std::string& tilesetPath);
};
