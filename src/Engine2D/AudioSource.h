#pragma once
#include "Component.h"
#include <string>

class AudioSource : public Component
{
private:
    bool m_loop;
    std::string m_soundId;

public:
    AudioSource();

    void Play(const std::string& _soundId);
    void Stop();
    void SetLoop(bool loop);
};
