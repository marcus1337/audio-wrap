
#include "Audio.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <chrono>
#include <thread>

std::vector<std::string> getResourceFolderPaths() {
    std::vector<std::string> paths;
    std::string resourceFolderPath = std::filesystem::current_path().string() + "//res//";
    paths.push_back(resourceFolderPath + "audio//fx//");
    paths.push_back(resourceFolderPath + "audio//music//");
    return paths;
}

int main(int argc, char* argv[]) {

    Audio audio;
    auto soundFolders = getResourceFolderPaths();
    auto fxFolder = soundFolders[0];
    auto musicFolder = soundFolders[1];
    std::string pianoWavPath = musicFolder + "sample.wav";

    audio.unmuteSound();
    audio.loadSounds({ pianoWavPath }, { "piano" });
    audio.playMusic("piano");

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    

    return 0;
}