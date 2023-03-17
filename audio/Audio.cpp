#include "Audio.h"
#include <iostream>
#include <string>

Audio::Audio() : randNumGenerator(randDev()) {

}

Audio::~Audio() {

}

void Audio::playMusic(std::string musicName) {
    if (isMuted())
        return;
    audio.playMusic(musicName);
}
void Audio::playEffect(std::string effectName) {
    if (isMuted())
        return;
    audio.playEffect(effectName);
}
void Audio::queueMusic(std::string musicName, int maxQueueSize) {
    if (isMuted())
        return;
    audio.queueMusic(musicName, maxQueueSize);
}
void Audio::queueEffect(std::string effectName, int maxQueueSize) {
    if (isMuted())
        return;
    audio.queueEffect(effectName, maxQueueSize);
}
float Audio::getMusicVolume() {
    if (isMuted())
        return 0.0f;
    return audio.getMusicVolume();
}
void Audio::setMusicVolume(float volumePercentage) {
    if (isMuted())
        return;
    audio.setMusicVolume(volumePercentage);
}
float Audio::getEffectVolume() {
    if (isMuted())
        return 0.0f;
    return audio.getEffectVolume();
}
void Audio::setEffectVolume(float volumePercentage) {
    if (isMuted())
        return;
    audio.setEffectVolume(volumePercentage);
}
void Audio::muteSound() {
    if (isMuted())
        return;
    audio.muteSound();
}
void Audio::unmuteSound() {
    if (!audio.isInitialized()) {
        audio.init();
        loadSounds(unloadedWavFolderPaths);
        unloadedWavFolderPaths.clear();
    }
    if (audio.isMuted())
        audio.unmuteSound();
}
bool Audio::isMuted() {
    if (!audio.isInitialized())
        return true;
    return audio.isMuted();
}

void Audio::loadSounds(std::vector<std::string> wavFolderPaths) {
    if (!audio.isInitialized()) {
        unloadedWavFolderPaths = wavFolderPaths;
    }
    else {
        audio.loadSounds(wavFolderPaths);
    }
}

std::vector<std::string> Audio::getSoundNames(std::string nameSubStr) {
    std::vector<std::string> names;
    for (const auto& str : audio.getSoundNames()) {
        if (str.find(nameSubStr) != std::string::npos) {
            names.push_back(str);
        }
    }
    return names;
}

std::string Audio::getRandomSoundName(std::string nameSubStr) {
    auto names = getSoundNames(nameSubStr);
    if (names.empty())
        return "";
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, names.size()-1);
    std::size_t randIndex = distribution(randNumGenerator);
    return names[randIndex];
}


