#include "TagComponent.h"

TagComponent::TagComponent(const std::string& _tag)
{
	m_tags.push_back(_tag);
}

void TagComponent::AddTag(const std::string& _tag)
{
	for (std::string tag : m_tags)
	{
		if (tag == _tag)
			return;
	}
	m_tags.push_back(_tag);
}

bool TagComponent::Is(const std::string& _tag) const
{
	for (std::string tag : m_tags)
	{
		if (tag == _tag)
			return true;
	}
	return false;
}
