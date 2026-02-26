#pragma once
#include <tinyxml2.h>
#include <string>

class TiledUtils
{
    TiledUtils() = default;
public:
    template<typename T>
    static T GetProperty(tinyxml2::XMLElement* obj, const std::string& name, const T& defaultValue) = delete;
};

template<>
inline std::string TiledUtils::GetProperty<std::string>(tinyxml2::XMLElement* obj, const std::string& name, const std::string& defaultValue)
{
    if (obj == nullptr) return defaultValue;

    tinyxml2::XMLElement* props = obj->FirstChildElement("properties");
    if (!props) return defaultValue;

    for (tinyxml2::XMLElement* prop = props->FirstChildElement("property");
        prop != nullptr;
        prop = prop->NextSiblingElement("property"))
    {
        const char* propName = prop->Attribute("name");

        if (propName && name == propName)
        {
            const char* value = prop->Attribute("value");
            if (value)
                return value;
        }
    }

    return defaultValue;
}

template<>
inline int TiledUtils::GetProperty<int>(tinyxml2::XMLElement* obj, const std::string& name, const int& defaultValue)
{
    std::string val = TiledUtils::GetProperty<std::string>(obj, name, "");
    if (val.empty()) return defaultValue;

    return std::stoi(val);
}

template<>
inline float TiledUtils::GetProperty<float>(tinyxml2::XMLElement* obj, const std::string& name, const float& defaultValue)
{
    std::string val = TiledUtils::GetProperty<std::string>(obj, name, "");
    if (val.empty()) return defaultValue;

    return std::stof(val);
}

template<>
inline bool TiledUtils::GetProperty<bool>(tinyxml2::XMLElement* obj, const std::string& name, const bool& defaultValue)
{
    std::string val = TiledUtils::GetProperty<std::string>(obj, name, "");
    if (val.empty()) return defaultValue;

    return val == "true" || val == "1";
}
