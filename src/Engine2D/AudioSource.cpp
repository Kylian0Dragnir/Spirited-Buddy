#include "AudioSource.h"
#include "AudioEngine.h"

AudioSource::AudioSource()
{
    m_loop = false;
}

void AudioSource::Play(const std::string& _soundId)
{
    m_soundId = _soundId;
    AudioEngine::Get().PlaySound(_soundId, m_loop);
}

void AudioSource::Stop()
{
    AudioEngine::Get().StopSound(m_soundId);
}

void AudioSource::SetLoop(bool _loop)
{
    m_loop = _loop;
}