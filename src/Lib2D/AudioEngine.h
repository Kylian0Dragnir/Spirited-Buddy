#pragma once
#include <string>
#include <map>

struct Mix_Chunk;
struct Mix_Music;

class AudioEngine
{
private:
    std::map<std::string, Mix_Chunk*> m_sounds;
    std::map<std::string, Mix_Music*> m_musics;

    Mix_Music* m_currentMusic;
    std::string m_currentMusicId;

    AudioEngine();

public:
    static AudioEngine& Get();

    bool Init();
    void Shutdown();

    void LoadSound(const std::string& _id, const std::string& _path);
    void LoadMusic(const std::string& _id, const std::string& _path);

    int PlaySound(const std::string& _id, bool _loop);
    void PlayMusic(const std::string& _id, bool _loop);

    void StopMusic();
    void StopAllSounds();
    void StopSound(int _channel);

    void SetMasterVolume(int _volume);
};
