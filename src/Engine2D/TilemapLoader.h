#pragma once
#include <string>
#include "Lib2D/Vector2f.h"
#include <functional>
#include "tinyxml2.h"

class AScene;

class TilemapLoader
{
public:

    using ObjectLayerHandler = std::function<void(tinyxml2::XMLElement* object, AScene* scene, Vector2f scale)>;

    void AddObjectLayerHandler(const std::string& layerName, ObjectLayerHandler handler);

    void Load(const std::string& path, AScene* scene, const std::string& tilesetPath, Vector2f scale = { 1.f, 1.f });

private:
    std::unordered_map<std::string, ObjectLayerHandler> m_objectLayerHandlers;
};
