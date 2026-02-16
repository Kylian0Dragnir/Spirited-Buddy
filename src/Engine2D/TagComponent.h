#pragma once
#include "Component.h"
#include <string>

class TagComponent : public Component
{
    std::string m_tag;

public:
    TagComponent(const std::string& _tag);

    const std::string& GetTag() const { return m_tag; }

    bool Is(const std::string& _tag) const;
};