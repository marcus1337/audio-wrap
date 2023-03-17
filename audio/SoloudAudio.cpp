#include "SoloudAudio.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <filesystem>
#include "WavPath.h"

SoloudAudio::SoloudAudio() {
}

SoLoud::Wav* SoloudAudio::getWavPointer(std::string soundName) {
    if (!soundMap.contains(soundName))
    {
        std::cerr << "Sound error: " << soundName << " not loaded.\n";
        return nullptr;
    }
    return soundMap[soundName];
}

void SoloudAudio::init() {
    std::cout << "initializing audio...\n";
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "Failed to load SDL_INIT\n";
        return;
    }
    soloud.init();
    musicBusHandle = soloud.play(musicBus);
    effectBusHandle = soloud.play(effectBus);
    initialized = true;
}

SoloudAudio::~SoloudAudio() {
    for (const auto& [key, value] : soundMap) {
        delete value;
    }
    soloud.deinit();
    SDL_CloseAudio();
    SDL_Quit();
}

void SoloudAudio::queueMusic(std::string musicName, int maxQueueSize) {
    if (musicQueue.getQueueCount() < maxQueueSize) {
        musicBus.play(musicQueue);
        auto wavPtr = getWavPointer(musicName);
        if (wavPtr != nullptr)
            musicQueue.play(*wavPtr);
    }
}
void SoloudAudio::queueEffect(std::string effectName, int maxQueueSize) {
    if (effectQueue.getQueueCount() < maxQueueSize) {
        effectBus.play(effectQueue);
        auto wavPtr = getWavPointer(effectName);
        if (wavPtr != nullptr)
            effectQueue.play(*wavPtr);
    }
}

void SoloudAudio::loadSounds(std::vector<std::string> wavFolderPaths) {
    for (const auto& namePathPair : WavPath(wavFolderPaths).getWavNamePathPairs()) {
        std::string soundName = namePathPair.first;
        std::string soundFilePath = namePathPair.second;
        loadSound(soundFilePath, soundName);
    }
}

void SoloudAudio::loadSound(std::string path, std::string name) {
    if (!soundMap.contains(name)) {
        SoLoud::Wav* wav = new SoLoud::Wav();
        wav->load(path.c_str());
        soundMap[name] = wav;
    }
}

void SoloudAudio::playMusic(std::string musicName) {
    auto wavPtr = getWavPointer(musicName);
    if (wavPtr != nullptr)
        musicBus.play(*wavPtr);
}

void SoloudAudio::playEffect(std::string effectName) {
    auto wavPtr = getWavPointer(effectName);
    if (wavPtr != nullptr)
        effectBus.play(*wavPtr);
}

float SoloudAudio::getMusicVolume() {
    return soloud.getVolume(musicBusHandle);
}

void SoloudAudio::setMusicVolume(float volumePercentage) {
    soloud.setVolume(musicBusHandle, volumePercentage);
    prevMusicVolume = volumePercentage;
}

float SoloudAudio::getEffectVolume() {
    return soloud.getVolume(effectBusHandle);
}

void SoloudAudio::setEffectVolume(float volumePercentage) {
    soloud.setVolume(effectBusHandle, volumePercentage);
    prevEffectVolume = volumePercentage;
}

void SoloudAudio::muteSound() {
    soloud.stopAll();
    muted = true;
}

void SoloudAudio::unmuteSound() {
    musicBusHandle = soloud.play(musicBus);
    effectBusHandle = soloud.play(effectBus);
    effectBus.play(effectQueue);
    musicBus.play(musicQueue);
    setMusicVolume(prevMusicVolume);
    setEffectVolume(prevEffectVolume);
    muted = false;
}

bool SoloudAudio::isMuted() {
    return muted;
}

bool SoloudAudio::isInitialized() {
    return initialized;
}

std::vector<std::string> SoloudAudio::getSoundNames() {
    std::vector<std::string> names;
    for (const auto& [key, value] : soundMap) {
        names.push_back(key);
    }
    return names;
}

