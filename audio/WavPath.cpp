#include "WavPath.h"

WavPath::WavPath(std::vector<std::string> wavFolderPaths) : wavFolderPaths(wavFolderPaths) {

}

std::vector<std::filesystem::path> WavPath::transformToFilesystemPaths(std::vector<std::string> strFolderPaths) {
    std::vector<std::filesystem::path> folderPaths;
    folderPaths.reserve(strFolderPaths.size());
    std::transform(strFolderPaths.begin(), strFolderPaths.end(), std::back_inserter(folderPaths),
        [](const std::string& path) {
            return std::filesystem::path(path);
        });
    return folderPaths;
}

std::vector<std::pair<std::string, std::string>> WavPath::getWavNamePathPairs() {
    std::vector<std::pair<std::string, std::string>> namePathPairs;
    for (const auto& folder : transformToFilesystemPaths(wavFolderPaths)) {
        if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
            for (const auto& entry : std::filesystem::directory_iterator(folder)) {
                if (isWavFile(entry)) {
                    namePathPairs.push_back(getWavNamePathPair(entry));
                }
            }
        }
    }
    return namePathPairs;
}

bool WavPath::isWavFile(const std::filesystem::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension() == ".wav";
}

std::pair<std::string, std::string> WavPath::getWavNamePathPair(const std::filesystem::directory_entry& entry) {
    std::string soundName = entry.path().stem().string();
    std::string soundFilePath = entry.path().string();
    auto namePathPair = std::make_pair(soundName, soundFilePath);
    return namePathPair;
}

