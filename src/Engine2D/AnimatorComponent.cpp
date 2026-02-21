#include "AnimatorComponent.h"
#include "SpriteRenderer.h"
#include "Entity.h"

void AnimatorComponent::AddAnimation(const std::string& name, const Animation& anim)
{
    m_animations[name] = anim;
}

void AnimatorComponent::Play(const std::string& name)
{
    if (m_animations.contains(name) == false)
        return;

    if (m_currentAnimation == &m_animations[name])
        return;

    m_currentAnimation = &m_animations[name];
    m_currentFrame = 0;
    m_timer = 0.f;
    m_finished = false;
    m_finishEventCalled = false;
}

void AnimatorComponent::Update(float dt)
{
    if (m_currentAnimation == nullptr)
        return;

    m_timer += dt;

    if (m_timer < m_currentAnimation->frameDuration)
        return;

    m_timer = 0.f;
    m_currentFrame++;

    if (m_currentFrame >= m_currentAnimation->frames.size())
    {
        if (m_currentAnimation->loop)
        {
            m_currentFrame = 0;
        }
        else
        {
            m_currentFrame = m_currentAnimation->frames.size() - 1;

            if (m_finishEventCalled == false)
            {
                m_finished = true;
                m_finishEventCalled = true;

                if (m_currentAnimation->onFinish)
                    m_currentAnimation->onFinish();
            }
        }
    }

    SpriteRenderer* sr = m_owner->GetComponent<SpriteRenderer>();

    Vector2f framePos = m_currentAnimation->frames[m_currentFrame];

    sr->SetFrame(
        m_currentAnimation->frameWidth,
        m_currentAnimation->frameHeight,
        framePos.GetX() * m_currentAnimation->frameWidth,
        framePos.GetY() * m_currentAnimation->frameHeight
    );
}

bool AnimatorComponent::IsPlaying(const std::string& name)
{
    if (m_currentAnimation == &m_animations[name])
        return true;

    return false;
}
