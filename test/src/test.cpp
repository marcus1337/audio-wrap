
#include "Audio.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

std::vector<std::string> getResourceFolderPaths() {
    std::vector<std::string> paths;
    std::string resourceFolderPath = std::filesystem::current_path().string() + "//res//";
    paths.push_back(resourceFolderPath + "audio//fx//");
    paths.push_back(resourceFolderPath + "audio//music//");
    return paths;
}

int main(int argc, char* argv[]) {

    Audio audio;

    return 0;
}