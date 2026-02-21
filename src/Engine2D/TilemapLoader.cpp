#include "TilemapLoader.h"
#include "AScene.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "TilemapRenderer.h"
#include "BoxCollider.h"
#include "TagComponent.h"

#include <tinyxml2.h>
#include <vector>
#include <sstream>

using namespace tinyxml2;

void TilemapLoader::Load(const std::string& path, AScene* scene, const std::string& tilesetPath, Vector2f scale)
{
    XMLDocument doc;
    if (doc.LoadFile(path.c_str()) != XML_SUCCESS)
        return;

    XMLElement* map = doc.FirstChildElement("map");

    int width = map->IntAttribute("width");
    int height = map->IntAttribute("height");
    int tileSize = map->IntAttribute("tilewidth");

    // READ TILE LAYER

    XMLElement* layer = map->FirstChildElement("layer");
    XMLElement* data = layer->FirstChildElement("data");

    std::vector<int> tiles;
    std::stringstream ss(data->GetText());
    std::string value;

    while (std::getline(ss, value, ','))
        tiles.push_back(std::stoi(value));

    // CREATE TILEMAP ENTITY

    Entity* mapEntity = scene->CreateEntity();

    mapEntity->AddComponent<TagComponent>("Tilemap");

    TransformComponent* transform = mapEntity->GetComponent<TransformComponent>();
    transform->SetPos({ 0, 0 });
    transform->SetScale(scale);

    mapEntity->AddComponent<TilemapRenderer>(tiles, width, height, tileSize, tilesetPath);

    // GENERATE SMART COLLIDERS

    for (XMLElement* group = map->FirstChildElement("objectgroup");
        group != nullptr;
        group = group->NextSiblingElement("objectgroup"))
    {
        const char* layerName = group->Attribute("name");

        if (!layerName)
            continue;

        if (std::string(layerName) == "Collisions")
        {
            for (XMLElement* obj = group->FirstChildElement("object");
                obj != nullptr;
                obj = obj->NextSiblingElement("object"))
            {
                float x = obj->FloatAttribute("x") * scale.GetX();
                float y = obj->FloatAttribute("y") * scale.GetY();
                float w = obj->FloatAttribute("width") * scale.GetX();
                float h = obj->FloatAttribute("height") * scale.GetY();

                Entity* collider = scene->CreateEntity();
                auto transform = collider->GetComponent<TransformComponent>();

                transform->SetPos({ x + w * 0.5f, y + h * 0.5f });

                collider->AddComponent<BoxCollider>(w, h, ENV_LAYER, PLAYER_LAYER | SPIRIT_LAYER)->SetVisible(true);
                collider->AddComponent<TagComponent>("Ground");
            }
        }
    }
}
