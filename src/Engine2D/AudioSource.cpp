#include "AudioSource.h"
#include "AudioEngine.h"

AudioSource::AudioSource()
{
    m_channel = -1;
    m_loop = false;
}

void AudioSource::Play(const std::string& _soundId)
{
    m_channel = AudioEngine::Get().PlaySound(_soundId, m_loop);
}

void AudioSource::Stop()
{
    if (m_channel != -1)
        AudioEngine::Get().StopSound(m_channel);
}

void AudioSource::SetLoop(bool _loop)
{
    m_loop = _loop;
}