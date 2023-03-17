#include <string>
#include <vector>
#include <utility>
#include <filesystem>

#ifndef WAV_PATH_H
#define WAV_PATH_H

class WavPath {
    std::vector<std::string> wavFolderPaths;
    std::vector<std::filesystem::path> transformToFilesystemPaths(std::vector<std::string> folderPaths);
    bool isWavFile(const std::filesystem::directory_entry& entry);
    std::pair<std::string, std::string> getWavNamePathPair(const std::filesystem::directory_entry& entry);
public:
    WavPath(std::vector<std::string> wavFolderPaths);
    std::vector<std::pair<std::string, std::string>> getWavNamePathPairs();
};

#endif // !WAV_PATH_H
