#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Lib2D/Vector2f.h"
#include <string>
#include <unordered_map>
#include <functional>

struct Animation
{
    int frameWidth;
    int frameHeight;

    std::vector<Vector2f> frames; 

    float frameDuration;
    bool loop;

    std::function<void()> onFinish = nullptr;
};

class AnimatorComponent : public Component, public Updatable
{
public:
    void AddAnimation(const std::string& name, const Animation& anim);
    void Play(const std::string& name);
    void Update(float dt) override;
    bool IsFinished() const { return m_finished; }
    bool IsPlaying(const std::string& name);

private:
    std::unordered_map<std::string, Animation> m_animations;
    Animation* m_currentAnimation = nullptr;

    float m_timer = 0.f;
    int m_currentFrame = 0;
    bool m_finished = false;
    bool m_finishEventCalled = false;
};