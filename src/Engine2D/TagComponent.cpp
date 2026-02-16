#include "TagComponent.h"

TagComponent::TagComponent(const std::string& _tag)
{
	m_tag = _tag;
}

bool TagComponent::Is(const std::string& _tag) const
{
	return m_tag == _tag;
}
