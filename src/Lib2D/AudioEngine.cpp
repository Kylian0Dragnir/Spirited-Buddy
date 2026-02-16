#include "AudioEngine.h"
#include <iostream>
#include <SDL_mixer.h>

AudioEngine::AudioEngine() 
{
    m_currentMusic = nullptr;
}

AudioEngine& AudioEngine::Get()
{
    static AudioEngine instance;
    return instance;
}

bool AudioEngine::Init()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void AudioEngine::Shutdown()
{
    for (auto& s : m_sounds)
        Mix_FreeChunk(s.second);

    for (auto& m : m_musics)
        Mix_FreeMusic(m.second);

    Mix_CloseAudio();
}

void AudioEngine::LoadSound(const std::string& _id, const std::string& _path)
{
    Mix_Chunk* chunk = Mix_LoadWAV(_path.c_str());
    if (!chunk)
        std::cout << "Failed to load sound: " << _path << std::endl;
    else
        m_sounds[_id] = chunk;
}

void AudioEngine::LoadMusic(const std::string& _id, const std::string& _path)
{
    Mix_Music* music = Mix_LoadMUS(_path.c_str());
    if (!music)
        std::cout << "Failed to load music: " << _path << std::endl;
    else
        m_musics[_id] = music;
}

int AudioEngine::PlaySound(const std::string& _id, bool _loop)
{
    if (!m_sounds.count(_id))
        return -1;

    int loops = _loop ? -1 : 0;
    return Mix_PlayChannel(-1, m_sounds[_id], loops);
}

void AudioEngine::PlayMusic(const std::string& _id, bool _loop)
{
    auto it = m_musics.find(_id);
    if (it == m_musics.end())
    {
        std::cout << "Music not found: " << _id << std::endl;
        return;
    }

    if (m_currentMusicId == _id && Mix_PlayingMusic())
        return;

    m_currentMusic = it->second;
    m_currentMusicId = _id;

    int loops = _loop ? -1 : 0;
    Mix_PlayMusic(m_currentMusic, loops);
}


void AudioEngine::StopMusic()
{
    Mix_HaltMusic();
}

void AudioEngine::StopAllSounds()
{
    Mix_HaltChannel(-1);
}

void AudioEngine::StopSound(int _channel)
{
    Mix_HaltChannel(_channel);
}


void AudioEngine::SetMasterVolume(int _volume)
{
    Mix_Volume(-1, _volume);
    Mix_VolumeMusic(_volume);
}
