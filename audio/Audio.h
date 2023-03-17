#include <string>
#include <map>
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include "SoloudAudio.h"
#include <random>

#ifndef AUDIO_H
#define AUDIO_H

class Audio {

    SoloudAudio audio;
    std::vector<std::string> unloadedWavFolderPaths;

    std::random_device randDev;
    std::mt19937 randNumGenerator;

public:
    Audio();
    ~Audio();

    void playMusic(std::string musicName);
    void playEffect(std::string effectName);
    void queueMusic(std::string musicName, int maxQueueSize);
    void queueEffect(std::string effectName, int maxQueueSize);

    float getMusicVolume();
    void setMusicVolume(float volumePercentage);
    float getEffectVolume();
    void setEffectVolume(float volumePercentage);
    void muteSound();
    void unmuteSound();
    bool isMuted();

    void loadSounds(std::vector<std::string> wavFolderPaths);

    std::vector<std::string> getSoundNames(std::string nameSubStr);
    std::string getRandomSoundName(std::string nameSubStr);

};

#endif