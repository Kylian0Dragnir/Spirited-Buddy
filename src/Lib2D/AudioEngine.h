#pragma once
#include <string>
#include <map>
#include <unordered_map>

struct Mix_Chunk;
struct Mix_Music;

class AudioEngine
{
private:
    std::map<std::string, Mix_Chunk*> m_sounds;
    std::map<std::string, Mix_Music*> m_musics;
    std::unordered_map<std::string, std::vector<int>> m_activeChannels;

    Mix_Music* m_currentMusic;
    std::string m_currentMusicId;

    AudioEngine();

public:
    static AudioEngine& Get();

    bool Init();
    void Shutdown();

    void LoadSound(const std::string& _id, const std::string& _path);
    void LoadMusic(const std::string& _id, const std::string& _path);

    int PlaySound(const std::string& _id, bool _loop, int _volume = 128);
    void PlayMusic(const std::string& _id, bool _loop, int _volume = 128);

    bool IsPlaying(const std::string& _id);

    void StopMusic();
    void StopAllSounds();
    void StopSound(const std::string&);

    void SetMasterVolume(int _volume);
    static void ChannelFinishedCallback(int channel);
};
