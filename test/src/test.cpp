
#include "Audio.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <chrono>
#include <thread>
#include "AudioSingleton.h"

std::vector<std::string> getResourceFolderPaths() {
    std::vector<std::string> paths;
    std::string resourceFolderPath = std::filesystem::current_path().string() + "//res//";
    paths.push_back(resourceFolderPath + "audio//fx//");
    paths.push_back(resourceFolderPath + "audio//music//");
    return paths;
}

void pause() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void testAudio(Audio& audio) {
    audio.loadSounds(getResourceFolderPaths());
    audio.unmuteSound();
    audio.playMusic("sample");
    pause();
}

void test1() {
    Audio audio;
    testAudio(audio);
}

void test2() {
    auto audio = AudioSingleton::getInstance();
    testAudio(audio);
}

int main(int argc, char* argv[]) {

    test2();    

    return 0;
}

