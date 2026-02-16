#pragma once
#include "Component.h"
#include <string>

class AudioSource : public Component
{
private:
    bool m_loop;
    int m_channel;

public:
    AudioSource();

    void Play(const std::string& _soundId);
    void Stop();
    void SetLoop(bool loop);
};
